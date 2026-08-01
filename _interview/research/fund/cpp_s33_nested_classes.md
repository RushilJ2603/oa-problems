# Nested and Local Classes

C++ allows you to define a class inside another class or even inside a function. This is primarily a tool for **name scoping** and encapsulation, keeping implementation-detail types hidden from the rest of the program.

## Nested classes

A **nested class** is a class declared inside the scope of another class. It acts as a member of the enclosing class for scoping purposes and obeys standard access control (`public`, `private`, `protected`).

A typical use case is hiding a tightly coupled helper type — such as a node inside a linked list, or an iterator inside a custom container — so that it does not pollute the global namespace.

```cpp
class LinkedList {
private:
    // Nested class hidden from the outside world
    class Node {
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head = nullptr;

public:
    void append(int val) {
        Node* newNode = new Node(val);
        // ... list insertion logic ...
    }
};
```

If a nested class is `public`, external code can use it by qualifying the name with the scope resolution operator (`::`), forming `Outer::Inner`.

```cpp
class Container {
public:
    class Iterator {
    public:
        void advance() { /* ... */ }
    };
};

int main() {
    // Accessing a public nested class requires the Outer:: prefix
    Container::Iterator it;
    it.advance();
    return 0;
}
```

### Relationship with the outer class

::: keypoint
Unlike Java inner classes, a C++ nested class has **no implicit outer instance**. It is an entirely separate object type.
:::

Because it lacks an implicit link to an outer object, a nested class does not get special access to the outer class's non-static members. There is no automatic `this` pointer pointing to the enclosing class. If a nested class needs to interact with the state of an outer object, you must explicitly pass a pointer or reference to that outer object into the nested class.

### Defining inside versus outside

For cleaner code, you can forward-declare a nested class inside the outer class and define its body later, outside the enclosing class. When defining it outside, you must use the `Outer::Inner` syntax.

```cpp
class NetworkManager {
private:
    // Forward declaration of the nested class
    class ConnectionState; 
    
    ConnectionState* state;

public:
    NetworkManager();
    // ...
};

// Definition outside the outer class
class NetworkManager::ConnectionState {
public:
    int latency;
    bool isActive;
    
    ConnectionState() : latency(0), isActive(false) {}
};
```

## Local classes

A **local class** is a class defined entirely within the body of a function. It is visible only inside that specific function block, making it useful for tiny, throwaway objects.

```cpp
void processData() {
    // Local class defined inside the function
    class Processor {
    public:
        void run() { /* ... */ }
    };

    Processor p;
    p.run();
}
```

Local classes have severe restrictions:
- They **cannot access non-static local variables** of the enclosing function.
- They cannot have `static` data members.
- They have limited linkage.

Because of these limitations and the advent of modern lambda expressions, local classes are rarely used in practice today.

::: interview
**Do nested classes cost memory?** 
No. A nested class is merely a type declaration. It does not increase the memory footprint (`sizeof`) of the outer class unless the outer class explicitly declares a data member of that nested type.

**Does a nested class access the outer's privates?** 
Yes and no. By language rules, a nested class is a member and therefore has access rights to the outer class's private members (e.g. private `static` variables or `typedef`s). However, because there is no implicit instance, it cannot read an outer object's private non-static data unless you explicitly pass it an outer object reference to read from.
:::
