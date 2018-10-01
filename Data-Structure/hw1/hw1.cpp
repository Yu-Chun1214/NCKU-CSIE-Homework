#include<iostream>
#include<vector>
using namespace std;

int fibonacci_recursive(int num){
    if(num == 0)
        return 0;
    else if(num == 1)
        return 1;
    else
        return fibonacci_recursive(num - 1) + fibonacci_recursive(num -2);
}

int fibonacci_iterative(int num){
    int an_2 = 0,an_1 = 1;
    int ans,temp;
    if (num == 0)
        return 0;
    else if (num == 1)
        return 1;
    else
        for(int i = 1; i < num; ++i){
            temp = an_1;
            ans = an_2 + an_1;
            an_1 = ans;
            an_2 = temp;
        }
    return ans;
}

int main(int argc, char **argvs){
    int num_test_case;
    int test_case;
    vector<int> cases;
    cin>>num_test_case;
    for(int i = 0;i<num_test_case;i++){
        cin>>test_case;
        cases.push_back(test_case);
    }
    printf("\n");
    for(vector<int>::iterator it = cases.begin();it!=cases.end();it++){
        cout<<fibonacci_recursive(*it)<<" "<<fibonacci_iterative(*it)<<endl;
    }
    return 0;
}
