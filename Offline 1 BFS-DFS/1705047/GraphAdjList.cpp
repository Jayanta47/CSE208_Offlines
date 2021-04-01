///created on 2/28/2020
///Author: Jayanta Sadhu

#include<stdio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}


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

void ArrayList::removeItemAt(int position) ///do not preserve order of items!!!
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
	bool directed ;
	ArrayList  * adjList ;
	int *color, *dist, *parent;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);//declaration of default argument made only once
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    int getEdges(){return nEdges;}
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getOccurence(int u,int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source);
	void dfsVisit(int v);

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	color=0;
	dist=0;
	parent=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(color)delete [] color;
	color = new int [nVertices];

	if(dist)delete [] dist;
	dist = new int[nVertices];

	if(parent) delete [] parent;
	parent = new int [nVertices];
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices||u==v) return false; //check the inclusive criterion part//vertex out of range

    if(isEdge(u,v))return false;
    //cout<<" ok"<<endl;
    this->nEdges++ ;
    // use the func is edge to verify if there is any edge.
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(!isEdge(u,v)||u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    //cout<<" ok"<<endl;
    if(adjList[u].searchItem(v)==NULL_VALUE)return 0;
    else return 1;
}

int Graph::getOccurence(int u, int v)
{
    int count=0;
    for(int i=0;i<adjList[v].getLength();i++)
    {
        if(adjList[v].getItem(i)==u)count++;
    }
    return count;
}

int Graph::getInDegree(int u)
{
    //returns the degree of vertex u
    if(!directed)
    {
        return adjList[u].getLength();
    }
    int in_degree=0;
    for(int i=0;i<nVertices;i++)
    {
        if(i!=u)
        {
            if(adjList[i].searchItem(u)!=NULL_VALUE)in_degree++;
        }
    }

    return in_degree;
}

int Graph::getOutDegree(int u)
{
    return adjList[u].getLength();  // check
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    cout<<"The Adjacent Vertices of vertex "<<u<<" are: ";
    adjList[u].printList();

}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0||v<0||u>=nVertices || v>=nVertices)return false;

    for(int i=0;i<adjList[u].getLength();i++)
    {
        int vertex=adjList[u].getItem(i);
        if(vertex!=v && adjList[v].searchItem(vertex)!=NULL_VALUE)return true;
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
    cout<<"Vertices visited in order of (bfs): ";


    while(!Q.empty())
    {
        u = Q.dequeue();
        cout<<u<<" ";
        for(int i=0;i<adjList[u].getLength();i++)
        {

            v = adjList[u].getItem(i);// gets the item at position i
            if(color[v]==WHITE)
            {
                color[v]=GREY;
                dist[v]= dist[u]+1;
                parent[v]=u;
                Q.enqueue(v);
            }
        }
        color[u]==BLACK;
    }

    cout<<endl;
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
    cout<<"The vertices visited in order: ";
    dfsVisit(source);

}

void Graph::dfsVisit(int v)
{
    color[v] = GREY;
    cout<<v<<" ";
    for(int i=0;i<adjList[v].getLength();i++)
    {
        int u= adjList[v].getItem(i);
        if(color[u]==WHITE)
        {
            parent[u] = v;
            dfsVisit(u);
        }
    }
    color[v] = BLACK;
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
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList)delete [] adjList;
    if(color)delete[] color;
    if(dist)delete[] dist;
    if(parent) delete [] parent;
    //delete nVertices,nEdges,directed;
    //adjList=color=dist=parent=nullptr;
}
/// vertices start from 0

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

        }
    }

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


            int source[10];
            for(int i=0;i<10;i++)
            {
                source[i] = rand()%vertexN;

            }
            auto init = high_resolution_clock::now();
            for(int i=0;i<10;i++)
            {

                g.bfs(source[i]);

            }
            auto finish = high_resolution_clock::now();
            duration<double, std::nano> time = (finish-init);
            cout<<"The average duration for bfs on "<<vertexN<<" vertices and "<<
            edges<<" edges is: "<<time.count()/10<<" nanoseconds"<<endl;
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
