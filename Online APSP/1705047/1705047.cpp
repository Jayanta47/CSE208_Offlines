///online
#include<bits/stdc++.h>

#define NULL_VALUE -99999
#define INFINITY 99999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define NIL -1
#define Println(s) cout<<s<<endl

using namespace std;


class Edge
{
    int u,v;
    double w;
public:
    Edge(int u,int v,double w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    Edge(){}
    void setVertex(int u)
    {
        this->v = u;
    }
    void setWeight(double w)
    {
        this->w = w;
        //cout<<"w= "<<this->w<<endl;
    }
    void setSource(int u)
    {
        this->u = u;
    }
    int getVertex(){return v;}
    double getWeight(){return w;}
    int getSource(){return u;}
};



class ArrayList
{
	Edge * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item);
    void insertItem(int item,double weight);
	void removeItem(int item);
	void removeItemAt(int item);
    void reWeight(int item,double w);

	Edge getItem(int position);
	int getLength();
	double getEdgeWeight(int item);
	bool empty();
	void printList();
} ;

ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new Edge[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem, double newWeight)
{
	Edge * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new Edge[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i].setVertex(list[i].getVertex()); //copy all items from list to tempList
            tempList[i].setWeight(list[i].getWeight());
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length].setVertex(newitem); //store new item
	list[length].setWeight(newWeight);
	length++ ;
}

int ArrayList::searchItem(int item)//returns the index of the node
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].getVertex() == item ) return i;// weight check korbe na, sudhu node value check korbe
        //cout<<"item= "<<item<<" getvertex="<<list[i].getVertex()<<endl;
	}
	//cout<<"end"<<endl;
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) ///does not preserve order of items!!!
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

Edge ArrayList::getItem(int position)
{
	if(position < 0 || position >= length)
    {
        Edge temp;
        temp.setVertex(NULL_VALUE);
        temp.setWeight(NULL_VALUE);
        return temp;
    }
	return list[position] ;
}
// node value return korbe na, puro node tai return korbe, so catch korar somoy consider it


int ArrayList::getLength()
{
	return length ;
}

double ArrayList::getEdgeWeight(int item)
{
    int position;
    position = searchItem(item);
    //cout<<"position = "<<position<<endl;
    if(position == NULL_VALUE)return INFINITY;
    return list[position].getWeight();
}

void ArrayList::reWeight(int item,double w)
{
    int position;
    position = searchItem(item);
    return list[position].setWeight(w);
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
        printf("%d-(%lf) ", list[i].getVertex(), list[i].getWeight());
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
	int *parent;
	double *dist;
	bool *Set;

	double **distanceMatrix;
	double **parentMatrix;

public:
	Graph(bool dir = true);//declaration of default argument made only once
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v,double w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDist(int u, int v);
    double distance(int u);
    void printGraph();

    void reweightEdge(int u, int v, double w);
    double getWeight(int u,int v);
    Edge *searchEdge(int u,int v);

    void floydWarshall();
    void prepareDistanceGraph();
    void prepareParentGraph();
    void printPredecessorMatrix();
    void printDistanceMatrix();

    void initializeSingleSource(int source);
    void relax(int u, int v);
    bool bellmanFord(int source);
    void dijkstra(int source);
    int extractMin();

    void johnsonsAlgo();
    void cleanSPInfo();

    double getShortestPathWeight(int u,int v);
    void printShortestPath(int u,int v, bool last=true);
    stack<int> getShortestPath(int u,int v);
    double getMatrixWeight(int u, int v)
    {
        return distanceMatrix[u][v];
    }

    void printSingleSourceShortestPath(int source,int dest);
    double calculateDistanceSum(int source,int dest,bool weightAbs);//weightAbs true for dijkstra
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	dist=0;
	parent=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(dist)delete [] dist;
	dist = new double[nVertices];

	if(parent) delete [] parent;
	parent = new int [nVertices];

	if(Set) delete [] Set;
	Set = new bool[nVertices];

	distanceMatrix = new double*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        distanceMatrix[i] = new double[nVertices];
        for(int j=0;j<nVertices;j++)
            distanceMatrix[i][j] = INFINITY; //initialize the matrix cells to 0
    }

    parentMatrix = new double *[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        parentMatrix[i] = new double[nVertices];
        for(int j=0;j<nVertices;j++)
            parentMatrix[i][j] = NIL; //initialize the matrix cells to 0
    }
}

bool Graph::addEdge(int u, int v, double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(isEdge(u,v))return false;
    this->nEdges++ ;
	adjList[u].insertItem(v,w) ;
	if(!directed) adjList[v].insertItem(u,w) ;
	return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
    else return false;
}

double Graph::getWeight(int u,int v)
{
    return adjList[u].getEdgeWeight(v);
}

double Graph::distance(int u)
{
    return dist[u];
}

void Graph::printGraph()
{
    printf("Number of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d :", i+1);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            Edge temp = adjList[i].getItem(j);
            //printf(" %d-(%ld)",temp.getVertex(), temp.getWeight());
            if(j!=0)cout<<" --> "<<temp.getVertex()+1<<"("<<temp.getWeight()<<")";
            else cout<<temp.getVertex()+1<<"("<<temp.getWeight()<<")";
        }
        printf("\n");
    }
}

