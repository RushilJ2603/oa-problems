import sys

def solve(supplier_stock, orders):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    stock = [int(data[i]) for i in range(1, n + 1)]
    orders = int(data[n + 1])
    print(solve(stock, orders))

if __name__ == "__main__":
    main()
