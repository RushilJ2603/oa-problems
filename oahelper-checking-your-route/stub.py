import sys

def classifyEdges(g_nodes, g_from, g_to, g_weight):
    # WRITE YOUR CODE HERE
    return []

def main():
    input_data = sys.stdin.read().split()
    if not input_data: return
    g_nodes = int(input_data[0])
    g_edges = int(input_data[1])
    g_from, g_to, g_weight = [], [], []
    idx = 2
    for _ in range(g_edges):
        g_from.append(int(input_data[idx]))
        g_to.append(int(input_data[idx+1]))
        g_weight.append(int(input_data[idx+2]))
        idx += 3
    res = classifyEdges(g_nodes, g_from, g_to, g_weight)
    for s in res: print(s)

if __name__ == '__main__':
    main()
