# Type Casting: the four cast operators

The traditional **C-style cast** `(int*)ptr` will convert almost any type to any other type with a single terse syntax. It is dangerous precisely because it is so permissive: it does not state the programmer's intent, silently picks whichever conversion happens to compile, and is nearly impossible to search for (grep) in a large codebase.

Modern C++ therefore provides **four named cast operators**. Each expresses a single, specific intent, is easily searchable, and lets the compiler enforce strict rules about which conversions are permitted.

## static_cast

The **`static_cast`** operator performs compile-time checked conversions between related types. It is the workhorse of C++ casting.

**Syntax:** `static_cast<TargetType>(expression)`

You should use `static_cast` for well-defined, safe conversions, or to explicitly reverse an implicit conversion. 

### Common uses for static_cast

1. **Numeric conversions**: Converting between basic numeric types (e.g., `float` to `int`).
2. **Upcasting**: Converting a derived class pointer/reference to a base class pointer/reference. (This happens implicitly anyway, but can be made explicit).
3. **Explicit downcasting**: Converting a base class pointer/reference to a derived class pointer/reference *without* a run-time check. It assumes you are absolutely certain of the object's actual type.
4. **`void*` conversion**: Casting a `void*` back to a typed pointer.
5. **Explicit constructors**: Forcing a conversion that calls an explicit constructor or conversion operator.

```cpp
#include <iostream>

class Base {};
class Derived : public Base {};

class ExplicitInt {
public:
    explicit ExplicitInt(int v) : val(v) {}
    int val;
};

int main() {
    // 1. Numeric conversions
    double d = 3.14;
    int i = static_cast<int>(d); // Explicitly truncates to 3
    
    // 2. Upcasting (safe, implicit, but can be explicit)
    Derived derivedObj;
    Base* basePtr = static_cast<Base*>(&derivedObj); 
    
    // 3. Explicit downcasting (NO run-time check - you must be sure!)
    Derived* derivedPtr = static_cast<Derived*>(basePtr); 
    
    // 4. void* to typed pointer
    void* rawMemory = &d;
    double* dPtr = static_cast<double*>(rawMemory);
    
    // 5. Calling an explicit constructor
    // ExplicitInt obj = 5; // ERROR: constructor is explicit
    ExplicitInt obj = static_cast<ExplicitInt>(5); 
    
    return 0;
}
```

## dynamic_cast

The **`dynamic_cast`** operator performs safe, run-time checked polymorphic downcasting. 

**Syntax:** `dynamic_cast<TargetType>(expression)`

While `static_cast` blindly trusts that a downcast is valid, `dynamic_cast` asks the run-time system to verify the actual type of the object. It uses **Run-Time Type Information** (RTTI) to ensure the conversion makes sense.

![`dynamic_cast` reads the object’s vtable to verify its real type, yielding a valid pointer or `nullptr`.](assets/s36_dynamic_cast.png)

Because it relies on the vtable to identify the object's type at run time, `dynamic_cast` **requires a polymorphic type** — meaning the base class must have at least one virtual function.

::: trap
Using `dynamic_cast` on a class hierarchy with no virtual functions will result in a compile-time error. The base class typically needs a virtual destructor.
:::

If the cast is invalid (i.e. the object is not actually of the target derived type):
- For **pointers**, `dynamic_cast` returns `nullptr`.
- For **references**, `dynamic_cast` throws a `std::bad_cast` exception (since there is no such thing as a null reference).

```cpp
#include <iostream>
#include <exception>

class Base {
public:
    virtual ~Base() = default; // Makes the class polymorphic
};

class Derived : public Base {
public:
    void useDerivedFeature() { std::cout << "Derived feature used\n"; }
};

class OtherDerived : public Base {};

int main() {
    Base* basePtr = new Derived();
    Base* otherPtr = new OtherDerived();

    // 1. Casting with pointers
    Derived* successPtr = dynamic_cast<Derived*>(basePtr);
    if (successPtr) {
        successPtr->useDerivedFeature(); // Succeeds
    }

    Derived* failPtr = dynamic_cast<Derived*>(otherPtr);
    if (!failPtr) {
        std::cout << "Failed pointer cast: object is not a Derived\n"; // Executes
    }

    // 2. Casting with references
    try {
        Derived& ref = dynamic_cast<Derived&>(*otherPtr);
    } catch (const std::bad_cast& e) {
        std::cout << "Failed reference cast threw exception: " << e.what() << "\n";
    }

    delete basePtr;
    delete otherPtr;
    return 0;
}
```

## const_cast

