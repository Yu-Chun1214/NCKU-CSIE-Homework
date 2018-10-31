#include<iostream>
#include<vector>
using namespace std;
template<class T>
class deque : protected vector<T>{
public:
    void push_front(T object){vector<T>::insert(vector<T>::begin(),object);}
    void push_back(T object){vector<T>::push_back(object);}
    void pop_back(){ vector<T>::pop_back();}
    void pop_front(){ vector<T>::erase(vector<T>::begin()); }
    void show(){
        for(typename vector<T>::iterator it = vector<T>::begin();it!=vector<T>::end();it++)
            cout<<*it<<" ";
        cout<<endl;
    }
};
int main(){
    
}