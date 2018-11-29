#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

vector<int> InputInstructions(){
    char *pch;
    int num;
    char str_data[110];
    vector<int> numbers;
    scanf("%[^\n]",str_data);
    pch = strtok(str_data," ");
    while(pch != NULL){
        num = atoi(pch);
        pch = strtok(NULL," ");
        numbers.push_back(num);
    }
    while((getchar() != '\n'));
    return numbers;
}

class Heap : public vector<int>{
public:
    // constructor
    Heap():vector<int>(){vector<int>::push_back(RAND_MAX);}
    Heap(vector<int> input);
    //----------------------------
    void InputElements(vector<int> input);
    bool IsEmpty();
    void Show();
    int pop_back();
    Heap To_Heap(int(*method)(Heap &, int));
    Heap reArrange(int(*method)(Heap &, int),int which, int num);
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

void Heap::Show(){
    for(int i = 1; i < vector<int>::size(); i++)
        cout<<(*this)[i]<<" ";
    cout<<endl;
}

Heap Heap::To_Heap(int(*method)(Heap &, int)){
    int flag;
    for(int i = 1; i < vector<int>::size();){
        flag = method(*this,i);
        if((flag / 2) == 1) i = 1;
        else if(flag){i = flag / 4;}
        else i++;
    }
    return *this;
}

Heap Heap::reArrange(int(*method)(Heap &, int),int which,int num){
    int pos,flag;
    for(int i = 0; i < vector<int>::size();i++)
        if((*this)[i] == which){
            pos = i;
            break;
        }
    this->operator[](pos) = num;
    for(int i = pos; i > 0 && i < vector<int>::size();){
        flag = method(*this,i);
        cout<<"flag = "<<flag<<endl;
        cout<<"i = "<<i<<endl;
        if(flag == 1) i = 1;
        else if(flag / 2 == i){i = flag;}
        else i /= 2 ;
        Show();
    }

    return *this;
}

int MaxHeapSwap(Heap &heap, int parent_pos){
    int temp;
    int swap_pos;
    if(parent_pos * 2 + 1 < heap.size()){
        temp = (heap[parent_pos * 2] > heap[parent_pos * 2 + 1] ? (swap_pos = parent_pos * 2,heap[parent_pos * 2]) : (swap_pos = parent_pos * 2 + 1,heap[parent_pos * 2 + 1]));
        printf("Parent : %d\nChild1 : %d\nChild2 : %d\n",heap[parent_pos],heap[parent_pos * 2],heap[parent_pos * 2 + 1]);
    }
    else if (parent_pos * 2 < heap.size()){
        temp = heap[parent_pos * 2];
        swap_pos = parent_pos * 2;
        printf("Parent : %d\nChild1 : %d\n",heap[parent_pos],heap[parent_pos * 2]);
    }
    else return false;

    if(temp > heap[parent_pos]){
        swap(heap[parent_pos],heap[swap_pos]);
        cout<<"---------------------\n\n";
        return swap_pos;
    }
    return false;
}


int main(){
    vector<int> nums = InputInstructions();
    Heap heap;
    heap.InputElements(nums);
    // heap.Show();
    heap.To_Heap(MaxHeapSwap);
    printf("======================\n\n");
    heap.reArrange(MaxHeapSwap,heap[3],60).Show();
}