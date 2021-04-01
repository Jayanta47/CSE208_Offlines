#ifndef ARRAYLIST_H

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
    void insertItem(int item,double weight);
	void removeItem(int item);
	void removeItemAt(int item);
    void reWeight(int item,double w);

	Edge getItem(int position);
	int getLength();
	double getEdgeWeight(int item);
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

void ArrayList::insertItem(int newitem, double newWeight)
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
            tempList[i].setVertex(list[i].getVertex()); //copy all items from list to tempList
            tempList[i].setWeight(list[i].getWeight());
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length].setVertex(newitem); //store new item
	list[length].setWeight(newWeight);
	length++ ;
}

int ArrayList::searchItem(int item)//returns the index of the node
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].getVertex() == item ) return i;// weight check korbe na, sudhu node value check korbe
        //cout<<"item= "<<item<<" getvertex="<<list[i].getVertex()<<endl;
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
        temp.setVertex(NULL_VALUE);
        temp.setWeight(NULL_VALUE);
        return temp;
    }
	return list[position] ;
}
// node value return korbe na, puro node tai return korbe, so catch korar somoy consider it


int ArrayList::getLength()
{
	return length ;
}

double ArrayList::getEdgeWeight(int item)
{
    int position;
    position = searchItem(item);
    //cout<<"position = "<<position<<endl;
    if(position == NULL_VALUE)return INFINITY;
    return list[position].getWeight();
}

void ArrayList::reWeight(int item,double w)
{
    int position;
    position = searchItem(item);
    return list[position].setWeight(w);
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
        printf("%d-(%lf) ", list[i].getVertex(), list[i].getWeight());
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}


#endif // ARRAYLIST_H
