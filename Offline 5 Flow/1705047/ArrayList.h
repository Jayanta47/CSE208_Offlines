/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ArrayList.h
 * Author: USER
 *
 * Created on March 31, 2020, 12:16 AM
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#define NULL_VALUE -99999
#define INFINITY 99999

#include "Edge.h"


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
    void insertItem(Edge e);
    void removeItem(int item);
    void removeItemAt(int item);
    void reWeight(int item,int w);

    Edge getItem(int position); /* returns the item at position 'position' */
    int getLength();
    int getCapacity(int item);
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

void ArrayList::insertItem(Edge e)
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
            tempList[i].setU(list[i].getU());
            tempList[i].setV(list[i].getV()); //copy all items from list to tempList
            tempList[i].setCapacity(list[i].getCapacity());
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

//	list[length].setU(u);
//    list[length].setV(v); //store new item
//	list[length].setCapacity(c);
    list[length] = e;
	length++ ;
}

int ArrayList::searchItem(int item)//returns the index of the node
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].getV() == item ) return i;
        //cout<<"item= "<<item<<" getV="<<list[i].getV()<<endl;
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
        temp.setU(NULL_VALUE);
        temp.setV(NULL_VALUE);
        temp.setCapacity(NULL_VALUE);
        return temp;
    }
	return list[position] ;
}


int ArrayList::getLength()
{
    return length ;
}

int ArrayList::getCapacity(int item)
{
    int position;
    position = ArrayList::searchItem(item);
    //cout<<"position = "<<position<<endl;
    if(position == NULL_VALUE)return 0; // if there is no edge then capacity is 0
    return list[position].getCapacity();
}

void ArrayList::reWeight(int item,int w)
{
    int position;
    position = searchItem(item);
    list[position].setCapacity(w);
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
        printf("%d-(%d) ", list[i].getV(), list[i].getCapacity());
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}



#endif /* ARRAYLIST_H */

