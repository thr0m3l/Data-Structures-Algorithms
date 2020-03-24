#include<stdio.h>
#include<iostream>
#include<random>
#include<fstream>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

long long inf = numeric_limits<long long>::max();
long long NULL_VALUE = numeric_limits<long long>::min();
#define WHITE 0
#define GRAY 1
#define BLACK 2

long long src, dest;

class Graph
{
	long long nVertices, nEdges ;
	bool directed ;
	vector<pair<long long,long long>> *adjList;
    long long *distance, *parent, *color, *inDegree;


public:
    
    Graph(long long size, bool dir){
	    directed = dir;
        nVertices = size;
        nEdges = 0;
        
        adjList = new vector<pair<long long, long long>>[nVertices];
        inDegree = new long long[nVertices];
        parent = new long long[nVertices];
        color = new long long[nVertices];
        distance = new long long[nVertices];

        
        for(long long i = 0; i < nVertices; ++i){
             inDegree[i] = 0;
        }
        
    }


    bool addEdge(long long u, long long v, long long w = 1){
        if(u<0 || v<0 || u>=nVertices || v>=nVertices || u == v || isEdge(u,v)) 
            return false;

        adjList[u].push_back({v, w});
        this->nEdges++ ;
        inDegree[v]++;

	    if(!directed) {
            adjList[v].push_back({u, w});
            inDegree[u]++;
        }
        return true;
    }

    void removeEdge(long long u, long long v)
    {
        if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
        
        auto it = find_if( adjList[u].begin(), adjList[u].end(),
            [&](const std::pair<long long, long long>& element){ return element.first == v;} );
        
        if (it != adjList[u].end())
            adjList[u].erase(it);
        --nEdges;

        if (!directed){
            auto it1 = find_if( adjList[v].begin(), adjList[v].end(),
            [&](const std::pair<long long, long long>& element){ return element.first == u;} );
        
            if (it1 != adjList[v].end())
                adjList[v].erase(it);
                --nEdges;
        }
    }

    bool isEdge(long long u, long long v){
        if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

        auto it = find_if( adjList[u].begin(), adjList[u].end(),
            [&](const pair<long long, long long>& element){ return element.first == v;} );

        if (it != adjList[u].end())
            return true;
        
        if (!directed){
            auto it1 = find_if( adjList[v].begin(), adjList[v].end(),
            [&](const pair<long long, long long>& element){ return element.first == u;} );

            if (it1 != adjList[u].end()){
                return true;
            }
        }
        return false;
    }

    long long getOutDegree(long long u){
        if(u<0 ||  u>=nVertices) return NULL_VALUE;

        return adjList[u].size();
    }

    void bfs(long long source, bool analysis = false)
    {
        if (source < 0 || source >= nVertices)
            return;

        for(long long i = 0; i < nVertices; ++i){
            color[i] = WHITE;
            parent[i] = NULL_VALUE;
            distance[i] = inf;
        }

        color[source] = GRAY;
        distance[source] = 0;
        parent[source] = NULL_VALUE;

        queue<long long> q;
        q.push(source);
    
        if (!analysis)
            cout<<"\nBFS Traversal : ";

        while(!q.empty()){
            long long u = q.front();
            q.pop();
            long long len = adjList[u].size();
    
            if (!analysis)
                cout<<u<<" ";

            for(long long i = 0; i < len; ++i){
                long long v = adjList[u][i].first;
                if (color[v] == WHITE){
                    q.push(v);
                    color[v] = GRAY;
                    distance[v] = distance[u] + adjList[u][i].second;
                    parent[v] = u;
                }
            }
            color[u] = BLACK;
        }
    }

    void dfs(long long source, bool analysis = false)
    {
        if (source < 0 || source >= nVertices)
            return;
        

        for(long long i = 0; i < nVertices; ++i){
            color[i] = WHITE;
            parent[i] = NULL_VALUE;
            distance[i] = inf;
        }

        color[source] = GRAY;
        distance[source] = 0;
        parent[source] = NULL_VALUE;

        stack<long long> st;
        st.push(source);
    
        if (!analysis)
            cout<<"\nDFS Traversal : ";

        while(!st.empty()){
            long long u = st.top();
            st.pop();
            long long len = adjList[u].size();
    
            if (!analysis)
                cout<<u<<" ";

            for(long long i = 0; i < len; ++i){
                long long v = adjList[u][i].first;
                if (color[v] == WHITE){
                    st.push(v);
                    color[v] = GRAY;
                    distance[v] = distance[u] + adjList[u][i].second;
                    parent[v] = u;
                }
            }
            color[u] = BLACK;
        }
    }

