/*
* Author: Jayanta Sadhu
* Ford Fulkerson Algorithm Implementation
*/

#ifndef FORDFULKERSONGRAPH_H
#define FORDFULKERSONGRAPH_H
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color, *dist, *parent;
	int *set_of_vertices;
	bool isBipartite; // store whether the graph is bipartite or not
	int maxFlow;
	vector<Edge> antiparallel_edges;
	map<pair<int, int>, int> replacement;
	vector<pair<Edge, int>> flow_result;
	Graph prepare_ResNetwork();

public:
    Graph(bool dir = true);//declaration of default argument made only once
    void setnVertices(int n);
    bool addEdge(int u,int v,int c);
    void removeEdge(int u, int v);
    void removeAllAdjacent(int u);
    bool isEdge(int u, int v);
    void printAdjVertices(int u);
    void toggleGraphType();
    int parentVertex(int u); // returns the parent vertex of u after breadth first search

    bool check_bipartite_util();
    int *vertices_set() { return set_of_vertices;}
    void reweightEdge(int u, int v, int w);//changes the capacity of edge (u,v) to w
    int getEdgeCapacity(int u,int v);// returns the capacity of the edge (u,v)
    Edge *searchEdge(int u,int v);// searches for edge (u,v) and returns the edge if found. Otherwise returns a null edge

    void printGraph();//prints graph in adjacent list format
    bool bfs_aug_path(int source, int terminal, bool bipartite = false); /*will check if there is an augmentation path
    by running breadth first search in the graph*/
    bool bfs_bipartite(int source);
    bool isGraphBipartite() {return isBipartite;}
    void fordFulkerson(int s,int t); // will calculate maximum flow
    void MaxFlowResult(Graph residual_g); // stores the MaxFlow Result
    int maxFlowValue() { return maxFlow;} // returns max flow
    vector<pair<Edge, int>> getFlowResult(); // returns the vector containing edges with capacity and flow
    void printFlowResult();
    void writeFlowResultToFile(string filename);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	color=0;
	dist=0;
	parent=0;
	set_of_vertices = 0;
	isBipartite = true;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(color)delete [] color;
	color = new int [nVertices];

	if(dist)delete [] dist;
	dist = new int[nVertices];

	if(parent) delete [] parent;
	parent = new int [nVertices];

	if(set_of_vertices) delete [] set_of_vertices;
	set_of_vertices = new int [nVertices];
}

bool Graph::addEdge(int u,int v,int c)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(isEdge(u,v))return false;
    this->nEdges++ ;

    Edge e(u,v,c);
    adjList[u].insertItem(e) ;
    if(!directed)
    {
        Edge e_(v,u,c);
        adjList[v].insertItem(e_) ;
    }
    if(isEdge(v,u))
    {
        antiparallel_edges.push_back(e);
    }
    return true;
}

void Graph::toggleGraphType()
{
    if(directed)directed = false;
    else directed = true;
    //if(directed)cout<<"Directed Graph"<<endl;
    //else cout<<"Undirected Graph"<<endl;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed)adjList[v].removeItem(u);
}

void Graph::removeAllAdjacent(int u)
{
    while(adjList[u].getLength())
        adjList[u].removeItemAt(0);
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
    else return false;
}

int Graph::parentVertex(int u)
{
    return parent[u];
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    cout<<"The Adjacent Vertices of vertex "<<u<<" are: ";
    adjList[u].printList();

}

int Graph::getEdgeCapacity(int u,int v)
{
    return adjList[u].getCapacity(v);
}

bool Graph::bfs_aug_path(int source,int terminal, bool bipartite)
{
    if(source<0||source>=nVertices)return false;
    int u,v;
    //white color represents unvisited node
    //grey color represents visited but not completely explored node
    //black color represents visited and explored node
    for(int i=0;i<nVertices;i++)
    {
        color[i] = WHITE;
        dist[i] = INFINITY;
        parent[i] = NULL_VALUE;
    }
    color[source] = GREY;
    dist[source] = 0;
    Queue Q ;
    Q.enqueue(source);
    while(!Q.empty())
    {
        u = Q.dequeue();
        for(int i=0;i<adjList[u].getLength();i++)
        {
            Edge e = adjList[u].getItem(i);
            v = e.getV();

            if(color[v]==WHITE && getEdgeCapacity(u,v)>0)
            {
                color[v] = GREY;
                dist[v]= dist[u]+1;
                parent[v]=u;
                Q.enqueue(v);
            }
        }
        color[u]= BLACK;
        //cout<<"Done"<<endl;
    }
    if(color[terminal] == BLACK ) return true; // true is returned for an augmented path and false otherwise
    else return false;

}

bool Graph::bfs_bipartite(int source)
{
    if(source<0||source>=nVertices)return false;
    int u,v;
    int total_V = nVertices - 2;

    int current_set_state = 1;
    set_of_vertices[source] = current_set_state;
    Queue Q ;
    Q.enqueue(source);
    while(!Q.empty())
    {
        u = Q.dequeue();
        current_set_state = -1*set_of_vertices[u];
        for(int i=0;i<adjList[u].getLength();i++)
        {
            Edge e = adjList[u].getItem(i);
            v = e.getV();
            if(set_of_vertices[v] == 0)
            {
                set_of_vertices[v] = current_set_state;
                Q.enqueue(v);

            }
            else if(set_of_vertices[u] == set_of_vertices[v])
            {
                return false;
            }

        }
    }

    return true;
}

