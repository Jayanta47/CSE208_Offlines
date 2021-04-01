//created on 2/28/2020
//Jayanta Sadhu
#include<stdio.h>
#include<stdlib.h>
#include<bits/stdc++.h>
#include<iostream>
#define NULL_VALUE -99999
#define INFINITY 99999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;
using namespace std::chrono;

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

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	int *color, *dist, *parent;


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	int traverse_row(int row);
	//bool searchItem(int item, int row);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
    void dfs(int source);
    void dfsVisit(int source);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	color=0;
	dist=0;
	parent=0;
	directed = dir ; ; //set direction of the graph
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

    if(color)delete [] color;
	color = new int [nVertices];

	if(dist)delete [] dist;
	dist = new int[nVertices];

	if(parent) delete [] parent;
	parent = new int[nVertices];

}

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(isEdge(u,v))return false;
    matrix[u][v] = 1;
    this->nEdges++;
    if(!directed) matrix[v][u] = 1;
    return true;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v]=0;
    this->nEdges--;
    if(!directed)matrix[v][u]=0;
}

int Graph::traverse_row(int row)
{
    int count=0;
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[row][i])count++;
    }
    return count;
}


bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(matrix[u][v])return true;
    else return false;
}

int Graph::getInDegree(int u)
{
    //returns the indegree of vertex u
    if(!directed)return traverse_row(u);/// check that the directed bool is not needed. remainder

    int count=0;
    for(int i=0;i<nVertices;i++)
    {
        if(i!=u)count+=matrix[i][u];
    }
    return count;
}

int Graph::getOutDegree(int u)
{
    return traverse_row(u);

}
void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    cout<<"The adjacent vertices of vertex "<<u<<" are:"<<endl;
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i])cout<<i<<" ";
    }
    cout<<endl;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0;i<nVertices;i++)
    {
        if(i!=u && i!=v && matrix[u][i] && matrix[v][i])return true;
    }
    return false;
}

void Graph::bfs(int source)
{

    if(source<0||source>=nVertices)return ;
    int u,v;
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        dist[i] = INFINITY;
        parent[i] = NULL_VALUE;
    }
    color[source] = GREY;
    dist[source] = 0;
    parent[source] = NULL_VALUE;

    Queue Q ;
    Q.enqueue(source);
    cout<<"The vertices are visited in the order of(bfs): ";
    while(!Q.empty())
    {
        u = Q.dequeue();
        cout<<u<<" ";
        for(int v=0;v<nVertices;v++)
        {
            if(matrix[u][v])
            {
                if(color[v]==WHITE)
                {
                color[v]=GREY;
                dist[v]= dist[u]+1;
                parent[v]=u;
                Q.enqueue(v);
                }
            }
        }
        color[u]==BLACK;
    }
    cout<<endl;
    return;

}

void Graph::dfs(int source)
{
    if(source<0||source>=nVertices)return ;
    int u,v;
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        parent[i] = NULL_VALUE;
    }
    cout<<"The vertices are visited in the order of(dfs): ";
    dfsVisit(source);
}

