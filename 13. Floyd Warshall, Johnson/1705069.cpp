#include<iostream>
#include<vector>
#include<queue>
using namespace std;

double INF = 100000;
int NULL_VALUE = -1;

class Edge{
public:
    int v;
    double w;

    Edge(int v, double w){
        this->v = v;
        this->w = w;
    }

    void setV(int v){
        this->v = v;
    }
    
    void setW(double w){
        this->w = w;
    }

    int getV(){
        return v; 
    }

    double getW(){
        return w;
    }
};

class Graph{
    
    int nVertices, nEdges;
    vector<Edge> *list;
    double **distanceMatrix;
    int **parentMatrix;
    int *h;

public:
    Graph(){

    }

    void setnVertices(int n){
        this->nVertices = n;
        this->nEdges = 0;

        list = new vector<Edge>[nVertices];
        
        distanceMatrix = new double*[nVertices];
        for(int i = 0; i < nVertices; ++i){
            distanceMatrix[i] = new double[nVertices];

            for(int j = 0; j < nVertices; ++j){
                distanceMatrix[i][j] = INF;
            }
        }

        parentMatrix = new int*[nVertices];
        for(int i = 0; i < nVertices; ++i){
            parentMatrix[i] = new int[nVertices];

            for(int j = 0; j < nVertices; ++j){
                parentMatrix[i][j] = NULL_VALUE;
            }
        }

        h = new int[nVertices];
    }

    bool addEdge(int u, int v, double w){
        if (u >= nVertices || v >= nVertices)
            return false;
        
        Edge e(v, w);
        if (searchEdge(u, v) != nullptr)
            return false;
        list[u].push_back(e);
        ++nEdges;
        return true;
    }

    void printGraph(){
        // cout<<"Vertices: "<<nVertices-1<<" Edges: "<<nEdges<<endl;
        cout<<"Graph: \n";
        for(int i = 1; i < nVertices; ++i){
            cout<<i<<" : ";
            for(int j  = 0; j < list[i].size(); ++j){
                cout<<list[i][j].v<<"("<<list[i][j].w<<")";
                if (j < list[i].size() - 1) cout<<" -> ";
            }
            cout<<endl;
        }
    }

    Edge* searchEdge(int u, int v){
        if (u >= nVertices || v >= nVertices)
            return nullptr;
        
        for(auto itr = list[u].begin(); itr != list[u].end(); ++itr){
            if (itr->v == v){
                return &(*itr);
            }
        }
        return nullptr;
    }

    void removeEdge(int u, int v){
        if (u >= nVertices || v >= nVertices)
            return;

        for(auto itr = list[u].begin(); itr != list[u].end(); ++itr){
            if(itr->v == v){
                list[u].erase(itr);
                break;
            }
        }
    }

    void reWeightEdge(int u, int v, int w){
        if (u >= nVertices || v >= nVertices)
            return;
        
        Edge *e = searchEdge(u, v);
        if (e == nullptr){
            return;
        }
        e->w = w;
    }

    bool isEdge(int u, int v){
        if (u >= nVertices || v >= nVertices || searchEdge(u, v) == nullptr)
            return false;
        
        return true;
    }

    double getWeight(int u, int v){
        if (u >= nVertices || v >= nVertices)
            return INF;
        
        Edge *e = searchEdge(u, v);
        if (e == nullptr){
            return NULL_VALUE;
        }
        return e->getW();
    }

