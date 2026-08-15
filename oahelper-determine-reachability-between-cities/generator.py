import sys
import random
import string

def get_random_string(length):
    return ''.join(random.choices(string.ascii_letters, k=length))

def generate(seed, size):
    random.seed(seed)
    
    # Scale parameters
    # size is roughly between 1 and 100, where 100 is max scale.
    # Max sum of stations is 2 * 10^5.
    # Max Q is 2 * 10^5.
    if size >= 90:
        L = 10000
        max_total_stations = 200000
        Q = 200000
    else:
        L = max(1, int(10000 * size / 100))
        max_total_stations = max(2, int(200000 * size / 100))
        Q = max(1, int(200000 * size / 100))
        
    cities = [get_random_string(5) for _ in range(max_total_stations // 2 + 1)]
    
    total_stations = 0
    lines = []
    
    # ensure we don't exceed max_total_stations
    remaining_stations = max_total_stations
    
    for i in range(L):
        lineName = "Line_" + get_random_string(5) + str(i)
        
        # At least 1 station per line, max 1000
        # Average should distribute remaining_stations over remaining L
        avg_stations = remaining_stations // (L - i)
        k = random.randint(1, min(1000, max(1, avg_stations * 2)))
        k = min(k, remaining_stations - (L - i - 1))
        k = max(1, k)
        
        stations = random.choices(cities, k=k)
        lines.append((lineName, k, stations))
        
        remaining_stations -= k
        total_stations += k
        if remaining_stations <= 0:
            break
            
    out = []
    out.append(str(len(lines)))
    for lineName, k, stations in lines:
        out.append(f"{lineName} {k} " + " ".join(stations))
        
    out.append(str(Q))
    for _ in range(Q):
        if random.random() < 0.5:
            # pick random cities from the pool
            u = random.choice(cities)
            v = random.choice(cities)
        else:
            # pick completely random strings to test non-existent cities
            u = get_random_string(5)
            v = get_random_string(5)
        out.append(f"{u} {v}")
        
    return "\n".join(out) + "\n"

if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit(1)
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    print(generate(seed, size), end="")