bool Graph::check_bipartite_util()
{
    for(int i=0;i<nVertices;i++)
    {
        set_of_vertices[i] = 0;
    }
    for(int i=0;i<nVertices-2;i++)
    {
        color[i] = WHITE;
    }
    for(int u = 0; u < nVertices-2; u++)
    {
        if(set_of_vertices[u] == 0)
        {
            if(!bfs_bipartite(u))
            {
                isBipartite = false;
                return false;
            }
        }
    }
    isBipartite = false;
    return true;
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

            if(j!=0)cout<<" --> "<<temp.getV()<<"("<<temp.getCapacity()<<")";
            else cout<<temp.getV()<<"("<<temp.getCapacity()<<")";
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

void Graph::reweightEdge(int u, int v, int c)
{
    if(isEdge(u,v))
    {
        adjList[u].reWeight(v,c);
        if(!directed)adjList[v].reWeight(u,c);
    }
    else
    {
        addEdge(u,v,c);
        if(!directed)addEdge(v,u,c);
    }
}


Graph Graph::prepare_ResNetwork()
{
    int antiparallel_nos = antiparallel_edges.size();
    int nVertices_new = nVertices + antiparallel_nos;

    Graph residual_g;
    residual_g.setnVertices(nVertices_new);
    for(int u=0;u<nVertices;u++)
    {
        for(int v=0;v<adjList[u].getLength();v++)
        {
            Edge e = adjList[u].getItem(v);
            residual_g.addEdge(e.getU(),e.getV(),e.getCapacity());
        }
    }

    for(int new_e_sl = 0; new_e_sl < antiparallel_nos; new_e_sl++)
    {
        Edge e = antiparallel_edges[new_e_sl];
        residual_g.removeEdge(e.getU(), e.getV());
        if(!residual_g.addEdge(e.getU(), nVertices+new_e_sl, e.getCapacity()))cout<<"Failed"<<endl;
        if(!residual_g.addEdge(nVertices+new_e_sl, e.getV(), e.getCapacity()))cout<<"Failed"<<endl;
        replacement.insert(make_pair(make_pair(e.getU(), e.getV()), nVertices+new_e_sl));
    }
    return residual_g;
}


void Graph::fordFulkerson(int s, int t)
{
    Graph residual_g = prepare_ResNetwork();
    maxFlow = 0;

    while(residual_g.bfs_aug_path(s,t))
    {
        int pathResidualCap = INFINITY;
        for(int v = t; v != s; v = residual_g.parentVertex(v))
        {
            int u = residual_g.parentVertex(v);
            pathResidualCap = min(pathResidualCap,residual_g.getEdgeCapacity(u,v));
        }

        for(int v = t; v != s; v = residual_g.parentVertex(v))
        {
            int u = residual_g.parentVertex(v);
            residual_g.reweightEdge(u,v,residual_g.getEdgeCapacity(u,v)-pathResidualCap);
            residual_g.reweightEdge(v,u,residual_g.getEdgeCapacity(v,u)+pathResidualCap);
        }
        maxFlow += pathResidualCap;
    }
    this->MaxFlowResult(residual_g);
}

void Graph::MaxFlowResult(Graph residual_g)
{
    map<pair<int, int>, int> :: iterator itr;

    for(int i=0;i<nVertices;i++)
    {
        for(int j=0; j<adjList[i].getLength();j++)
        {
            Edge temp = adjList[i].getItem(j);
            itr = replacement.find(make_pair(temp.getU(), temp.getV()));
            if(itr!=replacement.end())
            {
                pair<int, int> p = itr->first;
                int node = itr->second;
                flow_result.push_back(make_pair(temp,
                                                temp.getCapacity()-residual_g.getEdgeCapacity(node, p.second)));
            }
            else
            {
                flow_result.push_back(make_pair(temp,
                                                temp.getCapacity()-residual_g.getEdgeCapacity(temp.getU(), temp.getV())));
            }

        }

    }
}


vector<pair<Edge, int>> Graph::getFlowResult()
{
    return flow_result;
}


void Graph::printFlowResult()
{
    cout<<"Maxflow:"<<maxFlow<<endl;
    vector<pair<Edge, int>> :: iterator itr;
    for(itr = flow_result.begin(); itr != flow_result.end(); itr++)
    {
        Edge e = itr->first;
        int flow = itr->second;
        cout<<e.getU()<<" "<<e.getV()<<" "<<flow<<"/"<<e.getCapacity()<<endl;
    }
}

void Graph::writeFlowResultToFile(string filename)
{
    ofstream outfile;
    outfile.open(filename);
    if(outfile.is_open())
    {
        outfile<<maxFlow<<endl;
        vector<pair<Edge, int>> :: iterator itr;
        for(itr = flow_result.begin(); itr != flow_result.end(); itr++)
        {
            Edge e = itr->first;
            int flow = itr->second;
            outfile<<e.getU()<<" "<<e.getV()<<" "<<flow<<"/"<<e.getCapacity()<<endl;
        }
        cout<<"Output Results Written Successfully"<<endl;
    }
    else
    {
        cout<<"Unable to open file: "<<filename<<endl;
    }
}


#endif




