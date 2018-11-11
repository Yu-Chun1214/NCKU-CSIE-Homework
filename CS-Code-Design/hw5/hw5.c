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
        for(j = 1; j <= *newMapping0; j++){
            if(!map_match[j] && newMapping[j] == original_bucket[i]){
                map_match[j] = 1;
                bucket_index[j] = '1';
                ++result;
                break;
            }
        }
        if(j > *newMapping0){
            no_match[count] = original_bucket[i];
            ++count;          
        }
   }
    
    if(Max - *newMapping0 < count) return EOF;
    for(i = 0; i < count; i++){
        newMapping[*newMapping0 + 1] = no_match[i];
        bucket_index[*newMapping0 + 1] = '1';
        (*newMapping0)++;
    }

    return result;
}

int bucket_union(int newMappingRows,int *original_bucket,int ** newMapping,char ** bucket_index, int Max){
    int original_match = 0;
    int temp;
    int max_match = -1, max_match_row = 0;
    for(int i = 0; i < newMappingRows; i++){
        original_match = newMapping[i][0];
        temp = Merge(original_bucket,newMapping[i],bucket_index[1],Max,&original_match);
        max_match = temp > max_match ? max_match_row = i,temp : max_match;
    }
    printf("max_match = %d\n",max_match);
    printf("max_match_row = %d\n",max_match_row);
    printf("============================\n");
    return max_match == EOF ? max_match : max_match_row;
}

int ** Compress(int ** original_bucket, int ** newMapping, int n,int Max){
    
    int newMappingRows = 0;
    int successful = 0;
    int count = 0;
    int temp = 0,max_match,max_match_row;
    int or_mapping;
    int i,j;
    char *** bucket_index = (char ***)malloc(n*sizeof(char **));
	newMapping = malloc(102*sizeof(int **));
    for(int i = 0; i < n; i++){
        bucket_index[i] = (char **)malloc(2*sizeof(char *));
        bucket_index[i][0] = (char *)malloc(5*sizeof(char));
        bucket_index[i][1] = (char *)malloc((Max + 2)*sizeof(char));
    }
    
    for(i = 0; i < n; i++){
        max_match = EOF;
        for(int k = 1; k <= original_bucket[i][0]; k++)
            printf("%5d",original_bucket[i][k]);
        printf("\n");
        // for(j = 0; j < newMappingRows; j++){
        //     or_mapping = newMapping[j][0];
        //     temp = Merge(original_bucket[i],newMapping[j],bucket_index[i][1],Max,&or_mapping);
        //     max_match = (temp > max_match) ? max_match_row = j,temp : max_match; 
        // }
        max_match = bucket_union(newMappingRows,original_bucket[i],newMapping,bucket_index[i],Max);
        // printf("max_match_row = %d\n",max_match_row);
        printf("max_match = %d\n",max_match);
        system("pause");
        if(max_match == EOF){
            
            newMapping = realloc(newMapping,(newMappingRows  + 1)*sizeof(int **));
            newMapping[newMappingRows] = (int *)malloc((Max + 1) * sizeof(int));
            newMapping[newMappingRows][0] = 0;
            printf("newMappingRows = %d\n",newMappingRows);
            Merge(original_bucket[i],newMapping[newMappingRows],bucket_index[i][1],Max,&newMapping[newMappingRows][0]);
            sprintf(bucket_index[i][0],"%d",newMappingRows);
            newMappingRows ++;
        }else{
            max_match_row = max_match;
            Merge(original_bucket[i],newMapping[max_match_row],bucket_index[i][1],Max,&newMapping[max_match_row][0]);
            sprintf(bucket_index[i][0],"%d",max_match_row);
        }
        for(int k = 0; k < newMappingRows; k++){
            printf("%d | ",newMapping[k][0]);
            for(int l = 1; l <= newMapping[k][0]; l++)
                printf("%5d",newMapping[k][l]);
            printf("\n");
        }
        system("pause");
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
    int amounts_of_elements;
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

    // {
    //     bucket[0] = (int *)malloc(5 * sizeof(int));
    //     bucket[0][0] = 3;bucket[0][1] = 2;bucket[0][2] = 3;bucket[0][3] = 5;bucket[0][4] = 7;

    //     bucket[1] = (int *)malloc(5 * sizeof(int));
    //     bucket[1][0] = 4;bucket[1][1] = 1;bucket[1][2] = 3;bucket[1][3] = 7;bucket[1][4] = 9;

    //     bucket[2] = (int *)malloc(4 * sizeof(int));
    //     bucket[2][0] = 2;bucket[2][1] = 3;bucket[2][2] = 1;bucket[2][3] = 8;

    //     bucket[3] = (int *)malloc(6 * sizeof(int));
    //     bucket[3][0] = 5;bucket[3][1] = 1;bucket[3][2] = 2;bucket[3][3] = 3; bucket[3][4] = 4; bucket[3][5] = 5;

    //     bucket[4] = (int *)malloc(3 * sizeof(int));
    //     bucket[4][0] = 2; bucket[4][1] = 2; bucket[4][2] = 7;

    //     bucket[5] = (int *)malloc(3 * sizeof(int));
    //     bucket[5][0] = 2; bucket[5][1] = 1; bucket[5][2] = 3; 

    //     bucket[6] = (int *)malloc(2 * sizeof(int));
    //     bucket[6][0] = 1; bucket[6][1] = 2;

    //     bucket[7] = (int *)malloc(4 *sizeof(int));
    //     bucket[7][0] = 3; bucket[7][1] = 1; bucket[7][2] = 5;bucket[7][3] = 6;

    //     bucket[8] = (int *)malloc(4 *sizeof(int));
    //     bucket[8][0] = 3; bucket[8][1] = 1; bucket[8][2] = 5; bucket[8][3] = 7;
    // }
    for(int i = 0; i < n; i++){
        printf("%d | ",bucket[i][0]);
        for(int j = 1;j <= bucket[i][0];j++){
            printf("%5d",bucket[i][j]);
        }
        printf("\n");
    }
    bucketAmountOfNewMapping = MaxAmountOfElementInBucket(bucket,n);
    Compress(bucket,newMapping,n,m);
    return 0;
}
