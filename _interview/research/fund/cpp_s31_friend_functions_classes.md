# Friend Functions and Friend Classes

The core principle of encapsulation dictates that a class's `private` and `protected` members are inaccessible to the outside world. However, C++ provides a controlled loophole: the **`friend`** keyword. A class can explicitly grant specific external functions or entirely different classes full access to its internal state. 

::: definition
A **friend** is a function or class that is explicitly granted access to another class's `private` and `protected` members. Friendship is always granted by the class that holds the data, never taken by the outside entity.
:::

::: keypoint
In Python, there is no direct equivalent to `friend`; access control relies on convention (like prefixing with `_`) rather than compiler enforcement.
:::

## Friend functions

A **friend function** is a free function (not a member of the class) that has been granted access to the class's internals. 

To make a function a friend, you place the `friend` keyword followed by the function declaration anywhere inside the class definition. Access modifiers (`public`, `private`) do not affect `friend` declarations.

```cpp
#include <iostream>

class Sensor {
private:
    int rawValue;

public:
    Sensor(int val) : rawValue(val) {}

    // Grant access to this specific free function
    friend void calibrateSensor(Sensor& s);
};

// This is a normal free function, not a member of Sensor.
// Notice there is no 'Sensor::' prefix.
void calibrateSensor(Sensor& s) {
    // Accessing private member directly
    s.rawValue = 0; 
    std::cout << "Sensor calibrated to 0.\n";
}

int main() {
    Sensor mySensor(42);
    calibrateSensor(mySensor); // Call like a normal function
    return 0;
}
```

### The canonical use case: operator overloading

If `friend` allows external functions to breach encapsulation, when is it the right tool versus simply writing a public getter or setter? 

The most common, idiomatic reason to use friend functions is for overloading symmetric binary operators (like `operator+`) and stream insertion/extraction operators (`operator<<` and `operator>>`). 

When you overload `operator<<` to print your custom object, the left-hand operand is an `std::ostream` (like `std::cout`). Because you cannot modify the standard library's `std::ostream` class to add a member function for your custom type, the operator *must* be implemented as a free function. If this free function needs to print private data, it must be declared as a friend.

```cpp
#include <iostream>

class Matrix {
private:
    int grid[2][2];

public:
    Matrix(int a, int b, int c, int d) {
        grid[0][0] = a; grid[0][1] = b;
        grid[1][0] = c; grid[1][1] = d;
    }

    // Friend declaration for the stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

// Implementation of the friend free function
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    // Directly accessing the private grid array
    os << "[" << m.grid[0][0] << ", " << m.grid[0][1] << "]\n"
       << "[" << m.grid[1][0] << ", " << m.grid[1][1] << "]";
    return os;
}

int main() {
    Matrix m(1, 2, 3, 4);
    std::cout << m << "\n";
    return 0;
}
```

## Friend classes

Sometimes, an entire separate class needs deep access to another class's internals. You can declare a whole class as a friend. This means every member function of the friend class can access the private and protected members of the granting class.

A classic example is the **Container/Iterator** pattern. An iterator object needs intimate knowledge of the container's internal data structure (like raw pointers or node links) to traverse it efficiently, but these internals should be hidden from the general public.

```cpp
#include <iostream>

class LinkedList; // Forward declaration

class Iterator {
private:
    LinkedList* list;
    int currentIndex;

public:
    Iterator(LinkedList* l) : list(l), currentIndex(0) {}
    void printNext(); // Needs to access LinkedList internals
};

class LinkedList {
private:
    int data[5] = {10, 20, 30, 40, 50}; // Simplified array for example
    
    // Grant the entire Iterator class access to private members
    friend class Iterator; 
};

// Implementation must come after LinkedList is fully defined
void Iterator::printNext() {
    // Accessing the private 'data' array of LinkedList
    if (currentIndex < 5) {
        std::cout << list->data[currentIndex++] << " ";
    }
}

int main() {
    LinkedList list;
    Iterator it(&list);
    
    it.printNext(); // Outputs 10
    it.printNext(); // Outputs 20
    return 0;
}
```

## The three properties of friendship

C++ restricts friendship with strict, unbending rules to prevent runaway encapsulation leaks. Think of granting friendship like giving someone a key to your house. 

![Friendship is one-way: granting B access to A does not grant A access to B.](assets/s31_friendship.png)

1. **Friendship is not mutual.** If you give Bob a key to your house, it does not mean you have a key to Bob's house. If class `A` declares class `B` as a friend, `B` can access `A`'s private members. `A` cannot access `B`'s private members unless `B` explicitly reciprocates.
2. **Friendship is not transitive.** If Bob has a key to your house, and Charlie is Bob's friend, Charlie cannot use Bob's key to enter your house. If `A` is a friend of `B`, and `B` is a friend of `C`, `A` does not automatically get access to `C`.
3. **Friendship is not inherited.** Bob's children do not inherit the right to use the key to your house. If a base class has a friend, that friend does not automatically get access to the derived class's private members. Similarly, classes deriving from a friend do not inherit the friendship privilege.

::: interview
**"Does `friend` break encapsulation?"**
This is a trap question. The correct answer is **no**. Because friendship must be explicitly granted *inside* the class definition itself, the class author retains total control over who can access the data. A true breach of encapsulation would be if an external entity could unilaterally declare itself a friend, which C++ forbids.
:::

::: interview
**"Is friendship inherited?"**
Expect this in quick-fire rounds. The answer is **no**. Friendship is strictly granted to the specific class or function named, and does not pass down to derived classes.
:::
