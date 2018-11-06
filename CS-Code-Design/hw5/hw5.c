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

int Merge(int * original_bucket, int * newMapping, char * bucket_index,int Max){
    int map_match[newMapping[0] + 1]; // record the position element in mapping array , which has been matched;
    int no_match[original_bucket[0]+1]; // record the value of original_bucket.
    int count = 0;
    int i,j;

    /*-------------initialize the arrays--------------*/
    Zeroing(no_match,original_bucket[0] + 1);
    Zeroing(map_match,newMapping[0] + 1);
    for(int i = 0; i < Max + 1; i++) bucket_index[i] = '0';// initialize the string;
    bucket_index[Max+1] = '\0'; // set the end of bucket_index, because bucket_index is string type data;

    
    // search begin
    for(i = 1; i <= original_bucket[0]; i++){
        for(j = 1; j <= newMapping[0]; j++){
            if(!map_match[j] && newMapping[j] == original_bucket[i]){
                map_match[j] = 1;
                bucket_index[j] = '1';
                break;// avoid original_bucket[i] matching again.
            }
        }
        if(j > newMapping[0]){
            no_match[count] = original_bucket[i];
            ++count;          
        }
   }
    
    if(Max - newMapping[0] < count) return 0; // if remain array isn't 
    for(i = 0; i < count; i++){
        newMapping[newMapping[0] + 1] = no_match[i];
        bucket_index[newMapping[0] + 1] = '1';
        newMapping[0]++;
    }

    return 1;
}

int ** Compress(int ** original_bucket, int ** newMapping, int n,int Max){
    
    int newMappingRows = 0;
    int successful = 0;
    int count = 0;
    int temp = 0;
    int i,j;
    char *** bucket_index = (char ***)malloc(n*sizeof(char **));

    for(int i = 0; i < n; i++){
        bucket_index[i] = (char **)malloc(2*sizeof(char *));
        bucket_index[i][0] = (char *)malloc(5*sizeof(char));
        bucket_index[i][1] = (char *)malloc((Max + 2)*sizeof(char));
    }
    
    
    for(i = 0; i < n; i++){
        for(j = 0; j < newMappingRows; j++){
            if(Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max)){
                sprintf(bucket_index[i][0],"%d",j);
                break;
            }
        }
        if(j >= newMappingRows){
            newMappingRows ++;
            newMapping = realloc(newMapping,(newMappingRows)*sizeof(int **));
            newMapping[j] = (int *)malloc((Max + 1) * sizeof(int));
            newMapping[j][0] = 0;
            Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max);
            sprintf(bucket_index[i][0],"%d",j);
        }
        free(original_bucket[i]);
    }
    for(int i = 0; i < n; i++){
        printf("%s %s\n",bucket_index[i][0],bucket_index[i][1]);
    }
    for(int i = 0; i < newMappingRows; i++){
        printf("%d | ",newMapping[i][0]);
        for(int j = 1;j <= newMapping[i][0]; j++){
            printf("%5d ",newMapping[i][j]);
        }
        printf("\n");
    }
    return newMapping;
}

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]),m = atoi(argv[2]),d = atoi(argv[3]), s = atoi(argv[4]);
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
            printf("%5d",bucket[i][j]);
        }
        printf("\n");
    }
    bucketAmountOfNewMapping = MaxAmountOfElementInBucket(bucket,n);
    Compress(bucket,newMapping,n,bucketAmountOfNewMapping);
    return 0;
}
