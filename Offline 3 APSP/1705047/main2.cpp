
#include "Graph_APSP.h"

using namespace std;


int main(void)
{
    ifstream infile;
    infile.open("input.txt");
    string s, u, v;
    int n, m;
    double w;
    map<string, int> mp;
    mp["Dhaka"] = 1;
    mp["Khulna"] = 2;
    mp["Rajshahi"] = 3;
    mp["Barisal"] = 4;
    mp["Sylhet"] = 5;

    Graph g;
    g.setnVertices(n);

    if (infile.is_open())
    {
        infile>>n>>m;
        cout<<"Vertices = "<<n<<" Edges = "<<m<<endl;
        for(int i=0;i<m;i++)
        {
            infile>>u>>v>>w;
            cout<<mp[u]<<" "<<mp[v]<<" "<<w<<endl;
        }
    }
}



