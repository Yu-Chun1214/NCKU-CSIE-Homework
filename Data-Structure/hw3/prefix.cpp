#include<iostream>
#include<string>
#include<vector>
using namespace std;

template<class T>
class Stack : public vector<T>{
public:
    T pop_back(){
        if(vector<T>::size() > 0){
            T object = *(vector<T>::end()-1);
            vector<T>::pop_back();
            return object;
        }
        else throw "there has no elements in Stack object";
    }
    // T pop_front(){
    //     if(vector<T>::size() > 0){
    //         T object = *(vector<T>::begin());
    //         vector<T>::erase(vector<T>::begin());
    //         return object;
    //     }
    //     else throw "there has no elements in deque object";
    // }
    // void push_front(T object){
    //     vector<T>::insert(vector<T>::begin(),object);
    // }
};

bool isNumeric(char * c_string){
    char * charp = c_string;
    while(*charp && isdigit(*charp))
        charp++;
    return (*charp?false : true);
}

int Precedence(string operatr){
    if(operatr.c_str()[0] == '*' || operatr.c_str()[0] == '/' || operatr.c_str()[0] == '%') return 13;
    else if(operatr.c_str()[0] == '+' || operatr.c_str()[0] == '-') return 12;
    else if(operatr.c_str()[0] == '>' || operatr.c_str()[0] == '<') return 10;
    else if(strcmp(operatr.c_str(),"==") == 0 ||strcmp(operatr.c_str(),"!=") == 0) return 9;
    else if(strcmp(operatr.c_str(),"&&") == 0) return 5;
    else if(strcmp(operatr.c_str(),"||") == 0) return 4;
    else return 0;
}
class OperatorStack : public Stack<string>{
public:
    Stack<string> OperatorPush(string op){
        Stack<string> return_op;
        string temp;
        for(Stack<string>::iterator dit = Stack<string>::end() - 1; dit != Stack<string>::begin() - 1; dit--){
            if(Precedence(op) < Precedence(*dit) || Precedence(op) == Precedence(*dit)){
                temp = *dit;
                Stack<string>::erase(dit);
                return_op.push_back(temp);
            }
        }
        Stack<string>::push_back(op);
        return return_op;
    }
};

Stack<string> InputInstructions(){
    char *pch;
    char str_data[150];
    Stack<string> instructions;
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

int main(int argc, char const * argv[]){ 
    char a[100];
    Stack<string> input = InputInstructions();
    OperatorStack ops;
    Stack<string> op;
    Stack<string> buffer;
    string eos("eos");
    string opern1,opern2;
    for(int i = 0; i < input.size(); i++){
        strcpy(a,input[i].c_str());
        if(isNumeric(a)){
            buffer.push_back(input[i]);
        }else{
            op = ops.OperatorPush(input[i]);
            for(int i = 0; i < op.size(); i++){
                opern2 = buffer.pop_back();
                opern1 = buffer.pop_back();
                buffer.push_back((op[i]+" "+opern1+" "+opern2+" "));
            }
        }
    }
    op = ops.OperatorPush(eos);
    for(int i = 0; i < op.size(); i++){
        opern2 = buffer.pop_back();
        opern1 = buffer.pop_back();
        buffer.push_back((op[i]+" "+opern1+" "+opern2+" "));
    }
    for(int i = 0; i < buffer.size(); i++)
        cout<<buffer[i];
    cout<<endl;
}