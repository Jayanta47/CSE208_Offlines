#ifndef Binomial_heap

#include "BinomialNode.h"

class BinomialHeap
{
    BinomialNode *head;
protected:
    void BinomialLink(BinomialNode* Nchld, BinomialNode *Nprnt); //
    BinomialNode *heapRootMerge(BinomialHeap *H1, BinomialHeap *H2); //
    void insertNode(BinomialNode *Node); //
    BinomialNode *unionHeap(BinomialHeap *H1, BinomialHeap *H2); //
    int binCoefficient(int n, int r);
    void printBinTree(BinomialNode* Root, ofstream *outFile = nullptr);
public:
    BinomialHeap(); //
    BinomialHeap(int key); //
    BinomialHeap(BinomialNode *Node);//

    BinomialNode *FindMin();
    BinomialNode *ExtractMin();
    void Insert(int key); //
    void Union(BinomialHeap *H); //
    void Union(vector<int> keysList); //
    void print(ofstream *outFile = nullptr);
};


BinomialHeap::BinomialHeap()
{
    this->head = nullptr;
}


BinomialHeap::BinomialHeap(int key)
{
    BinomialNode *Node = new BinomialNode(key);
    this->head = Node;
}


BinomialHeap::BinomialHeap(BinomialNode *Node)
{
    this->head = Node;
}


void BinomialHeap::Insert(int x)
{
    BinomialNode *Node = new BinomialNode(x);
    this->insertNode(Node);
}


void BinomialHeap::insertNode(BinomialNode *Node)
{
    BinomialHeap *H_ = new BinomialHeap(Node);
    this->head = this->unionHeap(this, H_);
}


void BinomialHeap::BinomialLink(BinomialNode* Nchld, BinomialNode *Nprnt)
{
    Nprnt->addChildNode(Nchld);
}


BinomialNode *BinomialHeap::heapRootMerge(BinomialHeap *H1, BinomialHeap *H2)
{
    BinomialNode *proxyHead = new BinomialNode();
    BinomialNode *tailNeedle = proxyHead;

    BinomialNode *H1_rootListNode = H1->head;
    BinomialNode *H2_rootListNode = H2->head;

    if (H1_rootListNode == nullptr) return H2_rootListNode;
    if (H2_rootListNode == nullptr) return H1_rootListNode;

    while (H1_rootListNode != nullptr || H2_rootListNode != nullptr)
    {
        if (H1_rootListNode == nullptr)
        {
            tailNeedle->connectSibling(H2_rootListNode);
            tailNeedle = tailNeedle->getSibling();
            H2_rootListNode = H2_rootListNode->getSibling();
        }
        else if (H2_rootListNode == nullptr)
        {
            tailNeedle->connectSibling(H1_rootListNode);
            tailNeedle = tailNeedle->getSibling();
            H1_rootListNode = H1_rootListNode->getSibling();

        }
        else
        {
            if (H1_rootListNode->Degree() < H2_rootListNode->Degree())
            {
                tailNeedle->connectSibling(H1_rootListNode);
                tailNeedle = tailNeedle->getSibling();
                H1_rootListNode = H1_rootListNode->getSibling();

            }
            else
            {
                tailNeedle->connectSibling(H2_rootListNode);
                tailNeedle = tailNeedle->getSibling();
                H2_rootListNode = H2_rootListNode->getSibling();
            }

        }

    }

    return proxyHead->getSibling();
}


void BinomialHeap::Union(BinomialHeap *H)
{
    this->head = unionHeap(this, H);
}


void BinomialHeap::Union(vector<int> keylist)
{
    BinomialHeap *H_ = new BinomialHeap();
    for (auto x : keylist)
    {
        H_->Insert(x);
    }
    this->head = unionHeap(this, H_);

}


BinomialNode *BinomialHeap::unionHeap(BinomialHeap *H1, BinomialHeap *H2)
{
    BinomialHeap *H = new BinomialHeap();

    H->head = heapRootMerge(H1, H2);

    if (H->head == nullptr)
    {
        return H->head;
    }

    BinomialNode *prev_x = nullptr;
    BinomialNode *x = H->head;
    BinomialNode *next_x = x->getSibling();

    while (next_x != nullptr)
    {

        if (x->Degree() != next_x->Degree() ||
                (next_x->getSibling() != nullptr
                    && next_x->getSibling()->Degree() == x->Degree()))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {

            if (x->Key() <= next_x->Key())
            {

                x->connectSibling(next_x->getSibling());
                H->BinomialLink(next_x, x);

            }
            else
            {

                if (prev_x == nullptr)
                {
                    H->head = next_x;
                }
                else
                {
                    prev_x->connectSibling(next_x);
                }
                H->BinomialLink(x, next_x);
                x = next_x;

            }
        }

        next_x = x->getSibling();

    }

    return H->head;
}


