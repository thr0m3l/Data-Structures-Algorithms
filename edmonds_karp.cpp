#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int INF = numeric_limits<int>::max();
int NULL_VALUE = -1;

class edge{
    public:
    int v, c, f;
    edge(int v, int c, int f){
        this->v = v; 
        this->c = c;
        this->f = f;
    }
    
};

class graph {
    int nVertices;
    vector<edge> *adjList;
    public:
    vector<int> path;
    graph(int n){
        nVertices = n;
        adjList = new vector<edge> [nVertices];
    }

    void addEdge(int u, int v, int c){
        edge e(v, c, 0);
        adjList[u].push_back(e);
    }

    edge* searchEdge(int u, int v){
        for(auto itr = adjList[u].begin(); itr != adjList[u].end(); ++itr){
            if (itr->v == v){
                return &(*itr);
            }
        }
        return nullptr;
    }

    graph residual_network(){
        //generates residual network
        graph residual(this->nVertices);

        for(int u = 0; u < nVertices; ++u){
            for(edge e : adjList[u]){
                if (e.f == 0){
                    residual.addEdge(u, e.v, e.c);
                } else if (e.f < e.c) {
                    residual.addEdge(u, e.v, e.c - e.f);
                    residual.addEdge(e.v, u, e.f);
                } else if (e.f == e.c){
                    residual.addEdge(e.v, u, e.f);
                }
            }
        }

        return residual;
    }

    int bfs(int src, int dest){
        vector<int> parent(nVertices, -1);
        vector<bool> visited(nVertices, false);
        queue<int> q;
        path.clear();
        int cf = INF;

        //Good ol' BFS
        q.push(src);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto e : adjList[u]){
                if (visited[e.v])
                    continue;
                parent[e.v] = u;
                q.push(e.v);
                if (e.v == dest)
                    break;
            }
            visited[u] = true;
        }        
        //no augmenting path
        if (parent[dest] == -1){
            return INF;
        }
        //constructs augmenting path, if there's one
        int curr = dest;
        while(curr != src){
            path.push_back(curr);
            curr = parent[curr];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        //calculates min capacity of augmenting path
        for(int i = 1; i < path.size(); ++i){
            edge *e = searchEdge(path[i-1], path[i]);
            cf = min(cf, e->c);
        }
        return cf;
    }

    void edmonds_karp(int s, int t){
        while(true){
            graph residual = residual_network();
            int cf = residual.bfs(s, t);
            this->path = residual.path;
            if (cf == INF)
                break;
            for(int i = 1; i < path.size(); ++i){
                edge *e = searchEdge(path[i-1], path[i]);
                if (e == nullptr){
                    edge *e1 = searchEdge(path[i], path[i-1]);
                    e1->f -= cf;
                } else {
                    e->f += cf;
                }
            }
        }

        //Calculates the Max Flow
        int max_flow = 0;
        for(auto e : adjList[s]){
            max_flow += e.f;
        }
        cout<<"Max Flow = "<<max_flow<<endl;
    }

    void printGraph(){
        for(int i = 0; i < nVertices; ++i){
            cout<<i<<" : ";
            for(auto e : adjList[i]){
                cout<<"("<<e.v<<", "<<e.f<<", "<<e.c<<"), ";
            }
            cout<<endl;
        }
    }
};

int main(){
    int E, V;
    cin>>V>>E;
    graph g(V);
    for(int i = 0; i < E; ++i){
        int u, v, c;
        cin>>u>>v>>c;
        g.addEdge(u, v, c);
    }
    g.edmonds_karp(0, 5);
    g.printGraph();
}