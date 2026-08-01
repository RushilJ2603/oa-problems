# 15. C for Hardware: Memory-Mapped I/O & Registers

When writing software for a typical desktop computer, you interact with the outside world through an operating system (OS). If you want to turn on a webcam or send a network packet, you call an OS function. 

In *bare-metal* embedded programming (writing code for a microcontroller with no OS), that safety net is gone. Your C code runs directly on the CPU, and it must control the hardware peripherals—the GPIO pins, the UART serial ports, the timers—by itself. 

To bridge the gap between software and hardware, microcontrollers use a brilliantly simple architectural trick: they pretend the hardware is just memory.

## Memory-Mapped I/O (MMIO)

```{=typst}
#heavy[
```

Dense — slow down: A memory address in an embedded system does not always point to data storage. It might point to a physical wire.

```{=typst}
]
```

**Analogy:** Imagine a wall of post office boxes. Most boxes are normal (RAM): you put a letter in, and later you can take that exact letter out. But some boxes are magical: putting a letter in box #400 sends a fax to London. Looking inside box #401 tells you the current temperature outside. 

![Peripheral address map: CPU to bus to peripherals](assets/s15_mmio_map.png)

**Example:** On an STM32 Cortex-M microcontroller, the address `0x40020014` does not point to RAM. It is the address of the "Output Data Register" for a bank of physical pins (Port A). 

**Plain English:** The CPU communicates with the rest of the chip over a data bus. The bus routes read and write requests based on the address. The chip designer wires specific address ranges to RAM, other ranges to Flash memory (where your code lives), and specific, fixed addresses to the control circuits of the hardware peripherals.

**Technical:** *Memory-Mapped I/O (MMIO)* [1] is a design where peripheral control and data registers are mapped into the same address space as program memory and RAM. Reading or writing to these specific addresses triggers hardware actions.

```{=typst}
#trap[
```

**The Storage Trap:** Beginners assume that if they write a value to a memory address, they can read that same value back. With MMIO registers, a write might trigger an action, and a read might return the status of a sensor. They are not guaranteed to be symmetrical.

```{=typst}
]
```

*Question to sit with:* If an address points to a hardware timer that is constantly ticking upward, what happens if you read the exact same address twice in a row? This breaks when you assume memory is static state.

## Accessing a Register from C

To control hardware, we need C code that reads and writes to these specific, hardcoded MMIO addresses.

```{=typst}
#heavy[
```

Dense — slow down: We must violently override the compiler's optimizations to ensure it actually performs the memory operations we write.

```{=typst}
]
```

**Analogy:** If you ask an assistant to check the thermostat in the hallway ten times in one minute, a smart assistant might check it once, realize the temperature hasn't changed, and just give you the first answer nine more times to save effort. But if the thermostat is a rapidly changing hardware sensor, the assistant *must* physically walk to the hallway every single time.

![Compiler optimization vs volatile read](assets/s15_volatile.png)

**Example:** Turning on a GPIO pin by writing a `1` to bit 5 at address `0x40020014`.

```c
// The raw idiom
*(volatile uint32_t *)0x40020014 = (1u << 5);

// The cleaner macro idiom
#define GPIOA_ODR (*(volatile uint32_t *)0x40020014)

int main(void) {
    GPIOA_ODR = (1u << 5); // Writes to the hardware
    return 0;
}
```

**Plain English:** We take the raw integer address (`0x40020014`), cast it into a pointer to an unsigned 32-bit integer, and then dereference that pointer (`*`) to write a value. Crucially, we tag the pointer as `volatile`.

**Technical:** 
1. `uint32_t`: Width matters immensely in hardware. If the silicon expects a 32-bit write on the bus, writing an 8-bit `char` might be ignored or cause a bus fault. We use exact-width `<stdint.h>` types.
2. `volatile`: This keyword tells the C compiler that the value at this address may change outside the program's control, or that writing to it has observable side effects [2]. It strictly forbids the compiler from caching the value in a CPU register or optimizing away "redundant" reads and writes.

