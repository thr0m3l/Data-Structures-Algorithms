import random

ENSURE_CONNECTIVITY = False

random.seed(2)

def get_weight(limit):
    return random.randint(1, limit)

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
            for x, y, z in graph[u]:
                if x == v:
                    break
            else:
                graph[u].append((v, get_weight(1000000), get_weight(10000)))
    return (nodes[0], nodes[-1])
       

if __name__ == "__main__":
    N = int(input("Enter number of nodes: "))
    M = int(input("Enter number of edges: "))
    density = M / (N * (N - 1) / 2) * 100
    fout = open("online3.input", "w")


    graph = [[] for i in range(N)]


    edge_count = 0
    for u in range(N - 1):
        for v in range(u + 1, N):
            edge_probability = random.randint(0, 100)
            if edge_probability <= density:
                t = get_weight(1000000)
                d = get_weight(10000)
                q = random.randint(0, 1)
                if q == 0:
                    graph[u].append((v, t, d))
                else:
                    graph[v].append((u, t, d))
                    

  
    H1, H2, S, D = random.sample(range(0, N), 4)

    # if ENSURE_CONNECTIVITY:
    #     S, D = ensure_connectivity(N, M, graph)


    for u in range(N):
        for _, _, _ in graph[u]:
            edge_count += 1

    print(N, edge_count, file=fout)
    for u in range(N):
        for v, t, d in graph[u]:
            print(u, v, t, d, file=fout)
    print(H1, H2, file=fout)
    print(S, D, file=fout)