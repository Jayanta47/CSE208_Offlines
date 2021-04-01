#ifndef MAXBIPARTITE_H
#define MAXBIPARTITE_H
#include "FordFulkersonGraph.h"
#define Edge_weight 1

class MaximumBipartite
{
    Graph g;
    int nVertices, nEdges; /// vertices already include source and terminal
    int source, terminal;

public:
    MaximumBipartite(bool dir = false);
    void setnVertices(int n);
    bool addEdge(int u,int v); /// add undirected edge of Edge_weight u-v
    bool construct_bipartite(); /// construct a graph and check if its bipartite
    void run_matching(); /// implement Ford Fulkerson Algorithm to find Maximum Matching
    void printMatching(); /// print the edges corresponding to maximum matching
    void printGraph(); /// print constructed Graph
    void writeResultToFile(string filename, bool result); /// Write result of the algorithm to a file
};

MaximumBipartite::MaximumBipartite(bool dir)
{
    nVertices = 0 ;
	nEdges = 0 ;
	if (!dir)g.toggleGraphType(); /// Initially Toggled graph to Undirected(was directed by default)
}

void MaximumBipartite::setnVertices(int n)
{
	this->nVertices = n ;
	g.setnVertices(nVertices);
}

bool MaximumBipartite::addEdge(int u, int v)
{
    return g.addEdge(u,v,Edge_weight);
}

void MaximumBipartite::printGraph()
{
    g.printGraph();
}

bool MaximumBipartite::construct_bipartite()
{
    if(g.check_bipartite_util())
    {
        int *vertex_set = g.vertices_set();
        source = nVertices-2;
        terminal = source+1;
        for(int i = 0; i <nVertices-2; i++)
        {
            if(vertex_set[i] == -1)
            {
                g.removeAllAdjacent(i);
            }
        }
        g.toggleGraphType(); /// Undirected Graph toggled to directed Graph
        for(int i = 0; i <nVertices-2; i++)
        {
            if(vertex_set[i] == 1)g.addEdge(source, i, Edge_weight);
            else g.addEdge(i, terminal, Edge_weight);
        }
        return true;
    }
    return false;
}

void MaximumBipartite::run_matching()
{
    g.fordFulkerson(source, terminal);
}

void MaximumBipartite::printMatching()
{
    cout<<g.maxFlowValue()<<endl;
    vector<pair<Edge, int>> flowResult = g.getFlowResult();
    vector<pair<Edge, int>> :: iterator itr;
    for(itr = flowResult.begin(); itr != flowResult.end(); itr++)
    {
        Edge e = itr->first;
        int flow = itr->second;
        if(flow == 1 && e.getU()!=source && e.getV()!=terminal)
        {
            cout<<e.getU()<<" "<<e.getV()<<endl;
        }
    }
}

void MaximumBipartite::writeResultToFile(string filename, bool result)
{
    ofstream outfile(filename);
    if(outfile.is_open())
    {
        if(result)
        {
            outfile<<g.maxFlowValue()<<endl;
            vector<pair<Edge, int>> flowResult = g.getFlowResult();
            vector<pair<Edge, int>> :: iterator itr;
            for(itr = flowResult.begin(); itr != flowResult.end(); itr++)
            {
                Edge e = itr->first;
                int flow = itr->second;
                if(flow == 1 && e.getU()!=source && e.getV()!=terminal)
                {
                    outfile<<e.getU()<<" "<<e.getV()<<endl;
                }
            }
        }
        else
        {
            outfile<<"The Graph is not a Bipartite Graph"<<endl;
        }
        cout<<"Output Results Written Successfully"<<endl;
    }
    else
    {
        cout<<"Unable to open file: "<<filename<<endl;
    }
}




#endif // MAXBIPARTITE_H
