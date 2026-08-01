# Inheritance

**Inheritance** allows a new class to be built upon an existing one, absorbing its data and behaviour while adding its own. It is the mechanism by which C++ models an **"is-a" relationship**: a `Car` *is a* `Vehicle`, and a `Cuboid` *is a* `Rectangle`.

## Generalisation and specialisation

Inheritance operates in two conceptual directions to help organise code:
- **Generalisation** extracts common characteristics from several classes into a single shared base class. If you have `Dog`, `Cat`, and `Bird` classes, you can generalise their common traits (like eating and sleeping) into a shared `Animal` class to eliminate code duplication.
- **Specialisation** extends an existing general class to create a more specific one. You might take a basic `Rectangle` class and add a `height` property to specialise it into a `Cuboid`. The derived class reuses the base's tested design and adds only what makes it unique.

::: definition
The original class being reused is the **base class** (or parent/superclass). The new class that inherits from it is the **derived class** (or child/subclass).
:::

## Base and derived syntax

A derived class declares its relationship to a base class using a colon, followed by an access specifier (usually `public`) and the base class name.

```cpp
#include <iostream>

class Base {
public:
    int x;
    void show() { std::cout << x << "\n"; }
};

// Derived inherits from Base
class Derived : public Base {
public:
    int y;
    void display() { std::cout << x << " " << y << "\n"; }
};
```

The derived class silently absorbs all members of the base class. In the example above, `Derived` contains both `y` (its own) and `x` (inherited). It can use `x` directly in its `display()` member function just as if `x` had been declared locally.

```cpp
int main() {
    Derived d;
    d.x = 10;        // Inherited from Base
    d.y = 15;        // Derived's own member
    d.show();        // Calls inherited function, prints "10"
    d.display();     // Calls own function, prints "10 15"
    return 0;
}
```

## The "is-a" relationship and upcasting

Public inheritance strictly models an **"is-a"** relationship. Because a derived object physically contains a complete base subobject inside it in memory, a derived object *is* a valid base object. 

This enables a fundamental mechanism called **upcasting**: you can always treat a derived object as though it were a base object. A pointer or reference to a base type can safely bind to a derived object.

```cpp
#include <iostream>

class Animal {
public:
    void eat() { std::cout << "Eating...\n"; }
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof!\n"; }
};

int main() {
    Dog myDog;
    
    // Upcasting: Base reference binding to a derived object
    Animal& ref = myDog; 
    ref.eat(); // Valid: every Dog is an Animal
    
    // ref.bark(); // Error: the Animal interface doesn't know about bark()
    return 0;
}
```

::: keypoint
Upcasting is safe, implicit, and foundational to polymorphism (covered deeply in later sections). Note that a base pointer or reference can only access the base portion of the derived object.
:::

## Inheritance access modes

When deriving a class, you specify an inheritance access mode (`public`, `protected`, or `private`): `class Derived : public Base`. This mode dictates how the access modifiers of the *inherited* members are remapped within the derived class.

::: definition
The **`protected`** access modifier means a member is hidden from the outside world (like `private`), but remains accessible to derived classes.
:::

| Base member access | `public` inheritance | `protected` inheritance | `private` inheritance |
| :--- | :--- | :--- | :--- |
| **`public`** | remains `public` | becomes `protected` | becomes `private` |
| **`protected`** | remains `protected` | remains `protected` | becomes `private` |
| **`private`** | *inaccessible* | *inaccessible* | *inaccessible* |

::: trap
A derived class **never** has direct access to the `private` members of its base class, regardless of the inheritance mode. It must use the base class's `public` or `protected` functions to interact with that private data.
:::

### How access propagates

The inheritance mode affects not just the immediate derived class, but also any future grandchild classes (classes derived from the derived class):

1. **`public` inheritance** (`class D : public B`): The standard choice. It maintains the exact interface of the base class, strictly modelling "is-a". Public members stay public; protected stay protected.
2. **`protected` inheritance** (`class D : protected B`): Base public and protected members become protected in `D`. They are inaccessible to the outside world, but a grandchild class `G : public D` can still see them.
3. **`private` inheritance** (`class D : private B`): Base public and protected members become private in `D`. They are entirely sealed off. A grandchild class `G : public D` will **not** be able to access any of `B`'s members. It models "implemented-in-terms-of" rather than "is-a".

```cpp
class Base {
public:    int pub;
protected: int prot;
private:   int priv;
};

class PublicDerived : public Base {
    // pub is public
    // prot is protected
    // priv is inaccessible
    void test() { pub = 1; prot = 2; /* priv = 3; // Error */ }
};

class PrivateDerived : private Base {
    // pub becomes private
    // prot becomes private
    // priv is inaccessible
    void test() { pub = 1; prot = 2; }
};

int main() {
    PublicDerived pubD;
    pubD.pub = 10;   // OK: remains public in PublicDerived

    PrivateDerived privD;
    // privD.pub = 10; // Error: became private in PrivateDerived
    return 0;
}
```

## What is inherited and what is not

A derived class inherits almost everything from its base class — all data members and member functions. However, a few specific components are inextricably tied to a class's exact identity and memory layout, and are therefore **not** inherited:

1. **Constructors and Destructors**: The derived class must define how to construct and destruct its own added state. (Base constructors are invoked automatically during the derived class's construction, but they are not inherited as the derived class's own constructors).
2. **Assignment Operators** (`operator=`): Like constructors, assignment logic is specific to the exact fields a class holds.
3. **Friendships**: Friendship is explicitly granted, not inherited. If `Base` declares a function as a `friend`, that function does not automatically gain access to the private members of `Derived`.

::: interview
"What is not inherited in C++?" is a classic trivia question. Be ready to list them: constructors, destructors, overloaded assignment operators, and friend declarations.
:::
