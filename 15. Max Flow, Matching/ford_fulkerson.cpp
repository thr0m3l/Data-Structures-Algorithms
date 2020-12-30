#include<iostream>
#include<queue>
#include<vector>
using namespace std;
#define ll long long
class graph{
public:
    ll nV;
    vector<ll> *adj;
    ll **flow, **cap, **res;
    

    graph(ll size){
        this->nV = size + 2;
        adj = new vector<ll>[nV];

        flow = new ll*[nV];
        cap = new ll*[nV];
        res = new ll*[nV];
        for(ll i=0;i<nV;i++){
            flow[i] = new ll[nV];
            cap[i] = new ll[nV];
            res[i] = new ll[nV];
            for(ll j=0;j<nV;j++) flow[i][j] = cap[i][j] = res[i][j] = 0;
        }

    }
    void addEdge(ll u, ll v, ll c = 1){
        if (!cap[u][v]) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        cap[u][v] += c;
        res[u][v] += c;
    }

    ll bfs(ll s, ll t, vector<ll> &parent){ 
        fill(parent.begin(), parent.end(), -1);

        queue<pair<ll, ll>> q;
        ll res_flow = INT64_MAX;
        q.push({s, res_flow});
        while(!q.empty()){
            ll u = q.front().first;
            ll f = q.front().second;
            q.pop();
            for(ll v : adj[u]){
                if(parent[v] == -1 && res[u][v]){
                    parent[v] = u;
                    ll new_flow = min(f, res[u][v]);
                    if(v == t) return new_flow;
                    q.push({v, new_flow});
                }
            }
        }
        return 0;
    }

    ll edmonds_karp(ll s, ll t){
        ll new_flow, max_flow = 0;
        vector<ll> parent(nV);
        while(new_flow = bfs(s, t, parent)){
            max_flow += new_flow; // adds the new flow to total flow
            ll curr = t;
            while(curr != s){
                // traverses the augmenting path
                ll par = parent[curr];
                res[par][curr] -= new_flow; //modifies the residual graph
                res[curr][par] += new_flow;
                
                // increase flow, if the edge exists on original graph
                // else, decrease flow on reverse edge (which exists on original graph)
                if(cap[par][curr]) flow[par][curr] += new_flow;
                else flow[curr][par] -= new_flow;
                curr = par;
            }
        }
        return max_flow;
    }

    bool bipartite(vector<ll> &color){
        //BFS Coloring
        
        queue<ll> q;
        
        for(int s = 0; s < nV-2; s++){
            if (color[s] != -1) continue;

            q.push(s);
            color[s] = 0;

            while(!q.empty()){
                ll u = q.front();
                q.pop();
                for(ll v : adj[u]){
                    if (color[v] == -1) color[v] = !color[u], q.push(v);
                    else if (color[v] == color[u]) return false;
                }
            }
        }
        return true;
    }

    void matching(){
        vector<ll> color(nV);
        fill(color.begin(), color.end(), -1);

        if(!bipartite(color)){
            cout<<"The Graph is Not Bipartite\n";
            return;
        } 
        else {
            for(ll i = 0; i < nV-2; ++i){
                if (!color[i]) {
                    for(ll v : adj[i]){
                        if(!cap[i][v]){
                            //reverses the edges, in-case color 0 is on sink's side
                            cap[i][v] = res[i][v]= cap[v][i]; 
                            cap[v][i] = res[v][i] = 0;
                        }
                    }
                    addEdge(nV-2, i, 1); //if color 0 add edge from source
                }
                else addEdge(i, nV-1, 1); //if color 1 add edge to sink

            }
            cout<<edmonds_karp(nV-2, nV-1)<<endl;
            
            for(ll u = 0; u < nV-2; ++u){
                for(ll v : adj[u]){
                    if (cap[u][v] && v < nV-2 && flow[u][v]) cout<<u<<" "<<v<<endl;
                }
            }
        }
    }

    void printGraph(){
        for(ll u = 0; u < nV-2; ++u){
            for(ll v : adj[u]){
                if (cap[u][v]) cout<<u<<" "<<v<<" "<<flow[u][v]<<"/"<<cap[u][v]<<endl;
            }
        }
    }
};

int main(){
    // FILE *fp = freopen("output.txt", "w", stdout);
    // FILE *fp1 = freopen("input.txt", "r", stdin);

    ll ch = 1, V, E;
    cout<<"1. Max-Flow\n2. Bipartite Matching\n>>";
    cin>>ch;
    cin>>V>>E;
    graph g(V);

    for(ll i = 0; i < E; ++i){
        ll u, v, c = 1;
        cin>>u>>v;
        if (ch == 1) cin>>c;
        g.addEdge(u, v, c);
    }
    
    if (ch == 1){
        ll s = 1, t = V;
        cin>>s>>t;
        cout<<g.edmonds_karp(s, t)<<endl;
        g.printGraph();
    } else {
        g.matching();    
    }
    
}