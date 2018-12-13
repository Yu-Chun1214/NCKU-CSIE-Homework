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
    int del;
    cin>>del;
    try{
        heap.Delete(del).Show();
    }catch(char * e){
        cout<<e<<endl;
    }
}