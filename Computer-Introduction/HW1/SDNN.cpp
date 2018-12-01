#include<math.h>
#include<vector>
#include<iostream>

using namespace std;

int main(){
    int temp;
    double mean = 0;
    double ans = 0;
    vector<int> data;
    FILE * file = NULL;
    file = fopen("E64061151.2018-09-27-06-07-48.peakposition.txt","r");
    if(file == NULL) throw "Cannot open File";
    else{
        while(EOF != fscanf(file,"%d",&temp)){
            data.push_back(temp);
        }
    }
    for(int i = 0; i < data.size() - 1; i++)
        data[i] = (data[i + 1] - data[i]) * 2;
    data.pop_back();

    for(int i = 0; i < data.size(); i++)
        mean += data[i];
    mean /= (double)data.size();

    for(int i = 0; i < data.size(); i++)
        ans += pow((data[i] - mean),2);
    ans = sqrt(ans/(double)data.size());

    printf("SDNN = %.8f\n",ans);
}
