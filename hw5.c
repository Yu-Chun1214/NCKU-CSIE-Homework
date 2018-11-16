#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

void swap(int *p1,int *p2){
 int tmp=*p1;
 *p1=*p2;
 *p2=tmp;
}
int main(int argc,char *argv[]){
 int n=atoi(argv[1]);
 int m=atoi(argv[2]);
 int d=atoi(argv[3]);
 int s=atoi(argv[4]);
 srand(s);

 int origin[n][m];//={7,5,-1,-1,-1,7,6,1,6,-1,6,9,9,-1,-1,9,-1,-1,-1,-1,0,1,0,2,-1};     //起始bucket
 int total[n];      //每行總元素數目
 int final[n][m];     //結果bucket
 int left[n];      //用於確認final每行都剩下多少位置可以放

 bool list[n];
 int correspond[n];     //用於確認有幾個已經被放入
 int merges[n];      //用於排序merge
 int order[n];      //用於紀錄merge多少之順序
 bool check[n][m][1];
 bool count[m][1];

 for(int i=0;i<n;i++) for(int j=0;j<m;j++) {origin[i][j]=-1; final[i][j]=-2; check[i][j][0]=true;}//起始都先放-1 最終都先放-2 check拿來確認是否已經放入
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 for(int i=0;i<n;i++)//亂數產生origin
 {
  int k=(rand()%d)+1;
  for(int j=0;j<k;j++)
  {
   origin[i][j]=(rand()%d);
   printf("%d ",origin[i][j]);
  }
  printf("\n");
 }
 for(int i=0;i<n;i++)  
  for(int j=0;j<m;j++)   
  {
   if(origin[i][j]==-1) {total[i]=j; break;}
   if(origin[i][j]!=-1 && j==(m-1)) {total[i]=m; break;}
  }
 printf("\n");
//-----------------------------------------------------------------------------------------------------------------------------
 for(int i=0;i<n;i++) left[i]=m;
 for(int i=0;i<n;i++) {correspond[i]=0; merges[i]=0; order[i]=-100;}
 for(int i=0;i<m;i++) count[i][0]=true;
//--------------------------------------------------------------------------------------------------------------------------------

 for(int i=0;i<n;i++)    //origin的行數
 {
  for(int k=0;k<n;k++) list[k]=true;
  for(int k=0;k<n;k++)   //final的行數 每到新的一行 計數歸0
  {
   correspond[k]=0;
   merges[k]=0;

   for(int l=0;l<m;l++) count[l][0]=true;//跑到final的新行就要先把所有恢復成true

   for(int j=0;j<total[i];j++) //origin的欄號 用final去找原始
   {
    for(int l=0;l<m;l++) //final的欄號
    {
     if(count[l][0]==true) //如果是true代表還沒有放過
      if(final[k][l]==origin[i][j])
      {
       correspond[k]++;
       merges[k]++;
       count[l][0]=false;
       break;
      }
    }  
   }   
  }
//------------------------------------------------------------------------------------------------------------------
  for(int k=0;k<n;k++) if(merges[k]<merges[k+1]){swap(&merges[k],&merges[k+1]); k=0;}
  for(int k=0;k<n;k++) 
   for (int h=0;h<n;h++)
    if(merges[k]==correspond[h]&&list[h]) {order[k]=h; list[h]=false; break;}
//------------------------------------------------------------------------------------------------------------------
  
  for(int k=0;k<n;k++)
  {
   if(total[i]==correspond[order[k]])     break;

   if(left[order[k]]>(total[i]-correspond[order[k]])||left[order[k]]==(total[i]-correspond[order[k]])) //確認能不能放入該列
   { 
    for(int j=0;j<total[i];j++)  //用final掃原始
    {
     for(int l=0;l<m;l++)
     {
      if(check[order[k]][l][0]==true)   //確認是否已經被讀進去過了
      {
       if(origin[i][j]==final[order[k]][l]) //如果一樣且沒有被讀過 就把它變成讀過
       {
        check[order[k]][l][0]=false;
        break;
       }
       if(origin[i][j]!=final[order[k]][l])
        if(final[order[k]][l]==-2)
        {
         final[order[k]][l]=origin[i][j];
         check[order[k]][l][0]=false;
         break; 
        }
      }
     }
    }
    left[order[k]]-=(total[i]-correspond[order[k]]);
    break;
   }
  } 
  for(int k=0;k<n;k++) for(int l=0;l<m;l++) check[k][l][0]=true;
  
 }
//-----------------------------------------------------------------------------------------------
 for(int i=0;i<n;i++)
 {
  for(int j=0;j<m;j++)
  {
   if(final[i][j]!=-2) printf("%3d ",final[i][j]);
  }
  printf("\n");
 }
 return 0;
}