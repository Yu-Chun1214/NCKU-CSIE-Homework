#include<stdio.h>
#include<stdlib.h>

void alerm(int a)
{
        if( a <= 0 || a > 100 )
        printf("Given %d is illegal.\n", a);
}

int main(int argc, char*argv[])
{
        int n = atoi(argv[1]);
        int m = atoi(argv[2]);
        int d = atoi(argv[3]);
        int s = atoi(argv[4]);
        int i,j,k, temp = 0;

        alerm(n);
        alerm(m);
        alerm(d);
        alerm(s);

        int bucket[n][m];
        // initialize
        for( i = 0 ; i < m ; i++)
        {
                for( j = 0 ; j < n ; j++)
                {
                        bucket[i][j] = -1;
                }
        }
        printf("%d %d %d %d\n",n,m,d,s);
        srand(s);
		//int temp;
        // int generate_number_of_elements_in_a_bucket = (rand()%m) + 1;
        // int generate_a_random_num = (rand()%d);
        ////////////////////////////////////////////////////////////////////////////////
        for( j = 0; j < n; j++)
        {
				temp = rand()%m + 1;//BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!
                for( i = 0 ; i < temp ; i++)
                        {
                                bucket[j][i] = rand() % d;
                                printf("%d ", bucket[j][i]);
                        }
                printf("\n");
        }

        printf("\n");

        int new_bucket[n][m];
        for( j = 0; j < n; j++)
        {
                for( i = 0 ; i < m ; i++)
                        {
                                new_bucket[j][i] = bucket[j][i];
                        }
        }
        for( j = 0; j < n; j++)//every row
        {
                // Insertion Sort in new_bucket from small to big
                
                for( k = 1; k < m ; k++) // every element in row
                {
                        for( i = 0 ; i < m - k ; i++)
                        {
                                        if(new_bucket[j][i] < new_bucket[j][i+1])//BUG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                        {
                                                temp = new_bucket[j][i];
                                                new_bucket[j][i] = new_bucket[j][i+1];
                                                new_bucket[j][i+1] = temp;
                                        }
                        }
                }
        }

        for( j = 0; j < n; j++)// each row
        {
                for( i = 0 ; i < m ; i++) // each element in row
                {
                        // if(new_bucket[j][i] >= 0) // in initialization, each element is set to -1;
                            printf("%d ", new_bucket[j][i]);
                }
                printf("\n");
        }

        int final_bucket[n][m];
        // initializition
        for( i = 0 ; i < n ; i++)
        {
                for( j = 0 ; j < m ; j++)
                {
                        final_bucket[i][j] = -1;
                }
        }

        // first row of new_bucket
        for( i = 0 ; i < m ; i++)
        {
                final_bucket[0][i] = new_bucket[0][i];
        }

        printf("\n");
        int total[n];
        int h = 0;
        for(i = 0 ; i < n ; i++) // scan each row;
        {
                for(j = 0; j < m ; j++) // scan each element in row;
                {
                        if(new_bucket[i][j] == -1)
                        {
                                total[h] = m - j;
                                h++;
                                break; // means that arrive the last element;
                        }
                        // if(new_bucket[i][j] >= 0 && j == (m - 1))
                        // {
                        //         total[h] = m;
                        //         break;
                        // }
                }
                printf("%d\n", total[i]);
        }
        return 0;
}
