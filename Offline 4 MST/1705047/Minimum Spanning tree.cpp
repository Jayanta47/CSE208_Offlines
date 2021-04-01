///Created on 14/3/2020
///Last modified 28/3/2020
///Author Jayanta Sadhu


#include<bits/stdc++.h>

#define NULL_VALUE -999999
#define INFINITY 999999
#define NIL -1
#define Println(s) cout<<s<<endl


using namespace std;
ofstream myOutfile("outputMST.txt");

class Edge
{
    int u,v;
    int w;
public:
    Edge(int u,int v,int w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    Edge(){}
    void set_v(int v)
    {
        this->v = v;
    }
    void setWeight(int w)
    {
        this->w = w;
        //cout<<"w= "<<this->w<<endl;
    }
    void set_u(int u)
    {
        this->u = u;
    }
    int get_u() {return u;}
    int get_v() {return v;}
    int getWeight() const {return w;}
};

class Pair
{
    int u,v;
public:
    Pair(int u,int v)
    {
        this->u = u;
        this->v = v;
    }
    int getU() const {return u;}
    int getV() const {return v;}
};

class PairComparator
{
public:
    int operator() (const Pair& p1, const Pair& p2)
    {
        return p1.getV()>p2.getV();
    }
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
    void insertItem(int newitemU,int newitemV, int newWeight);
	void removeItem(int item);
	void removeItemAt(int item);
    void reWeight(int item,int w);

	Edge getItem(int position);
	int getLength();
	int getEdgeWeight(int item);
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

void ArrayList::insertItem(int newitemU,int newitemV, int newWeight)
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
            tempList[i].set_u(list[i].get_u());
            tempList[i].set_v(list[i].get_v()); //copy all items from list to tempList
            tempList[i].setWeight(list[i].getWeight());
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length].set_u(newitemU);
	list[length].set_v(newitemV); //store new item
	list[length].setWeight(newWeight);
	length++ ;
}

int ArrayList::searchItem(int item)//returns the index of the node
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].get_v() == item ) return i;// weight check korbe na, sudhu node value check korbe
        //cout<<"item= "<<item<<" get_v="<<list[i].get_v()<<endl;
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
        temp.set_u(NULL_VALUE);
        temp.set_v(NULL_VALUE);
        temp.setWeight(NULL_VALUE);
        return temp;
    }
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

int ArrayList::getEdgeWeight(int item)
{
    int position;
    position = searchItem(item);
    //cout<<"position = "<<position<<endl;
    if(position == NULL_VALUE)return INFINITY;
    return list[position].getWeight();
}

void ArrayList::reWeight(int item,int w)
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
        printf("%d-(%lf) ", list[i].get_v(), list[i].getWeight());
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Disjoint_Set
{
    int *parent, *rank, n;
    void Link(int x,int y)
    {
        if (rank[x]>rank[y])
        {
            parent[y]= x;
        }
        else parent[x]=y;
        if (rank[x]==rank[y])
        {
            rank[y]++;
        }
    }
public:
    Disjoint_Set(int n)
    {
        parent = new int[n];
        rank = new int[n];
        this->n = n;
    }

    void Make_Set(int x)
    {
        parent[x] = x;
        rank[x] = 0;
    }

    int Find_Set(int x)
    {
        if(parent[x]==x)
        {
            return x;
        }
        else
        {
            int new_parent = Find_Set(parent[x]);
            parent[x] = new_parent;
            return new_parent;
        }
    }

    void Union(int u,int v)
    {
        Link(Find_Set(u), Find_Set(v));
    }

    void Print(int u)
    {
        vector<int> v;

        for(int i=0;i<n;i++)
        {
            if(parent[i] == u)v.push_back(i);
        }



        cout<<"Elements of the set containing "<<u<<":"<<endl<<"{ ";
        for(int i=0;i<v.size();i++)
        {
            cout<<v[i]<<" ,";
        }
        cout<<"}"<<endl;
    }

};

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int  *key, *parent;
	bool *Set;
	stack<Pair> st;

	int MSTtreeWeightK;
	int MSTtreeWeightP;