Edge * Graph::searchEdge(int u,int v)
{
    if(isEdge(u,v))
    {
        Edge temp;
        temp = adjList[u].getItem(v);
        Edge *e = new Edge;
        e= &temp;
        return e;
    }
    return nullptr;
}

void Graph::reweightEdge(int u, int v, double w)
{
    if(isEdge(u,v))
    {
        adjList[u].reWeight(v,w);
        if(!directed)adjList[v].reWeight(u,w);
    }
    else
    {
        addEdge(u,v,w);
        if(!directed)addEdge(v,u,w);
    }
}


void Graph::floydWarshall()
{
    // Prepare the distance and predecessor matrices
    prepareDistanceGraph();
    prepareParentGraph();
    int i,j,k;
    //cout<<"done"<<endl;
    for(k=0;k<nVertices;k++)
    {
        ///each loop in k provides new distance matrix
        ///the value k represents Dk
        /// The recurrence relation:
        ///           | Wij if k=0
        /// dij(k) = |  min(dij(k-1),
        ///           |     dik(k-1) + dkj(k-1)  if k>=1

        ///           | Pij(k-1) if dij(k-1) <= dik(k-1) + dkj(k-1)
        /// Pij(k) = |  Pkj(k-1) if dij(k-1) > dik(k-1) + dkj(k-1)

        for(i=0;i<nVertices;i++)
        {
            for(j=0;j<nVertices;j++)
            {
                if(distanceMatrix[i][k]+distanceMatrix[k][j]<
                                           distanceMatrix[i][j])
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k]+distanceMatrix[k][j];
                    parentMatrix[i][j] = parentMatrix[k][j];
                }
            }
        }
    }
}

void Graph::prepareDistanceGraph()
{
    for(int i =0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(i==j){distanceMatrix[i][j] = 0;}
            else distanceMatrix[i][j] = getWeight(i,j);

            //cout<<"getweight"<<getWeight(i,j)<<" ";

        }
        //cout<<endl;
    }
}

void Graph::prepareParentGraph()
{
    for(int i =0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(i==j)parentMatrix[i][j] = NIL;
            else if(isEdge(i,j))parentMatrix[i][j] = i;
            else parentMatrix[i][j] = NIL;
        }
    }
}

void Graph::printDistanceMatrix()
{
    Println("Distance Matrix:");
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(distanceMatrix[i][j]==INFINITY)cout<<"INF ";
            else cout<<distanceMatrix[i][j]<<" ";
        }
        Println("");
    }
    Println("");
}

void Graph::printPredecessorMatrix()
{
    Println("Predecessor Matrix:");
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(parentMatrix[i][j] == NIL)cout<<"NIL ";
            else cout<<parentMatrix[i][j]+1<<" ";
        }
        cout<<endl;
    }
}

void Graph::initializeSingleSource(int source)
{
    for(int i=0;i<nVertices;i++)
    {
        dist[i] = INFINITY;
        parent[i] = NULL_VALUE;
        Set[i] = false;
    }
    dist[source] = 0;
}

void Graph::relax(int u,int v)//u and v are vertices of a directed graph in order
{
    if (dist[v]>dist[u]+getWeight(u,v))
    {
        dist[v] = dist[u] + getWeight(u,v);
        parent[v] = u;
    }

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
            if(isEdge(u,v) && (distance(v)>distance(u) + getWeight(u,v)))
            {
                //cout<<"neg cycle for "<<u<<" "<<v<<endl;
                return false;
            }
        }
    }

    return true;
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
        cout<<vertex<<"->";
        st.pop();
//        if(!st.empty())myOutfile<<vertex<<" -> ";
//        else myOutfile<<vertex;
    }
    cout<<endl;
}


double Graph::calculateDistanceSum(int source, int dest,bool weightAbs)//weightAbs true for dijkstra
{
    double distanceSum=0;
    int vertex=dest;
    //cout<<"done"<<endl;
    while(parent[vertex] != NULL_VALUE)
    {
        if(!weightAbs)distanceSum+=getWeight(parent[vertex],vertex);
        else distanceSum+=abs(getWeight(parent[vertex],vertex));
        vertex = parent[vertex];
    }
    return distanceSum;
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
            if(isEdge(vertex,v))relax(vertex,v);
        }
    }


}

