#include<stdio.h>
#include<iostream>
#include<random>
#include<fstream>
#include<queue>
#include<stack>
#include<vector>
#include<algorithm>
using namespace std;

#define ll long long
ll inf = numeric_limits<ll>::max();
ll NULL_VALUE = numeric_limits<ll>::min();
#define WHITE 0
#define GRAY 1
#define BLACK 2


ll src, dest;

class Graph
{
	ll nVertices, nEdges ;
	bool directed ;
	vector<pair<ll,ll>> *adjList;
    ll *distance, *parent, *color, *inDegree;


public:
    
    Graph(ll size, bool dir){
	    directed = dir;
        nVertices = size;
        nEdges = 0;
        
        adjList = new vector<pair<ll, ll>>[nVertices];
        inDegree = new ll[nVertices];
        parent = new ll[nVertices];
        color = new ll[nVertices];
        distance = new ll[nVertices];

        fill(inDegree, inDegree + nVertices, 0);
    }


    bool addEdge(ll u, ll v, ll w = 1){
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

    void removeEdge(ll u, ll v)
    {
        if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
        
        auto it = find_if( adjList[u].begin(), adjList[u].end(),
            [&](const std::pair<ll, ll>& element){ return element.first == v;} );
        
        if (it != adjList[u].end()){
            adjList[u].erase(it);
            inDegree[it->first]--;
        }
        --nEdges;

        if (!directed){
            auto it1 = find_if( adjList[v].begin(), adjList[v].end(),
            [&](const std::pair<ll, ll>& element){ return element.first == u;} );
        
            if (it1 != adjList[v].end()){
                adjList[v].erase(it);
                inDegree[it1->first]--;
            }
               --nEdges;
        }
    }

    bool isEdge(ll u, ll v){
        if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

        auto it = find_if( adjList[u].begin(), adjList[u].end(),
            [&](const pair<ll, ll>& element){ return element.first == v;} );

        if (it != adjList[u].end())
            return true;
        
        if (!directed){
            auto it1 = find_if( adjList[v].begin(), adjList[v].end(),
            [&](const pair<ll, ll>& element){ return element.first == u;} );

            if (it1 != adjList[u].end()){
                return true;
            }
        }
        return false;
    }

    ll getOutDegree(ll u){
        if(u<0 ||  u>=nVertices) return NULL_VALUE;

        return adjList[u].size();
    }

    void bfs(ll source, bool analysis = false)
    {
        if (source < 0 || source >= nVertices)
            return;

        fill(color, color + nVertices, WHITE);
        fill(parent, parent + nVertices, NULL_VALUE);
        fill(distance, distance + nVertices, inf);

        color[source] = GRAY;
        distance[source] = 0;
        parent[source] = NULL_VALUE;

        queue<ll> q;
        q.push(source);
    
        if (!analysis)
            cout<<"\nBFS Traversal : ";

        while(!q.empty()){
            ll u = q.front();
            q.pop();
            ll len = adjList[u].size();
    
            if (!analysis)
                cout<<u<<" ";

            for(ll i = 0; i < len; ++i){
                ll v = adjList[u][i].first;
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

    void dfs(ll source, bool analysis = false)
    {
        if (source < 0 || source >= nVertices)
            return;
        

        fill(color, color + nVertices, WHITE);
        fill(parent, parent + nVertices, NULL_VALUE);
        fill(distance, distance + nVertices, inf);

        color[source] = GRAY;
        distance[source] = 0;
        parent[source] = NULL_VALUE;

        stack<ll> st;
        st.push(source);
    
        if (!analysis)
            cout<<"\nDFS Traversal : ";

        while(!st.empty()){
            ll u = st.top();
            st.pop();
            ll len = adjList[u].size();
    
            if (!analysis)
                cout<<u<<" ";

            for(ll i = 0; i < len; ++i){
                ll v = adjList[u][i].first;
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

    ll getDist(ll u, ll v)
    {
        if(u<0 || v<0 || u>=nVertices || v>=nVertices)
            return inf;
        
        return distance[v];
    }

    void printGraph()
    {
        printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
        for(ll i=0;i<nVertices;i++)
        {
            printf("%d:", i);
            for(ll j=0; j<adjList[i].size();j++){
                printf("(%d, %d) ", adjList[i][j].first, adjList[i][j].second);
            }
            printf("\n");
        }
    }

    void random_generate(ll nEdge){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-10*nVertices,10*nVertices);

        for(ll i = 0 ; i < nEdge; ++i){
            ll u = dis(gen);
            ll v = dis(gen);
            ll w = dis(gen);
            if (!addEdge(u, v, w))
                --i;
        }
    }


    void dijkstra(ll source){
        fill(color, color + nVertices, WHITE);
        fill(parent, parent + nVertices, NULL_VALUE);
        fill(distance, distance + nVertices, inf);

        distance[source] = 0;

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>,
         greater<pair<ll, ll>>> q;

        q.push({0, source});

        while(!q.empty()){
            ll v = q.top().second, dv = q.top().first;
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

    bool bellman_ford(ll source){
        if (source < 0 || source >= nVertices)
            return false;
        
        //Initialization
        fill(parent, parent + nVertices, NULL_VALUE);
        fill(distance, distance + nVertices, inf);
        
        distance[source] = 0;

        //Relaxation of each edge for |V|-1 times
        for(ll i = 0; i < nVertices - 1; ++i){
            for(ll j = 0; j < nVertices; ++j){
                for(auto k : adjList[j]){
                    if (distance[k.first] > distance[j] + k.second && distance[j] != inf){
                        distance[k.first] = distance[j] + k.second;
                        parent[k.first] = j;
                    }
                }
            }
        }

        //Detection of negative weight cycle
        for(ll j = 0; j < nVertices; ++j){
            for(auto k : adjList[j]){
                if (distance[k.first] > distance[j] + k.second){
                    return false;
                }
            }
        }

        return true;

    }

    void print_path(ll src, ll dest){
        ll v = dest;
        vector<ll> path;

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

        for(ll i : path){
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

    ll nVertices, nEdges, u, v, w;
    file>>nVertices>>nEdges;

    Graph g(nVertices+1, true);

    for(ll i = 0; i < nEdges; ++i){
        file>>u>>v>>w;
        g.addEdge(u, v, w);
    }
    file>>src>>dest;
    file.close();

    return g;
}



int main()
{
    Graph g = load_graph("input.txt");

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
