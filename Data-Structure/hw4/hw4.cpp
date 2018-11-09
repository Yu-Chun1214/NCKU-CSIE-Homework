#include<iostream>

using namespace std;

class Node;
typedef Node * NodePointer;
class Node{
private:
    int row,col,value;
    
public:
    Node(int r,int c, int val){row = r,col = c, value = val; Next = Down = Right = this;}
    Node(){row = col = value = 0; Next = Down = Right = this;}
    int Row(){return row;}
    int Col(){return col;}
    int Value(){return value;}
    // NodePointer Down(){return down;};
    // NodePointer Right(){return right;}
    // NodePointer Down(NodePointer newdown){down = newdown; return down;}
    // NodePointer Right(NodePointer newright){right = newright; return right;}
    NodePointer Down;
    NodePointer Right;
    NodePointer Next;
    NodePointer ItSelf(){return this;}
};


int main(){

}