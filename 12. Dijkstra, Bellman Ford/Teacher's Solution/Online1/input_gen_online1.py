import random

ENSURE_CONNECTIVITY = False

def ensure_connectivity(N, M, graph):
    if N > 50:
        nodes_in_path = 50
    else:
        nodes_in_path = int(N * 0.8)
    nodes = [node for node in range(N)]
    random.shuffle(nodes)
    nodes = nodes[:nodes_in_path]
    for i in range(nodes_in_path - 1):
        j = i + 1
        u = nodes[i]
        v = nodes[j]
        for x, _ in graph[u]:
            if x == v:
                break
        else:
            graph[u].append((v, random.randint(1, 250)))
    return (nodes[0], nodes[-1])
  

if __name__ == "__main__":
    fin = open("places.txt")

    places = [place.strip() for place in fin.readlines()]

    random.shuffle(places)

    N = int(input("Enter number of states: "))
    N = N if N <= len(places) else len(places)
    M = int(input("Enter number of roads: "))
    density = M / (N * (N - 1) / 2) * 100
    print(density)

    quarantine = []

    for i in range(N):
        quarantine.append((places[i], random.randint(1, 100)))


    graph = [[] for i in range(N)]


    count = 0
    for u in range(N - 1):
        for v in range(u + 1, N):
            edge_probability = random.randint(0, 100)
            if edge_probability <= density:
                w = random.randint(1, 1000)
                q = random.randint(0, 1)
                if q == 0:
                    graph[u].append((v, w))
                else:
                    graph[v].append((u, w))
                count += 1
                    
    print(count)

  
    S, D = random.randint(0, N - 1), random.randint(0, N - 1)

    if ENSURE_CONNECTIVITY:
        S, D = ensure_connectivity(N, M, graph)


    edge_count = 0
    for u in range(N):
        for v, w in graph[u]:
            edge_count += 1

    fout = open("online1.input.txt", "w")
    print(N, edge_count, file=fout)
    for place, q in quarantine:
        print(place, q, file=fout)
    for u in range(N):
        for v, w in graph[u]:
            print(places[u], places[v], w, file=fout)
    print(places[S], places[D], file=fout)

