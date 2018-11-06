#include<stdio.h>
#include<stdlib.h>

int MaxAmountOfElementInBucket(int **original_bucket, int n){
    int Max = 0;
    for(int i = 0; i < n; i++){
        if(original_bucket[i][0] > Max)
            Max = original_bucket[i][0];
    }
    return Max;
}

void Zeroing(int *array,int size){
    for(int i = 0; i < size; i++) array[i] = 0;
}

int Merge(int * original_bucket, int * newMapping, int * bucket_index,int Max,int row){
    int map_match[newMapping[0] + 1];
    int no_match[original_bucket[0]+1];
    Zeroing(no_match,original_bucket[0] + 1);
    Zeroing(map_match,newMapping[0] + 1);
    // int successful_match;
    int result = 0,count = 0;
    int i,j;
    for(i = 1; i <= original_bucket[0]; i++){
        // successful_match = 0;
        for(j = 1; j <= newMapping[0]; j++){
            if(!map_match[j] && newMapping[j] == original_bucket[i]){
                map_match[j] = 1;
                printf("%d ",Max-j);
                // successful_match = 1;
                result += 1<<(Max - j);
                break;
            }
        }
        if(j > newMapping[0]){
            no_match[count] = original_bucket[i];
            ++count;            
        }
    }
    
    if(Max - newMapping[0] < count) return 0;
    for(i = 0; i < count; i++){
        newMapping[newMapping[0] + 1] = no_match[i];
        // printf("%d ",(Max - newMapping[0] - 1));
        result += 1 << (Max - newMapping[0] - 1);
        newMapping[0]++;
    }
    // printf("\n");
    // for(int i = 0; i <= newMapping[0];i++){
    //     printf("%d ",newMapping[i]);
    // }
    // printf("\n");
    // printf("\nresult = %d\n",result);
    // printf("count = %d\n",count);
    
    return 1;
}

int ** Compress(int ** original_bucket, int ** newMapping, int n,int Max){
    
    int newMappingRows = 0;
    int successful = 0;
    int count = 0;
    int temp = 0;
    
    char *** bucket_index = (char ***)malloc(n*sizeof(char **));
    for(int i = 0; i < n; i++){
        bucket_index[i] = (char **)malloc(2*sizeof(char *));
        bucket_index[i][0] = (char *)malloc(5*sizeof(char));
        bucket_index[i][1] = (char *)malloc(Max*sizeof(char));
    }

    do{
        // searching the appropriate row in newmapping array
        for(int i = 0; i < newMappingRows; i++){ // every row in newMapping;
            if(newMapping[i][0] < Max){ // if row i in newMapping isn't full
                for(int j = 1; j < original_bucket[n][0]; j++){ // elements in original bucket
                    for(int m = 1; j <= newMapping[i][0]; m++){ // elements in newmapping array
                        if(original_bucket[n][j] == 0)
                            return bucket_index;
                    }
                }
            }
        }
        --n;
        successful = 0;
    }while(n >= 0);
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
    int bucketAmountOfNewMapping;
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
    bucketAmountOfNewMapping = MaxAmountOfElementInBucket(bucket,n);
    int test1[5] = {3, 1, 5, 4, 4};
    int test2[7] = {4, 2, 4, 3, 2, 4};
    Merge(test1,test2,test1,7,3);
    return 0;
}
