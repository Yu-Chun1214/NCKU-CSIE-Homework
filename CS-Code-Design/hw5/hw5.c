#include<stdio.h>
#include<stdlib.h>

void CreateNewMappingArray(int **original_bucket, int ** newMappingArray,int n){
    int Max = 0;
    for(int i = 0; i < n; i++){
        if(original_bucket[i][0] > Max)
            Max = original_bucket[i][0];
    }
    
}

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]),m = atoi(argv[2]),d = atoi(argv[3]), s = atoi(argv[4]);
    // n is the amount of buckets
    // the element in bucket need to small than m
    // 0 ~ d-1 is the range of number of element
    // s is seed of srand
    srand(s);
    int amounts_of_elements = (rand() % m) + 1;
    int **bucket = (int **)malloc(n*sizeof(int *));
    int ** newMapping;
    for(int i = 0; i < n; i++){
        amounts_of_elements = (rand() % m) + 1;
        // printf("amounts of elements = %d\n",amounts_of_elements);
        bucket[i] = (int *)malloc((amounts_of_elements + 1)*sizeof(int)); // malloc amount_of_element + 1 '1' is for first element
        bucket[i][0] = amounts_of_elements;
        for(int j = 1; j <= bucket[i][0]; j++){
            bucket[i][j] = rand()%d;
        }
    }
    for(int i = 0; i < n; i++){
        printf("%d | ",bucket[i][0]);
        for(int j = 1;j <= bucket[i][0];j++){
            printf("%d ",bucket[i][j]);
        }
        printf("\n");
    }
    CreateNewMappingArray(bucket,newMapping,n);
    return 0;
}