```{=typst}
#trap[
```

**The Infinite Loop Trap:** If you write `while (*ptr == 0);` to wait for a hardware flag to change, and `ptr` is not `volatile`, the compiler will optimize it into `if (*ptr == 0) while (1);`. Your program will hang forever because it never re-reads the hardware.

```{=typst}
]
```

*Question to sit with:* What happens if you define a peripheral pointer globally, but forget the `volatile` keyword? This breaks when you enable compiler optimizations like `-O2`.

## Register Read-Modify-Write (RMW)

When you write to a register, you usually only want to change a few specific bits without disturbing the rest of the peripheral's configuration.

![Read-modify-write of one bit](assets/s15_rmw.png)

Using the bitwise operators from §11:
- **Set a bit:** `REG |= (1u << n);` (Read, OR in the bit, Write back)
- **Clear a bit:** `REG &= ~(1u << n);` (Read, AND with the inverted bit, Write back)
- **Toggle a bit:** `REG ^= (1u << n);` 

```{=typst}
#trap[
```

**The RMW Interrupt Hazard:** `REG |= (1u << 5);` looks like a single atomic action in C, but it compiles to three assembly instructions: load the register, modify the value in the CPU, and store it back. If a hardware interrupt (§16) pauses your code right after the "load" step, modifies the same register, and then returns to your code, your delayed "store" step will accidentally overwrite the interrupt's changes!

```{=typst}
]
```

## Modeling Peripherals: The CMSIS Pattern

Defining hundreds of individual macros like `#define GPIOA_ODR...` is tedious and error-prone. Modern embedded C, popularized by ARM's CMSIS (Cortex Microcontroller Software Interface Standard) [3], uses a structural approach.

A peripheral is just a block of registers sitting at sequential memory offsets. We can model this perfectly with a `struct` (recap §8).

```c
// 1. Define the layout of the peripheral
typedef struct {
    volatile uint32_t MODER;   // Offset 0x00: Mode register
    volatile uint32_t OTYPER;  // Offset 0x04: Output type register
    volatile uint32_t OSPEEDR; // Offset 0x08: Output speed register
    volatile uint32_t PUPDR;   // Offset 0x0C: Pull-up/pull-down register
    volatile uint32_t IDR;     // Offset 0x10: Input data register
    volatile uint32_t ODR;     // Offset 0x14: Output data register
} GPIO_TypeDef;

// 2. Map the struct to the base hardware address
#define GPIOA ((GPIO_TypeDef *) 0x40020000)

// 3. Access members cleanly
int main(void) {
    GPIOA->ODR |= (1u << 5); // Accesses 0x40020014 automatically!
}
```

This ensures that the compiler calculates the exact memory offsets for you. If the hardware has a gap (a missing register), you must insert reserved padding fields (e.g., `uint32_t _reserved[2];`) to keep the structural offsets perfectly aligned with the silicon.

### Bit-fields vs. Explicit Masks

![A 32-bit register carved into named bit-fields](assets/s15_register_bits.png)

You might be tempted to use C bit-fields to model the individual bits inside a register:
```c
struct StatusReg {
    volatile uint32_t error_flag : 1;
    volatile uint32_t ready_flag : 1;
    // ...
};
```

```{=typst}
#trap[
```

**The Bit-field Layout Trap:** The C standard explicitly states that the layout of bit-fields within an integer is *implementation-defined* (whether they pack left-to-right or right-to-left) [4]. A compiler update or a switch from GCC to Clang could quietly flip all your hardware configurations.

```{=typst}
]
```

For hardware registers, **always use explicit bitwise masks and shifts**, never C bit-fields.

## Special Register Kinds

