import heapq

INFINITY = 1000000

def print_path(previous, D, fout):
    if previous[D] == -1:
        print(D, end='', file=fout)
    else:
        print_path(previous, previous[D], fout)
        print(" -> ", D, end='', file=fout)

def print_result(dest_dist, previous, dest):
    fout = open("dijkstra.output", "w")
    
    if dest_dist == INFINITY:
        print("Destination is unreachable", file=fout)
        return
    
    print(dest_dist, file=fout)
    print_path(previous, dest, fout)
    print(file=fout)


if __name__ == "__main__":
    fin = open("directed.input")
    N, M = map(int, fin.readline().strip().split())

    graph = [[] for i in range(N)]
    distance = [INFINITY for i in range(N)]
    previous = [-1 for i in range(N)]
    visited = [False for i in range(N)]
    Q = []

    for i in range(M):
        u, v, w = map(int, fin.readline().strip().split())
        graph[u].append((v, abs(w)))


    S, D = map(int, fin.readline().strip().split())
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
    
    print_result(distance[D], previous, D)