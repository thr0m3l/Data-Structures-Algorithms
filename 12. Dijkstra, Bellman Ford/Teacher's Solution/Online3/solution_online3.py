import heapq

INFINITY = 1000000

def print_path(previous, D, fout):
    if previous[D] == -1:
        print(D, end='', file=fout)
    else:
        print_path(previous, previous[D], fout)
        print(" -> ", D, end='', file=fout)

def print_result(dest_dist, previous, dest):
    fout = open("online3.output", "w")
    
    if dest_dist == INFINITY:
        print("Mission Impossible", file=fout)
        return
    
    print(dest_dist, file=fout)
    print_path(previous, dest, fout)
    print(file=fout)

def get_forbidden_nodes(previous, destination, fnodes):
    if previous[destination] == -1:
        fnodes.append(destination)
    else:
        get_forbidden_nodes(previous, previous[destination], fnodes)
        fnodes.append(destination)

if __name__ == "__main__":
    fin = open("online3.input")
    N, M = map(int, fin.readline().strip().split())

    graph = [[] for i in range(N)]
    graphD = [[] for i in range(N)]
    distance = [INFINITY for i in range(N)]
    previous = [-1 for i in range(N)]
    visited = [False for i in range(N)]
    Q = []

    for i in range(M):
        u, v, t, d = map(int, fin.readline().strip().split())
        graph[u].append((v, t))
        graphD[u].append((v, d))

        graph[v].append((u, t))
        graphD[v].append((u, d))


    H1, H2 = map(int, fin.readline().strip().split())
    S, D = map(int, fin.readline().strip().split())

    # finding the path of Zimbim
    distance[H1] = 0

    heapq.heappush(Q, (distance[H1], H1))

    while len(Q):
        dist_u, u = heapq.heappop(Q)
        if u == H2:
            break
        if not visited[u]:
            visited[u] = True
            for v, w in graph[u]:
                assert dist_u == distance[u]

                if distance[u] + w < distance[v]:
                    distance[v] = distance[u] + w
                    heapq.heappush(Q, (distance[v], v))
                    previous[v] = u
    
    fnodes = []
    if distance[H2] == INFINITY:
        fnodes.extend((H1, H2))
    else:
        get_forbidden_nodes(previous, H2, fnodes)
    print(fnodes)
    # finding path to Kallixiza
    Q.clear()
    distance = [INFINITY for i in range(N)]
    previous = [-1 for i in range(N)]
    visited = [False for i in range(N)]
    distance[S] = 0

    heapq.heappush(Q, (distance[S], S))

    while len(Q):
        dist_u, u = heapq.heappop(Q)
        if u == D:
            break
        if not visited[u]:
            visited[u] = True
            for v, w in graphD[u]:
                assert dist_u == distance[u]

                #avoiding forbidden nodes
                if u in fnodes or v in fnodes:
                    continue
                
                if distance[u] + w < distance[v]:
                    distance[v] = distance[u] + w
                    heapq.heappush(Q, (distance[v], v))
                    previous[v] = u
    
    print_result(distance[D], previous, D)