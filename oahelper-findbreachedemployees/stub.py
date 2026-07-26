import sys

def solve(modified_units, access_rights):
    # WRITE YOUR CODE HERE
    return [-1]

def main():
    data = sys.stdin.read().split()
    if not data: return
    p = 0
    k = int(data[p]); p += 1
    modified = [int(data[p+i]) for i in range(k)]; p += k
    n = int(data[p]); p += 1
    access = data[p:p+n]
    for x in solve(modified, access):
        print(x)

if __name__ == "__main__":
    main()
