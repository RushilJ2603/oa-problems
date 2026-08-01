# Inheritance: Constructors, Access Control, and Types

When a class inherits from another, it does not just receive its members; it inherits its lifetime rules, its access restrictions, and its structural place in the class hierarchy. This section details how objects are built and destroyed, how access is controlled, and the various shapes inheritance graphs can take.

## Order of construction and destruction

When a derived object is created, the compiler ensures the foundational parts are built before the additions. The **base class constructor runs first**, followed by the derived class constructor. 

When the object is destroyed, the order is exactly reversed: the **derived class destructor runs first**, tearing down the specialised parts, and then the base class destructor cleans up the foundation.

```cpp
#include <iostream>

class Base {
public:
    Base()  { std::cout << "1. Base constructed\n"; }
    ~Base() { std::cout << "4. Base destroyed\n"; }
};

class Derived : public Base {
public:
    Derived()  { std::cout << "2. Derived constructed\n"; }
    ~Derived() { std::cout << "3. Derived destroyed\n"; }
};

int main() {
    Derived d;
    return 0;
}
```

::: keypoint
Construction proceeds from the base outwards. Destruction proceeds from the most derived class inwards.
:::

## Passing arguments to a base constructor

By default, creating a derived object invokes the *no-argument* (default) constructor of the base class. If the base class does not have a default constructor, or if you want to pass specific arguments to a parameterised base constructor, you must explicitly call it using the derived class's **member-initialiser list** (a syntax that initialises members before the constructor body runs).

```cpp
#include <iostream>
#include <string>

class Entity {
    std::string name;
public:
    Entity(std::string n) : name(n) {
        std::cout << "Entity " << name << " created.\n";
    }
};

class Player : public Entity {
    int score;
public:
    // Explicitly pass 'playerName' up to Entity's constructor
    Player(std::string playerName, int startingScore) 
        : Entity(playerName), score(startingScore) 
    {
        std::cout << "Player initialised with score " << score << ".\n";
    }
};
```

::: trap
You cannot initialise base class members directly inside the derived constructor's body or its initialiser list (e.g. `Player() : name("Bob") {}` is a compiler error). You must delegate to the base constructor.
:::

## The `protected` access specifier

You are already familiar with `public` (accessible to anyone) and `private` (accessible only within the class itself). Inheritance introduces a third level: **`protected`**, which specifically facilitates inheritance design. 

A `protected` member behaves like a private member to the outside world, but acts like a public member to derived classes.

```cpp
#include <iostream>

class Base {
private:
    int hiddenVal = 1;    // Inaccessible to derived classes
protected:
    int sharedVal = 2;    // Accessible to derived classes
public:
    int openVal = 3;      // Accessible to everyone
};

class Derived : public Base {
public:
    void display() {
        // std::cout << hiddenVal; // ERROR: private in Base
        std::cout << sharedVal;    // OK: protected in Base
        std::cout << openVal;      // OK: public in Base
    }
};
```

This table summarises where members can be accessed from:

| Access from | `private` | `protected` | `public` |
| :--- | :--- | :--- | :--- |
| **Inside the defining class** | yes | yes | yes |
| **Inside a derived class** | no | yes | yes |
| **Through an object** (`obj.member`) | no | no | yes |

## Types of inheritance

Inheritance hierarchies can be combined to form several standard structural shapes:

- **Single inheritance**: One derived class inherits from exactly one base class (`A → B`). This is the most common form.
- **Multilevel inheritance**: A class derives from another derived class, forming a chain (`A → B → C`). For example, `Vehicle → Car → SportsCar`.
- **Hierarchical inheritance**: Multiple classes derive from a single base class (`A → B` and `A → C`). For example, `Shape` acts as a base for both `Circle` and `Square`.
- **Multiple inheritance**: A single class derives from more than one base class simultaneously (`A, B → C`). For example, a `SmartPhone` inheriting from `Phone` and `Camera`.
- **Hybrid inheritance**: Any combination of the above shapes (e.g. hierarchical and multiple inheritance combined in one graph).

Multiple inheritance is powerful but introduces significant structural complexity, leading directly to one of C++'s most notorious design challenges.

::: heavy
The following section covers the "diamond problem" and virtual inheritance. This introduces complex memory layouts and object subtyping.
:::

## The diamond problem and virtual inheritance

Imagine a university where a `TeachingAssistant` acts as both a `Teacher` and a `Student`. Since both teachers and students are humans, both `Teacher` and `Student` inherit from a common `Person` base class. 

![The diamond problem: two paths to a common base duplicate its subobject.](assets/s28_diamond.png)

```cpp
class Person {
public:
    int age;
};

class Teacher : public Person {};
class Student : public Person {};

class TeachingAssistant : public Teacher, public Student {
    // Inherits from both Teacher and Student
};

int main() {
    TeachingAssistant ta;
    // ta.age = 22; // ERROR: ambiguous request
    return 0;
}
```

If you try to set the teaching assistant's age (`ta.age = 22;`), the compiler throws an error. 

The plain-English rule is: when an inheritance graph splits and then merges back together (forming a diamond shape), the class at the bottom gets duplicated copies of the class at the top. The compiler does not know which `Person` subobject's `age` you want to modify.

Technically, multiple inheritance from a common non-virtual base class creates a distinct subobject for each path in the inheritance graph. This leads to name lookup ambiguity and duplicated memory footprint for the common base members.

### Virtual inheritance

To fix this, C++ allows **virtual inheritance**. This is a mechanism where intermediate classes use the `virtual` keyword to promise they will share a single instance of a common base class.

![Virtual inheritance: one shared base subobject reached via hidden offsets.](assets/s28_virtual_inheritance.png)

```cpp
class Person {
public:
    int age;
};

// The 'virtual' keyword guarantees sharing of the Person subobject
class Teacher : virtual public Person {};
class Student : virtual public Person {};

class TeachingAssistant : public Teacher, public Student {};

int main() {
    TeachingAssistant ta;
    ta.age = 22; // OK! Only one 'Person' exists
    return 0;
}
```

By marking the inheritance as `virtual public`, `Teacher` and `Student` tell the compiler they are willing to share a single `Person` subobject. When `TeachingAssistant` is constructed, only **one** `Person` is created.

**Memory layout intuition:** Instead of embedding a `Person` directly inside the `Teacher` and `Student` parts of memory, the compiler places a single `Person` subobject at the very end of the `TeachingAssistant` memory footprint. The `Teacher` and `Student` subobjects are then given hidden pointers (or offsets) that point to that shared `Person`. This prevents duplication, though it makes object creation slightly slower and memory layouts heavier, which is why virtual inheritance is opt-in.

::: interview
A classic interview question asks: "What is the diamond problem and how is it resolved in C++?" Explain the ambiguity of duplicated base subobjects, and immediately mention that **virtual inheritance** (`class B : virtual public A`) forces the intermediate classes to share a single base instance via hidden offsets.
:::
