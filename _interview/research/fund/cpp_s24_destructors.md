# Destructors

::: definition
A **destructor** is a special member function that runs automatically when an object is destroyed. Its primary job is **cleanup** — releasing any resources the object acquired during its lifetime.
:::

## Syntax and mechanics

A destructor takes the class's name preceded by a tilde (`~`). 

```cpp
class Rectangle {
public:
    Rectangle() { /* constructor */ }
    
    ~Rectangle() {
        // destructor cleanup code
    }
};
```

Three strict rules govern destructors:
1. **No arguments:** A destructor takes no parameters, so it cannot be overloaded.
2. **No return type:** Like constructors, they return nothing (not even `void`).
3. **Exactly one:** Because it cannot be overloaded, a class has exactly one destructor.

Destructors are invoked automatically by the compiler in two main scenarios:
1. When a stack-allocated object goes out of scope (e.g., a function returns).
2. When a heap-allocated object is explicitly destroyed using `delete`.

Crucially, when multiple local objects go out of scope, they are destroyed in the **reverse order of construction** (the last one constructed is the first one destroyed).

::: keypoint
In Python, objects are cleaned up by a garbage collector at an unpredictable time, and the `__del__` method is rarely used. In C++, destruction is fully deterministic: the destructor fires the exact millisecond the object goes out of scope or is `delete`d.
:::

## Releasing resources

For a class containing only basic types (like integers or booleans), the compiler's automatically generated destructor is sufficient. The memory occupied by the object itself is reclaimed automatically. 

A destructor must be written explicitly when the object *owns* a resource that will not clean itself up, such as heap memory, an open file handle, or a network socket.

```cpp
#include <iostream>

class Player {
private:
    int* inventory;

public:
    Player() {
        // Acquire resource
        inventory = new int[100]; 
    }

    ~Player() {
        // Release resource
        delete[] inventory;       
        std::cout << "Player resources freed.\n";
    }
};

int main() {
    Player* p1 = new Player();  // Constructor runs, allocates heap array
    // ... use p1 ...
    delete p1;                  // Destructor runs, freeing inventory
    return 0;
}
```

When `delete p1;` executes, it first calls `~Player()` to release the internal `inventory` array, and then it frees the memory for the `Player` object itself.

## RAII (Resource Acquisition Is Initialisation)

::: heavy
This is the central idiom of safe C++ resource management. It guarantees that resources are never leaked, even when errors occur.
:::

**Analogy:** Think of renting a car. The contract (constructor) hands you the keys, and the expiration of the rental period (going out of scope) automatically triggers the return process (destructor). You do not have to manually remember to drive it back if an emergency forces you to leave early.

![RAII: stack unwinding runs the destructor even when an exception is thrown.](assets/s24_raii.png)

**Example:** Managing a file handle safely.

```cpp
#include <fstream>
#include <iostream>
#include <string>

class FileLogger {
private:
    std::ofstream file;

public:
    FileLogger(const std::string& filename) {
        // Acquire in constructor
        file.open(filename);
    }

    void log(const std::string& message) {
        if (file.is_open()) {
            file << message << "\n";
        }
    }

    ~FileLogger() {
        // Release in destructor
        if (file.is_open()) {
            file.close();
            std::cout << "File closed safely.\n";
        }
    }
};

void processData() {
    FileLogger logger("log.txt");
    logger.log("Processing started...");
    
    // If an exception is thrown here, or we return early,
    // logger goes out of scope and the file is guaranteed to be closed.
}
```

**Plain-English rule:** Tie the lifespan of a manual resource (like an open file or heap allocation) to the lifespan of a local, stack-allocated object. When the stack object dies, its destructor cleans up the resource.

**Technical statement:** **Resource Acquisition Is Initialisation** (RAII) ensures exception-safe resource management by binding resource acquisition to class constructors and release to destructors. Because C++ guarantees stack unwinding (calling destructors for all local objects) when an exception is thrown or a scope exits, resources are deterministically reclaimed.

## The virtual destructor

When dealing with inheritance and polymorphism, destructors require special care. If you point a base class pointer at a derived class object and then `delete` that pointer, C++ must know to call the derived class's destructor first.

```cpp
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base built\n"; }
    ~Base() { std::cout << "Base destroyed\n"; } 
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { 
        data = new int[50];
        std::cout << "Derived built\n"; 
    }
    ~Derived() { 
        delete[] data;
        std::cout << "Derived destroyed\n"; 
    }
};

int main() {
    Base* ptr = new Derived();
    delete ptr; // UNDEFINED BEHAVIOUR if ~Base() is not virtual!
    return 0;
}
```

::: trap
If `~Base()` is not marked `virtual`, deleting a `Derived` object through a `Base*` pointer only calls `~Base()`. The `Derived` destructor is skipped, leaking the `data` array entirely.
:::

To fix this, the base class destructor must be marked `virtual`:

```cpp
class Base {
public:
    virtual ~Base() { std::cout << "Base destroyed\n"; } 
};
```

Now, `delete ptr;` correctly triggers dynamic dispatch: it looks up the actual object type, calls `~Derived()` first, and then calls `~Base()`.

::: interview
**Q:** Why must a base class destructor be virtual?
**A:** To ensure that when a derived object is deleted via a base class pointer, the derived class's destructor is invoked, preventing memory leaks and undefined behaviour.
:::

## The Rule of Zero, Three, and Five

Writing a custom destructor strongly implies your class is manually managing a resource. If it manages a resource, the compiler-generated copy constructor and assignment operator will almost certainly do the wrong thing (creating shallow copies that lead to double-free errors).

This leads to a fundamental C++ design guideline:
- **The Rule of Three:** If a class requires a user-defined destructor, a copy constructor, or a copy assignment operator, it almost certainly requires all three.

Modern C++ expands this to the **Rule of Five** (adding move constructors and move assignment) and the **Rule of Zero** (preferring to use smart pointers and standard containers so you don't need to write *any* of them). The deep mechanics of these rules are deferred to the section on move semantics.
