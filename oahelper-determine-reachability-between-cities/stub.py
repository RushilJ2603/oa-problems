import sys

class TrainLine:
    def __init__(self, lineName, stations):
        self.lineName = lineName
        self.stations = stations

def canTravel(trainLines, queries):
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    it = iter(input_data)
    numLines = int(next(it))
    trainLines = []
    for _ in range(numLines):
        lineName = next(it)
        numStations = int(next(it))
        stations = [next(it) for _ in range(numStations)]
        trainLines.append(TrainLine(lineName, stations))
    
    numQueries = int(next(it))
    queries = []
    for _ in range(numQueries):
        queries.append([next(it), next(it)])
    
    results = canTravel(trainLines, queries)
    print(" ".join("true" if r else "false" for r in results))

if __name__ == '__main__':
    main()
