# Data Hiding: Access Specifiers, Accessors, and Mutators

::: definition
**Encapsulation** is the physical bundling of data and functions into a single class. **Data hiding** is the security policy applied to that bundle, restricting who can access or modify its internal state.
:::

Data hiding is achieved using **access specifiers**. It is the mechanism that ensures an object's internal state remains valid, and that its implementation details can change without breaking the code that uses it.

## Access specifiers: `public`, `private`, and `protected`

C++ provides three access specifiers to control visibility. They appear as labels followed by a colon (`:`), and they apply to all members declared below them until the next specifier or the end of the class.

::: keypoint
By default, all members of a `class` are `private` unless specified otherwise. (In a `struct`, they are `public` by default).
:::

Here is the syntax showing all three specifiers:

```cpp
#include <string>

class Employee {
private:
    // Reachable ONLY by member functions of Employee.
    // Always used for internal state and helper functions.
    int salary;

protected:
    // Reachable by Employee and any classes derived from it.
    int employeeId;

public:
    // Reachable by anyone (outside code, other classes).
    // Forms the interface of the class.
    std::string name;
    
    void setSalary(int newSalary) {
        // A public member function can access private members
        salary = newSalary;
    }
};
```

- **`private`**: The strictest level. Members are accessible only from within the class's own methods. This is the default and should be used for almost all data members.
- **`public`**: The most permissive level. Members are accessible from anywhere. This should be reserved for the class's interface (the methods it wants others to call).
- **`protected`**: A middle ground used in inheritance. Protected members act like `private` to the outside world, but act like `public` to derived child classes. (The mechanics of inheritance are covered in a later section).

## Why hide data?

If all data were `public`, external code could manipulate it directly. This leads to three major problems:

1. **Broken invariants**: An *invariant* is a rule that must always be true for the object to be valid. If a `BankAccount` exposes its balance publicly, external code could write `account.balance = -999;`, bypassing the rules of banking.
2. **Coupling to internals**: If external code reads a public raw array directly, you can never change your internal implementation to use a `std::vector` later, because doing so would break all external code that depends on the array.
3. **No access tracking**: If a variable is changed directly from anywhere in the codebase, you cannot easily set a breakpoint or add logging to see exactly when and where it is modified.

## Accessors and mutators (getters and setters)

When data is `private`, controlled access is provided through `public` member functions. 

An **accessor** (getter) retrieves the value of a member. It should be marked `const` at the end of its signature, which is a promise to the compiler that this function will not modify the object.
A **mutator** (setter) changes the value, providing a place to validate the new value or update related internal state.

```cpp
#include <iostream>

class Rectangle {
private:
    int length = 0;
    int breadth = 0;

public:
    // Mutators (setters) with validation
    void setLength(int l) {
        if (l >= 0) {
            length = l;
        } else {
            // Reject invalid state; could also throw an exception
            length = 0; 
        }
    }

    void setBreadth(int b) {
        if (b >= 0) {
            breadth = b;
        } else {
            breadth = 0;
        }
    }

    // Accessors (getters) marked 'const'
    int getLength() const {
        return length;
    }

    int getBreadth() const {
        return breadth;
    }
    
    int getArea() const {
        return length * breadth;
    }
};

int main() {
    Rectangle r;
    r.setLength(10);
    r.setBreadth(-5); // Rejected by the setter; stores 0 instead

    std::cout << "Length: " << r.getLength() << "\n";
    std::cout << "Area: " << r.getArea() << "\n";
    return 0;
}
```

### Read-only and read-write properties

By carefully choosing whether to provide a getter, a setter, or both, you can control exact permissions for different pieces of data:

- **Read-write**: Provide both `getX()` and `setX()`.
- **Read-only**: Provide only `getX()`. This is useful for data that is set once (like an ID) or computed internally.
- **Write-only**: Provide only `setX()`. This is rare, but might be used for things like passwords where you can set the hash but cannot read back the plaintext.

```cpp
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance = 0.0;

public:
    // Constructor (covered in detail later)
    BankAccount(std::string accNum) {
        accountNumber = accNum;
    }

    // Read-only property: no setter provided
    std::string getAccountNumber() const {
        return accountNumber;
    }

    // Controlled read-write: balance can only be changed via specific actions
    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }
};
```

::: keypoint
In Python, data hiding is merely a naming convention (e.g. `_variable`), but C++ enforces access control strictly at compile-time.
:::

::: interview
A classic interview question is asking for the difference between encapsulation and data hiding. Be precise: **encapsulation** is the mechanism of bundling data and behaviour into a single entity, while **data hiding** is the security benefit achieved by using access specifiers (like `private`). A class with entirely `public` members is encapsulated, but its data is not hidden.
:::
