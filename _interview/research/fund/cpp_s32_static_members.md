# Static Members

Normal class members belong to individual objects. **Static members**, on the other hand, belong to the class itself. They are shared across all instances, exist even if no objects have been created, and provide class-wide data and behaviour.

## Static data members

A **static data member** is a variable that is shared by all objects of the class. Only one copy of a static data member exists in the entire program, regardless of how many objects of that class are instantiated. Its lifetime is the whole program: it is created when the program starts and destroyed when it terminates.

### Declaration versus definition

Historically in C++, a static member must be declared inside the class but **defined** (and initialised) outside the class in a single source file. This is necessary because the class is just a blueprint, but a static member requires a concrete allocation in memory.

```cpp
#include <iostream>

class Server {
public:
    // Declaration inside the class
    static int activeConnections; 
    
    Server() { activeConnections++; }
    ~Server() { activeConnections--; }
};

// Definition and initialisation outside the class (usually in a .cpp file)
int Server::activeConnections = 0; 

int main() {
    Server s1;
    Server s2;
    std::cout << Server::activeConnections; // Outputs 2
    return 0;
}
```

You can access static members using the scope resolution operator (`::`) directly on the class name, such as `Server::activeConnections`. While you *can* access them through an object (e.g. `s1.activeConnections`), accessing them via the class name is strongly preferred as it clearly communicates that the member is static.

### C++17 `inline static`

C++17 introduced the `inline` keyword for variables, which allows you to define and initialise static members directly inside the class definition, avoiding the need for a separate out-of-class definition.

```cpp
class Server {
public:
    // Defined and initialised in-class (C++17 onwards)
    inline static int activeConnections = 0; 
};
```

## Static member functions

A **static member function** is a function that belongs to the class rather than to any specific object. Because it is not bound to an instance, it does not have a `this` pointer. 

Consequently, a static member function **can only directly access other static members** (variables or functions) of the class. It cannot read or modify non-static members because it does not know *which* object's data to use.

```cpp
#include <iostream>

class MathUtility {
private:
    int nonStaticValue = 10;
    static int staticValue;

public:
    static void printValue() {
        // std::cout << nonStaticValue; // ERROR: no 'this' pointer
        std::cout << staticValue;       // OK
    }
};

int MathUtility::staticValue = 42;

int main() {
    // Called as Class::fn() without creating an object
    MathUtility::printValue(); 
    return 0;
}
```

Static functions are typically used for utility groupings, instance management, or factory methods (functions that create and return new instances of the class). They are also the foundation of the Singleton design pattern, which ensures a class has only one instance and provides a global, static method to access it.

::: keypoint
In Python, the equivalent of a static data member is a **class variable** (defined directly in the class body), and a static member function is created by decorating a method with `@staticmethod`.
:::

## Constant and `constexpr` static members

There is an exception to the out-of-class definition rule for older C++ standards: if a static member is a `const` **integral type** (such as `int`, `char`, or `bool`), it can be initialised directly inside the class definition. 

```cpp
class NetworkConfig {
public:
    // OK: const integral type can be initialised in-class
    const static int maxRetries = 3; 
    
    // std::string is not an integral type; requires out-of-class definition
    // const static std::string host = "localhost"; 
};
```

For more complex types or values computed at compile time, use `constexpr`. A `constexpr static` member is implicitly `inline`, meaning it can (and must) be initialised directly in the class definition and requires no out-of-class definition.

```cpp
class Physics {
public:
    constexpr static double gravity = 9.81;
};
```

## Initialisation order caveat

When you have static variables spread across multiple translation units (different `.cpp` files), the C++ standard does not guarantee the exact order in which they are initialised. This is known as the **static initialisation order fiasco**. If one static variable's initialisation depends on another static variable from a different file, your program might crash or behave unpredictably because the dependency might not have been initialised yet. 

::: trap
Avoid cross-file dependencies between static variables. If you must depend on one, wrap the static variable inside a function that returns a reference to it (a technique called the Construct On First Use idiom).
:::

## Worked example: instance tracking

A classic use of static members is an object counter that tracks how many instances of a class currently exist.

```cpp
#include <iostream>

class Connection {
private:
    // Shared count of all active connections
    inline static int totalConnections = 0; 
    
    int connectionId; // Unique ID per object

public:
    Connection() {
        totalConnections++;
        connectionId = totalConnections;
        std::cout << "Opened connection #" << connectionId << "\n";
    }

    ~Connection() {
        totalConnections--;
        std::cout << "Closed connection #" << connectionId << "\n";
    }

    // Static function to read the static data
    static int getActiveCount() {
        return totalConnections;
    }
};

int main() {
    std::cout << "Initial: " << Connection::getActiveCount() << "\n";
    
    {
        Connection c1;
        Connection c2;
        std::cout << "Active: " << Connection::getActiveCount() << "\n";
    } // c1 and c2 are destroyed here
    
    std::cout << "Final: " << Connection::getActiveCount() << "\n";
    return 0;
}
```

::: interview
**Where are static members stored?** 
They are stored in the data segment (or BSS segment if uninitialised) of the process memory, not on the stack or heap alongside object instances.

**Why can't a static member function be `const` or `virtual`?** 
A `const` modifier on a member function promises not to modify the object's state (it makes the `this` pointer `const`). Since static functions have no `this` pointer, `const` is meaningless. Similarly, `virtual` functions rely on dynamic dispatch via a specific object's vtable at runtime; without an instance to supply the vtable, virtual dispatch is impossible.
:::
