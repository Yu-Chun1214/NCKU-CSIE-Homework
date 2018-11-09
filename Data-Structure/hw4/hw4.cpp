#include<iostream>

using namespace std;


class entryNode{
public:
    int row,col,value;
    entryNode(){row = col = value = 0;}
};

class Node;
typedef Node * NodePointer;
class Node{
public:
    NodePointer down;
    NodePointer right;
    NodePointer next;
    virtual void virtualfunction()=0;
};

class HeaderNode:public Node{
private:
    virtual void virtualfunction();
    
};

class matrixNode;
typedef matrixNode * matrixPointer;
class matrixNode : public HeaderNode{
private:
    virtual void virtualfunction();
    matrixPointer ItSelf(){return this;}
};

int main(){
    NodePointer test;
    test = new HeaderNode();
    HeaderNode * test2;
    // printf("teacher you are beautiful,please give me grades!")
}