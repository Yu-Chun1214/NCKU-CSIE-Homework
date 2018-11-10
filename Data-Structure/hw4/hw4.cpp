#include<iostream>
#include<vector>
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
    void mread_addNode(NodePointer item,NodePointer * &current_row, NodePointer * &current_col);
    void mread_final(NodePointer * &current_row,NodePointer * &current_col,const int HEADER_NODE_AMOUNT);
public:
    Mat(int rows,int cols,int num){mread(rows,cols,num);}
    Mat(){}
    NodePointer mread(int rows,int cols,int num);
    Mat operator * (Mat);
    Mat Transpose();
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

void Mat::mread_addNode(NodePointer item, NodePointer * &current_row,NodePointer * & current_col){
    current_row[item->Row()]->Right = item;
    current_col[item->Col()]->Down = item;
    current_row[item->Row()] = item;
    current_col[item->Col()] = item;
}

void Mat::mread_final(NodePointer * &current_row,NodePointer * &current_col, const int HEADER_NODE_AMOUNT){
    for(int i = 0; i < HEADER_NODE_AMOUNT; i++){
        current_col[i]->Down = &hdnode[i];
        current_row[i]->Right = &hdnode[i];
    }
}

NodePointer Mat::mread(int rows,int cols,int num){
    
    int row,col,value;
    NodePointer * current_element_row , * current_element_col;
    NodePointer  temp;

    const int HEADER_NODE_AMOUNT = mread_initialize(rows,cols,num,current_element_row,current_element_col);

    // Add "num" nodes;
    for(int i = 0; i < num; i++){
        cin>>row>>col>>value;
        temp = new Node(row,col,value);
        mread_addNode(temp,current_element_row,current_element_col);
    }
    
    mread_final(current_element_row,current_element_col,HEADER_NODE_AMOUNT);

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
    Mat newMat;
    NodePointer * current_row, * current_col;
    const int HEADER_NODE_AMOUNT = newMat.mread_initialize(FIRST_NODE->Col(),FIRST_NODE->Row(),FIRST_NODE->Value(),current_row,current_col);

    NodePointer hdpointer = FIRST_NODE->Right; // Initially, hdpointer points to the first headernode;
    NodePointer elementptr;
    while(hdpointer != FIRST_NODE){
        elementptr = hdpointer->Down;
        while(elementptr != hdpointer){
            newMat.mread_addNode(elementptr->Col(),elementptr->Row(),elementptr->Value(),current_row,current_col);
            elementptr = elementptr->Down;
        }
        hdpointer = hdpointer->Next;
    }
    newMat.mread_final(current_row,current_col,HEADER_NODE_AMOUNT);
    return newMat;
}

Mat Mat::operator*(Mat mat2){
    if(FIRST_NODE->Col() != mat2.FIRST_NODE->Row()) throw ("Matrix Should be the same size");
    Mat resultMat;
    vector<NodePointer> nodes;
    NodePointer mat1_element_ptr,mat2_element_ptr;
    NodePointer hdptr1 = FIRST_NODE->Right;
    NodePointer hdptr2 = mat2.FIRST_NODE->Right;
    NodePointer temp;
    NodePointer * current_element_row, * current_element_col;
    int sum,row,col;

    if(hdptr1->Next == FIRST_NODE){
        throw ("Link error");
    }
    while(hdptr1 != FIRST_NODE){
        for(hdptr2 = mat2.FIRST_NODE->Right;hdptr2 != mat2.FIRST_NODE;hdptr2 = hdptr2->Next){
            sum = 0;
            mat1_element_ptr = hdptr1->Right;
            mat2_element_ptr = hdptr2->Down;
            row = mat1_element_ptr->Row();
            col = mat2_element_ptr->Col();
            while(mat1_element_ptr != hdptr1 && mat2_element_ptr != hdptr2){
                // cout<<mat1_element_ptr->Value()<<"   "<<mat2_element_ptr->Value()<<endl;
                if(mat1_element_ptr->Col() == mat2_element_ptr->Row()){
                    sum += mat1_element_ptr->Value() * mat2_element_ptr->Value();
                    mat1_element_ptr = mat1_element_ptr->Right;
                    mat2_element_ptr = mat2_element_ptr->Down;
                }
                else if(mat1_element_ptr->Col() < mat2_element_ptr->Row()) mat1_element_ptr = mat1_element_ptr->Right;
                else  mat2_element_ptr = mat2_element_ptr->Down;
            }
            if(sum){
                temp = new Node(row,col,sum);
                nodes.push_back(temp);
            }
        }
        hdptr1 = hdptr1->Next;
    }
    const int HEADER_NODE_AMOUNT = resultMat.mread_initialize(FIRST_NODE->Row(),mat2.FIRST_NODE->Col(),nodes.size(),current_element_row,current_element_col);
    for(int i = 0; i < nodes.size(); i++) resultMat.mread_addNode(nodes[i],current_element_row,current_element_col);
    resultMat.mread_final(current_element_row,current_element_col,HEADER_NODE_AMOUNT);
    delete[] current_element_col;
    delete[] current_element_row;
    return resultMat;
} 

int main(){
    Mat mat(3,4,3);
    // cout<<"===================\n";
    // mat.mwrite();
    Mat mat2(2,4,4);
    // cout<<"====================\n";
    mat2.Transpose().mwrite();
    cout<<"====================\n";
    (mat*mat2.Transpose()).mwrite();
}