# Polymorphism and Virtual Functions

Polymorphism (meaning "many forms") is one of the core pillars of object-oriented programming. It allows us to treat objects of different derived types through a common base interface.

## Compile-time versus run-time polymorphism

::: definition
**Polymorphism** is the ability of different objects to respond in their own specific way to the same function call. 
:::

C++ supports two main types of polymorphism:
- **Compile-time (static) polymorphism**: Resolved during compilation. Examples include function overloading and templates.
- **Run-time (dynamic) polymorphism**: Resolved during program execution. This is achieved using inheritance and virtual functions, and is the focus of this section.

## Upcasting and static binding

Before understanding how dynamic polymorphism works, we must look at what happens without it. In C++, a base class pointer (or reference) is allowed to point to a derived class object. This is called **upcasting**, and it is perfectly safe because a derived object *is a* base object.

However, a base pointer only knows about the base class's interface. Consider this classic bug:

```cpp
#include <iostream>

class Car {
public:
    void startEngine() { std::cout << "Car engine starting...\n"; }
};

class AdvancedCar : public Car {
public:
    void startEngine() { std::cout << "AdvancedCar engine roaring!\n"; }
    void activateAutopilot() { std::cout << "Autopilot engaged.\n"; }
};

int main() {
    Car* p = new AdvancedCar(); // Upcasting: base pointer to derived object
    
    p->startEngine();         // Outputs: "Car engine starting..."
    // p->activateAutopilot(); // ERROR: 'Car' has no member named 'activateAutopilot'
    
    delete p;
    return 0;
}
```

Even though `p` actually points to an `AdvancedCar` object, calling `p->startEngine()` executes the base `Car::startEngine()`, and attempting to call `p->activateAutopilot()` will not compile at all. 

By default, C++ uses **static binding** (or early binding). The compiler looks exclusively at the *type of the pointer* (`Car*`), not the type of the actual object in memory, and wires the call to the base class version at compile time.

## The `virtual` keyword and dynamic dispatch

To achieve run-time polymorphism, we must tell the compiler to wait until the program is running to decide which function to call, based on the actual object's type. We do this by marking the base class function with the **`virtual`** keyword.

This enables **dynamic dispatch** (or late binding).

![Static binding uses the pointer type; dynamic dispatch uses the actual object via the vtable.](assets/s29_static_vs_dynamic_dispatch.png)

```cpp
#include <iostream>

class Car {
public:
    virtual void startEngine() { std::cout << "Car engine starting...\n"; }
};

class AdvancedCar : public Car {
public:
    // Overrides the base class virtual function
    void startEngine() override { std::cout << "AdvancedCar engine roaring!\n"; }
};

int main() {
    Car* p = new AdvancedCar(); 
    p->startEngine(); // Outputs: "AdvancedCar engine roaring!"
    
    delete p;
    return 0;
}
```

Now, because `startEngine()` is virtual, calling `p->startEngine()` correctly invokes `AdvancedCar::startEngine()`.

::: keypoint
In Python, methods are virtual by default; calling a method on a base reference always invokes the derived implementation if one exists. C++ prioritises performance, so static binding is the default, and dynamic dispatch requires explicitly writing `virtual`.
:::

## Function overriding versus overloading and hiding

When a derived class provides its own implementation for a base class's virtual function, it is called **overriding**. The derived function must match the base function's signature (name, parameters, and `const`-ness) exactly.

If the signature differs even slightly, it is not an override. Instead, it is **overloading** (if in the same scope) or **hiding** (if in a derived scope). 

::: trap
If a derived class defines a function with the same name as a base class function but different parameters, it hides the base class function entirely, preventing it from being called through a derived object.
:::

```cpp
class Base {
public:
    virtual void display(int x) const { std::cout << "Base " << x << "\n"; }
};

class Derived : public Base {
public:
    // TRAP: Missing 'const'. This does NOT override Base::display!
    // It hides Base::display(int) const.
    virtual void display(int x) { std::cout << "Derived " << x << "\n"; }
};
```

### The `override` and `final` specifiers

Because accidental hiding is a common and silent bug, C++11 introduced the `override` specifier. Appending `override` to a derived function declaration forces the compiler to check that it actually overrides a base virtual function. If the signatures do not match perfectly, it generates a compile-time error.

```cpp
class Derived : public Base {
public:
    // ERROR: marked override, but does not match Base::display(int) const
    void display(int x) override; 
};
```

You can also use the `final` specifier to prevent further overriding in subclasses, or to prevent a class from being inherited from entirely.

```cpp
class AdvancedCar : public Car {
public:
    void startEngine() final; // No class derived from AdvancedCar can override this
};
```

::: interview
Expect questions asking you to spot the bug in a hierarchy where a derived function slightly changes a parameter type or drops a `const` qualifier. Mention that replacing an override with an overload hides the base implementation, and always advocate using `override` to prevent this silent mistake.
:::

## Calling a specific version of a virtual function