public:
	Graph(bool dir = false);//declaration of default argument made only once
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int weight(int u,int v);
    int graphVertices(){return nVertices;}
    int getDist(int u, int v);
    void printGraph();

    int distance(int u);
    void cleanStack();
    int treeWeightKrus();
    int treeWeightPrim();

    void initialize(int source);
    void MST_Prim_Algo(int root);
    void MST_Kruskal_Algo();

    void MST_Prim_Print(int root,bool file = true);
    void MST_Kruskal_print(bool file = true);

};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	key=0;
	parent=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(key)delete [] key;
	key = new int[nVertices];

	if(parent) delete [] parent;
	parent = new int [nVertices];

	if(Set) delete [] Set;
	Set = new bool[nVertices];

	MSTtreeWeightK = 0;
	MSTtreeWeightP = 0;
}

bool Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(isEdge(u,v))return false;
    this->nEdges++ ;
	adjList[u].insertItem(u,v,w) ;
	if(!directed) adjList[v].insertItem(v,u,w) ;
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

int Graph::weight(int u,int v)
{
    return adjList[u].getEdgeWeight(v);
}

int Graph::distance(int u)
{
    return key[u];
}

void Graph::cleanStack()
{
    while(!st.empty())
    {
        st.pop();
    }
}

void Graph::initialize(int source)
{
    for(int i=0;i<nVertices;i++)
    {
        key[i] = INFINITY;
        parent[i] = NIL;
        Set[i] = false;
    }
    key[source] = 0;
}

void Graph::MST_Prim_Algo(int source)
{
    initialize(source);
    priority_queue<Pair , vector<Pair>,PairComparator> pq;

    pq.push(Pair(source,0)); // the first element in pair is vertex and second one is weight
    while(!pq.empty())
    {
        Pair p = pq.top();
        int u = p.getU();
        Set[u] = true;
        pq.pop();
        //cout<<"The selected vertex = "<<u<<endl;
        for(int i=0;i<adjList[u].getLength();i++)
        {
            Edge e = adjList[u].getItem(i);
            int vertex = e.get_v();
            int w = weight(u,vertex);
            if(Set[vertex]==false && w<key[vertex])
            {
                parent[vertex] = u;
                key[vertex] = w;
                //cout<<" Inserted: "<<vertex<<" "<<w<<endl;
                pq.push(Pair(vertex,w));
            }
        }
    }

    MSTtreeWeightP = 0;
    for(int i=0;i<nVertices;i++)
    {
        if(parent[i]!=NIL)
        {
            MSTtreeWeightP += weight(parent[i],i);
        }
    }
}

void Graph::MST_Kruskal_Algo()
{
    cleanStack();
    Disjoint_Set ds(nVertices);
    for(int u=0;u<nVertices;u++)
    {
        ds.Make_Set(u);
    }

    vector<Edge> v;
    stack<Pair> stTemp ;
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<adjList[i].getLength();j++)
        {
            Edge e = adjList[i].getItem(j);
            v.push_back(e);
        }
    }

    sort(v.begin(),v.end(),
         [] (const Edge& e1, const Edge& e2)
         {
             return e1.getWeight()< e2.getWeight();
         });

    vector<Edge>:: iterator iter;
    for(iter = v.begin();iter != v.end(); iter++)
    {
        Edge e = *iter;
        int u = e.get_u();
        int v = e.get_v();
        if(ds.Find_Set(u)!= ds.Find_Set(v))
        {
            st.push(Pair(u,v));
            stTemp.push(Pair(u,v));
            ds.Union(u,v);
        }
    }
    MSTtreeWeightK = 0;
    while(!stTemp.empty())
    {
        Pair p = stTemp.top();
        stTemp.pop();
        MSTtreeWeightK += weight(p.getU(),p.getV());
    }


}

