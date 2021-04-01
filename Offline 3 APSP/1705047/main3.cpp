

#include "Graph_APSP.h"

using namespace std;


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
//            cout<<"Program Terminated"<<end;
            exit(0);
        }
        if(Source>N || Dest>N)
        {
            cout<<"Wrong Vertices!"<<endl;
        }
        else
        {
            cout<<"Shortest Path Weight: "<<g.getShortestPathWeight(Source-1, mamabari-1)+g.getShortestPathWeight(mamabari-1, Dest-1)<<endl;
            stack<int> s1;
            stack<int> s2;
            s1 = g.getShortestPath(Source-1, mamabari-1);
            s2 = g.getShortestPath(mamabari-1, Dest-1);
            int vertex, u_prev;
            cout<<"Path: ";
            while(!s1.empty())
            {
                vertex = s1.top();
                s1.pop();
                cout<<" --> "<<vertex+1<<"("<<g.getMatrixWeight(u_prev, vertex)<<")";
                u_prev=vertex;
            }
            s2.pop();
            while(!s2.empty())
            {
                vertex = s2.top();
                s2.pop();
                cout<<" --> "<<vertex+1<<"("<<g.getMatrixWeight(u_prev, vertex)<<")";
                u_prev=vertex;
            }
            cout<<endl;
        }

    }
}


