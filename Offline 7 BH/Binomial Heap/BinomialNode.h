#ifndef BinomialNode

#include<iostream>
using namespace std;


class BinomialNode
{
    int key;
    int degree;
    BinomialNode *parent, *child, *sibling;

    void increaseDegree(int margin = 1);
    void decreaseDegree(int margin = 1);
public:
    BinomialNode();
    BinomialNode(int key);
    BinomialNode *getParent();
    BinomialNode *getChild();
    BinomialNode *getSibling();
    int Degree();
    int Key();

    void addChildNode(BinomialNode *childNode);
    // void addSibling (BinomialNode *siblingNode);
    void connectParent (BinomialNode *parentNode);
    void connectSibling(BinomialNode *siblingNode);
    BinomialNode *findChildWithKey(int key);
};

BinomialNode::BinomialNode()
{
    this->key = 0;
    this->degree = 0;
    this->parent = this->child = this->sibling = nullptr;
}

BinomialNode::BinomialNode(int key)
{
    this->key = key;
    this->degree = 0;
    this->parent = this->child = this->sibling = nullptr;
}

void BinomialNode::increaseDegree(int margin)
{
    this->degree = this->degree + margin;
}

void BinomialNode::decreaseDegree(int margin)
{
    this->degree = this->degree - margin;
}

BinomialNode* BinomialNode::getChild()
{
    return this->child;
}

BinomialNode* BinomialNode::getParent()
{
    return this->parent;
}

BinomialNode* BinomialNode::getSibling()
{
    return this->sibling;
}

int BinomialNode::Degree()
{
    return this->degree;
}

int BinomialNode::Key()
{
    return this->key;
}

void BinomialNode::addChildNode(BinomialNode *childNode)
{
    childNode->parent = this;
    childNode->sibling = this->child;
    this->child = childNode;
    this->increaseDegree();
}


//void BinomialNode::addSibling(BinomialNode *siblingNode)
//{
//    if (this->sibling != nullptr)
//    {
//        siblingNode->sibling = this->sibling;
//    }
//
//    this->sibling = siblingNode;
//}


void BinomialNode::connectSibling(BinomialNode *siblingNode)
{
    this->sibling = siblingNode;
}


void BinomialNode::connectParent(BinomialNode *parentNode)
{
    this->parent = parentNode;
}


BinomialNode* BinomialNode::findChildWithKey(int key)
{
    BinomialNode *childNode = nullptr;
    if (this->key == key) return this;
    else if (this->sibling != nullptr)
    {
        childNode = this->sibling->findChildWithKey(key);
    }
    if (this->key < key && childNode == nullptr)
    {
        if (this->child != nullptr)
        {
            childNode = this->child->findChildWithKey(key);
        }
    }

    return childNode;
}

#endif // BinomialNode