BinomialNode *BinomialHeap::FindMin()
{
    BinomialNode *minNode = nullptr;
    BinomialNode *currentNode = this->head;

    int minKey = INT_MAX;

    while (currentNode != nullptr)
    {
        if (currentNode->Key() < minKey)
        {
            minKey = currentNode->Key();
            minNode = currentNode;
        }
        currentNode = currentNode->getSibling();
    }

    return minNode;
}


BinomialNode *BinomialHeap::ExtractMin()
{
    BinomialNode *prev_minNode = nullptr;
    BinomialNode *minNode = this->head;

    if (minNode == nullptr)
        return minNode;

    BinomialNode *temp = this->head->getSibling();
    int minKey = minNode->Key();

    while (temp != nullptr)
    {
        if (temp->Key() < minKey)
        {
            prev_minNode = minNode;
            minNode = temp;
            minKey = temp->Key();
        }
        temp = temp->getSibling();
    }

    if (prev_minNode == nullptr) this->head = minNode->getSibling();
    else prev_minNode->connectSibling(minNode->getSibling());

    BinomialNode *revList = nullptr;
    BinomialNode *currentNode = minNode->getChild();
    BinomialNode *nextNode = nullptr;
    while (currentNode != nullptr)
    {
        nextNode = currentNode->getSibling();
        currentNode->connectSibling(revList);
        revList = currentNode;
        currentNode = nextNode;
    }

    BinomialHeap *H_ = new BinomialHeap();
    H_->head = revList;

    this->head = this->unionHeap(this, H_);

    return minNode;

}


void BinomialHeap::print(ofstream *outFile)
{
    BinomialNode *temp = this->head;

    if (temp == nullptr)
    {
        if (outFile == nullptr)
        {
            cout<<"( The Binomial Heap is Empty )"<<endl;
        }
        else
        {
            (*outFile)<<"( The Binomial Heap is Empty )"<<"\n";
        }
    }
    else
    {
         while (temp != nullptr)
        {
            if (outFile == nullptr)
            {
                cout<<"Binomial Tree, B"<<temp->Degree()<<endl;
                cout<<"Level 0 : "<<temp->Key()<<endl;
            }
            else
            {
                (*outFile)<<"Binomial Tree, B"<<temp->Degree()<<"\n";
                (*outFile)<<"Level 0 : "<<temp->Key()<<"\n";
            }
            printBinTree(temp, outFile);
            temp = temp->getSibling();
        }
    }
}


void BinomialHeap::printBinTree(BinomialNode *Root, ofstream *outFile)
{
    int totalLevels = Root->Degree();
    if(totalLevels == 0)
        return;
    queue<BinomialNode*> Q;
    BinomialNode *temp;
    Q.push(Root->getChild());
    int level = 1, ctr = 0, target = this->binCoefficient(totalLevels, level);

    (outFile == nullptr) ? cout<<"Level 1 : " : (*outFile)<<"Level 1 : ";

    while(!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        while(temp!=nullptr)
        {
            if (temp->getChild() != nullptr)
            {
                Q.push(temp->getChild());
            }
            if (outFile == nullptr) cout<<temp->Key()<<" ";
            else (*outFile) << temp->Key()<<" ";
            ctr++;
            if (ctr == target)
            {
                if (outFile == nullptr)cout<<endl;
                else (*outFile) << "\n";
                ctr = 0;
                level++;
                target = this->binCoefficient(totalLevels, level);
                if (level <= totalLevels)
                {
                    (outFile == nullptr) ? cout<<"Level "<<level<<" : " : (*outFile)<<"Level "<<level<<" : ";
                }
            }
            temp = temp->getSibling();
        }
    }

}


int BinomialHeap::binCoefficient(int n, int r)
{
    int sum = 1;
    if (r > n-r)
        r = n-r;

    for(int i = 0; i<r ; i++)
    {
        sum *= (n-i);
        sum /= (i+1);
    }
    return sum;
}

#endif // Binomial_heap
