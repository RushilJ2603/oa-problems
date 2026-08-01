# Abstract Classes and Interfaces

In the previous section, we saw how virtual functions and the vtable enable dynamic dispatch, allowing a base class pointer to invoke a derived class's method. However, sometimes a base class represents a concept so generic that it cannot provide a meaningful implementation for a function itself. 

## Pure virtual functions

A **pure virtual function** is a virtual function that is declared in a base class but has no implementation provided by default. It is created by appending `= 0` to the function declaration.

```cpp
class Shape {
public:
    // A pure virtual function
    virtual void draw() = 0; 
};
```

The `= 0` syntax specifically tells the compiler: "This function is intentionally left unimplemented in this class. Any class that inherits from me *must* provide its own implementation."

::: keypoint
In Python, this is achieved using the `abc` module by inheriting from `abc.ABC` and decorating the method with `@abstractmethod`. In C++, the `= 0` syntax achieves the same structural requirement natively.
:::

## Abstract classes

::: definition
An **abstract class** is any class that contains at least one pure virtual function (either declared directly or inherited without being overridden). 
:::

Because an abstract class is incomplete — it has missing behaviour — the compiler enforces a strict rule: **you cannot instantiate an abstract class**. Creating an object of an abstract class type will result in a compile-time error.

However, you *can* declare pointers and references to an abstract class. This is the entire point: they serve as handles for polymorphism.

```cpp
class Shape {
public:
    virtual void draw() = 0; 
    virtual ~Shape() = default; // ALWAYS provide a virtual destructor
};

int main() {
    // Shape s;       // ERROR: Cannot instantiate abstract class
    
    Shape* shapePtr;  // OK: Pointers to abstract classes are allowed
    Shape& shapeRef;  // OK: References are allowed (if bound to a derived object)
    
    return 0;
}
```

::: trap
If a derived class inherits from an abstract base class but fails to override *every* pure virtual function, the derived class itself remains an abstract class and cannot be instantiated.
:::

### A worked example

Here is how an abstract base class guarantees a common interface while allowing concrete derived classes to provide their specific implementations.

```cpp
#include <iostream>

// Abstract base class
class Shape {
public:
    // Pure virtual functions
    virtual void draw() const = 0;
    virtual double area() const = 0;
    
    // Virtual destructor is mandatory for safe polymorphic deletion
    virtual ~Shape() = default; 
};

// Concrete derived class
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    
    void draw() const override {
        std::cout << "Drawing a Circle.\n";
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// Concrete derived class
class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        std::cout << "Drawing a Rectangle.\n";
    }
    
    double area() const override {
        return width * height;
    }
};

int main() {
    Circle c(5.0);
    Rectangle r(4.0, 6.0);
    
    // Polymorphic array of pointers
    Shape* shapes[] = { &c, &r };
    
    for (Shape* s : shapes) {
        s->draw();                  // Dynamic dispatch resolves to correct draw()
        std::cout << s->area() << "\n";
    }
    return 0;
}
```

## The interface idiom

Unlike languages such as Java or C#, C++ does not have a built-in `interface` keyword. However, the concept of an interface is fully supported through a specific design pattern (an idiom). 

In C++, an **interface** is simply a class where *all* member functions are pure virtual, and it contains no member variables (state). It represents a pure behavioural contract.

```cpp
// This class acts as an interface
class IPrintable {
public:
    virtual void print() const = 0;
    virtual ~IPrintable() = default;
};
```

By convention, interface classes in C++ are often prefixed with an `I` (e.g. `IPrintable`), though this is a stylistic choice, not a language requirement.

::: heavy
The three-class taxonomy below breaks down the spectrum of class design from pure state/reuse to pure behaviour/polymorphism.
:::

## The three-class taxonomy

![Concrete, abstract (mixed), and interface (all pure virtual) classes and what each enables.](assets/s30_taxonomy.png)

When designing class hierarchies, you are fundamentally choosing where your class sits on a spectrum between state (data/reusability) and behaviour (contracts/polymorphism). There are three primary types of classes:

1. **All-concrete class**: Contains no pure virtual functions. All methods are fully implemented. 
   * **Purpose**: Code reusability and managing state. You instantiate these directly.
2. **Mixed abstract class**: Contains both concrete (implemented) methods and pure virtual methods.
   * **Purpose**: Reusability + Polymorphism. It shares common default behaviour or state with derived classes, but forces them to customise specific missing parts.
3. **All-pure-virtual class (Interface)**: Contains no state and only pure virtual functions (plus a virtual destructor).
   * **Purpose**: Pure polymorphism. It enforces a strict contract that derived classes must follow, completely decoupling the "what it does" from the "how it does it".

## Pure virtual functions with definitions

It is a rare but entirely valid C++ feature that a pure virtual function can actually have a definition. 

The rule "a class with a pure virtual function cannot be instantiated" still strictly applies. The purpose of defining a pure virtual function is to provide a shared default behaviour that derived classes *can* call if they want to, while still forcing them to explicitly override the function to acknowledge the contract.

```cpp
#include <iostream>

class Base {
public:
    // Pure virtual, but we will provide an implementation anyway
    virtual void show() = 0; 
    virtual ~Base() = default;
};

// Providing a definition for the pure virtual function
void Base::show() {
    std::cout << "Default Base behaviour.\n";
}

class Derived : public Base {
public:
    void show() override {
        // We MUST override it, but we can explicitly call the base implementation
        Base::show(); 
        std::cout << "Derived specific behaviour.\n";
    }
};
```

## Virtual destructors in abstract classes

You must **always** give an abstract base class a virtual destructor (typically `virtual ~Base() = default;`). 

Because abstract classes are designed to be used polymorphically via pointers (`Base* ptr = new Derived();`), deleting the object through that base pointer requires a virtual destructor to ensure the derived class's destructor runs. Without it, you will leak the derived object's resources and cause undefined behaviour.

::: interview
**Q:** What is the difference between an abstract class and an interface in C++?
**A:** C++ has no native `interface` construct. An abstract class is any class with at least one pure virtual function. An interface is a design idiom: an abstract class where *every* method is pure virtual (and has no state).

**Q:** Can an abstract class have a constructor?
**A:** Yes. Even though you cannot instantiate it directly, its constructor is called by the derived class's constructor (during the base-outwards construction process) to initialise any shared state the abstract class might hold.
:::
