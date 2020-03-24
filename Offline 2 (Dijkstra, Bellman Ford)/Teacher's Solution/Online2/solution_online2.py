import heapq

INFINITY = 1000000

def print_path(previous, D, fout, state_map):
    if previous[D] == -1:
        print(state_map[D], end='', file=fout)
    else:
        print_path(previous, previous[D], fout, state_map)
        print(" -> ", state_map[D], end='', file=fout)

def print_result(dest_dist, previous, dest, state_map):
    fout = open("online2.output", "w")
    
    if dest_dist == INFINITY:
        print("Destination is unreachable", file=fout)
        return
    
    print(dest_dist, file=fout)
    print_path(previous, dest, fout, state_map)
    print(file=fout)


if __name__ == "__main__":
    fin = open("online2.input")
    N1, M1, N2, M2 = map(int, fin.readline().strip().split())

    graph = [[] for i in range(N1 + N2)]
    distance = [INFINITY for i in range(N1 + N2)]
    previous = [-1 for i in range(N1 + N2)]
    visited = [False for i in range(N1 + N2)]
    ports1 = []
    ports2 = []
    Q = []
    city_map = dict()
    reverse_city_map = dict()

    count = 0
    for i in range(M1):
        c1, c2, d1 = fin.readline().strip().split()
        w = int(d1)
        if c1 not in city_map:
            city_map[c1] = count
            reverse_city_map[count] = c1 
            count += 1
        if c2 not in city_map:
            city_map[c2] = count
            reverse_city_map[count] = c2 
            count += 1
        u = city_map[c1]
        v = city_map[c2]

        graph[u].append((v, w))
        graph[v].append((u, w))
    for i in range(M2):
        c3, c4, d2 = fin.readline().strip().split()
        w = int(d2)
        if c3 not in city_map:
            city_map[c3] = count
            reverse_city_map[count] = c3 
            count += 1
        if c4 not in city_map:
            city_map[c4] = count
            reverse_city_map[count] = c4 
            count += 1
        u = city_map[c3]
        v = city_map[c4]

        graph[u].append((v, w))
        graph[v].append((u, w))

    p1 = int(fin.readline().strip())
    for i in range(p1):
        pt, tt = fin.readline().strip().split()
        ports1.append((pt, int(tt)))
    
    p2 = int(fin.readline().strip())
    for i in range(p2):
        pd, td = fin.readline().strip().split()
        ports2.append((pd, int(td)))


    C1, C2 = fin.readline().strip().split()
    S, D = city_map[C1], city_map[C2]

    for pt, tt in ports1:
        for pd, td in ports2:
            u = city_map[pt]
            v = city_map[pd]
            graph[u].append((v, tt + td))
            graph[v].append((u, tt + td))
            
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
    
    print_result(distance[D], previous, D, reverse_city_map)