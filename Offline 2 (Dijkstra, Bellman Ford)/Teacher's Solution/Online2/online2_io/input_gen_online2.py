import random

ENSURE_CONNECTIVITY = False

random.seed(2)

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
  

def gen_graph():
    finT = open("rplaces1.txt")
    finD = open("rplaces2.txt")
    placesT = [place.strip() for place in finT.readlines()]
    placesD = [place.strip() for place in finD.readlines()]
    random.shuffle(placesT)
    random.shuffle(placesD)

    S1, R1, S2, R2 = map(int, input("S1 R1 S2 R2: ").strip().split())
    S1 = S1 if S1 <= len(placesT) else len(placesT)
    S2 = S2 if S2 <= len(placesD) else len(placesD)

    density1 = R1 / (S1 * (S1 - 1) / 2) * 100
    density2 = R2 / (S2 * (S2 - 1) / 2) * 100

    graphT = [[] for i in range(S1)]

    print(placesT[:S1])
    print(placesD[:S2])

    count = 0
    for u in range(S1 - 1):
        for v in range(u + 1, S1):
            edge_probability = random.randint(0, 100)
            if edge_probability <= density1:
                w = random.randint(1, 1000)
                q = random.randint(0, 1)
                if q == 0:
                    graphT[u].append((v, w))
                else:
                    graphT[v].append((u, w))
                count += 1
                    
    print(count)

    graphD = [[] for i in range(S2)]


    count = 0
    for u in range(S2 - 1):
        for v in range(u + 1, S2):
            edge_probability = random.randint(0, 100)
            if edge_probability <= density2:
                w = random.randint(1, 1000)
                q = random.randint(0, 1)
                if q == 0:
                    graphD[u].append((v, w))
                else:
                    graphD[v].append((u, w))
                count += 1
                    
    print(count)

    P1, P2 = map(int, input("P1 P2: ").strip().split())

    P1 = min(P1, S1, 10)
    P2 = min(P2, S2, 10)

    random.shuffle(placesD)
    random.shuffle(placesT)

    print(placesT[:P1])
    print(placesD[:P2])

    C1, C2 = random.randint(P1, S1), random.randint(P2, S2)

    print(placesT[C1], placesD[C2])

    edge_count = 0
    for u in range(S1):
        for v, w in graphT[u]:
            edge_count += 1
    
    ec = 0
    for u in range(S2):
        for v, w in graphD[u]:
            ec += 1

    fout = open("online2.input", "w")
    print(S1, edge_count, S2, ec, file=fout)
    for u in range(S1):
        for v, w in graphT[u]:
            print(placesT[u], placesT[v], w, file=fout)
    for u in range(S2):
        for v, w in graphD[u]:
            print(placesD[u], placesD[v], w, file=fout)

    print(P1, file=fout)
    for i in range(P1):
        print(placesT[i], random.randint(1, 500), file=fout)

    print(P2, file=fout)
    for i in range(P2):
        print(placesD[i], random.randint(1, 500), file=fout)

    print(placesT[C1], placesD[C2], file=fout)



if __name__ == "__main__":

    gen_graph()
    

  
    # S, D = random.randint(0, N - 1), random.randint(0, N - 1)

    # if ENSURE_CONNECTIVITY:
    #     S, D = ensure_connectivity(N, M, graph)


    # edge_count = 0
    # for u in range(N):
    #     for v, w in graph[u]:
    #         edge_count += 1

    # fout = open("online1.input.txt", "w")
    # print(N, edge_count, file=fout)
    # for u in range(N):
    #     for v, w in graph[u]:
    #         print(places[u], places[v], w, file=fout)
    # print(places[S], places[D], file=fout)

