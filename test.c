#include <stdio.h>
#include <stdlib.h>

int bucket_union(int n,int m,int * original_bucket,int * buffer, int new_mapping[][m],int *left,int total){
	int storage = total;
	int k, l, j,g,h;
	int max_match = 0,temp = 0;
	for(k = 0; k < n; k++){
		total = storage;
		for(l = 0; l < m; l++){
			for(j = 0; j < storage; j++){
				if((new_mapping)[k][l] == original_bucket[j]){
					total--;
					original_bucket[j] = -1;
					temp += 2;
					break;
				}
			}
		}
		
		if(l == m){
			if(left[k] >= total){
				for(g = 0; g < storage; g++){
					if(original_bucket[g] != -1){
						for(h = 0; h < m; h++){
							if((new_mapping)[k][h] == -2){
								(new_mapping)[k][h] = original_bucket[g];
								temp++;
								break;
							}
						}
					}
				}
				left[k] -= total;
				k = n - 1;
			}
			if(left[k] < total){
				for(g = 0; g < storage; g++){
					original_bucket[g] = buffer[g];
					total = storage;
				}
			}
		}
	}
	return 0;
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

    // initialization for compress
    for (i = 0; i < n; i++)
        storage[i] = total[i];

    for (i = 0; i < n; i++)
        left[i] = m;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            buffer[i][j] = original_bucket[i][j];
	// printf("newMapping address = %p\n",&new_mapping[0][1]);
    //process of compress
    int l, h, g, k;
    for (i = 0; i < n; i++)         //each row in original_bucket
		bucket_union(n,m,original_bucket[i],buffer[i],new_mapping,left,total[i]);
        // for (k = 0; k < n; k++) // each row in new_mapping
        // {
        //     total[i] = storage[i];
        //     for (l = 0; l < m; l++) //each element in row in new_mapping
        //     {
        //         for (j = 0; j < storage[i]; j++) //each element in original_bucket
        //         {
        //             if (new_mapping[k][l] == original_bucket[i][j])
        //             {
        //                 total[i]--;
        //                 original_bucket[i][j] = -1;
        //                 break;
        //             }
        //         }
        //     }
        //     if (l == m)// the last element in row in new_mapping
        //     {
        //         if (left[k] >= total[i])
        //         {
        //             for (g = 0; g < storage[i]; g++)
        //             {
        //                 if (original_bucket[i][g] != -1)
        //                     for (h = 0; h < m; h++)
        //                         if (new_mapping[k][h] == -2)
        //                             {
        //                                 new_mapping[k][h] = original_bucket[i][g];
        //                                 break;
        //                             }
        //             }
        //             left[k] -= total[i];
        //             k = n - 1;
        //         }
        //         if (left[k] < total[i])
        //         {
        //             for (g = 0; g < storage[i]; g++)
        //                 original_bucket[i][g] = buffer[i][g];
        //                 total[i] = storage[i];
        //         }
        //     }
        // }
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