    void floydWarshall(){
        
        //Initializes the distanceMatrix
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                if (i == j){
                    distanceMatrix[i][j] = 0;
                    continue;
                } 
                Edge * e = searchEdge(i, j);
                if (e != nullptr){
                    distanceMatrix[i][j] = e->w; 
                }
            }
        }
        
        //Initializes the parentMatrix
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                if (distanceMatrix[i][j] == INF || i == j){
                    parentMatrix[i][j] = NULL_VALUE;
                } else {
                    parentMatrix[i][j] = i;
                }
            }
        }
        
        
        for(int k = 1; k < nVertices; ++k){
            for(int i = 1; i < nVertices; ++i){
                for(int j = 1; j < nVertices; ++j){
                    if (distanceMatrix[i][k] < INF && distanceMatrix[k][j] < INF){
                        if (distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]){
                            distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                            parentMatrix[i][j] = parentMatrix[k][j];
                        }
                    }
                }
            }
        }
    }

    bool BellmanFord(int source){
        if (source < 0 || source >= nVertices)
            return true;
        
        h[source] = 0;

        //Relaxation of each edge for |V|-1 times
        for(int i = 0; i < nVertices - 1; ++i){
            for(int j = 0; j < nVertices; ++j){
                for(auto k : list[j]){
                    if (h[k.v] > h[j] + k.w && h[j] != INF){
                        h[k.v] = h[j] + k.w;
                    }
                }
            }
        }

        //Detection of negative weight cycle
        for(int j = 0; j < nVertices; ++j){
            for(auto k : list[j]){
                if (h[k.v] > h[j] + k.w){
                    return true;
                }
            }
        }
        return false;
    }

    void Dijkstra(int source){

        bool visited[nVertices] = {0};
        priority_queue<pair<double, int>, vector<pair<double, int>>,
         greater<pair<double, int>>> q;

        distanceMatrix[source][source] = 0;
        q.push({0, source});
        while(!q.empty()){
            int v = q.top().second;
            double dv = q.top().first;
            q.pop();

            if(visited[v])
                continue;
            
            for(auto e : list[v]){
                //Relaxation
                if (distanceMatrix[source][v] + e.w < distanceMatrix[source][e.v] && distanceMatrix[source][v] != INF){
                    distanceMatrix[source][e.v] = distanceMatrix[source][v] + e.w;
                    parentMatrix[source][e.v] = v;
                    q.push({distanceMatrix[source][e.v], e.v});
                }
            }
            visited[v] = true;
        }

    }   

    void johnsonsAlgo(){
        for(int i = 1; i < nVertices; ++i){
            addEdge(0, i, 0);
        }

        if (BellmanFord(0)){
            cout<<"Negative cycle detected\n";
            return;
        }

        //Reweights the graph so that no edge has neg weight
        for(int i = 1; i < nVertices; ++i){
            for(int j = 0; j < list[i].size(); ++j){
                list[i][j].w += h[i] - h[list[i][j].v];
            }
        }

        //Runs Dijkstra for each vertex
        for(int i = 1; i < nVertices; ++i){
            Dijkstra(i);

            for(int j = 0; j < nVertices; ++j){
                distanceMatrix[i][j] += h[j] - h[i];
            }            
        }

        //puts the graph back in old weights
        for(int i = 1; i < nVertices; ++i){
            for(int j = 0; j < list[i].size(); ++j){
                list[i][j].w += h[list[i][j].v] - h[i];
            }
        }

    }

    double getShortestPathWeight(int u, int v){
        if (u >= nVertices || v >= nVertices)
            return INF;
        else
            return distanceMatrix[u][v];
    }

    void printShortestPath(int u, int v){
        vector<int> path;
        cout<<"Shortest path: ";
        if (parentMatrix[u][v] == NULL_VALUE){
            cout<<"No path\n";
            return;
        }
        int curr = v;
        while(curr != u){
            path.push_back(curr);
            curr = parentMatrix[u][curr];
        }
        cout<<u<<" -> ";
        curr = u; 
        for(auto itr = path.rbegin(); itr != path.rend(); ++itr){
            cout<<*itr<<"("<<getWeight(curr, *itr)<<")";
            if (*itr != v) cout<<" -> ";
            curr = *itr;
        }
        cout<<endl; 

    }
    
    void printDistanceMatrix(){
        cout<<"Distance Matrix: \n";
        for(int i = 1; i < nVertices; ++i){
            for(int j = 1; j < nVertices; ++j){
                if (distanceMatrix[i][j] == INF){
                    cout<<"INF ";
                }
                else
                    cout<<distanceMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void printPredecessorMatrix(){
        cout<<"Predecessor Matrix: "<<endl;
        for(int i = 1; i < nVertices; ++i){
            for(int j = 1; j < nVertices; ++j){
                if (parentMatrix[i][j] == NULL_VALUE){
                    cout<<"NIL ";
                }
                else
                    cout<<parentMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void cleanSPInfo(){
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                distanceMatrix[i][j] = INF;
            }
        }
        for(int i = 0; i < nVertices; ++i){
            for(int j = 0; j < nVertices; ++j){
                parentMatrix[i][j] = NULL_VALUE;
            }
        }
    }

    ~Graph(){
        delete list;
        delete [] parentMatrix;
        delete [] distanceMatrix;
        delete h;
    }
    
};

int main(){
    FILE *fp = freopen("result.txt", "w", stdout);
    
    int N, M;
    cin>>N>>M;
    Graph g;
    g.setnVertices(N+1);

    for(int i = 0; i < M; ++i){
        int u, v;
        double w;
        cin>>u>>v>>w;
        g.addEdge(u, v, w);
    }
    cout<<"Graph Created.\n";

    int C = 0;
    while(C <= 7){
        cin>>C;
        if (C > 7)
            break;
        else if (C == 1){
            g.cleanSPInfo();
            cout<<"APSP matrices cleared\n";
        } else if (C == 2){
            g.floydWarshall();
            cout<<"Floyd-Warshall algorithm implemented\n";
        } else if (C == 3){
            g.johnsonsAlgo();
            cout<<"Johnson's algorithm implemented\n";
        } else if (C == 4){
            int u, v;
            cin>>u>>v;
            double w = g.getShortestPathWeight(u, v);
            if (w < INF)
                cout<<"Shortest Path Weight: "<<w<<endl;
            g.printShortestPath(u, v);
        } else if (C == 5){
            g.printGraph();
        } else if (C == 6){
            g.printDistanceMatrix();
        } else if (C == 7){
            g.printPredecessorMatrix();
        }
    }

}