void Graph::dfsVisit(int u)
{
    color[u] = GREY;
    cout<<u<<" ";
    for(int v=0;v<nVertices;v++)
    {
        if(matrix[u][v])
        {
            if(color[v]==WHITE)
            {
                parent[v] = u;
                dfsVisit(v);
            }
        }
    }
    color[u] = BLACK;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return dist[v];
    //return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
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
    //write your destructor here
    for(int i=0;i<nVertices;i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
    if(color)delete[] color;
    if(dist)delete[] dist;
    if(parent) delete [] parent;
    //delete nVertices,nEdges,directed;
    //adjList=color=dist=parent=0;
}

Graph generateGraph(int n, int m)
{
    Graph g;
    g.setnVertices(n);
    int j=m-1;
    while(j)
    {
        int u = rand()%m;
        int v = rand()%m;

        if(g.addEdge(u,v))
        {
            j--;
            //cout<<u<<" "<<v<<" ok"<<endl;
        }
    }
    //cout<<"ok"<<endl;
    return g;
}

void timeGenerator()
{
    int verticesArr[5] ={1000,2000,4000,8000,16000};
    for(int i=0;i<5;i++)
    {
        int vertexN = verticesArr[i];
        long long int edges;
        long long int limit= (vertexN*(vertexN-1))/8;
        for(edges = vertexN;edges <=limit;edges=edges*2)
        {
            Graph g = generateGraph(vertexN,edges);

            //g.printGraph();
            int source[10];
            for(int i=0;i<10;i++)
            {
                source[i] = rand()%vertexN;
                //cout<<source[i]<<" ";
            }
            auto init = high_resolution_clock::now();
            for(int i=0;i<10;i++)
            {

                g.bfs(source[i]);

            }
            auto finish = high_resolution_clock::now();
            duration<double, std::nano> time = (finish-init);
            cout<<"The average duration for running bfs on "<<vertexN<<"vertices and "<<
            edges<<" edges is: "<<time.count()/10.0<<" nanoseconds"<<endl;
            //cout<<time.count()/10<<endl;
        }
    }
}


int main(void)
{
    srand(time(0));
    int n;
    int choice;
    bool dir;
    cout<<"Options: 1. Open Graph Menu 2. Generate BFS running time"<<endl;
    int opt;
    cin>>opt;
    if(opt==1)
    {
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
            printf("1. Add edge. \n");
            printf("2. Remove edge.\n3. Check if there is edge between 2 vertices \n");
            printf("4. Get In degree of a vertex\n");
            printf("5. Get Out degree of a vertex\n");
            printf("6. Print adjacent vertices\n");
            printf("7. Check if two vertices has any common adjoint vertex\n");
            printf("8. Find the shortest distance between two connected graphs\n");
            printf("9. Run Breadth First Search with source s\n");
            printf("10. Run depth first search with source s\n");
            printf("11. Print Graph\n12. Exit.\n");

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
                cout<<"Enter U and V (u--v):"<<endl;
                cin>>u>>v;
                g.removeEdge(u,v);
            }
            else if(ch==3)
            {
                int u,v;
                cout<<"Enter U and V (U--v):"<<endl;
                cin>>u>>v;
                if(g.isEdge(u,v))cout<<"There is edge between vertices "<<u<<" and "<<v<<endl;
                else cout<<"There is no edge between vertices "<<u<<" and "<<v<<endl;
            }
            else if(ch==4)// get in degree
            {
                int u;
                cout<<"Enter vertex U: "<<endl;
                cin>>u;

                cout<<"Indegree of vertex "<<u<<" :"<<g.getInDegree(u)<<endl;
            }
            else if(ch==5)//get out degree
            {
                int u;
                cout<<"Enter vertex U:"<<endl;
                cin>>u;
                cout<<"Outdegree of vertex "<<u<<" :"<<g.getOutDegree(u)<<endl;
            }
            else if(ch==6) // print adjacent vertices
            {
                int u;
                cout<<"Enter vertex U:" <<endl;
                cin>>u;
                g.printAdjVertices(u);
            }
            else if(ch==7)// if 2 vertices have common vertices
            {
                int u,v;
                cout<<"Enter vertex U and V (u--v): "<<endl;
                cin>>u>>v;
                if(g.hasCommonAdjacent(u,v))cout<<"The vertices "<<u<<" and "<<v<<" have common vertices."<<endl;
                else cout<<"The vertices "<<u<<" and "<<v<<" does not have common vertices."<<endl;
            }
            else if(ch==8)// shortest distance between two connected graphs
            {
                int u,v;
                cout<<"Enter vertex U and V (U--v): "<<endl;
                cin>>u>>v;
                int distance = g.getDist(u,v);
                if(distance==INFINITY)cout<<"The two vertices are not connected"<<endl;
                else cout<<"The shortest distance between "<<u<<" and "<<v<<" is :"<<distance<<endl;
            }
            else if(ch==9)// bfs with source s
            {
                int s;
                cout<<"Enter source"<<endl;
                cin>>s;
                g.bfs(s);
            }
            else if(ch==10)// dfs with source s
            {
                int s;
                cout<<"Enter source"<<endl;
                cin>>s;
                g.dfs(s);
                cout<<endl;
            }
            else if(ch==11)
            {
                g.printGraph();
            }
            else if(ch==12)
            {
                break;
            }
        }
    }
    else if(opt==2)
    {
        timeGenerator();
    }
    return 0;
}
