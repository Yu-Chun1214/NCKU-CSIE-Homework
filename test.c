#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

        int n = atoi(argv[1]);
        int m = atoi(argv[2]);
        int d = atoi(argv[3]);
        int s = atoi(argv[4]);

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

        // for( i = 0; i < n; i++)                         //計算每行共有幾個元素
        //         for( j = 0; j < m; j++)
        //         {
        //                 if(original_bucket[i][j] == -1)
        //                 {
        //                         total[i] = j;
        //                         break;
        //                 }
        //                 if(original_bucket[i][j]!=-1 && j==(m-1))
        //                 {
        //                         total[i] = m;
        //                         break;
        //                 }
        //         }

        /*
        for( i = 0; i<n; i++)                           //將其以小到大的方式排列好
                for(j=0;j<total[i]-1;j++)
                {
                        if(original_bucket[i][j+1]==-1) break;
                        if(original_bucket[i][j]>original_bucket[i][j+1])
                        {
                                temp=original_bucket[i][j];
                                original_bucket[i][j]=original_bucket[i][j+1];
                                original_bucket[i][j+1]=temp;
                                i=0;
                        }
                }
        printf("\n");


        for(i=0;i<n;i++)                                //印出以方便觀察
                {
                for(j=0;j<total[i];j++)
                        printf("%d ",original_bucket[i][j]);
                printf("\n");
                }
*/
        printf("\n");

        int storage[n]; //用於暫存每行共幾個元素
        int left[n];    //用於確認new_mapping每行剩下多少位置可以放
        int buffer[n][m];

        // initialization for compress
        for (i = 0; i < n; i++)
                storage[i] = total[i]; //將每行共需要幾個暫存起來

        for (i = 0; i < n; i++)
                left[i] = m;

        for (i = 0; i < n; i++)
                for (j = 0; j < m; j++)
                        buffer[i][j] = original_bucket[i][j];

        int l, h, g, k;
        for (i = 0; i < n; i++)         // each row in original_bucket                               //original_bucket的行數
                for (k = 0; k < n; k++) //new_mapping的行數
                {
                        total[i] = storage[i];
                        for (l = 0; l < m; l++) //each element in row in new_mapping               //new_mapping的欄號
                        {
                                for (j = 0; j < storage[i]; j++) //original_bucket的欄號 each element in bucket_original
                                {
                                        if (new_mapping[k][l] == original_bucket[i][j])
                                        {
                                                total[i]--;
                                                // --amount;
                                                original_bucket[i][j] = -1;
                                                break;
                                        }
                                }
                                // if (l == (m - 1))// the last element in row in new_mapping
                                // {
                                //         // if (left[k] >= total[i])
                                //         if(left[k] >= amount)
                                //         {
                                //                 for (g = 0; g < storage[i]; g++)
                                //                 {
                                //                         if (original_bucket[i][g] != -1)
                                //                                 for (h = 0; h < m; h++)
                                //                                         if (new_mapping[k][h] == -2)
                                //                                         {
                                //                                                 new_mapping[k][h] = original_bucket[i][g];
                                //                                                 break;
                                //                                         }
                                //                 }
                                //                 left[k] -= total[i];
                                //                 k = n - 1;
                                //         }
                                //         if (left[k] < total[i])
                                //         {
                                //                 for (g = 0; g < storage[i]; g++)
                                //                         original_bucket[i][g] = buffer[i][g];
                                //                 total[i] = storage[i];
                                //         }
                                // }
                        }
                        if (l == m )// the last element in row in new_mapping
                        {
                                if (left[k] >= total[i])
                                {
                                        for (g = 0; g < storage[i]; g++)
                                        {
                                                if (original_bucket[i][g] != -1)
                                                        for (h = 0; h < m; h++)
                                                                if (new_mapping[k][h] == -2)
                                                                {
                                                                        new_mapping[k][h] = original_bucket[i][g];
                                                                        break;
                                                                }
                                        }
                                        left[k] -= total[i];
                                        
                                        k = n - 1;
                                }
                                if (left[k] < total[i])
                                {
                                        for (g = 0; g < storage[i]; g++)
                                                original_bucket[i][g] = buffer[i][g];
                                        total[i] = storage[i];
                                }
                        }
                }
        for (i = 0; i < n; i++)
        {
                printf("%d | ", i);
                for (j = 0; j < m; j++)
                {
                        if (new_mapping[i][j] != -2)
                                printf("%d ", new_mapping[i][j]);
                }
                printf("\n");
        }
        return 0;
}