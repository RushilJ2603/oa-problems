# The `this` Pointer and `struct` versus `class`

Two final pieces complete the basic picture of how classes work: the `this` pointer that every member function carries, and the close relationship between `struct` and `class`.

## The `this` pointer

Every non-static member function receives a hidden pointer called **`this`**. It holds the memory address of the object the function was called on, allowing a member function to refer to "the current object" explicitly. 

### Mechanism and type

When you call `rect.area()`, how does the `area` function know to use `rect`'s data rather than another object's? 

The compiler achieves this by automatically passing the object's address as an implicit, invisible parameter to the function. Inside the non-static member functions of a class `Rectangle`, `this` is a pointer of type `Rectangle* const`. It is a constant pointer, meaning you cannot change *where* `this` points, but you can modify the object it points to.

::: keypoint
In Python, the current object is explicitly passed as the first parameter (conventionally named `self`) to every instance method. In C++, this mechanism is hidden: the compiler implicitly passes the object's address, and it is accessed via the keyword `this`.
:::

### Disambiguating names

The most common everyday use of `this` is to disambiguate a parameter whose name deliberately matches a data member's name.

```cpp
#include <iostream>

class Rectangle {
private:
    int length;
    int breadth;

public:
    // Parameters deliberately shadow the members' names
    Rectangle(int length, int breadth) {
        this->length = length;     // this->length is the member
        this->breadth = breadth;   // bare length is the parameter
    }

    int area() { return length * breadth; }
};
```

Inside the constructor, the parameter `length` shadows the member `length`. Writing `this->length = length` resolves the clash: `this->length` names the *member* (reached through the object's address), while the bare `length` is the *parameter*.

### Method chaining (returning `*this`)

Another critical use for the `this` pointer is to enable **method chaining**, where multiple member functions are called in a single continuous sequence, such as `obj.setA().setB()`. 

To support this, a function must return a reference to the current object. Since `this` is a pointer to the object, dereferencing it as `*this` yields the object itself.

```cpp
#include <iostream>

class TextFormatter {
private:
    bool bold = false;
    bool italic = false;

public:
    // Returning a reference to the current object
    TextFormatter& setBold() {
        bold = true;
        return *this;
    }

    TextFormatter& setItalic() {
        italic = true;
        return *this;
    }

    void print() {
        std::cout << "Formatting: " 
                  << (bold ? "Bold " : "") 
                  << (italic ? "Italic" : "") 
                  << "\n";
    }
};

int main() {
    TextFormatter formatter;
    
    // Method chaining: setBold() returns the object, 
    // which then immediately receives the setItalic() call
    formatter.setBold().setItalic();
    
    formatter.print();
    return 0;
}
```

::: interview
Method chaining is a common pattern for fluent interfaces and the Builder design pattern. Be ready to write setter functions that return `ClassType&` and end with `return *this;`.
:::

## `struct` versus `class`

A **`struct`** is functionally almost identical to a **`class`**. It is not limited to passive data; a `struct` may also have member functions, constructors, and access specifiers.

```cpp
#include <iostream>

struct Point {
    int x;
    int y;

    void display() {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

int main() {
    Point p{10, 20};  // Aggregate initialisation
    p.display();      // Outputs: (10, 20)
    return 0;
}
```

### The differences

There are exactly two technical differences between a `struct` and a `class`:

1. **Default access level**: In a `struct`, members are `public` by default. In a `class`, members are `private` by default.
2. **Default inheritance access**: When deriving from a `struct`, the inheritance is `public` by default. When deriving from a `class`, the inheritance is `private` by default.

```cpp
class Base {};

class MyClass : Base {
    // 1. Members are private by default
    int a; 
    
    // 2. Inherits Base privately by default
};

struct MyStruct : Base {
    // 1. Members are public by default
    int a; 
    
    // 2. Inherits Base publicly by default
};
```

### Convention

Because they are technically so similar, the difference in usage is primarily one of convention. 

::: keypoint
Use a `struct` for passive data aggregates where all members are logically public and there are no complex internal invariants to maintain. Use a `class` when encapsulation, data hiding, and maintaining state consistency are the point.
:::
