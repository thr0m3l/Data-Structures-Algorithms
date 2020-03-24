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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
	int nVertices, nEdges ;
    int *inDegree;
	bool directed ;
	ArrayList  *adjList ;
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
    void save();
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

void Graph::save()
{
    ofstream outfile;
    outfile.open("graph.txt");

    outfile<<nVertices<<" "<<nEdges<<"\n";

    for(int i=0;i<nVertices;i++)
    {   
        int len = adjList[i].getLength();
        outfile<<i<<" "<<len<<" ";

        for(int j=0; j<len;j++)
        {
            outfile<<adjList[i].getItem(j)<<" ";
        }
        outfile<<"\n";
    }

    outfile.close();

}
Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
    inDegree = new int[nVertices];
    color = new int[nVertices];
    distance = new int[nVertices];
    parent = new int[nVertices];

    dfs_color = new int[nVertices];
    dfs_parent = new int[nVertices];

    for(int i = 0; i < nVertices; ++i){
        inDegree[i] = 0;
    }
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || u == v || isEdge(u,v)) return false;
    
    adjList[u].insertItem(v);
    this->nEdges++ ;
    inDegree[v]++;

	if(!directed) {
        adjList[v].insertItem(u);
        inDegree[u]++;
    }
    return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges--;
    adjList[u].removeItem(v);
    inDegree[v]--;
    if(!directed) {
        adjList[v].removeItem(u);
        inDegree[u]--;
    }

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    return adjList[u].searchItem(v) == NULL_VALUE? false : true;
}

int Graph::getOutDegree(int u)
{
    //returns the out degree of vertex u
    if(u<0 ||  u>=nVertices) return NULL_VALUE;

    return adjList[u].getLength();
}

int Graph::getInDegree(int u)
{
    if(u<0 ||  u>=nVertices) return NULL_VALUE;
    
    return inDegree[u];
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 ||  u>=nVertices) return;
    adjList[u].printList();
    
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
        return false;

    int len = adjList[u].getLength();
    for(int i=0; i<len; i++)
    {
        if(adjList[v].searchItem(adjList[u].getItem(i))!=NULL_VALUE)
        {
            return true;
        }
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
    
    if (!analysis)
        cout<<"\nBFS Traversal : ";

    while(!q.empty()){
        int u = q.dequeue();
        int len = adjList[u].getLength();
    
        if (!analysis)
            cout<<u<<" ";

        for(int i = 0; i < len; ++i){
            int v = adjList[u].getItem(i);
            if (color[v] == WHITE){
                q.enqueue(v);
                color[v] = GRAY;
                distance[v] = distance[u] + 1;
                parent[v] = u;
            }
        }
        color[u] = BLACK;
    }
    

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
    int len = adjList[source].getLength();
    for(int i = 0; i < len; ++i){
        int v = adjList[source].getItem(i);
        if (dfs_color[v] == WHITE){
            dfs_parent[v] = source;
            dfs_visit(v);
        }
    }
    dfs_color[source] = BLACK;
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

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
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
    adjList = 0;
    if (distance) delete distance;
    if (color) delete color;
    if (parent) delete parent;
}

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
    //cin>>choice;
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
        cout<<"12. Save"<<endl;
        cout<<"13. Analysis\n";
        cout<<"14. Exit\n";
        cout<<"<< ";

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if (!g.addEdge(u, v)){
                cout<<"\nEdge already exists\n";
            }
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
        else if(ch==12)
        {
            g.save();
        }
        else if (ch == 8){
            int u,v;
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u,v)<<endl;
        }
        else if (ch == 9){
            uniform_int_distribution<> dis(0, n-1);
            long long total = 0;
            for(int i = 0; i < 100; ++i){
                int u = dis(gen);
                auto start = high_resolution_clock::now();
                g.bfs(u, true);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start);
                total += duration.count();
            }  
            cout <<"\nAverage time taken to finish: "<< total/100 <<" ns" << endl;
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
        else if (ch == 14){
            break;
        }
        else if (ch == 13){
            int arr[] = {1000, 2000, 4000, 8000, 16000};
            ofstream file;
            file.open("result_list.txt");
            file<<" V "<<" E "<<" Time \n";
            
            for(int i : arr){
                int nEdge = i, prev;
                Graph graph = new Graph(dir);
                graph.setnVertices(i);
                while(nEdge <= i*(i-1)/8){
                    graph.random_generate(nEdge - prev);
                    uniform_int_distribution<> dis(0, n-1);
                    long long total = 0;
                    for(int j = 0; j < 100; ++j){
                        int u = dis(gen);
                        auto start = high_resolution_clock::now();
                        graph.bfs(u, true);
                        auto stop = high_resolution_clock::now();
                        auto duration = duration_cast<nanoseconds>(stop - start);
                        total += duration.count();
                    }

                    file<<i<<" "<<nEdge<<" "<<total/100<<"\n";
                    prev = nEdge;
                    nEdge *= 2;
                }     
            }
            file.close(); 
        }
    }

}
