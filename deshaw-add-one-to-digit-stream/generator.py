import sys
import random

seed = int(sys.argv[1])
size = int(sys.argv[2])
random.seed(seed)

length = max(1, min(size, 1000000))
if length == 1:
    sys.stdout.write(str(random.randint(0, 9)) + "\n")
else:
    # first digit 1..9 (no leading zero), rest 0..9; bias some runs toward trailing 9s to exercise carry
    first = str(random.randint(1, 9))
    if random.random() < 0.35:
        # end with a run of 9s
        run = random.randint(1, length - 1)
        mid = "".join(random.choice("0123456789") for _ in range(length - 1 - run))
        rest = mid + "9" * run
    else:
        rest = "".join(random.choice("0123456789") for _ in range(length - 1))
    sys.stdout.write(first + rest + "\n")