void Graph::printGraph()
{
    printf("Number of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d :", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            Edge temp = adjList[i].getItem(j);
            //printf(" %d-(%ld)",temp.get_v(), temp.getWeight());
            if(j!=0)cout<<" --> "<<temp.get_v()<<"("<<temp.getWeight()<<")";
            else cout<<temp.get_v()<<"("<<temp.getWeight()<<")";
        }
        printf("\n");
    }
}

void Graph::MST_Kruskal_print(bool file)
{
    stack<Pair> stTemp = st;
    if(file)
    {
        myOutfile<<treeWeightKrus()<<endl;
        myOutfile<<"Kruskal's Algorithm: \n";
        while(!stTemp.empty())
        {
            Pair p = stTemp.top();
            stTemp.pop();
            myOutfile<<p.getU()<<" "<<p.getV()<<"\n";
        }
    }
    else
    {
        cout<<"Kruskal's Algorithm:"<<endl;
        while(!stTemp.empty())
        {
            Pair p = stTemp.top();
            stTemp.pop();
            cout<<p.getU()<<" "<<p.getV()<<endl;
        }
    }

}

void Graph::MST_Prim_Print(int root,bool file)
{
    if(file)
    {
        myOutfile<<"Prim's Algorithm:\nRoot node = "<<root<<"\n";
        for(int v=0;v<nVertices;v++)
        {
            if(parent[v]!=NIL)
            {
            myOutfile<<parent[v]<<" "<<v<<"\n";
            }
        }
    }
    else
    {
        cout<<"Prim's Algorithm:\nRoot node = "<<root<<endl;
        for(int i=0;i<nVertices;i++)
        {
            if(parent[i]!=NIL)
            {
            cout<<parent[i]<<" "<<i<<endl;
            }
        }
    }

}

int Graph::treeWeightKrus()
{
    return MSTtreeWeightK;
}

int Graph::treeWeightPrim()
{
    return MSTtreeWeightP;
}

Graph::~Graph()
{
    if(adjList)delete [] adjList;
    if(key)delete[] key;
    if(parent) delete [] parent;
}

int main(void)
{
    Graph g;
    ifstream myfile("MST input.txt");
    srand(time(0));
    int n,m,o;
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
            if(!g.addEdge(n,m,o))
            {
                cout<<"Failed to add edge "<<n<<" "<<m<<endl;
            }
        }
    }
    else cout<<"unable to open file"<<endl;

    //g.printGraph();
    int ch;
    while(true)
    {
        Println("1. Print Graph");
        Println("2. Run Prims Algorithm");
        Println("3. Run Kruskal's Algorithm");
        Println("4. Write file");
        Println("5. Exit");
        cin >>ch;
        int source = rand()%g.graphVertices();
        if(ch==1)
        {
            g.printGraph();
        }
        else if(ch==2)
        {
            Println("Enter source:");
            cin>>source;
            if(source>=g.graphVertices())
            {
                Println("Invalid source");
                continue;
            }
            g.MST_Prim_Algo(source);
            Println("Prim's Algorithm executed.");
            Println("Minimum Spanning Tree weight(Prim):");
            Println(g.treeWeightPrim());
            g.MST_Prim_Print(source,false);
        }
        else if(ch == 3)
        {
            g.MST_Kruskal_Algo();
            Println("Kruskal's Algorithm executed.");
            Println("Minimum Spanning Tree weight(Kruskal):");
            Println(g.treeWeightKrus());
            g.MST_Kruskal_print(false);
        }
        else if(ch == 4)
        {
            myOutfile.seekp(0,ios::beg);
            g.MST_Prim_Algo(source);
            g.MST_Kruskal_Algo();
            g.MST_Kruskal_print(true);
            g.MST_Prim_Print(source, true);
            Println("File Writing Command Executed.");
        }
        else
        {
            exit(0);
        }
    }


    //g.MST_Prim_Algo(3);
    //g.MST_Kruskal_Algo();
    return 0;
}

