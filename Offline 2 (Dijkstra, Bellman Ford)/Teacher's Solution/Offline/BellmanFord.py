INFINITY = 1000000


def print_path(previous, D, fout):
    if previous[D] == -1:
        print(D, end='', file=fout)
    else:
        print_path(previous, previous[D], fout)
        print(" -> ", D, end='', file=fout)

def print_result(negative_cycle, dest_dist, previous, dest):
    fout = open("bf.output", "w")
    if negative_cycle:
        print("The graph contains negative cycle", file=fout)
        return
    
    if dest_dist == INFINITY:
        print("Destination is unreachable", file=fout)
        return
    
    print(dest_dist, file=fout)
    print_path(previous, dest, fout)
    print(file=fout)



if __name__ == "__main__":
    fin = open("directed.input")
    N, M = map(int, fin.readline().strip().split())

    graph = []
    distance = [INFINITY for i in range(N)]
    previous = [-1 for i in range(N)]

    for i in range(M):
        u, v, w = map(int, fin.readline().strip().split())
        graph.append((u, v, w))

    S, D = map(int, fin.readline().strip().split())

    distance[S] = 0

    for i in range(1, N):
        isUpdated = False
        for u, v, w in graph:
            if distance[u] + w < distance[v]:
                distance[v] = distance[u] + w
                previous[v] = u
                isUpdated = True
        if not isUpdated:
            print(f"Algorithm converges in {i} iteretion")
            break

    negative_cycle = False
    for u, v, w in graph:
        if distance[u] + w < distance[v]:
            negative_cycle = True
            break

    print_result(negative_cycle, distance[D], previous, D)