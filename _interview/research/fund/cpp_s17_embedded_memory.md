# 17. Embedded Memory, Startup & the Build

## The Bare-Metal Memory Map

A microcontroller integrates computing power and memory directly onto a single piece of silicon. This memory is physically divided into distinct regions.

* **Flash/ROM:** Non-volatile memory. It retains data when power is lost. It houses your compiled code, read-only constants (`.rodata`), and the initial templates for initialized variables.
* **RAM:** Volatile memory. It loses its contents on power loss. It serves as the live workspace, holding initialized globals (`.data`), zeroed globals (`.bss`), the call stack, and the heap.
* **Peripherals:** Hardware features (like timers or serial ports) are mapped into memory addresses. Writing to these addresses configures the hardware (see §6, §15).

![Memory Map](assets/s17_flash_ram.png)

## The Startup Sequence

```{=typst}
#heavy[
```

Dense — slow down: A C program does not magically start executing at `main`. The hardware requires setup, and the C language specification expects your global variables to be fully ready before your first line of code runs.

```{=typst}
]
```

**Analogy:** Think of opening a restaurant for the day. You don't immediately let customers in (running `main`). First, you unlock the door (hardware reset), turn on the lights and arrange the tables according to your blueprint (copying initial values), and wipe down the empty counters (zeroing memory).

![The Startup Sequence](assets/s17_startup.png)

**Example First:**
Consider a program with these globals:
```c
int active_users = 5;
int buffer[100];

int main(void) {
    return active_users;
}
```
When power is first applied, the RAM chip is filled with random electrical garbage. If the CPU immediately jumped into `main`, `active_users` would not equal 5, and `buffer` would contain random noise.

**Plain English:**
When a microcontroller resets, the processor looks at a hardcoded address to find its initial stack pointer and the address of a function called the Reset Handler. This handler is a small routine, usually called the C runtime (`crt0`), which prepares the environment. 

It performs two critical memory operations:
1. It copies the initial values of variables (like `active_users`) from the permanent Flash storage into live RAM.
2. It zeroes out the block of RAM reserved for uninitialized global variables (like `buffer`).

Only after doing this does it finally call `main()`.

**Technical Statement:**
The startup sequence implements the C standard's requirement that all variables with static storage duration are initialized before program startup [1]. Variables explicitly initialized to non-zero values are placed in the `.data` section. Variables implicitly or explicitly zero-initialized go to the `.bss` section. Because RAM is volatile, the `.data` section has a Load Memory Address (LMA) in Flash and a Virtual Memory Address (VMA) in RAM. The `crt0` code executes a physical memory copy from the LMA to the VMA.

```{=typst}
#trap[
```

A common trap is assuming that triggering a "soft reset" from software automatically resets your global variables. If your soft reset jumps directly to `main` without re-running the `crt0` startup code, your `.data` and `.bss` variables will retain their stale values from before the reset, causing bizarre bugs.

```{=typst}
]
```

This breaks when you use a custom bootloader that fails to properly hand off execution, or if the microcontroller enters a deep sleep that powers down RAM and you fail to re-execute the initialization loop upon waking.

## The Linker Script

```{=typst}
#heavy[
```

Dense — slow down: The compiler translates source files into isolated puzzle pieces (object files). It is the linker script that acts as the master blueprint, assigning those pieces to exact physical memory addresses on the chip.

```{=typst}
]
```

**Analogy:** Moving into a new house. The compiler packs your belongings into boxes (sections) labeled "Books" or "Clothes". The linker script is the floor plan given to the movers, instructing them: "Put all Books in the Living Room (Flash), and all Clothes in the Bedroom (RAM)."

![Linker Sections](assets/s17_linker_sections.png)

**Example First:**
```ld
MEMORY {
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}
```
During compilation, a variable's address is unknown. After the linker runs using this script, `main` might be placed exactly at `0x08000104`.

**Plain English:**
The linker takes input sections (like `.text` for code) from multiple object files and merges them into cohesive output sections. It then maps these output sections into the physical memory regions defined by the chip manufacturer. 

Crucially, the linker script defines symbols (like `_sdata` for "start of data") that act as bookmarks. The startup code we discussed earlier uses these bookmarks to know exactly where to copy bytes.

**Technical Statement:**
A GNU linker script relies on the `SECTIONS` command to map input sections to output sections, and the `MEMORY` command to define the physical layout [2]. It assigns both the VMA (execution address) and LMA (storage address). It exports boundary symbols to the global symbol table, allowing C or assembly code to reference linker-calculated addresses as standard pointers.

```{=typst}
#interview[
```

**Q: What is the difference between VMA and LMA?**
VMA (Virtual Memory Address) is the address where data or code is expected to be when the program executes. LMA (Load Memory Address) is where it is permanently stored. For the `.data` section, the LMA is in Flash, but its VMA is in RAM.

```{=typst}
]
```

This breaks if your code or data grows larger than the `LENGTH` defined in the `MEMORY` block, resulting in a linker error warning that a region has "overflowed."

