#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

enum bool{
    true = 1,
    false = 0,
};

struct number{
    int num;
    int position;
    enum bool taken;
};

struct userdata{
    int data[100];
    int amount;
};

double Random(int U, int D){
    return(((double)U - (double)D + 1)*rand() / (double)RAND_MAX + (double)D);
}

int *rnd(int *block, int amount){
    int i; // iterator
    for(int i = 0; i < amount; i++){
        block[i] = (int)Random(1,amount);
        printf("%d\n",block[i]);
    }
    return block;
}

enum bool SetData(struct userdata *data,const char *choice){
    char str_data[200];
    char *pch;
    int i = 0;
    int scf;
    scf = scanf(choice,str_data);
    if(scf == false || scf == EOF){
        printf("Tape Wrong\n");
        return false;
    }
    else{
        pch = strtok(str_data," ");
        while(pch!=NULL){
            data->data[i] = atoi(pch);
            
            printf("i = %d  ,  %d\n",i,data->data[i]);
            pch = strtok(NULL," ");
            i++;
        }
        data->amount = i;
    }
    return true;
}

enum bool Check(struct userdata *data,int P,int N){
    int i;
    if(data->amount != N -1)
        return false;
    for(i = 0; i < N - 1;i++){
        if(data->data[i] > N || data->data[i] < 1){
            return false;
        }
    }
    return true;
}

void HX(int *ans,int *guess,int P){
    int i = 0;// iterator
    for(i = 0; i < P; i++ ){
        
    }
}
int main(int argc, char const *argv[])
{
    int N = atoi(argv[1]);
    int P = atoi(argv[2]);
    printf("You set N=%d, P=%d\n",N,P);
    struct userdata ans,guess;
    enum bool success;
    success = SetData(&ans,"ans:%[^\n]");
    if(Check(&ans,P,N)){
        
    }
    
    int i = 0;// iterator
    for(i = 0; i < ans.amount; i++){
        printf("%d\n",ans.data[i]);
    }
    if(Check(&ans,P,N)){
       	printf("correct\n");
    }else{
        printf("Wrong\n");
    }
}
