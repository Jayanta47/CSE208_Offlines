#include<bits/stdc++.h>
using namespace std;

#define WHITE 1
#define GREY 2
#define BLACK 3
#include "Queue.h"
#include "ArrayList.h"
#include "Edge.h"
#include "MaximumBipartite.h"


int main(void)
{
    MaximumBipartite mb;
    ifstream myfile("D:/test cases/Matching/in6.txt");
    int n,m;
    int s,t;
    if(myfile.is_open())
    {
        myfile>>n>>m;
        mb.setnVertices(n+2);
        int edge=m;
        while(edge--)
        {
            myfile>>n>>m;
            if(!mb.addEdge(n,m))
            {
                cout<<"Failed to add edge "<<n<<" "<<m<<endl;
            }
        }
    }
    else {cout<<"unable to open file"<<endl; return 0; }

    bool result;

    if(!mb.construct_bipartite()) result = false;
    else
    {
        mb.run_matching();
        result = true;
    }
    int ch;
    cout<<"Maximum Bipartite Matching Algorithm Implemented"<<endl;
    cout<<"1. Show in Console"<<endl;
    cout<<"2. Write in File"<<endl;
    cin>>ch;
    if (ch == 1)
    {
        if(result)mb.printMatching();
        else cout<<"The Graph is not a Bipartite Graph"<<endl;
    }
    else if (ch==2)
    {
        cout<<"Enter Filename"<<endl;
        string filename;
        cin>>filename;
        mb.writeResultToFile(filename, result);
    }
    else
    {
        cout<<"Incorrect Command"<<endl;
    }

    return 0;

}

