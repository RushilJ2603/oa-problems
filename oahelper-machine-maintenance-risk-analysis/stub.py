import sys

def solve(ref, machines, profiles, sensors, logs, faults):
    # WRITE YOUR CODE HERE
    return "NA"

def main():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    p = 0
    def tok():
        nonlocal p
        v = data[p]; p += 1
        return v
    ref = int(tok())
    nM = int(tok()); nP = int(tok()); nS = int(tok()); nL = int(tok()); nF = int(tok())
    machines = []
    for _ in range(nM):
        machines.append((tok().decode(), tok().decode(), tok().decode()))
    profiles = []
    for _ in range(nP):
        profiles.append((tok().decode(), int(tok()), int(tok())))
    sensors = []
    for _ in range(nS):
        sensors.append((tok().decode(), tok().decode(), int(tok()), int(tok()), int(tok())))
    logs = []
    for _ in range(nL):
        logs.append((tok().decode(), tok().decode(), int(tok()), tok().decode()))
    faults = []
    for _ in range(nF):
        faults.append((tok().decode(), tok().decode(), int(tok()), tok().decode()))
    print(solve(ref, machines, profiles, sensors, logs, faults))

if __name__ == "__main__":
    main()
