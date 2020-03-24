#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<random>
#include<chrono>
#include<fstream>
using namespace std::chrono;
using namespace std;

random_device rd;
mt19937 gen(rd());

#define NULL_VALUE -999999
#define INFINITY 2147483647;
#define WHITE 0
#define GRAY 1
#define BLACK 2


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
    int *inDegree;
    int *distance, *parent, *color;
    int *dfs_color, *dfs_parent;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source, bool analysis);
    void dfs(int source);
    void dfs_visit(int source);
    void random_generate(int nEdge);
    void load(); 
};

void Graph::load()
{
    ifstream file;
    file.open("graph.txt");

    int nv, ne;
    file>>nv>>ne;
    setnVertices(nv);

    for(int i = 0; i < nv; ++i){
        int u, sz, v;
        file>>u>>sz;
        for(int j = 0; j < sz; ++j){
            file>>v;
            addEdge(u,v);
        }
    }
    file.close();
}

Graph::Graph(bool dir)
{
	
    nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0  ;
	directed = dir ;

}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

    inDegree = new int[nVertices];

    for(int i = 0; i < nVertices; ++i){
        inDegree[i] = 0;
    }
    color = new int[nVertices];
    distance = new int[nVertices];
    parent = new int[nVertices];

    dfs_color = new int[nVertices];
    dfs_parent = new int[nVertices];

}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices || isEdge(u, v) || u == v) return false;
    matrix[u][v] = 1;
    nEdges++;
    inDegree[v]++;
    if(!directed) {
        matrix[v][u] = 1;
        inDegree[u]++;
    }
    return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    matrix[u][v] = 0;
    inDegree[v]--;
    if(!directed){
        matrix[v][u] = 0;
        inDegree[u]--;
    } 

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;

    return matrix[u][v];
}

int Graph::getOutDegree(int u)
{
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int deg = 0;
    for(int i=0;i<nVertices;i++){
        if(i!=u && matrix[u][i])
            deg++;
        }
    return deg;    
}

int Graph::getInDegree(int u)
{
    if(u<0 ||  u>=nVertices) return NULL_VALUE;
    
    return inDegree[u];
}
    

void Graph::printAdjVertices(int u)
{
    cout<<endl;
    for (int i = 0 ; i<nVertices ; i++){
        if(matrix[u][i])
            cout<<i<<" "<<endl;
    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for (int i = 0 ; i<nVertices; i++){
        if(matrix[u][i] && matrix[v][i])
            return true;
    }
    return false;
}

void Graph::bfs(int source, bool analysis = false)
{
    if (source < 0 || source >= nVertices)
        return;


    for(int i = 0; i < nVertices; ++i){
        color[i] = WHITE;
        parent[i] = NULL_VALUE;
        distance[i] = INFINITY;
    }

    color[source] = GRAY;
    distance[source] = 0;
    parent[source] = NULL_VALUE;

    Queue q;
    q.enqueue(source);

    if (!analysis) cout<<"\nBFS Traversal : ";
    while(!q.empty()){
        int u = q.dequeue();
        if (!analysis) cout<<u<<" ";
        for(int i = 0; i < nVertices; ++i){
            if (color[i] == WHITE && matrix[u][i]){
                q.enqueue(i);
                color[i] = GRAY;
                distance[i] = distance[u] + 1;
                parent[i] = u;
            }
        }
        color[u] = BLACK;
    }
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return INFINITY;

    bfs(u);
    return distance[v];
}

void Graph::dfs(int source)
{

    for(int i = 0; i < nVertices; ++i){
        dfs_color[i] = WHITE;
        dfs_parent[i] = NULL_VALUE;
    }
    cout<<"DFS Traversal : ";
    dfs_visit(source);
}

void Graph::dfs_visit(int source)
{
    dfs_color[source] = GRAY;
    cout<<source<<" ";
    for(int i = 0; i < nVertices; ++i){
        if (dfs_color[i] == WHITE && matrix[source][i]){
            dfs_parent[i] = source;
            dfs_visit(i);
        }
    }
    dfs_color[source] = BLACK;
}

void Graph::printGraph()
{
    printf("Number of vertices: %d, \n Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j])
                printf(" %d", j);
        }
        printf("\n");
    }
}

