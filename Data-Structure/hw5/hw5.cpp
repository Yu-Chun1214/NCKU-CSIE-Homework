#include <iostream>
#include <vector>
#include "heap.hpp"

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

int main(){
    vector<int> nums = InputInstructions();
    Heap heap;
    heap.InputElements(nums);
    heap.To_Heap(MaxHeapSwap);
    cout<<"===========Replace arbitrary element==============\n";
    int replace1,replace2;
    cin>>replace1>>replace2;
    heap.reArrange(replace1,replace2).Show();
    cout<<"===========Delete arbitrary element===============\n";
    int del;
    cin>>del;
    heap.Delete(del).Show();

}