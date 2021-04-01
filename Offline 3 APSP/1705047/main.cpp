
/// Created on 8.3.2020
///Author Jayanta Sadhu
/// Ended 11:09

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
    int C;
    while(true)
    {
//        Println("\nEnter your choiche:");
//        Println("1. Clear distance and parent matrices");
//        Println("2. Implement Floyd-Warshall Algorithm");
//        Println("3. Implement Johnson's Algorithm");
//        Println("4. Shortest Path and Distance between u and v");
//        Println("5. Print Graph(in adjacency list format)");
//        Println("6. Print distance matrix D");
//        Println("7. Print parent matrix P");
//        Println("8. Any other key to exit");
        cin>>C;
        if(C==1)
        {
            g.cleanSPInfo();
            Println("APSP matrices cleared");
        }
        else if(C==2)
        {
            g.floydWarshall();
            Println("Floyd-Warshall algorithm implemented");
        }
        else if(C==3)
        {
            g.johnsonsAlgo();
            Println("Johnson's algorithm implemented");
        }
        else if(C==4)
        {
            // call function with value one less
            int u,v;
            cin>>u>>v;
            Println("Shortest Path Weight: "<<g.getShortestPathWeight(u-1,v-1));
            g.printShortestPath(u-1,v-1);
        }
        else if(C==5)
        {
            Println("Graph:");
            g.printGraph();
        }
        else if(C==6)
        {
            g.printDistanceMatrix();
        }
        else if(C==7)
        {
            g.printPredecessorMatrix();
        }
        else
        {
            return 0;
        }

    }
}