## Hardware Exceptions and the Vector Table

The vector table (recap §16) is an array of function pointers placed at a fixed memory address expected by the CPU core. The earliest entries dictate how the CPU begins execution: the initial value for the stack pointer, followed by the Reset Handler. The linker script forces this table into the very beginning of the FLASH region using a targeted input section, commonly named `.isr_vector`.

## Data Placement: Const, Stack, and Heap

Where you declare a variable determines where the linker places it, which directly impacts memory consumption.

* **`const` variables:** Stored entirely in Flash (`.rodata`).
* **Initialized globals:** Stored permanently in Flash, and copied to RAM at startup (`.data`). They consume *both* Flash and RAM.
* **Zero-initialized globals:** Stored only in RAM (`.bss`).
* **Local variables:** Allocated dynamically on the stack, which typically grows downwards from the highest available RAM address.
* **Heap allocations (`malloc`):** The heap, if enabled, grows upwards from the end of the `.bss` section.

```{=typst}
#keypoint[
```

On bare metal, marking a lookup table or string literal as `const` isn't just about type safety—it physically saves precious RAM by forcing the linker to keep the data exclusively in Flash.

```{=typst}
]
```

## Cross-Compilation and the Toolchain

Developing for embedded systems means writing code on a host machine (like an x86 PC) to run on a completely different target architecture (like ARM). This is known as cross-compilation.

You use a toolchain prefixed with the target, such as `arm-none-eabi-gcc`. The `-mcpu` flag tells the compiler the exact instruction set to emit. You pass the linker script using `-T script.ld`. Because a bare-metal microcontroller cannot run standard operating system executables (like ELF files), a utility called `objcopy` strips away debugging metadata to extract a raw binary (`.bin`) or hex (`.hex`) file. This raw file is what gets flashed onto the chip.

## Retargeting the C Library

Standard C libraries expect an operating system to handle I/O. Calling `printf` normally invokes an OS system call to write to a terminal. On bare metal, there is no OS. 

Embedded toolchains bundle lightweight C libraries like `newlib` or `newlib-nano`. To make `printf` actually output characters, you must "retarget" the library by implementing a low-level function (often named `_write`) that routes characters to a hardware UART peripheral [3]. 

Without this, linking `printf` pulls in massive, generic I/O handlers that can instantly exhaust a microcontroller's memory budget. Developers often generate a `.map` file during the build to audit exactly how much Flash and RAM every function consumes.

## Stack Collision and System Budgeting

Because the stack grows downward from the top of RAM, while `.data` and `.bss` sit at the bottom, there is a risk of collision. If you declare massive local arrays or recurse too deeply, the stack pointer will move down into your global variables, silently overwriting them. 

This is a stack overflow. To prevent this, embedded systems heavily prefer static allocation (recap §7). By avoiding the heap and deeply nested stacks, memory requirements can be proven at compile time, eliminating runtime out-of-memory errors.

## Worked Examples

### Tracing Initialized Data

Let's track a variable `int counter = 42;` from compile-time to execution. 

First, the **Linker Script** defines the physical memory and places the `.data` section. It sets the VMA to RAM, the LMA to FLASH, and exports symbols marking the boundaries.

```ld
MEMORY {
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS {
    .text : { *(.text) } > FLASH
    .data : {
        . = ALIGN(4);
        _sdata = .;      /* VMA Start (RAM) */
        *(.data)
        . = ALIGN(4);
        _edata = .;      /* VMA End (RAM) */
    } > RAM AT > FLASH
    
    _sidata = LOADADDR(.data); /* LMA Start (FLASH) */
}
```

Next, the **Startup Sequence** (the Reset Handler) uses those linker symbols to perform the physical memory copy before calling `main()`.

```c
#include <stdint.h>

/* Import the linker script symbols */
extern uint32_t _sdata, _edata, _sidata;
extern int main(void);

void Reset_Handler(void) {
    /* Pointers to Flash (source) and RAM (destination) */
    uint32_t *src = &_sidata;
    uint32_t *dest = &_sdata;
    
    /* Copy data words from Flash to RAM */
    while (dest < &_edata) {
        *dest++ = *src++;
    }
    
    main();
}
```

### Faded Example: Zeroing .bss

After copying `.data`, the startup code must zero out the `.bss` section. Complete the loop condition using the linker symbols `_sbss` (start of bss) and `_ebss` (end of bss).

```c
extern uint32_t _sbss, _ebss;

void zero_bss(void) {
    uint32_t *dest = &_sbss;
    
    /* Fill in the missing boundary condition */
    while (dest < /* ??? */) {
        *dest++ = 0;
    }
}
```

### References
[1] ISO/IEC 9899:2011 (C11 Standard Draft N1570) — Open-Std — https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf
[2] Linker Scripts — GNU Binutils Documentation — https://sourceware.org/binutils/docs/ld/Scripts.html
[3] Newlib OS Interface — Sourceware — https://sourceware.org/newlib/libc.html#Syscalls