Hardware designers use registers creatively. Be aware of these common variations:
- **Read-Only Status:** Modelled as `const volatile uint32_t`. The hardware changes it, but your C code is forbidden from writing to it.
- **Write-Only:** Reading it returns garbage or triggers a bus fault.
- **Write-1-to-Clear (W1C):** To clear a hardware error flag, you don't write `0`. Instead, you write a `1` directly to that specific bit. Writing `0` has no effect. This allows you to clear one flag without risking an RMW interrupt hazard on neighboring flags.
- **Side-Effects on Read:** Simply reading a register might clear a hardware buffer (e.g., reading a UART data register removes the byte from the incoming queue).

```{=typst}
#interview[
```

**Interview Question:** "Why is `volatile` used in embedded C?"
**Answer:** "It prevents the compiler from optimizing away reads and writes to a memory address. This is mandatory for memory-mapped I/O registers where the hardware changes the value independently of the software, or where writing to the address triggers hardware side-effects. Without it, polling loops would be optimized into infinite hangs."

```{=typst}
]
```

## Worked Examples

### Worked: Blink an LED (GPIO Toggle)

This snippet demonstrates configuring a peripheral clock, setting a pin mode, and toggling it.

```c
#include <stdint.h>

// Simplified MCU definitions
#define RCC_BASE      0x40023800
#define GPIOA_BASE    0x40020000

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t _reserved[11];
    volatile uint32_t AHB1ENR; // Clock enable register
} RCC_TypeDef;

typedef struct {
    volatile uint32_t MODER;   
    volatile uint32_t _reserved[4]; // Padding to align ODR
    volatile uint32_t ODR;     // Output data
} GPIO_TypeDef;

#define RCC   ((RCC_TypeDef *) RCC_BASE)
#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)

int main(void) {
    // 1. Enable power/clock to GPIO Port A (Bit 0)
    RCC->AHB1ENR |= (1u << 0);
    
    // 2. Set Port A, Pin 5 to Output Mode (Bits 11:10 = 01)
    // First clear the bits, then set the mode
    GPIOA->MODER &= ~(3u << 10);
    GPIOA->MODER |=  (1u << 10);
    
    // 3. Toggle the LED endlessly
    while (1) {
        GPIOA->ODR ^= (1u << 5); // Toggle pin 5
        
        // Naive software delay (for demonstration only)
        for (volatile uint32_t i = 0; i < 500000; i++); 
    }
}
```

### Worked: Polling a Status Flag

Waiting for a serial transmission to complete.

```c
#define UART_TX_EMPTY_FLAG (1u << 7)

typedef struct {
    volatile uint32_t STATUS;
} UART_TypeDef;

void uart_wait_for_tx(UART_TypeDef *uart) {
    // Hang here AS LONG AS the empty flag is 0.
    // 'volatile' on the struct member guarantees a fresh memory read every loop.
    while ((uart->STATUS & UART_TX_EMPTY_FLAG) == 0) {
        // Wait
    }
}
```

### Faded Example: Struct Padding

Design a CMSIS-style struct for a timer peripheral. The reference manual dictates:
- `CTRL` register at offset `0x00`
- `RELOAD` register at offset `0x04`
- Gap at offset `0x08` (silicon reserved)
- `COUNT` register at offset `0x0C`

```c
typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t RELOAD;
    
    // FILL IN THE BLANK: Handle the 4-byte gap at 0x08
    _________________________________;
    
    volatile uint32_t COUNT;
} Timer_TypeDef;
```

### References

[1] Memory-mapped I/O (MMIO) — Arm Developer Documentation — https://developer.arm.com/documentation/102618/0100
[2] ISO/IEC 9899:2011 (C11 Standard) — ISO — https://www.iso.org/standard/57853.html
[3] CMSIS-Core (Cortex-M) Peripheral Access Layer — Arm Software — https://arm-software.github.io/CMSIS_6/latest/Core/index.html
[4] Bit-field Implementation Constraints — GCC Manual — https://gcc.gnu.org/onlinedocs/gcc/Structures-unions-enumerations-and-bit-fields-implementation.html
