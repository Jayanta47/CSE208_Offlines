///Created on 2/3/2020
///Last modified 4/3/2020
///Author Jayanta Sadhu
#include<bits/stdc++.h>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3


using namespace std;
ofstream myOutfile("output.txt");

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
	int  *dist, *parent;
    bool *Set;

public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	int traverse_row(int row);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int weight(int u,int v);
    void printGraph();
    int graphVertices();
    int distance(int u);
    void initializeSingleSource(int source);
    void relax(int u, int v);
    void relaxDij(int u,int v);
    bool bellmanFord(int source);
    void dijkstra(int source);
    void printSingleSourceShortestPath(int source,int dest);
    int calculateDistanceSum(int source,int dest,bool weightAbs);//weightAbs true for dijkstra
    int extractMin();

};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	dist=0;
	parent=0;
	directed = dir ;  //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocates space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

	if(dist)delete [] dist;
	dist = new int[nVertices];

	if(parent) delete [] parent;
	parent = new int[nVertices];

	if(Set) delete [] Set;
	Set = new bool[nVertices];

}

bool Graph::addEdge(int u, int v,int w)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(isEdge(u,v))return false;
    matrix[u][v] = w;
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

int Graph::graphVertices()
{
    return nVertices;
}

int Graph::distance(int u)
{
    return dist[u];
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j])
                printf(" %d-(%d)", j,matrix[i][j]);
        }
        printf("\n");
    }
}

int Graph::weight(int u,int v)
{
    return matrix[u][v];
}

int Graph::extractMin()
{
    int minDist = INFINITY;
    int minValueVertex = 0;
    for(int i=0;i<nVertices;i++)
    {
        if(dist[i]<minDist && !Set[i]) // if a vertex is visited, then it is true. Explore for only unvisited
        {
            minDist = dist[i];
            minValueVertex = i;
        }
    }
    return minValueVertex;
}

void Graph::initializeSingleSource(int source)
{
    for(int i=0;i<nVertices;i++)
    {
        dist[i] = INFINITY;
        parent[i] = NULL_VALUE;
    }
    dist[source] = 0;
}

void Graph::relax(int u,int v)//u and v are vertices of a directed graph in order
{
    if (dist[v]>dist[u]+weight(u,v))
    {
        dist[v] = dist[u] + weight(u,v);
        parent[v] = u;
    }

}

void Graph::relaxDij(int u,int v)
{
    if(dist[v]>dist[u]+abs(weight(u,v)))
    {
        dist[v] = dist[u] + abs(weight(u,v));
        parent[v] = u;
    }
}

