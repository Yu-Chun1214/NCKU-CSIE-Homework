#include <stdio.h>
#include <stdlib.h>

void Copy(int * dest, int * object,int n){
	for(int i = 0; i < n; i++){
		dest[i] = object[i];
	}
}

int compress(int n,int m,int * original_bucket,int * buffer, int new_mapping[],int *left,int total,int *new_mapping_row){
	int storage = total;
	int k, l, j,g,h;
	int max_match = 0,match;
	total = storage;
	match = -1;
	for(int i = 0; original_bucket[i] != -1; i++) printf("%d ",original_bucket[i]);
	printf("\n");

	for(l = 0; l < m; l++){ // for each element in new_mapping
		for(j = 0; j < storage; j++){ // for each element in original_bucket
			if((new_mapping)[l] == original_bucket[j]){
				total--;
				original_bucket[j] = -1;
				match += 2;
				break;
			}
		}
	}
	printf("left = %d, total = %d\n",*left,total);
	if(*left >= total){
		for(g = 0; g < storage; g++){
			if(original_bucket[g] != -1){
				for(h = 0; h < m; h++){
					if((new_mapping)[h] == -2){
						(new_mapping)[h] = original_bucket[g];
						// printf("new_mapping[%d] = %d\n",h,new_mapping[h]);
						match++;
						break;
					}
				}
			}
		}
		*left -= total;
		k = n - 1;
		return match;
	}
	if(*left < total){
		printf("in Copy\n");
		for (g = 0; g < m; g++)
        	original_bucket[g] = buffer[g];
			printf("%d ",original_bucket[g]);
	}
	// printf("befor return\n");
	return -1;
}

int bucket_union(int n,int m,int * original_bucket,int * buffer, int new_mapping[][m],int *left,int total,int *new_mapping_row){
	int max_match_row = -1,match_row;
	int max_match_num = 0,temp;
	int temp_left = 0;
	int temp_new_mapping[m];
	int temp_original_bucket[m];
	for(int i = 0; i < *new_mapping_row; i++){
		for(int j = 0 ; original_bucket[j]!=-1; j++) printf("%d ",original_bucket[j]);
		printf("\n");
		printf("newmapping row = %d\n",i);
		temp_left = left[i];
		Copy(temp_new_mapping,new_mapping[i],m);
		Copy(temp_original_bucket,buffer,m);
		temp = compress(n,m,temp_original_bucket,buffer,temp_new_mapping,&temp_left,total,new_mapping_row);
		max_match_num = (temp > max_match_num ? max_match_row = i,temp : max_match_num);
		// system("pause");
	}
	return max_match_row;
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int d = atoi(argv[3]);
    int s = atoi(argv[4]);

        if(n<=0||n>100||m<=0||m>100||d<=0||d>100||s<=0||s>100)
        {
                printf("Given number in command argument line is illegal.\n");
                return 2;
        }

    int temp = 0;
    int total[n];

    int original_bucket[n][m]; //起始bucket
    int new_mapping[n][m];     //最終bucket
    int i, j, r;
    // initializion
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            original_bucket[i][j] = -1;
            new_mapping[i][j] = -2;
        }

    //亂數產生original_bucket
    srand(s);
    for (i = 0; i < n; i++)
    {
        printf("%d | ", i);
        r = (rand() % m) + 1;
            total[i] = r;
        for (j = 0; j < r; j++)
        {
            original_bucket[i][j] = (rand() % d);
            printf("%d ", original_bucket[i][j]);
        }
        printf("\n");
        }

        printf("\n");

    int storage[n]; //用於暫存每行共幾個元素
    int left[n];    //用於確認new_mapping每行剩下多少位置可以放
    int buffer[n][m];
	int new_mapping_row = 0;

    // initialization for compress
    for (i = 0; i < n; i++)
        storage[i] = total[i];

    for (i = 0; i < n; i++)
        left[i] = m;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            buffer[i][j] = original_bucket[i][j];



    //process of compress
    int l, h, g, k;
	
    for (i = 0; i < n; i++){         //each row in original_bucket
		l = bucket_union(n,m,original_bucket[i],buffer[i],new_mapping,left,total[i],&new_mapping_row);
		printf("i = %d, l = %d\n",i,l);
		if(l == -1){
			h = compress(n,m,original_bucket[i],buffer[i],new_mapping[new_mapping_row],&left[new_mapping_row],total[i],&new_mapping_row);
			new_mapping_row +=1;
		}
		else {
			printf("match!!!\n");
			compress(n,m,original_bucket[i],buffer[i],new_mapping[l],&left[l],total[i],&new_mapping_row);
		}
		// system("pause");
		for(int p = 0; p < new_mapping_row; p++){
			for(int f = 0; new_mapping[p][f]!=-2; f++)
				printf("%d ", new_mapping[p][f]);
			printf("\n");
		}
		// system("pause");
	}
        
	for (i = 0; i < n && new_mapping[i][0] != -2; i++)
	{
			printf("%d / ", i);
			for (j = 0; j < m&&new_mapping[i][j] != -2; j++)
		{
					printf("%d ", new_mapping[i][j]);
		}
	printf("\n");
	}

	printf("\n");
	for (i = 0; i < n; i++)
	{
			if (new_mapping[i][0] == -2)
			{
					printf("The correct total number of buckets: %d\n", i);
					break;
			}
	}
    return 0;
}