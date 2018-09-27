#include<iostream>
using namespace std;

int fibonacci1(int num){
    if(num == 0)
        return 0;
    else if(num == 1)
        return 1;
    else
        return fibonacci1(num - 1) + fibonacci1(num -2);
}

int fibonacci2(int num){
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
    int num = atoi(argvs[1]);
    int ans1,ans2;
    for(int i = 0;i<=num;++i){
        ans1 = fibonacci1(i);
        ans2 = fibonacci2(i);
        if(ans1 != ans2){
            printf("f1(%d) = %d\n",i,ans1);
            printf("f2(%d) = %d\n",i,ans2);
            system("pause");
            exit(0);
        }
        else{
            printf("%d %d\n",ans1,ans2);
        }
    }
    cout<<"All Right"<<endl;
    return(0);
}

// int main(){
//     for(int i = 0;i<10;i++)
//         cout<<fibonacci2(i)<<endl;
//     return 0;
// }