#include <stdio.h>
#include<stdlib.h>


typedef struct{
    char lastname[10];
    char firstname[16];
    unsigned sex : 1;
    unsigned age : 6;
    unsigned day : 5;
    unsigned month : 4;
    unsigned year : 7;
    unsigned :0;
    char IP[100];
    char cellphone[5];
}person;

int main(int argc, char const *argv[])
{
    FILE * file = NULL;
    file = fopen(argv[1],"r");
    if(!file){
        printf("file open failed\n");
        exit(0);
    }
    person p[100];
    unsigned num1;
    char sex[10];
    int age,day,month,year;
    int ip1,ip2,ip3,ip4;
    int i = 0;
    char ip[100];
    while(EOF != fscanf(file,"%s %s %s %d %d %d %d %u %s",p[i].lastname,p[i].firstname,sex,&age,&day,&month,&year,&num1,p[i].IP)){
        if(sex[i] == 'm')p[i].sex = 0;else p[i].sex = 1;
        p[i].age = age;
        p[i].day = day;
        p[i].month = month;
        p[i].year = year - 1900;
        p[i].cellphone[0] = num1 / 10000000;
        p[i].cellphone[1] = (num1 % 10000000)/100000; 
        p[i].cellphone[2] = (num1 % 100000) / 1000;
        p[i].cellphone[3] = (num1 % 1000) / 100;
        p[i].cellphone[4] = num1 % 100;
        i++;
   }
   int count = i;
   for(i = 0; i < count; i++){
       printf("%s %s %u %u %u %u %u %s %s\n",p[i].lastname,p[i].firstname,p[i].sex,p[i].age,p[i].day,p[i].month,p[i].year,p[i].cellphone,p[i].IP);
       system("pause");
   }

    return 0;
}
