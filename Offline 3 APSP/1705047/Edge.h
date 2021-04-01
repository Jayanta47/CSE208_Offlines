#ifndef EDGE_H
#define NULL_VALUE -99999
#define INFINITY 99999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define NIL -1
#define Println(s) cout<<s<<endl
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

#endif // EDGE_H


