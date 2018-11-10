#include<iostream>

using namespace std;


class Node;
typedef Node * NodePointer;
class Node{
private:
    int row,col,value;
public:
    Node(int r,int c, int val){row = r,col = c, value = val; Next = Down = Right = NULL;}
    Node(){row = col = value = -1; Next = Down = Right = NULL;}
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
    int mread_initialize(int rows,int cols, int num,NodePointer * &current_row,NodePointer * &current_col);
    void mread_addNode(int row,int col,int value,NodePointer * &current_row,NodePointer * &current_col);
public:
    Mat(int rows,int cols,int num){mread(rows,cols,num);}

    NodePointer mread(int rows,int cols,int num);
    void mwrite();
};

int Mat::mread_initialize(int rows,int cols, int num,NodePointer * &current_row,NodePointer * &current_col){
    FIRST_NODE = new Node(rows,cols,num);
    const int HEADER_NODE_AMOUNT = (rows >= cols ? rows : cols);
    current_col = new NodePointer[HEADER_NODE_AMOUNT];
    current_row = new NodePointer[HEADER_NODE_AMOUNT];
    hdnode = new Node[HEADER_NODE_AMOUNT];

    for(int i = 0; i < HEADER_NODE_AMOUNT; i++){
        current_col[i] = &hdnode[i];
        current_row[i] = &hdnode[i];
    }

    FIRST_NODE->Right = &hdnode[0];
    for(int i = 0; i < HEADER_NODE_AMOUNT - 1; i++) hdnode[i].Next = &hdnode[i + 1];
    hdnode[HEADER_NODE_AMOUNT - 1].Next = FIRST_NODE;

    return HEADER_NODE_AMOUNT;
}

void Mat::mread_addNode(int row,int col,int value,NodePointer * &current_row,NodePointer * &current_col){
    NodePointer item = new Node(row,col,value);
    current_row[row]->Right = item;
    current_col[col]->Down = item;
    current_row[row] = item;
    current_col[col] = item;
}

NodePointer Mat::mread(int rows,int cols,int num){
    
    int row,col,value;
    NodePointer * current_element_row , * current_element_col;

    const int HEADER_NODE_AMOUNT = mread_initialize(rows,cols,num,current_element_row,current_element_col);

    // Add "num" nodes;
    for(int i = 0; i < num; i++){
        cin>>row>>col>>value;
        mread_addNode(row,col,value,current_element_row,current_element_col);
    }
    
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++){
        current_element_col[i]->Down = &hdnode[i];
        current_element_row[i]->Right = &hdnode[i];
    }

    delete[] current_element_col;
    delete[] current_element_row;
    
    return FIRST_NODE;
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