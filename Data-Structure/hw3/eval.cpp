#include<iostream>
#include<string>
#include<vector>
using namespace std;

template<class T>
class deque : public vector<T>{
public:
    T pop_back(){
        if(vector<T>::size() > 0){
            T object = *(vector<T>::end()-1);
            vector<T>::pop_back();
            return object;
        }
        else throw "there has no elements in deque object";
    }
    T pop_front(){
        if(vector<T>::size() > 0){
            T object = *(vector<T>::begin());
            vector<T>::erase(vector<T>::begin());
            return object;
        }
        else throw "there has no elements in deque object";
    }
    void push_front(T object){
        vector<T>::insert(vector<T>::begin(),object);
    }
};

bool isNumeric(char * c_string){
    char * charp = c_string;
    return ((isdigit(*charp) || strlen(c_string) > 1)) ? true : false;
}

deque<string> InputInstructions(){
    char *pch;
    char str_data[150];
    deque<string> instructions;
    string ptok;
    scanf("%[^\n]",str_data);
    pch = strtok(str_data," ");
    while(pch != NULL){
        ptok = pch;
        pch = strtok(NULL," ");
        instructions.push_back(ptok);
    }
    while ((getchar()) != '\n');
    return instructions;
}

double performace(string token, string num1,string num2){
    string add("+"),subtract("-"),divide("/"),multi("*");
    double result;
    if(token == add)
        result = atof(num1.c_str()) + atof(num2.c_str());
    else if(token == subtract)
        result = atof(num1.c_str()) - atof(num2.c_str());
    else if (token == multi)
        result = atof(num1.c_str()) * atof(num2.c_str());
    else if(token == divide)
        result = atof(num1.c_str()) / atof(num2.c_str());
    return result;
}

int main(){
    deque<string> input = InputInstructions();
    do{
        
        for(deque<string>::iterator dsit = input.begin(); dsit <= input.end() - 2; dsit++){
            if(!isNumeric((char *)dsit->c_str()) && isNumeric((char *)(dsit + 1)->c_str()) && isNumeric((char *)(dsit + 2)->c_str())){
                // cout<<"in if dsit = "<<*dsit<<endl;
                *dsit = to_string(performace(*dsit,*(dsit + 1),*(dsit + 2)));
                // cout<<"after to string"<<endl;
                
                // cout<<*dsit<<" "<<*(dsit+1)<<" "<<*(dsit + 2)<<endl;
                input.erase(dsit + 2);
                input.erase(dsit + 1);

                // cout<<"erase end"<<endl;
                // for(deque<string>::iterator dsit = input.begin(); dsit != input.end(); dsit++)
                //     cout<<*dsit<<endl;
                // system("pause");
            }
        }
        // cout<<"out of for"<<endl;
    }while(input.size() != 1);
    cout<<input[0]<<endl;
}