Graph::~Graph()
{

    for(int i=0;i<nVertices;i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
    if(dist)delete[] dist;
    if(parent) delete [] parent;

}

bool Graph::bellmanFord(int source)
{
    initializeSingleSource(source);
    for(int i=1;i<nVertices;i++) // nVertices represents |G.V|-1
    {
        for(int u=0;u<nVertices;u++)
        {
            for(int v=0;v<nVertices;v++)
            {
                if(isEdge(u,v))
                {
                    relax(u,v);
                }
            }
        }
    }

    //detecting negative cycle
    for(int u=0;u<nVertices;u++)
    {
        for(int v=0;v<nVertices;v++)
        {
            if(isEdge(u,v) && (distance(v)>distance(u) + weight(u,v)))return false;
        }
    }
}

void Graph::dijkstra(int source)
{
    initializeSingleSource(source);
    int vertex;
    for(int i=0;i<nVertices;i++)
    {
        vertex = extractMin();
        Set[vertex] = true;
        for(int v=0;v<nVertices;v++)
        {
            if(isEdge(vertex,v))relaxDij(vertex,v);
        }
    }
}

void Graph::printSingleSourceShortestPath(int source,int dest)
{
    if(source<0||source>=nVertices||dest<0||dest>=nVertices)
    {
        cout<<"The source and destination are not valid"<<endl;
        return;
    }
    //ofstream myOutfile("output.txt");
    stack<int> st;
    int vertex = dest;
    while(parent[vertex] != NULL_VALUE)
    {
        st.push(vertex);
        vertex = parent[vertex];
    }
    st.push(source);
    while(!st.empty())
    {
        vertex = st.top();
        //cout<<vertex<<"->";
        st.pop();
        if(!st.empty())myOutfile<<vertex<<" -> ";
        else myOutfile<<vertex;

    }
    //cout<<endl;
}

int Graph::calculateDistanceSum(int source, int dest,bool weightAbs)//weightAbs true for dijkstra
{
    int distanceSum=0;
    int vertex=dest;
    while(parent[vertex] != NULL_VALUE)
    {
        if(!weightAbs)distanceSum+=weight(parent[vertex],vertex);
        else distanceSum+=abs(weight(parent[vertex],vertex));
        vertex = parent[vertex];
    }
    return distanceSum;
}



int main(void)
{
    Graph g;
    ifstream myfile("input.txt");
    int n,m,o;
    int source, dest,ans;
    if(myfile.is_open())
    {
        myfile>>n>>m;
        //cout<<n<<" "<<m<<endl;
        g.setnVertices(n);
        int edge=m;
        while(edge--)
        {
            myfile>>n>>m>>o;
            //cout<<n<<" "<<m<<" "<<o<<endl;
            g.addEdge(n,m,o);
        }

        myfile>>source>>dest;
        //cout<<"source= "<<source<<" dest = "<<dest<<endl;
    }
    else cout<<"unable to open file"<<endl;

    myfile.close();
    //ofstream myOutfile("output.txt");
    //g.printGraph();

    if(g.bellmanFord(source))
    {
        ans = g.calculateDistanceSum(source,dest,false);
        //cout<<"Bellman Ford Distance: "<<ans<<endl;
        myOutfile<<"Bellman Ford Algorithm: \n"<<ans<<"\n";
        //myOutfile.close();
        g.printSingleSourceShortestPath(source,dest);
    }
    else
    {
	myOutfile<<"Bellman Ford Algorithm: Negative cycle found\n";
    }

    g.dijkstra(source);
    ans = g.calculateDistanceSum(source,dest,true);
    //cout<<"Dijkstra Algorithm: \n"<<ans<<endl;
    myOutfile<<"\n\nDijkstra Algorithm: \n"<<ans<<"\n";
    g.printSingleSourceShortestPath(source,dest);
    myOutfile.close();
    return 0;
}

















//#include<bits/stdc++.h>
//
//#define NULL_VALUE -999999
//#define INFINITY 999999
//#define WHITE 1
//#define GREY 2
//#define BLACK 3
//
//using namespace std;
//ofstream myOutfile("output3.txt");
//
//class Queue
//{
//    int queueInitSize ;
//    int queueMaxSize;
//    int * data;
//    int length;
//    int front;
//    int rear;
//public:
//    Queue();
//    ~Queue();
//    void enqueue(int item); //insert item in the queue
//    int dequeue(); //returns the item according to FIFO
//    bool empty(); //return true if Queue is empty
//};
//
//Queue::Queue()
//{
//    queueInitSize = 2 ;
//    queueMaxSize = queueInitSize;
//    data = new int[queueMaxSize] ; //allocate initial memory
//    length = 0 ;
//    front = 0;
//    rear = 0;
//}
//
//
//void Queue::enqueue(int item)
//{
//	if (length == queueMaxSize)
//	{
//		int * tempData ;
//		//allocate new memory space for tempList
//		queueMaxSize = 2 * queueMaxSize ;
//		tempData = new int[queueMaxSize] ;
//		int i, j;
//		j = 0;
//		for( i = rear; i < length ; i++ )
//		{
//			tempData[j++] = data[i] ; //copy items from rear
//		}
//		for( i = 0; i < rear ; i++ )
//		{
//			tempData[j++] = data[i] ; //copy items before rear
//		}
//		rear = 0 ;
//		front = length ;
//		delete[] data ; //free the memory allocated before
//		data = tempData ; //make list to point to new memory
//	}
//
//	data[front] = item ; //store new item
//	front = (front + 1) % queueMaxSize ;
//	length++ ;
//}
//
//
//bool Queue::empty()
//{
//	if(length == 0) return true ;
//	else return false ;
//}
//
//
//int Queue::dequeue()
//{
//	if(length == 0) return NULL_VALUE ;
//	int item = data[rear] ;
//	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
//	length-- ;
//	return item ;
//}
//
//
//Queue::~Queue()
//{
//    if(data) delete[] data; //deallocate memory
//    data = 0; //set to NULL
//}
//
////****************Queue class ends here************************
//
////****************Dynamic ArrayList class based************************
//
//typedef struct ListNode
//{
//    int node;
//    int weight;
//}Node;
//
//class ArrayList
//{
//	Node * list;
//	int length ;
//	int listMaxSize ;
//	int listInitSize ;
//public:
//	ArrayList() ;
//	~ArrayList() ;
//	int searchItem(int item);
//    void insertItem(int item,int weight);
//	void removeItem(int item);
//	void removeItemAt(int item);
//	int getPathWeight(int item);
//	Node getItem(int position);
//	int getLength();
//	bool empty();
//	void printList();
//} ;
//
//
//ArrayList::ArrayList()
//{
//	listInitSize = 2 ;
//	listMaxSize = listInitSize ;
//	list = new Node[listMaxSize] ;
//	length = 0 ;
//}
//
//void ArrayList::insertItem(int newitem, int weight)
//{
//	Node * tempList ;
//	if (length == listMaxSize)
//	{
//		//allocate new memory space for tempList
//		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
//		tempList = new Node[listMaxSize] ;
//		int i;
//        for( i = 0; i < length ; i++ )
//        {
//            tempList[i].node = list[i].node ; //copy all items from list to tempList
//            tempList[i].weight= list[i].weight;
//        }
//        delete[] list ; //free the memory allocated before
//        list = tempList ; //make list to point to new memory
//	};
//
//	list[length].node = newitem ; //store new item
//	list[length].weight = weight;
//	length++ ;
//}
//
//int ArrayList::searchItem(int item)
//{
//	int i = 0;
//	for (i = 0; i < length; i++)
//	{
//		if( list[i].node == item ) return i;// weight check korbe na, sudhu node value check korbe
//	}
//	return NULL_VALUE;
//}
//
//
//void ArrayList::removeItemAt(int position) ///do not preserve order of items!!!
//{
//	if ( position < 0 || position >= length ) return ; //nothing to remove
//	list[position] = list[length-1] ;
//	length-- ;
//}
//
//
//void ArrayList::removeItem(int item)
//{
//	int position;
//	position = searchItem(item) ;
//	if ( position == NULL_VALUE ) return ; //nothing to remove
//	removeItemAt(position) ;
//}
//
//
//Node ArrayList::getItem(int position)
//{
//	if(position < 0 || position >= length)
//    {
//        Node temp;
//        temp.node = NULL_VALUE;
//        temp.weight = NULL_VALUE;
//        return temp;
//    }
//	return list[position] ;
//}
//// node value return korbe na, puro node tai return korbe, so catch korar somoy consider it
//
//
//int ArrayList::getLength()
//{
//	return length ;
//}
//
//int ArrayList::getPathWeight(int item)
//{
//    int position;
//    position = searchItem(item);
//    if(position == NULL_VALUE)return NULL_VALUE;
//    return list[position].weight;
//}
//
//bool ArrayList::empty()
//{
//    if(length==0)return true;
//    else return false;
//}
//
//void ArrayList::printList()
//{
//    int i;
//    for(i=0;i<length;i++)
//        printf("%d-(%d) ", list[i].node, list[i].weight);
//    printf("Current size: %d, current length: %d\n", listMaxSize, length);
//}
//
//ArrayList::~ArrayList()
//{
//    if(list) delete [] list;
//    list = 0 ;
//}
//
//
////******************ArrayList class ends here*************************
//
////******************Graph class starts here**************************
//class Graph
//{
//	int nVertices, nEdges ;
//	bool directed ;
//	ArrayList  * adjList ;
//	int  *dist, *parent;
//	bool *Set;
//
//public:
//	Graph(bool dir = true);//declaration of default argument made only once
//	~Graph();
//	void setnVertices(int n);
//	void addEdge(int u, int v,int w);
//	void removeEdge(int u, int v);
//	bool isEdge(int u, int v);
//    int weight(int u,int v);
//    int getOccurence(int u,int v);
//    int getDist(int u, int v);
//    void printGraph();
//    void initializeSingleSource(int source);
//    void relax(int u, int v);
//    bool bellmanFord(int source);
//    int distance(int u);
//    void dijkstra(int source);
//    int extractMin();
//    void relaxDij(int u,int v);
//    void printSingleSourceShortestPath(int source,int dest);
//    int calculateDistanceSum(int source,int dest,bool weightAbs);//weightAbs true for dijkstra
//};
//
//
//Graph::Graph(bool dir)
//{
//	nVertices = 0 ;
//	nEdges = 0 ;
//	adjList = 0 ;
//	dist=0;
//	parent=0;
//	directed = dir ; //set direction of the graph
//	//define other variables to be initialized
//}
//
//void Graph::setnVertices(int n)
//{
//	this->nVertices = n ;
//	if(adjList!=0) delete[] adjList ; //delete previous list
//	adjList = new ArrayList[nVertices] ;
//
//	if(dist)delete [] dist;
//	dist = new int[nVertices];
//
//	if(parent) delete [] parent;
//	parent = new int [nVertices];
//
//	if(Set) delete [] Set;
//	Set = new bool[nVertices];
//}
//
//void Graph::addEdge(int u, int v, int w)
//{
//    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
//    this->nEdges++ ;
//	adjList[u].insertItem(v,w) ;
//	if(!directed) adjList[v].insertItem(u,w) ;
//}
//
//void Graph::removeEdge(int u, int v)
//{
//    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
//    this->nEdges-- ;
//    adjList[u].removeItem(v);
//    if(!directed)adjList[v].removeItem(u);
//}
//
//bool Graph::isEdge(int u, int v)
//{
//    //returns true if (u,v) is an edge, otherwise should return false
//    if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
//    else return false;
//}
//
//int Graph::getOccurence(int u, int v)
//{
//    int count=0;
//    for(int i=0;i<adjList[v].getLength();i++)
//    {
//        if(adjList[v].getItem(i).node==u)count++;
//    }
//    return count;
//}
//
//int Graph::weight(int u,int v)
//{
//    return adjList[u].getPathWeight(v);
//}
//
//void Graph::initializeSingleSource(int source)
//{
//    for(int i=0;i<nVertices;i++)
//    {
//        dist[i] = INFINITY;
//        parent[i] = NULL_VALUE;
//    }
//    dist[source] = 0;
//}
//
//void Graph::relax(int u,int v)//u and v are vertices of a directed graph in order
//{
//    if (dist[v]>dist[u]+weight(u,v))
//    {
//        dist[v] = dist[u] + weight(u,v);
//        parent[v] = u;
//    }
//
//}
//
//bool Graph::bellmanFord(int source)
//{
//    initializeSingleSource(source);
//    for(int i=1;i<nVertices;i++) // nVertices represents |G.V|-1
//    {
//        for(int u=0;u<nVertices;u++)
//        {
//            for(int v=0;v<nVertices;v++)
//            {
//                if(isEdge(u,v))
//                {
//                    relax(u,v);
//                }
//            }
//        }
//    }
//
//    //detecting negative cycle
//    for(int u=0;u<nVertices;u++)
//    {
//        for(int v=0;v<nVertices;v++)
//        {
//            if(isEdge(u,v) && (distance(v)>distance(u) + weight(u,v)))return false;
//        }
//    }
//}
//
//int Graph::distance(int u)
//{
//    return dist[u];
//}
//
//void Graph::printGraph()
//{
//    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
//    for(int i=0;i<nVertices;i++)
//    {
//        printf("%d:", i);
//        for(int j=0; j<adjList[i].getLength();j++)
//        {
//            Node temp = adjList[i].getItem(j);
//            printf(" %d-(%d)",temp.node, temp.weight);
//        }
//        printf("\n");
//    }
//}
//
//void Graph::printSingleSourceShortestPath(int source,int dest)
//{
//    if(source<0||source>=nVertices||dest<0||dest>=nVertices)
//    {
//        cout<<"The source and destination are not valid"<<endl;
//        return;
//    }
//    //ofstream myOutfile("output.txt");
//    stack<int> st;
//    int vertex = dest;
//    while(parent[vertex] != NULL_VALUE)
//    {
//        st.push(vertex);
//        vertex = parent[vertex];
//    }
//    st.push(source);
//    while(!st.empty())
//    {
//        vertex = st.top();
//        //cout<<vertex<<"->";
//        st.pop();
//        if(!st.empty())myOutfile<<vertex<<" -> ";
//        else myOutfile<<vertex;
//    }
//    //cout<<endl;
//}
//
//int Graph::calculateDistanceSum(int source, int dest,bool weightAbs)//weightAbs true for dijkstra
//{
//    int distanceSum=0;
//    int vertex=dest;
//    while(parent[vertex] != NULL_VALUE)
//    {
//        if(!weightAbs)distanceSum+=weight(parent[vertex],vertex);
//        else distanceSum+=abs(weight(parent[vertex],vertex));
//        vertex = parent[vertex];
//    }
//    return distanceSum;
//}
//
//void Graph::dijkstra(int source)
//{
//    initializeSingleSource(source);
//    int vertex;
//
//    for(int i=0;i<nVertices;i++)
//    {
//        vertex = extractMin();
//        Set[vertex] = true;
//
//        for(int v=0;v<nVertices;v++)
//        {
//            if(isEdge(vertex,v))relaxDij(vertex,v);
//        }
//    }
//
//
//}
//
//void Graph::relaxDij(int u,int v)
//{
//    if(dist[v]>dist[u]+abs(weight(u,v)))
//    {
//        dist[v] = dist[u] + abs(weight(u,v));
//        parent[v] = u;
//    }
//}
//
//int Graph::extractMin()
//{
//    int minDist = INFINITY;
//    int minValueVertex = 0;
//    for(int i=0;i<nVertices;i++)
//    {
//        if(dist[i]<minDist && !Set[i]) // if a vertex is visited, then it is true. Explore for only unvisited
//        {
//            minDist = dist[i];
//            minValueVertex = i;
//        }
//    }
//    return minValueVertex;
//}
//
//Graph::~Graph()
//{
//    //write your destructor here
//    if(adjList)delete [] adjList;
//    if(dist)delete[] dist;
//    if(parent) delete [] parent;
//    //delete nVertices,nEdges,directed;
//    //adjList=color=dist=parent=0;
//}
///// vertices start from 0
//
////**********************Graph class ends here******************************
//
//
//int main(void)
//{
//    Graph g;
//    ifstream myfile("input.txt");
//    int n,m,o;
//    int source, dest,ans;
//    if(myfile.is_open())
//    {
//        myfile>>n>>m;
//        //cout<<n<<" "<<m<<endl;
//        g.setnVertices(n);
//        int edge=m;
//        while(edge--)
//        {
//            myfile>>n>>m>>o;
//            //cout<<n<<" "<<m<<" "<<o<<endl;
//            g.addEdge(n,m,o);
//        }
//
//        myfile>>source>>dest;
//        //cout<<"source= "<<source<<" dest = "<<dest<<endl;
//    }
//    else cout<<"unable to open file"<<endl;
//
//    myfile.close();
//    //ofstream myOutfile("output.txt");
//    //g.printGraph();
//
//    if(g.bellmanFord(source))
//    {
//        ans = g.calculateDistanceSum(source,dest,false);
//        //cout<<"Bellman Ford Distance: "<<ans<<endl;
//        myOutfile<<"Bellman Ford Algorithm: \n"<<ans<<"\n";
//        //myOutfile.close();
//        g.printSingleSourceShortestPath(source,dest);
//    }
//
//    g.dijkstra(source);
//    ans = g.calculateDistanceSum(source,dest,true);
//    //cout<<"Dijkstra Algorithm: \n"<<ans<<endl;
//    myOutfile<<"\n\nDijkstra Algorithm: \n"<<ans<<"\n";
//    g.printSingleSourceShortestPath(source,dest);
//    myOutfile.close();
//    return 0;
//}
//
//


