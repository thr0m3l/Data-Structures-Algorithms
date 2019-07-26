#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999


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
	int *distance;
    int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u, bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	
    nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0  ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
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

}

void Graph::addEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    nEdges++;
    if(!directed) {
        matrix[v][u] = 1;
    }
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;

    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;

    return matrix[u][v];
}

int Graph::getDegree(int u, bool out = true)
{
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int deg = 0;
    if(out){
        for(int i=0;i<nVertices;i++){
            if(i!=u && matrix[u][i])
                deg++;
            }
        return deg;    
    } else {
        for (int i = 0; i<nVertices; i++){
            if(i!=u && matrix[i][u])
                deg++;
        }
        return deg;
    }

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

void Graph::bfs(int source)
{
    int i, j;

    if(distance)
        delete[] distance;

    distance = new int[nVertices];
  
    int visited[nVertices];
    Queue q;

    for(i = 0; i < nVertices; i++) {
        visited[i] = 0;
    }
    visited[source] = 1;
    q.enqueue(source);
    distance[source] = 0;
    cout<<source<<endl;

    while(!q.empty()) {
        i = q.dequeue();
        for(j = 0; j < nVertices; j++) {
            if(visited[j] == 0 && matrix[i][j] == 1) {
                visited[j] = 1;
                q.enqueue(j);
                distance[j] = distance[i] + 1;
            } 
        }
    }
    cout<<endl;
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
    printf("Number of vertices: %d, \n Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
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
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        cout<<"1. Add edge."<<endl;
        cout<<"2. Remove Edge"<<endl; 
        cout<<"3. isEdge"<<endl;
        cout<<"4. getDegree"<<endl;
        cout<<"5. Print Adjacent Vertices"<<endl;
        cout<<"6. Print Graph"<<endl;
        cout<<"7. Get Distance"<<endl;
        cout<<"8. Has Common Adjacent Vertices"<<endl;
        cout<<"9. Exit"<<endl;

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
            cout<<g.getDegree(u);
        }
        else if (ch == 5){
            int u;
            cin>>u;

        }
        else if(ch==6)
        {
            g.printGraph();
        }
        else if (ch == 7){
            int u,v;
            cin>>u>>v;
            cout<<"Distance: "<<g.getDist(u,v)<<endl;
        }
        else if(ch==9)
        {
            break;
        }
        else if (ch == 8){
            int u,v;
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u,v)<<endl;
        }
    }

}