Sometimes a derived class override needs to invoke the original base class implementation as part of its work. You can bypass dynamic dispatch and force a static call by qualifying the function name with the base class's scope resolution operator (`::`).

```cpp
class SportsCar : public Car {
public:
    void startEngine() override {
        Car::startEngine(); // Explicitly calls the base version statically
        std::cout << "Activating turbo!\n";
    }
};
```

## The virtual function with default arguments trap

A notoriously tricky edge case in C++ is mixing virtual functions with default arguments.

::: trap
Virtual functions are bound dynamically at run time, but their default arguments are bound statically at compile time based on the pointer's type.
:::

```cpp
#include <iostream>

class Base {
public:
    virtual void print(int val = 10) { std::cout << "Base: " << val << "\n"; }
};

class Derived : public Base {
public:
    void print(int val = 20) override { std::cout << "Derived: " << val << "\n"; }
};

int main() {
    Base* p = new Derived();
    p->print(); // Outputs: "Derived: 10"
    delete p;
    return 0;
}
```

The pointer `p` is of type `Base*`, so the compiler statically substitutes the default argument `10`. However, the function called is dynamically resolved to `Derived::print`, resulting in the derived function executing with the base class's default argument.

::: heavy
The following topics cover the internal mechanics of dynamic dispatch (vtables) and the dangers of value semantics with polymorphic types (object slicing).
:::

## Under the hood: VTABLEs and vptrs

To implement dynamic dispatch, the compiler must somehow keep track of which function belongs to which object type at run time.

Imagine a company where employees receive a generic "do work" instruction. Each employee carries a secret ID badge pointing to their specific job manual. When told to work, they look at their own badge, find their specific manual, and follow those instructions.

![Each polymorphic object holds a hidden vptr to its class vtable of function pointers.](assets/s29_vtable_vptr.png)

```cpp
class Base {
public:
    virtual void func() {}
};

class Derived : public Base {
public:
    void func() override {}
};
```

The plain-English rule is: when a class has at least one virtual function, the compiler builds a hidden lookup table of function pointers for that class, and secretly embeds a pointer to this table inside every object of that class.

Technically, this mechanism relies on two components:
1. **Virtual Table (vtable)**: The compiler creates a static array of function pointers per class (not per object). This table contains the addresses of the most-derived virtual functions accessible to that class.
2. **Virtual Pointer (vptr)**: The compiler secretly injects a hidden pointer member into the class. When an object is constructed, its `vptr` is initialised to point to its class's vtable.

When a virtual function is called through a base pointer, the program performs an indirect jump: it reads the object's `vptr` to find the vtable, looks up the function pointer at the correct offset, and executes it. 

**Performance note**: This indirection means virtual function calls are slightly slower than regular function calls. Furthermore, because the exact function being called is not known until run time, the compiler generally cannot inline virtual function calls.

::: interview
"How does dynamic dispatch work under the hood?" is a very common technical interview question. Explain the vtable (one per class) and the vptr (one per object), and describe the cost: a slight memory overhead per object (for the vptr) and a performance overhead per call (the pointer dereference and missed inlining opportunities).
:::

## Object slicing

Polymorphism only works through pointers and references. If you pass or assign a derived object to a base object *by value*, you trigger a destructive behaviour called **object slicing**.

Imagine trying to fit a detailed encyclopaedia into a small envelope meant for a pocket dictionary. The extra pages simply will not fit and must be torn off and left behind.

![Copying a Derived into a Base value slices off the derived part.](assets/s29_object_slicing.png)

```cpp
#include <iostream>

class Car {
public:
    int speed = 50;
    virtual void identify() { std::cout << "I am a standard Car\n"; }
};

class AdvancedCar : public Car {
public:
    int batteryLevel = 100;
    void identify() override { std::cout << "I am an AdvancedCar\n"; }
};

void printByValue(Car c) {
    c.identify();
}

int main() {
    AdvancedCar myAdvancedCar;
    
    // Slicing occurs! 'myAdvancedCar' is copied into 'c', dropping 'batteryLevel'.
    // The resulting object is strictly a Car.
    printByValue(myAdvancedCar); // Outputs: "I am a standard Car"
    
    return 0;
}
```

The plain-English rule is: when you copy a derived object into a base variable, the compiler slices off all the derived-specific data and treats the remainder exactly as a base object, completely breaking polymorphism.

Technically, assigning a `Derived` to a `Base` (or passing by value) invokes the `Base` copy constructor. This constructor copies only the `Base` subobject (the members declared in `Base`). The `vptr` of the newly constructed object is set to the `Base` vtable, meaning any virtual function calls will resolve statically to the base class versions. The derived state is lost permanently in the copy.

Always pass polymorphic objects by pointer (`Base*`) or reference (`Base&`) to preserve their dynamic type and avoid object slicing.

## Looking ahead

We have seen how `virtual` allows a derived class to replace a base class's implementation. But what if the base class does not have a meaningful implementation to provide at all, and exists *only* to define an interface? The next section explores pure virtual functions and abstract classes, which enforce overriding in derived classes.
