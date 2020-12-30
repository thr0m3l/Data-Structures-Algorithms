import random

ENSURE_CONNECTIVITY = False
NEGATIVE_EDGE_PROBABILITY = 10

def get_weight(negative_probabilty):
    p = random.randint(1, 100)
    if p <= negative_probabilty:
        return random.randint(-500, -1)
    else:
        return random.randint(0, 1000)


def ensure_connectivity(N, M, graph):
    if N > 50:
        nodes_in_path = 50
    else:
        nodes_in_path = int(N * 0.8)
    nodes = [node for node in range(N)]
    random.shuffle(nodes)
    nodes = nodes[:nodes_in_path]
    for i in range(nodes_in_path - 1):
        for j in range(i + 1, nodes_in_path):
            u = nodes[i]
            v = nodes[j]
            for x, y in graph[u]:
                if x == v:
                    break
            else:
                graph[u].append((v, get_weight(NEGATIVE_EDGE_PROBABILITY)))
    return (nodes[0], nodes[-1])
       

if __name__ == "__main__":
    N = int(input("Enter number of nodes: "))
    M = int(input("Enter number of edges: "))
    density = M / (N * (N - 1) / 2) * 100
    fout = open("directed.input", "w")


    graph = [[] for i in range(N)]


    edge_count = 0
    for u in range(N - 1):
        for v in range(u + 1, N):
            edge_probability = random.randint(0, 100)
            if edge_probability <= density:
                w = get_weight(NEGATIVE_EDGE_PROBABILITY)
                q = random.randint(0, 1)
                if q == 0:
                    graph[u].append((v, w))
                else:
                    graph[v].append((u, w))
                    

  
    S, D = random.randint(0, N - 1), random.randint(0, N - 1)

    if ENSURE_CONNECTIVITY:
        S, D = ensure_connectivity(N, M, graph)


    for u in range(N):
        for v, w in graph[u]:
            edge_count += 1

    print(N, edge_count, file=fout)
    for u in range(N):
        for v, w in graph[u]:
            print(u, v, w, file=fout)
    print(S, D, file=fout)