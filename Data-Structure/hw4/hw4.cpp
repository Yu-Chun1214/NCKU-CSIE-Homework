#include<iostream>

using namespace std;


class Node;
typedef Node * NodePointer;
class Node{
private:
    int row,col,value;
public:
    Node(int r,int c, int val){row = r,col = c, value = val; Next = Down = Right = this;}
    Node(){row = col = value = -1; Next = Down = Right = this;}
    int Row(){return row;}
    int Col(){return col;}
    int Value(){return value;}
    NodePointer Down;
    NodePointer Right;
    NodePointer Next;
    NodePointer ItSelf(){return this;}
};

class Mat{
private:
    NodePointer hdnode;
    NodePointer FIRST_NODE;
    void Insertion(NodePointer item,NodePointer hd_begin,NodePointer hd_end,int n,NodePointer (*Compare)(NodePointer,NodePointer));
    NodePointer Compare_row(NodePointer node1,NodePointer node2);
    
public:
    Mat(int rows,int cols,int num){mread(rows,cols,num);}

    NodePointer mread(int rows,int cols,int num);
    void mwrite();
};

NodePointer Mat::Compare_row(NodePointer node1,NodePointer node2){
    NodePointer temp = node1->Right;
    node1->Right = (node1->Right->Row() < node2 ->Row() ? node1->Right : (node2->Right = temp),node2); // if node2-Row() > last1-Row(), swap 
    return node1;
}

NodePointer Mat::mread(int rows,int cols,int num){
    const int HEADER_NODE_AMOUNT = rows >= cols ? rows : cols;
    int row,col,value;

    NodePointer * current_element_row = new NodePointer[HEADER_NODE_AMOUNT];
    NodePointer * current_element_col = new NodePointer[HEADER_NODE_AMOUNT];

    FIRST_NODE = new Node(rows,cols,num);
    hdnode = new Node[HEADER_NODE_AMOUNT];
    NodePointer temp;


    // initially, current_element_col of each row will point to the head node; same as currnet_element_row;
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++){
        current_element_col[i] = &hdnode[i];
        current_element_row[i] = &hdnode[i];
    }

    for(int i = 0; i < HEADER_NODE_AMOUNT - 1; i++) hdnode[i].Next = &hdnode[i + 1];
    FIRST_NODE->Right = &hdnode[0];
    hdnode[HEADER_NODE_AMOUNT - 1].Next = FIRST_NODE;

    for(int i = 0; i < num; i++){
        cin>>row>>col>>value;
        temp = new Node(row,col,value);
        current_element_row[row]->Right = temp;
        current_element_col[col]->Down = temp;
        current_element_row[row] = temp;
        current_element_col[col] = temp;
    }
    
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++){
        current_element_col[i]->Down = &hdnode[i];
        current_element_row[i]->Right = &hdnode[i];
    }

    delete[] current_element_col;
    delete[] current_element_row;
    
    return FIRST_NODE;
}

void Mat::Insertion(NodePointer item,NodePointer begin,NodePointer end, int n, NodePointer (*Compare)(NodePointer,NodePointer)){
    // NodePointer temp = begin;
    while(begin != end){
        if(begin != Compare(begin,item)){//meas that item is bigger than item
            
        }
    }
}

void Mat::mwrite(){
    // NodePointer first = FIRST_NODE;
    NodePointer O;
    NodePointer current_hd = FIRST_NODE->Right;
    
    while(current_hd != FIRST_NODE){
        O = current_hd->Down;
        while(O != current_hd){
            printf("%d %d %d\n",O->Row(),O->Col(),O->Value());
            O = O->Down;
        }
        current_hd = O->Next;
    }
}

int main(){
    Mat mat(3,4,4);
    cout<<"===================\n";
    mat.mwrite();
}