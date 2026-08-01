# Namespaces

As programs grow and rely on multiple third-party libraries, the chance of two libraries using the same name for a class or function increases. If a graphics library and a networking library both define a `Socket` class, combining them would result in a compilation error.

**Namespaces** solve this by grouping related names (functions, classes, variables) into a distinct scope. They act as declarative regions that prevent name collisions across large projects and libraries.

## Defining and accessing namespaces

You define a namespace using the `namespace` keyword. A crucial property of namespaces is that they are **open**: you can add to the same namespace across multiple files or multiple blocks in the same file.

```cpp
// graphics_engine.h
namespace Graphics {
    class Window {
        // ...
    };
}

// graphics_renderer.h
namespace Graphics {
    // Re-opens the Graphics namespace to add more members
    void renderFrame(); 
}
```

To access a name defined inside a namespace from outside it, you use the **scope-resolution operator** (`::`).

```cpp
#include "graphics_engine.h"

int main() {
    // Explicitly specifies the Window class from the Graphics namespace
    Graphics::Window myWindow;
    return 0;
}
```

## Nested namespaces and aliases

Namespaces can be nested within other namespaces to create hierarchical structures. Before C++17, you had to open each namespace explicitly:

```cpp
namespace Engine {
    namespace Physics {
        namespace Collision {
            bool checkIntersection();
        }
    }
}
```

C++17 introduced a compact syntax for nested namespaces:

```cpp
// C++17 compact nested namespace syntax
namespace Engine::Physics::Collision {
    bool checkIntersection();
}
```

To access this, you would write `Engine::Physics::Collision::checkIntersection()`. Since typing long, fully-qualified names can become tedious, you can create a **namespace alias**:

```cpp
namespace EPC = Engine::Physics::Collision;

int main() {
    EPC::checkIntersection();
    return 0;
}
```

::: keypoint
In Python, you might write `import matplotlib.pyplot as plt` to create a short alias. In C++, `namespace EPC = Engine::Physics::Collision;` serves exactly the same purpose for long namespace paths.
:::

## `using`-declarations versus `using`-directives

Rather than fully qualifying every name, C++ provides ways to bring namespace members into the current scope. There are two very different mechanisms.

A **using-declaration** brings exactly *one* specific name into the current scope.

```cpp
#include <iostream>

void printMessage() {
    using std::cout; // using-declaration
    
    cout << "Hello!\n";             // OK: 'cout' is now in scope
    // cout << std::endl;           // Would need std:: for endl
    // endl;                        // ERROR: 'endl' is not in scope
}
```

A **using-directive** brings *all* names from a namespace into the current scope.

```cpp
#include <iostream>
#include <vector>

void printAll() {
    using namespace std; // using-directive
    
    cout << "Hello!\n";
    vector<int> v;
}
```

### Why global `using namespace std;` is dangerous

While `using namespace std;` is common in beginner tutorials, it is widely considered bad practice in professional code when placed at file scope (globally). The `std` namespace is massive. Bringing everything into the global scope defeats the entire purpose of namespaces and invites naming ambiguities (for example, if you define your own `data` or `size` function).

If you must use a using-directive, restrict its scope by placing it strictly *inside* a function or a local block.

::: trap
**Never** put a using-directive like `using namespace std;` in a header file. Any source file that includes your header will be forced to silently import the entire namespace, inevitably causing collisions in the code of anyone consuming your header.
:::

::: interview
A common interview question asks the difference between `using std::cout;` and `using namespace std;`, and why the latter is globally discouraged. Explain that a using-declaration is surgical (importing one name), while a using-directive is a blunt instrument that pollutes the scope, risking collisions — especially if placed in a header file.
:::

## Anonymous namespaces

An **anonymous namespace** (or unnamed namespace) is simply a namespace defined without a name. 

```cpp
namespace {
    int internalCounter = 0;
    
    void helperFunction() {
        internalCounter++;
    }
}
```

Names declared in an anonymous namespace have **internal linkage**. This means they are only visible within the translation unit (the source file) where they are defined. If another source file defines an anonymous namespace with the same names, they will not collide. 

Anonymous namespaces are the modern, preferred C++ replacement for the legacy `static` keyword applied to file-scope variables or free functions.

## Argument-Dependent Lookup (ADL)

::: heavy
ADL is a subtle compiler mechanism that makes operator overloading and function calls across namespaces behave intuitively.
:::

Imagine telling a friend, "Feed the dog!" If you are both standing in your house, your friend automatically knows you mean *your* family dog, without you having to explicitly say "Feed the Smith family dog". The context of what you are interacting with defines where to look.

![Argument-dependent lookup also searches the namespaces of the call’s argument types.](assets/s40_adl.png)

```cpp
#include <iostream>
#include <string>

int main() {
    std::string name = "Ada";
    
    // We do not need to write std::operator<<(std::cout, name);
    std::cout << name; 
    
    return 0;
}
```

The plain-English rule is: when you call a function and pass it objects, the compiler automatically searches for that function inside the namespaces where those objects' types are defined.

Technically, this is **Argument-Dependent Lookup** (often called Koenig lookup). When the compiler sees the unqualified call to `operator<<(std::cout, name)` generated by the `<<` expression, it notes that `std::cout` is of type `std::ostream` and `name` is of type `std::string`. Because both arguments belong to the `std` namespace, ADL adds the `std` namespace to the set of scopes it searches. It successfully finds `std::operator<<` without you needing to explicitly qualify it.

::: interview
"What is ADL?" Expect this in senior C++ interviews. ADL (Argument-Dependent Lookup) is the rule that adds the namespaces of a function's arguments to the scope resolution process. Mention that without ADL, writing `std::cout << "Hello"` would fail unless we explicitly qualified the operator.
:::

## The `std` namespace and inline namespaces

The `std` namespace is reserved by the C++ Standard Library. 

The strict rule is: **you must not add your own declarations or definitions to the `std` namespace.** Modifying `std` results in undefined behaviour. There is only one specific allowed exception: you are permitted to specialise standard templates (like `std::hash`) for your own user-defined types.

```cpp
#include <functional>
#include <string>

struct User {
    std::string id;
};

// The ONLY valid reason to open 'namespace std' is for template specialisation
namespace std {
    template <>
    struct hash<User> {
        size_t operator()(const User& u) const {
            return hash<string>()(u.id);
        }
    };
}
```

### Inline namespaces

C++11 introduced **inline namespaces**, typically used for library versioning. When a nested namespace is marked `inline`, all its members are treated as if they were directly in the parent namespace.

```cpp
namespace MyLib {
    inline namespace v2 {
        void doWork(); // New implementation
    }
    
    namespace v1 {
        void doWork(); // Old implementation kept for backwards compatibility
    }
}

int main() {
    // Calls MyLib::v2::doWork() because v2 is inline
    MyLib::doWork(); 
    
    // Explicitly calls the older version
    MyLib::v1::doWork(); 
    
    return 0;
}
```

This allows library authors to ship updates while maintaining older versions, without breaking existing client code that relies on the unqualified names.
