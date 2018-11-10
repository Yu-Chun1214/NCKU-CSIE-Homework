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
public:
    Mat(int rows,int cols,int num){mread(rows,cols,num);}
    Mat(){}
    NodePointer mread(int rows,int cols,int num);
    Mat operator * (Mat);
    Mat Transpose();
    void mwrite();
};

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
    
    // close row and col
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

Mat Mat::Transpose(){
    NodePointer hdpointer = FIRST_NODE->Next; // Initially, hdpointer points to the first headernode;
    Mat newMat;
    newMat.FIRST_NODE = new Node(FIRST_NODE->Col(), FIRST_NODE->Row(), FIRST_NODE->Value());
    // NodePointer NewMat  = new Node(FIRST_NODE->Col(), FIRST_NODE->Row(), FIRST_NODE->Value());// Initially set the first node of NewMat;
    NodePointer elementptr;
    while(hdpointer != FIRST_NODE){
        elementptr = hdpointer->Down;
        while(elementptr != hdpointer){

        }
    }
}

Mat Mat::operator*(Mat mat2){
    return *this;
}

int main(){
    Mat mat(3,4,4);
    cout<<"===================\n";
    mat.mwrite();
}