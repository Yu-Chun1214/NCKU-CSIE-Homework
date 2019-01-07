#ifndef __BIGNUM_HPP__
#define __BIGNUM_HPP__
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <string.h>

using namespace std;

class String : public string{
public:
    String(string n):string(n){}
    String(String &n):string(n.c_str()){}
    String(char * n):string(n){}
    String():string(){}

    // unsigned int length(){return strlen(this->c_str());}
};

template<class T>
class Vector :public vector<T>{
public:
    T pop_back(){
        if(vector<T>::size() > 0){
            T object = *(vector<T>::end()-1);
            vector<T>::pop_back();
            return object;
        }
        else throw "pop_back raise exception: There has no elements in deque object to pop_back";
    }
    void push_front(T object){vector<T>::insert(vector<T>::begin(),object);}

    T pop_front(){
        if(vector<T>::size() > 0){
            T object = *(vector<T>::begin());
            vector<T>::erase(vector<T>::begin());
            return object;
        }
        else throw "pop_front raise exception: There has no elements in deque object to pop_front";
    }
};

class Bignum :public String{
private:
    int cut;
    Vector<int> segement;
public:    
    void Cutting();
public:
    Bignum(string n):String(n){
        cut = 4;
        Cutting();
    }
    Bignum(char * n):String(n){
        cut = 4;
        Cutting();
    }
    Bignum operator+(Bignum);
    Bignum():String(){cut = 4;}
};

void Bignum::Cutting(){
    char temp[20];
    size_t length;
    int pos = 0;

    int first = this->length() % 4;
    if(first){
        length = this->copy(temp,first,pos);
        temp[length] = '\0';
        pos += first;
        segement.push_back(atoi(temp));
    }
    while(pos <= this->length() - 1){
        length = this->copy(temp,cut,pos);
        temp[length] = '\0';
        segement.push_back(atoi(temp));
        pos += 4;
    }
}

Bignum Bignum::operator+(Bignum n2){
    Vector<int>result;
    Bignum n3;
    int t;
    while(segement.size() && n2.segement.size()){
        t = segement.pop_back() + n2.segement.pop_back();
        result.push_front(t);
        // cout<<t<<endl;
    }
    // cout<<"-------------------------"<<endl;
    while(segement.size())
        result.push_front(segement.pop_back());
    while(n2.segement.size())
        result.push_front(n2.segement.pop_back());
    // for(int i = 0; i < result.size(); i++)
    //     cout<<result[i]<<endl;
    // cout<<"----------------"<<endl;
    char temp[cut + 10];
    int dec;
    dec = (result[1] - (result[1] % (int)pow(10,cut) ) );
    result[1] -= dec;
    sprintf(temp,"%d",result[0] + (int)((double)dec / pow(10,cut)));
    n3.append(temp);
    // cout<<temp<<endl;
    for(int i = 1; i < result.size() - 1; i++){
        dec = (result[i + 1] - (result[i + 1] % (int)pow(10,cut) ) );
        result[i + 1] -= dec;
        sprintf(temp,"%04d",result[i] + (int)((double)dec / pow(10,cut)));
        n3.append(temp);
        // cout<<temp<<endl;
    }
    sprintf(temp,"%04d",*(result.end()-1));
    n3.append(temp);
    // cout<<temp<<endl;

    return n3;
}


#endif