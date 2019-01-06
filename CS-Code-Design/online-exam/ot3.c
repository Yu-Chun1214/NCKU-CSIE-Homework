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
    unsigned IP;
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

    char sex[10],phone[20];
    int edge,day,month,year;
    int p1,p2,p3,p4;

    int iter = 0;
    unsigned char * ipit = (unsigned char *)&p[iter].IP;
    printf("sizeof(unsigned) = %lu\n",sizeof(unsigned));
    while(EOF != fscanf(file,"%s%s%s%d%d%d%4d%2d%2d%2d%2d%2d%3d.%3d.%3d.%3d\n",p[iter].lastname,p[iter].firstname,sex,&edge,&day,&month,&year,&phone[0],&phone[1],&phone[2],&phone[3],&phone[4],ipit,ipit + 1,ipit + 2,ipit + 3)){
        if(sex[0] == 'm') p[iter].sex = 1;
        else p[iter].sex = 0;
        p[iter].age = edge;
        p[iter].day = day;
        p[iter].month = month;
        p[iter].year = year - 1900;
        // printf("year = %d\n",year);
        // printf("phone = %d%d%d%d%d\n",phone[0],phone[1],phone[2],phone[3],phone[4]);
        // printf("phone = %d%d%d%d%d\n",p[iter].cellphone[0],p[iter].cellphone[1],p[iter].cellphone[2],p[iter].cellphone[3],p[iter].cellphone[4]);
        /*Need to find a better solution*/
        for(int i = 0; i < 5;i++)
            p[iter].cellphone[i] = phone[i];
        iter++;
        ipit = (unsigned char *)&p[iter].IP;
        // printf("%d.%d.%d.%d\n",*(ipit),*(ipit + 1),*(ipit + 2),*(ipit + 3));
    }
    int count = iter;
    fclose(file);
    file = fopen("online_test.dat","w");
    for(int i = 0 ; i < count; i++){
        ipit = (unsigned char *)&p[i].IP;
        fprintf(file,"%s %s %s %d %d %d %d %02d%2d%2d%2d%2d %d.%d.%d.%d\n",
        p[i].lastname,p[i].firstname,p[i].sex ? "male" : "female",p[i].age,p[i].day,p[i].month,p[i].year + 1900,p[i].cellphone[0],p[i].cellphone[1],p[i].cellphone[2],p[i].cellphone[3],p[i].cellphone[4],*(ipit),*(ipit + 1),*(ipit + 2),*(ipit + 3));
    }
    
    return 0;
}
