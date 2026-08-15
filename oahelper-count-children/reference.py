import sys

def fib(n):
    if n == 0:
        return (0, 1)
    p = fib(n >> 1)
    a = p[0]
    b = p[1]
    c = a * ((b << 1) - a)
    d = a * a + b * b
    if n & 1:
        return (d, c + d)
    return (c, d)

def countChildren(n: int, i: int) -> int:
    if n < 1 or i < 1 or i > n:
        return 0
    k = n - i + 1
    return fib(k)[0]

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    n = int(input_data[0])
    i = int(input_data[1])
    
    print(countChildren(n, i))

if __name__ == '__main__':
    main()
