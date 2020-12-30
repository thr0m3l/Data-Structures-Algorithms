import heapq
from sys import argv

INFINITY = 1000000

def print_path(previous, D, fout, state_map):
    if previous[D] == -1:
        print(state_map[D], end='', file=fout)
    else:
        print_path(previous, previous[D], fout, state_map)
        print(" -> ", state_map[D], end='', file=fout)

def print_result(dest_dist, previous, dest, state_map):
    fout = open("online1.output", "w")
    
    if dest_dist == INFINITY:
        print("Destination is unreachable", file=fout)
        return
    
    print(dest_dist, file=fout)
    print_path(previous, dest, fout, state_map)
    print(file=fout)



if __name__ == "__main__":
    filename = argv[1] if len(argv) == 2 else "online1.input"
    fin = open(filename)
    N, M = map(int, fin.readline().strip().split())

    graph = [[] for i in range(N)]
    distance = [INFINITY for i in range(N)]
    previous = [-1 for i in range(N)]
    visited = [False for i in range(N)]
    Q = []
    state_map = dict()
    reverse_state_map = dict()

    for i in range(N):
        s, q = fin.readline().strip().split()
        q = int(q)
        state_map[s] = (i, q)
        reverse_state_map[i] = s

    for i in range(M):
        u, v, w = fin.readline().strip().split()
        u, qu = state_map[u]
        v, qv = state_map[v]
        w = int(w)
        graph[u].append((v, w + qv))
        graph[v].append((u, w + qu))


    S, D = fin.readline().strip().split()
    S, _ = state_map[S]
    D, _ = state_map[D]
    distance[S] = 0

    heapq.heappush(Q, (distance[S], S))

    while len(Q):
        dist_u, u = heapq.heappop(Q)
        if u == D:
            break
        if not visited[u]:
            visited[u] = True
            for v, w in graph[u]:
                assert dist_u == distance[u]

                if distance[u] + w < distance[v]:
                    distance[v] = distance[u] + w
                    heapq.heappush(Q, (distance[v], v))
                    previous[v] = u
    
    print_result(distance[D], previous, D, reverse_state_map)