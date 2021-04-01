#include<bits/stdc++.h>
using namespace std;

#define WHITE 1
#define GREY 2
#define BLACK 3
#include "Queue.h"
#include "ArrayList.h"
#include "Edge.h"
#include "FordFulkersonGraph.h"


int main(void)
{
    Graph g;
    ifstream myfile("D:/test cases/FoFl input2.txt");
    int n,m,o;
    int s,t;
    if(myfile.is_open())
    {
        myfile>>n>>m;
        g.setnVertices(n);
        int edge=m;
        while(edge--)
        {
            myfile>>n>>m>>o;
            if(!g.addEdge(n,m,o))
            {
                cout<<"Failed to add edge "<<n<<" "<<m<<endl;
            }
        }
        myfile>>s>>t;
    }
    else {cout<<"unable to open file"<<endl; return 0;}

    g.fordFulkerson(s,t);
    int ch;
    cout<<"Ford Fulkerson Algorithm For Maximum Flow Implemented"<<endl;
    cout<<"1. Show in Console"<<endl;
    cout<<"2. Write in File"<<endl;
    cin>>ch;
    if (ch == 1)
    {
        g.printFlowResult();
    }
    else if (ch==2)
    {
        cout<<"Enter Filename"<<endl;
        string filename;
        cin>>filename;
        g.writeFlowResultToFile(filename);
    }
    else
    {
        cout<<"Incorrect Command"<<endl;
    }


    return 0;

}
