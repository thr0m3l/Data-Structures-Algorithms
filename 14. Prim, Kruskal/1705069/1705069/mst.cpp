#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int INF = numeric_limits<int>::max();
int NULL_VALUE = -1;

class disjoint_set{
private:
	int *parent = NULL;
	int *rank = NULL;
	int length;

public:
	disjoint_set(int numOfElem){
		length = numOfElem;
		parent = new int[numOfElem];
		rank = new int[numOfElem];
		
		for(int i=0;i<numOfElem;i++){
			rank[i] = 0;
			parent[i] = -1;
		}
		
	}
	void make_set(int v){
		parent[v] = v;
		rank[v] = 0;
	}

	int find_set(int v){
		if(parent[v] == v)
			return v;
		else 
			return parent[v] = find_set(parent[v]);
	}

	void union_set(int a, int b){
		
		if (parent[a]  == -1 || parent[b] == -1){
			return;
		}

		a = find_set(a);
		b = find_set(b);

		if(a!=b){
			if(rank[a]<rank[b])
				swap(a,b);
			parent[b] = a;
			if(rank[a] == rank[b])
				rank[a]++;
		}
	}

	~disjoint_set(){
		delete[] parent;
		delete[] rank;
	}

};

class Edge{
    public:
    int u, v;
    double w;
    
    Edge(int u, int v, int w){
        this->u = u;
        this->v = v;
        this->w = w;
    }
    
};

class Graph{
    int nVertices, nEdges;
    vector<Edge> *list;
    int *key, *parent;
    public:

    Graph(int n){
        this->nVertices = n;
        this->nEdges = 0;

        list = new vector<Edge>[nVertices];
        key = new int[nVertices];
        parent = new int[nVertices];

    }

    bool addEdge(int u, int v, double w){
        if (u >= nVertices || v >= nVertices || u < 0 || v < 0)
            return false;
        
        Edge e(u, v, w);
        Edge e1 (v, u, w);
        list[u].push_back(e);
        list[v].push_back(e1);
        ++nEdges;
        return true;
    }

    void mst_prim(int root = 0){
        fill(key, key + nVertices, INF);
        fill(parent, parent + nVertices, NULL_VALUE);
        int weight = 0;
        bool visited[nVertices] = {0};
        priority_queue<pair<int, int>, vector<pair<int, int>>,
         greater<pair<int, int>>> q;

        key[root] = 0;
        q.push({0, root});

        while(!q.empty()){
            int u = q.top().second;
            q.pop();
            visited[u] = true;

            for(Edge e : list[u]){
                if (visited[e.v] == false && key[e.v] > e.w ){
                    parent[e.v] = u;
                    key[e.v] = e.w;
                    q.push({key[e.v], e.v});
                }
            }
        }

        cout<<"Prim's Algorithm: \n";
        cout<<"Root Node: "<<root<<endl;


        for(int i = 0; i < nVertices; ++i){
            if (parent[i] != -1){
                cout<<parent[i]<<" "<<i<<endl;
            }
        }
        cout<<endl;

    }

    void mst_kruskal(){

        vector<Edge> edgeList, mst;
        disjoint_set ds(nVertices);

        for(int i = 0; i < nVertices; ++i){
            ds.make_set(i);
            for(auto e : list[i]){
                edgeList.push_back(e);
            }
        }
        int weight = 0;

        sort(edgeList.begin(), edgeList.end(), [ ]( const auto& lhs, const auto& rhs ){
            return lhs.w < rhs.w;});

        for(auto e : edgeList){
            int up = ds.find_set(e.u), vp = ds.find_set(e.v);
            
            if (up != vp){
                ds.union_set(up, vp);
                mst.push_back(e);
                weight += e.w;
            }
        }
        cout<<weight<<endl;
        cout<<"Kruskal's Algorithm: \n";
        

        for(auto e : mst){
            cout<<e.u<<" "<<e.v<<endl;
        }

        
    }

};


int main(){
	FILE *fp = freopen("result.txt", "w", stdout);
    FILE *fp1 = freopen("in5.txt", "r", stdin);
    int n, m;
    cin>>n>>m;

    Graph g(n);
    for(int i = 0; i < m; ++i){
        int u, v, w;
        cin>>u>>v>>w;
        g.addEdge(u, v, w);
    }

    g.mst_kruskal();
    g.mst_prim();


}
