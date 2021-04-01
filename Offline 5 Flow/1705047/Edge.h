/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Edge.h
 * Author: USER
 *
 * Created on March 31, 2020, 12:21 AM
 */

#ifndef EDGE_H
#define EDGE_H

class Edge
{
    int u,v;
    int capacity;
public:
    Edge(int u,int v,int c)
    {
        this->u = u;
        this->v = v;
        this->capacity = c;
    }
    Edge()
    {
        u = v = capacity = NULL_VALUE;
    }
    void setU(int u)
    {
        this->u = u;
    }
    void setV(int v)
    {
        this->v = v;
    }
    void setCapacity(int c)
    {
        this->capacity = c;
        //cout<<"w= "<<this->w<<endl;
    }

    int getV(){return v;}
    int getCapacity(){return capacity;}
    int getU(){return u;}
};

#endif /* EDGE_H */

