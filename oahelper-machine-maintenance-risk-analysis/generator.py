#!/usr/bin/env python3
import random
import sys

TYPES = ["PRESS", "CUTTER", "WELDER", "PACKER"]
MTYPES = ["PREVENTIVE", "CORRECTIVE", "REPAIR"]
SEVS = ["LOW", "MEDIUM", "HIGH", "SEVERE"]

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Hit constraint bounds at large size for TLE/overflow discrimination.
    if size >= 1000:
        nM = 100000
        nP = 4
        nS = 200000
        nL = 50000
        nF = 50000
        ref = 1000000
    else:
        nM = max(2, min(size, 2000))
        nP = min(4, max(1, nM))
        nS = max(0, min(200000, size * 3))
        nL = max(0, min(200000, size * 2))
        nF = max(0, min(200000, size * 2))
        ref = random.randint(1, max(1, min(1000000, size * 100 + 50)))

    types_used = TYPES[:nP]
    out = []
    out.append(str(ref))
    out.append(str(nM))
    out.append(str(nP))
    out.append(str(nS))
    out.append(str(nL))
    out.append(str(nF))

    for i in range(nM):
        out.append(f"M{i+1} Mach{i+1} {types_used[i % len(types_used)]}")

    for t in types_used:
        out.append(f"{t} {random.randint(10, 200)} {random.randint(10, 200)}")

    for i in range(nS):
        mid = "X9" if ((i + seed) % 37 == 0) else f"M{((i + seed) % nM) + 1}"
        day = ((i * seed) % ref) + 1 if (i % 11) else -1
        temp = (i * 7 + seed) % 201
        vib = (i * 13 + seed) % 201
        if i % 19 == 0:
            temp = -1
        out.append(f"R{i} {mid} {day} {temp} {vib}")

    for i in range(nL):
        mid = "X9" if ((i + seed) % 41 == 0) else f"M{((i + seed) % nM) + 1}"
        day = ((i * seed) % ref) + 1 if (i % 9) else 0
        mt = MTYPES[(i + seed) % len(MTYPES)]
        out.append(f"MT{i} {mid} {day} {mt}")

    for i in range(nF):
        mid = "X9" if ((i + seed) % 43 == 0) else f"M{((i + seed) % nM) + 1}"
        day = ((i * seed) % ref) + 1 if (i % 7) else ref + 1
        sev = SEVS[(i + seed) % len(SEVS)]
        out.append(f"F{i} {mid} {day} {sev}")

    sys.stdout.write("\n".join(out) + "\n")

if __name__ == "__main__":
    main()