void Graph::random_generate(int nEdge){
    uniform_int_distribution<> dis(0, nVertices - 1 );

    for(int i = 0 ; i < nEdge; ++i){
        int u = dis(gen);
        int v = dis(gen);
        if (!addEdge(u, v))
            --i;
    }
}

Graph::~Graph()
{
    if(matrix)
        delete [] matrix;
    if(distance)
        delete[] distance;

}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    // cout<<"1. Load Graph\n";
    // cout<<"2. Create Graph\n";
    // cin>>choice;

    choice = 2;
    if (choice == 1){
        g.load();
    }
    else {
        printf("Enter number of vertices: ");
        scanf("%d", &n);
        g.setnVertices(n);
    }
    

    while(1)
    {
        
        cout<<endl;
        cout<<"1. Add edge."<<endl;
        cout<<"2. Remove Edge"<<endl; 
        cout<<"3. isEdge"<<endl;
        cout<<"4. getDegree"<<endl;
        cout<<"5. Print Adjacent Vertices"<<endl;
        cout<<"6. Print Graph"<<endl;
        cout<<"7. Get Distance"<<endl;
        cout<<"8. Has Common Adjacent Vertices"<<endl;
        cout<<"9. BFS Traversal\n";
        cout<<"10. DFS Traversal\n";
        cout<<"11. Generate Random Graph\n";
        cout<<"12. Analysis\n";
        cout<<"13. Exit"<<endl;
        cout<<"<< ";

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u,v;
            cin>>u>>v;
            g.removeEdge(u,v);
        }
        else if(ch==3)
        {
            int u,v;
            cin>>u>>v;
            cout<<endl;
            cout<<g.isEdge(u,v)<<endl;
        }
        else if (ch == 4){
            int u;
            cin>>u;
            cout<<"In Degree : "<<g.getInDegree(u)<<"\n";
            cout<<"Out Degree : "<<g.getOutDegree(u)<<"\n";
        }
        else if (ch == 5){
            int u;
            cin>>u;
            g.printAdjVertices(u);
        }
        else if(ch==6)
        {
            g.printGraph();
        }
        else if (ch == 7){
            int u,v;
            cin>>u>>v;
            int dist = g.getDist(u,v);
            cout<<"\nDistance: "<<dist<<"\n"<<endl;
        }
        else if(ch==13)
        {
            break;
        }
        else if (ch == 8){
            int u,v;
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u,v)<<endl;
        }
        else if (ch == 9){
            int u;
            cin>>u;

            auto start = high_resolution_clock::now();
            g.bfs(u);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start);
            cout <<"Time taken to finish: "<< duration.count() <<" ns" << endl;
        }
        else if (ch == 10){
            int u;
            cin>>u;
            g.dfs(u);
        }
        else if (ch == 11){
            cout<<"Enter the number of edges between 0 - "<<n*(n-1)/2<<" : ";
            int nEdge;
            cin>>nEdge;
            g.random_generate(nEdge);
        }
        else if (ch == 12){
            int arr[] = {1000, 2000, 4000, 8000, 16000};
            ofstream file;
            file.open("result_matrix3.txt");
            file<<" V "<<" E "<<" Time \n";
            for(int i : arr){
                int nEdge = i, prev;
                Graph graph = new Graph(dir);
                graph.setnVertices(i);
                while(nEdge <= i*(i-1)/8){
                    graph.random_generate(nEdge - prev);
                    uniform_int_distribution<> dis(0, n-1);
                    long long total = 0;
                    for(int j = 0; j < 10; ++j){
                        int u = dis(gen);
                        auto start = high_resolution_clock::now();
                        graph.bfs(u, true);
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<nanoseconds>(stop - start);
                        total += duration.count();
                    }

                    file<<i<<" "<<nEdge<<" "<<total/10<<"\n";
                    prev = nEdge;
                    nEdge *= 2;
                }     
            }
            file.close();
        }
    }

}