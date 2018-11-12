#include<stdio.h>
#include<stdlib.h>
#define EOB -1

void fprint_result(int newMappingRow,int **newMapping,char *** bucket_index,int **original_bucket,int n);

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
                result += 2;
                break;
            }
        }
        if(j > *newMapping0){
            no_match[count] = original_bucket[i];
            ++count;          
        }
   }
    
    if(Max - *newMapping0 < count) return EOB;
    for(i = 0; i < count; i++){
        newMapping[*newMapping0 + 1] = no_match[i];
        bucket_index[*newMapping0 + 1] = '1';
        (*newMapping0)++;
        result ++;
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
    return max_match == EOB ? max_match : max_match_row;
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
        max_match = EOB;
        max_match = bucket_union(newMappingRows,original_bucket[i],newMapping,bucket_index[i],Max);
        if(max_match == EOB){
            newMapping[newMappingRows] = (int *)malloc((Max + 1) * sizeof(int));
            newMapping[newMappingRows][0] = 0;
            Merge(original_bucket[i],newMapping[newMappingRows],bucket_index[i][1],Max,&newMapping[newMappingRows][0]);
            sprintf(bucket_index[i][0],"%d",newMappingRows);
            newMappingRows ++;
        }else{
            max_match_row = max_match;
            Merge(original_bucket[i],newMapping[max_match_row],bucket_index[i][1],Max,&newMapping[max_match_row][0]);
            sprintf(bucket_index[i][0],"%d",max_match_row);
        }
    }
    // for(int i = 0; i < n; i++){
    //     printf("%s %s\n",bucket_index[i][0],bucket_index[i][1]);
    // }
    // for(int i = 0; i < newMappingRows; i++){
    //     printf("%d | ",newMapping[i][0]);
    //     for(int j = 1;j <= newMapping[i][0]; j++){
    //         printf("%5d ",newMapping[i][j]);
    //     }
    //     printf("\n");
    // }
    fprint_result(newMappingRows,newMapping,bucket_index,original_bucket,n);
    return newMapping;
}

void fprint_result(int newMappingRow,int **newMapping,char *** bucket_index,int **original_bucket,int n){
    FILE * f_out = NULL;
    f_out = fopen("hw5.out","w");
    if(f_out){
        fprintf(f_out,"%3d\n\n",newMappingRow);
        for(int i = 0; i < n; i++){
            fprintf(f_out,"%3s /",bucket_index[i][0]);
            for(int j = 1; j <= original_bucket[i][0]; j++){
                fprintf(f_out,"%3d",original_bucket[i][j]);
            }
            fprintf(f_out,"\n");
        }
        fprintf(f_out,"\n");
        for(int i = 0; i < newMappingRow; i++){
            fprintf(f_out,"%3d /",i);
            for(int j = 1; j <= newMapping[i][0]; j++)
                fprintf(f_out,"%3d",newMapping[i][j]);
            fprintf(f_out,"\n");
        }
    }else{
        printf("Cannot open hw5.out");
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]),m = atoi(argv[2]),d = atoi(argv[3]), s = atoi(argv[4]);
    srand(s);
    int amounts_of_elements;
    int **bucket = (int **)malloc(n*sizeof(int *));
    int ** newMapping;
    int bucketAmountOfNewMapping;
    char *** bucket_index;
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
    Compress(bucket,newMapping,n,m);
    return 0;
}