    long long getDist(long long u, long long v)
    {
        if(u<0 || v<0 || u>=nVertices || v>=nVertices)
            return inf;
        
        return distance[v];
    }

    void printGraph()
    {
        printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
        for(long long i=0;i<nVertices;i++)
        {
            printf("%d:", i);
            for(long long j=0; j<adjList[i].size();j++){
                printf("(%d, %d) ", adjList[i][j].first, adjList[i][j].second);
            }
            printf("\n");
        }
    }

    void random_generate(long long nEdge){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-10*nVertices,10*nVertices);

        for(long long i = 0 ; i < nEdge; ++i){
            long long u = dis(gen);
            long long v = dis(gen);
            long long w = dis(gen);
            if (!addEdge(u, v, w))
                --i;
        }
    }


    void dijkstra(long long source){
        for(long long i = 0; i < nVertices; ++i){
            distance[i] = inf;
            parent[i] = NULL_VALUE;
            color[i] = WHITE;
        }
        distance[source] = 0;

        priority_queue< pair<long long, long long>, vector<pair<long long, long long>>,
         greater<pair<long long, long long>>> q;

        q.push({0, source});

        while(!q.empty()){
            long long v = q.top().second, dv = q.top().first;
            q.pop();

            if(color[v] == BLACK)
                continue;
            
            for(auto e : adjList[v]){
                //Relaxation
                if (distance[v] + abs(e.second) < distance[e.first] && distance[v] != inf){
                    distance[e.first] = distance[v] + abs(e.second);
                    parent[e.first] = v;
                    q.push({distance[e.first], e.first});
                }
            }
            color[v] == BLACK;
        }

    }   

    bool bellman_ford(long long source){
        if (source < 0 || source >= nVertices)
            return false;
        
        //Initialization
        for(long long i = 0; i < nVertices; ++i){
            parent[i] = NULL_VALUE;
            distance[i] = inf;
        }
        distance[source] = 0;

        //Relaxation of each edge for |V|-1 times
        for(long long i = 0; i < nVertices - 1; ++i){
            for(long long j = 0; j < nVertices; ++j){
                for(auto k : adjList[j]){
                    if (distance[k.first] > distance[j] + k.second && distance[j] != inf){
                        distance[k.first] = distance[j] + k.second;
                        parent[k.first] = j;
                    }
                }
            }
        }

        //Detection of negative weight cycle
        for(long long j = 0; j < nVertices; ++j){
            for(auto k : adjList[j]){
                if (distance[k.first] > distance[j] + k.second){
                    return false;
                }
            }
        }

        return true;

    }

    void print_path(long long src, long long dest){
        long long v = dest;
        vector<long long> path;

        if (parent[dest] == NULL_VALUE){
            cout<<"-1\n";
            return;
        }
        while(v != src){
            path.push_back(v);
            v = parent[v];
        }

        path.push_back(src);
        reverse(path.begin(), path.end());

        for(long long i : path){
            cout<<i;
            if (i != dest)
                cout<<" -> ";
        }
        cout<<"\n";
    }

    ~Graph(){
        delete adjList;
        delete color;
        delete parent;
        delete distance;
        delete inDegree;
    }

};

Graph load_graph(string filename){
    ifstream file;
    file.open(filename);

    long long nVertices, nEdges, u, v, w;
    file>>nVertices>>nEdges;

    Graph g(nVertices+1, true);

    for(long long i = 0; i < nEdges; ++i){
        file>>u>>v>>w;
        g.addEdge(u, v, w);
    }
    file>>src>>dest;
    file.close();

    return g;
}



int main()
{
    Graph g = load_graph("graph.txt");

    FILE *fp = freopen("result.txt", "w", stdout);

    g.dijkstra(src);
    cout<<"Dijkstra Algorithm: \n";
    cout<<g.getDist(src, dest)<<endl;
    g.print_path(src, dest);

    cout<<"Bellman Ford Algorithm: \n";
    if (g.bellman_ford(src)){
        cout<<g.getDist(src, dest)<<endl;
        g.print_path(src, dest);
    }
    else{
        cout<<"Negative weight cycle detected";
    }
    fclose(stdout);

}
