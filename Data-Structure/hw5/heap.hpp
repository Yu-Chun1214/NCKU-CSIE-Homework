#ifndef __heap_hpp__
#define __heap_hpp__
#include <iostream>
#include <vector>

using namespace std;

class Heap;

int MaxHeapSwap(Heap &heap, int parent_pos);
int minHeapSwap(Heap &heap, int parent_pos);

class Heap : public vector<int>{
private:
    int (*heap_method)(Heap &,int);
public:
    // constructor
    Heap():vector<int>(){vector<int>::push_back(RAND_MAX); heap_method = MaxHeapSwap;}
    Heap(vector<int> input);
    //----------------------------

    void InputElements(vector<int> input);
    bool IsEmpty();
    void Show();
    int pop_back();
    Heap Delete(int num);
    Heap To_Heap(int(*method)(Heap &, int));
    Heap reArrange(int which, int num);
};

Heap::Heap(vector<int> input){
    vector<int>::push_back(RAND_MAX);
    InputElements(input);
}

void Heap::InputElements(vector<int> input){
    for(int i = 0; i < input.size(); i++)
        vector<int>::push_back(input[i]);
}

bool Heap::IsEmpty(){
    return (vector<int>::size() == 0 ? false : true);
}

int Heap::pop_back(){
    if(!IsEmpty()) throw "Heap Is Empty";
    int num = *(vector<int>::end() - 1);
    vector<int>::pop_back();
    return num;
}

Heap Heap::Delete(int num){
    reArrange(num,pop_back());
    return *this;
}

void Heap::Show(){
    for(int i = 1; i < vector<int>::size(); i++)
        cout<<(*this)[i]<<" ";
    cout<<endl;
}

Heap Heap::To_Heap(int(*method)(Heap &, int)){
    heap_method = method;
    int flag;
    for(int i = 1; i < vector<int>::size();){
        flag = method(*this,i);
        if((flag / 2) == 1) i = 1;
        else if(flag){i = flag / 4;}
        else i++;
    }
    return *this;
}

Heap Heap::reArrange(int which,int num){
    int pos,flag;
    int i;
    for(i = 0; i < vector<int>::size();i++)
        if((*this)[i] == which){
            pos = i;
            break;
        }
    if(i == vector<int>::size()){
        char * error_msg = (char *)malloc(100* sizeof(char));
        sprintf(error_msg,"There has no element which value is %d store in heap object.\n",num);
        throw error_msg;
    }

    this->operator[](pos) = num;
    for(int i = pos; i > 0 && i < vector<int>::size();){
        flag = heap_method(*this,i);
        if(flag == 1) i = 1;
        else if(flag / 2 == i){i = flag;}
        else i /= 2 ;
    }

    return *this;
}

int MaxHeapSwap(Heap &heap, int parent_pos){
    int temp;
    int swap_pos;
    if(parent_pos * 2 + 1 < heap.size()){
        temp = (heap[parent_pos * 2] > heap[parent_pos * 2 + 1] ? (swap_pos = parent_pos * 2,heap[parent_pos * 2]) : (swap_pos = parent_pos * 2 + 1,heap[parent_pos * 2 + 1]));
    }
    else if (parent_pos * 2 < heap.size()){
        temp = heap[parent_pos * 2];
        swap_pos = parent_pos * 2;
    }
    else return false;

    if(temp > heap[parent_pos]){
        swap(heap[parent_pos],heap[swap_pos]);
        return swap_pos;
    }
    return false;
}

int minHeapSwap(Heap &heap, int parent_pos){
    int temp;
    int swap_pos;
    if(parent_pos * 2 + 1 < heap.size()){
        temp = (heap[parent_pos * 2] < heap[parent_pos * 2 + 1] ? (swap_pos = parent_pos * 2,heap[parent_pos * 2]) : (swap_pos = parent_pos * 2 + 1,heap[parent_pos * 2 + 1]));
    }
    else if (parent_pos * 2 < heap.size()){
        temp = heap[parent_pos * 2];
        swap_pos = parent_pos * 2;
    }
    else return false;

    if(temp < heap[parent_pos]){
        swap(heap[parent_pos],heap[swap_pos]);
        return swap_pos;
    }
    return false;
}


#endif