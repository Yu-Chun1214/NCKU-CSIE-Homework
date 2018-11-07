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

int Merge(int * original_bucket, int * newMapping, char * bucket_index,int Max,int *newMapping0){
    int map_match[newMapping[0] + 1];
    int no_match[original_bucket[0]+1];
    int count = 0,i,j, result = 0;
    printf("In Merge\n");
    Zeroing(no_match,original_bucket[0] + 1);
    Zeroing(map_match,newMapping[0] + 1);
    for(int i = 0; i < Max + 1; i++) bucket_index[i] = '0';// initialize the string;
    bucket_index[Max+1] = '\0'; // set the end of bucket_index, because bucket_index is string type data;

    
    // search begin
    for(i = 1; i <= original_bucket[0]; i++){
        // successful_match = 0;
        for(j = 1; j <= *newMapping0; j++){
            if(!map_match[j] && newMapping[j] == original_bucket[i]){
                map_match[j] = 1;
                bucket_index[j] = '1';
                // result += 1<<(Max - j);
                ++result;
                break;
            }
        }
        if(j > *newMapping0){
            no_match[count] = original_bucket[i];
            ++count;          
        }
   }
    
    if(Max - *newMapping0 < count){
        // printf("failed to merge\n");
        return 0;
    }
    for(i = 0; i < count; i++){
        newMapping[*newMapping0 + 1] = no_match[i];
        // printf("%d ",(Max - newMapping[0] - 1));
        // result += 1 << (Max - newMapping[0] - 1);
        bucket_index[*newMapping0 + 1] = '1';
        (*newMapping0)++;
    }

    return result;
}

int ** Compress(int ** original_bucket, int ** newMapping, int n,int Max){
    
    int newMappingRows = 0;
    int successful = 0;
    int count = 0;
    int temp = 0,max_match,max_match_row;
    int or_mapping;
    int i,j;
    char *** bucket_index = (char ***)malloc(n*sizeof(char **));

    for(int i = 0; i < n; i++){
        bucket_index[i] = (char **)malloc(2*sizeof(char *));
        bucket_index[i][0] = (char *)malloc(5*sizeof(char));
        bucket_index[i][1] = (char *)malloc((Max + 2)*sizeof(char));
    }
    
    
    for(i = 0; i < n; i++){
        max_match = 0;
        for(j = 0; j < newMappingRows; j++){
            // if(Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max)){
            //     sprintf(bucket_index[i][0],"%d",j);
            //     // printf("successful\n");
            //     break;
            // }
            or_mapping = newMapping[j][0];
            temp = Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max,&or_mapping);
            max_match = (temp > max_match) ? max_match_row = j,temp : max_match; 
        }
        system("pause");
        if(!max_match){
            newMappingRows ++;
            newMapping = realloc(newMapping,(newMappingRows)*sizeof(int **));
            newMapping[j] = (int *)malloc((Max + 1) * sizeof(int));
            newMapping[j][0] = 0;
            printf("j = %d\n",j);
            system("pause");
            Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max,&newMapping[j][0]);
            sprintf(bucket_index[i][0],"%d",j);
        }else{
            Merge(original_bucket[i],newMapping[max_match_row],bucket_index[i][1],Max,&newMapping[max_match_row][0]);
            sprintf(bucket_index[i][0],"%d",max_match_row);
        }

        // printf("%s\n",bucket_index[i][1]);
        // printf("-------------\n");
        // printf("%s | %s\n",bucket_index[i][0],bucket_index[i][1]);
        // printf("=============\n");
        // printf("%d | ",newMapping[j][0]);
        // for(int i = 1;  i <= newMapping[j][0]; i++) printf("%d ",newMapping[j][i]);
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
    // for(int i = 0; i < n; i++){
    //     amounts_of_elements = (rand() % m) + 1;
    //     // printf("amounts of elements = %d\n",amounts_of_elements);
    //     bucket[i] = (int *)malloc((amounts_of_elements + 1)*sizeof(int)); // malloc amount_of_element + 1 '1' is for first element
    //     bucket[i][0] = amounts_of_elements;
    //     for(int j = 1; j <= bucket[i][0]; j++){
    //         bucket[i][j] = rand()%d;
    //     }
    // }

    {
        bucket[0] = (int *)malloc(5 * sizeof(int));
        bucket[0][0] = 4;bucket[0][1] = 1;bucket[0][2] = 2;bucket[0][3] = 5;bucket[0][4] = 7;

        bucket[1] = (int *)malloc(5 * sizeof(int));
        bucket[1][0] = 4;bucket[1][1] = 2;bucket[1][2] = 3;bucket[1][3] = 5;bucket[1][4] = 7;

        bucket[2] = (int *)malloc(4 * sizeof(int));
        bucket[2][0] = 3;bucket[2][1] = 2;bucket[2][2] = 4;bucket[2][3] = 8;

        bucket[3] = (int *)malloc(4 * sizeof(int));
        bucket[3][0] = 3;bucket[3][1] = 2;bucket[3][2] = 3;bucket[3][3] = 8;

        bucket[4] = (int *)malloc(3 * sizeof(int));
        bucket[4][0] = 2; bucket[4][1] = 2; bucket[4][2] = 7;

        bucket[5] = (int *)malloc(3 * sizeof(int));
        bucket[5][0] = 2; bucket[5][1] = 1; bucket[5][2] = 3; 

        bucket[6] = (int *)malloc(2 * sizeof(int));
        bucket[6][0] = 1; bucket[6][1] = 2;

        bucket[7] = (int *)malloc(4 *sizeof(int));
        bucket[7][0] = 3; bucket[7][1] = 1; bucket[7][2] = 5;bucket[7][3] = 6;

        bucket[8] = (int *)malloc(4 *sizeof(int));
        bucket[8][0] = 3; bucket[8][1] = 1; bucket[8][2] = 5; bucket[8][3] = 7;
    }
    for(int i = 0; i < n; i++){
        printf("%d | ",bucket[i][0]);
        for(int j = 1;j <= bucket[i][0];j++){
            printf("%5d",bucket[i][j]);
        }
        printf("\n");
    }
    system("pause");
    bucketAmountOfNewMapping = MaxAmountOfElementInBucket(bucket,n);
    Compress(bucket,newMapping,n,bucketAmountOfNewMapping);
    return 0;
}