void Graph::johnsonsAlgo()
{
    int s = nVertices,v;
    double w;
    Graph gtemp;
    gtemp.setnVertices(nVertices+1);

    for(int u=0;u<nVertices;u++)
    {
        for(int j=0;j<adjList[u].getLength();j++)
        {
            Edge e = adjList[u].getItem(j);
            v = e.getVertex();
            w = e.getWeight();
            gtemp.addEdge(u,v,w);
        }
    }

    //gtemp.printGraph();
    if(gtemp.bellmanFord(s)==false)
    {
        cout<<"The input graph contains a negative-weight cycle"<<endl;
    }
    else
    {
        double h[s];
        for(int i=0;i<=nVertices;i++)
        {
            h[i] = gtemp.calculateDistanceSum(s,i,false);
            //cout<<i+1<<"= "<<h[i]<<" ";
            //gtemp.printSingleSourceShortestPath(s,i);
        }
        int v;
        double newW;
        for(int u=0;u<nVertices;u++)
        {
            for(int j=0;j<adjList[u].getLength();j++)
            {
                Edge e = adjList[u].getItem(j);
                v = e.getVertex();
                newW = e.getWeight();
                newW = newW + h[u] - h[v];
                reweightEdge(u,v,newW);
            }
        }
        //cout<<"After reWeighting:"<<endl;
        //printGraph();
        cleanSPInfo();
        for(int u=0;u<nVertices;u++)
        {
            dijkstra(u);
            for(int v =0;v<nVertices;v++)
            {
                double S=calculateDistanceSum(u,v,false);
                distanceMatrix[u][v] = S+h[v]-h[u];
                if(parent[v] == NULL_VALUE)parentMatrix[u][v] = NIL;
                else parentMatrix[u][v] = parent[v];
            }
        }


        ///reviving the previously weighted graph
        for(int u=0;u<nVertices;u++)
        {
            for(int j=0;j<adjList[u].getLength();j++)
            {
                Edge e = adjList[u].getItem(j);
                v = e.getVertex();
                newW = gtemp.getWeight(u,v);
                reweightEdge(u,v,newW);
            }
        }
//        Println("After recovery");
//        printGraph();

    }


}

void Graph::cleanSPInfo()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            distanceMatrix[i][j] = INFINITY;
            parentMatrix[i][j] = NIL;
        }
    }
}

int Graph::extractMin()
{
    double minDist = INFINITY;
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

double Graph::getShortestPathWeight(int u,int v)
{
    return distanceMatrix[u][v];
}

void Graph::printShortestPath(int u,int v, bool last)
{
    if(u<0||u>=nVertices||v<0||v>=nVertices)
    {
        cout<<"The source and destination are not valid"<<endl;
        return;
    }

    stack<int> st;
    // here the source is u
    while(v != u)
    {
        st.push(v);
        v = parentMatrix[u][v];
    }
    int vertex;
    if(last==false)
    {

        cout<<"Path: "<<u+1;
    }
    else
    {
        cout<<u+1;
    }

    while(!st.empty())
    {

        vertex = st.top();
        st.pop();
        if(last == false)
        {
            if(st.empty())
            {
                cout<<"-->";
                break;
            }

        }
        cout<<" --> "<<vertex+1<<"("<<distanceMatrix[u][vertex]<<")";
        u=vertex;
    }
    if(last == true)
    {
        cout<<endl;
    }

}

stack<int> Graph::getShortestPath(int u,int v)
{
    stack<int> st;
    // here the source is u
    while(v != u)
    {
        st.push(v);
//        cout<<v<<" ";
        v = parentMatrix[u][v];
    }
    st.push(u);
    return st;
}

Graph::~Graph()
{
    if(adjList)delete [] adjList;
    if(dist)delete[] dist;
    if(parent) delete [] parent;
}





int main(void)
{
    //by default the graph is directed.
    int N,M;
    cin>>N>>M;
    Graph g;
    g.setnVertices(N);
    int u,v;
    double w;
    for(int i=0;i<M;i++)
    {
        cin>>u>>v>>w;
        if(!g.addEdge(u-1,v-1,w))
        {
            cout<<"Edge Insertion Failed"<<endl;
        }
    }
    cout<<"Graph Created"<<endl;
    int mamabari;
    cin>>mamabari;
    int Source, Dest;
    g.floydWarshall();
    Println("Floyd-Warshall algorithm implemented");
    while(true)
    {
        cin>>Source>>Dest;
        if(Source == -1 && Dest == -1)
        {
            Println("Program Terminated");
            return 0;
        }
        if(Source>N || Dest>N)
        {
            cout<<"Wrong Vertices!"<<endl;
        }
        else
        {
            cout<<"Shortest Path Weight: "<<g.getShortestPathWeight(Source-1, mamabari-1)+g.getShortestPathWeight(mamabari-1, Dest-1)<<endl;
            g.printShortestPath(Source-1, mamabari-1, false);
            g.printShortestPath( mamabari-1, Dest-1);
//            stack<int> s1;
//            stack<int> s2;
//            s1 = g.getShortestPath(Source-1, mamabari-1);
//            s2 = g.getShortestPath(mamabari-1, Dest-1);
//            int vertex, u_prev;
//            cout<<"Path: ";
//            while(!s1.empty())
//            {
//                vertex = s1.top();
//                s1.pop();
//                cout<<" --> "<<vertex+1<<"("<<g.getMatrixWeight(u_prev, vertex)<<")";
//                u_prev=vertex;
//            }
//            s2.pop();
//            while(!s2.empty())
//            {
//                vertex = s2.top();
//                s2.pop();
//                cout<<" --> "<<vertex+1<<"("<<g.getMatrixWeight(u_prev, vertex)<<")";
//                u_prev=vertex;
//            }
//            cout<<endl;
        }

    }
}

