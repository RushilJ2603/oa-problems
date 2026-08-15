import sys

def getRich(initialEnergy, energy, coins):
    # WRITE YOUR CODE HERE
    return 0

def main():
    input_data = sys.stdin.read().split()
    if not input_data: return
    initialEnergy = int(input_data[0])
    n = int(input_data[1])
    energy = [int(x) for x in input_data[2:2+n]]
    idx = 2 + n
    m = int(input_data[idx])
    coins = [int(x) for x in input_data[idx+1:idx+1+m]]
    res = getRich(initialEnergy, energy, coins)
    print(res)

if __name__ == '__main__':
    main()
