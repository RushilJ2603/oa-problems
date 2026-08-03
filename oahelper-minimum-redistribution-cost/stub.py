import sys

def calculateMinimumRedistributionCost(products):
    # WRITE YOUR CODE HERE
    return 0

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    n = int(data[0])
    products = [int(x) for x in data[1:1 + n]]
    print(calculateMinimumRedistributionCost(products))

if __name__ == "__main__":
    main()