The **`const_cast`** operator is the *only* cast in C++ that can add or remove `const` or `volatile` qualifiers from a variable.

**Syntax:** `const_cast<TargetType>(expression)`

It is typically used to interface with legacy C APIs that take non-const pointers but do not actually modify the data.

```cpp
#include <iostream>

void legacyCFunction(char* text) {
    // A legacy API that promises not to modify text, but lacks the 'const' keyword
    std::cout << text << "\n";
}

int main() {
    const char* message = "Hello, World!";
    
    // legacyCFunction(message); // ERROR: Cannot pass const char* to char*
    legacyCFunction(const_cast<char*>(message)); // OK: const is stripped away
    
    return 0;
}
```

::: trap
Using `const_cast` to strip `const` from an object that was originally declared as `const`, and then modifying it, is **undefined behaviour**. Only cast away `const` if the underlying object is truly mutable.
:::

## reinterpret_cast

The **`reinterpret_cast`** operator performs low-level bit reinterpretation between completely unrelated pointer or integer types. 

**Syntax:** `reinterpret_cast<TargetType>(expression)`

It simply instructs the compiler to treat a sequence of bits as if it were a different type, without performing any data conversion. It is inherently dangerous, highly non-portable, and its behaviour is largely implementation-defined. It is generally reserved for low-level systems programming, such as interacting with hardware or custom memory allocators.

```cpp
#include <iostream>
#include <cstdint>

int main() {
    int value = 42;
    int* ptr = &value;
    
    // Cast a pointer to an integer type large enough to hold it
    uintptr_t memoryAddress = reinterpret_cast<uintptr_t>(ptr);
    
    // Cast an unrelated integer back into a pointer
    int* restoredPtr = reinterpret_cast<int*>(memoryAddress);
    
    std::cout << *restoredPtr << "\n"; // Outputs 42
    
    return 0;
}
```

## C-style and functional casts

C++ still supports the old C-style cast `(Type)expression` and its functional equivalent `Type(expression)`. 

However, you should **avoid them entirely** in modern C++. A C-style cast is a sledgehammer that silently attempts to perform a sequence of C++ casts in the background. It will try a `const_cast`, then a `static_cast`, then a `reinterpret_cast` until one compiles. 

```cpp
const int constant = 10;
const int* constPtr = &constant;

// C-style cast: silently acts as a const_cast here!
int* mutablePtr = (int*)constPtr; 
```

Because it can silently degrade into a `reinterpret_cast` or `const_cast` when you only intended a `static_cast`, it masks bugs and obscures your intent.

## Run-Time Type Information (RTTI) and typeid

**Run-Time Type Information (RTTI)** is the mechanism C++ uses to keep track of the dynamic types of objects at run time. `dynamic_cast` relies heavily on RTTI. 

RTTI also provides the `typeid` operator (defined in the `<typeinfo>` header), which allows you to query the exact run-time type of an object and retrieve a `std::type_info` object representing it.

```cpp
#include <iostream>
#include <typeinfo>

class Base { public: virtual ~Base() = default; };
class Derived : public Base {};

int main() {
    Base* p = new Derived();
    
    // Inspect the run-time type using typeid
    if (typeid(*p) == typeid(Derived)) {
        std::cout << "p points to a Derived object\n";
    }
    
    delete p;
    return 0;
}
```

::: interview
**"What is the difference between static_cast and dynamic_cast?"**
Explain that `static_cast` performs compile-time conversions without run-time overhead, making it fast but unsafe for downcasting if the actual type is wrong. `dynamic_cast` performs a safe, run-time checked downcast using RTTI, returning `nullptr` (or throwing) on failure. It requires a polymorphic class.

**"How do you safely downcast?"**
By using `dynamic_cast` on a pointer and checking if the result is `nullptr`.

**"What is RTTI?"**
Run-Time Type Information; the C++ mechanism (often using the vtable) that exposes the dynamic type of an object at run time, enabling `dynamic_cast` and `typeid`.
:::

## Summary of cast operators

| Cast | What it does | Checked? | Typical use |
| :--- | :--- | :--- | :--- |
| `static_cast` | Converts between related types (upcast, explicit downcast, numeric). | Compile-time | Safe, intended conversions. |
| `dynamic_cast` | Polymorphic downcast using RTTI. | Run-time | Safely querying if a base pointer holds a specific derived type. |
| `const_cast` | Adds or removes `const` or `volatile` qualifiers. | Compile-time | Interfacing with legacy non-const C APIs. |
| `reinterpret_cast` | Low-level bit pattern reinterpretation. | None | Systems programming, raw memory manipulation. |
