#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    unsigned int TCP_num;
    unsigned int UDP_num;
    unsigned int ICMP_num;
}Ans;

void ANS_initialize(Ans * ans){
    ans->TCP_num = ans->UDP_num = ans->ICMP_num = 0;
}

void Skip(FILE * fp,int num){
    fpos_t position;
    fgetpos(fp,&position);
    position += num;
    fsetpos(fp,&position);
}

void PrintMac(const char * option,unsigned char * data){
    printf("%s",option);
    for(int i = 0; i < 5; i++)
        printf("%02x:",data[i]);
    printf("%02x\n",data[5]);
}

void PrintIP(const char * option,unsigned char * data){
    printf("%s",option);
    for(int i = 0; i < 3; i++)
        printf("%d.",data[i]);
    printf("%d\n",data[3]);
}

Ans * READING(FILE * fp){
    Ans * ans = (Ans *)malloc(sizeof(Ans));
    ANS_initialize(ans);
    
    int i = 1,counter = 0,length,packet_pos;

    unsigned char trash[10];
    unsigned char protocol;
    unsigned char total_length[2];
    unsigned char port[2];
    unsigned int packet_length;
    
    unsigned char data[10];
    unsigned char SRC_IP[4];
    unsigned char DST_IP[4];

    fseek(fp,0L,SEEK_END);
    length = ftell(fp);
    fseek(fp,0L,SEEK_SET);

     while(counter < length){
        packet_pos = 0;
        printf("#%d\n",i);
        fread(data,sizeof(char),6,fp);
        PrintMac("DST MAC: ",data);
        fread(data,sizeof(char),6,fp);
        PrintMac("Src MAC: ",data);
        fread(trash,sizeof(char),4,fp);
        fread(total_length,sizeof(char),2,fp);
        fread(trash,sizeof(char),5,fp);
        fread(&protocol,sizeof(char),1,fp);
        fread(trash,sizeof(char),2,fp);
        fread(SRC_IP,sizeof(char),4,fp);
        fread(DST_IP,sizeof(char),4,fp);
        
        packet_pos += 34;
        packet_length = 256 * total_length[0] + total_length[1] + 14;
        if(protocol == 0x06){
            printf("Protocol: TCP\n");
            PrintIP("SRC IP: ",SRC_IP);
            PrintIP("DST IP: ",DST_IP);
            fread(port,sizeof(char),2,fp);
            printf("SRC PORT: %d\n",256*port[0]+port[1]);

            fread(port,sizeof(char),2,fp);
            printf("DST PORT: %d\n",256*port[0]+port[1]);
            packet_pos += 4;
            ans->TCP_num += 1;
        }
        else if(protocol == 0x01){
            printf("Protocol: ICMP\n");
            PrintIP("SRC IP: ",SRC_IP);
            PrintIP("DST IP: ",DST_IP);
            ans->ICMP_num += 1;
        }
        else if(protocol == 0x11) {
            printf("Protocol: UDP\n");
            PrintIP("SRC IP: ",SRC_IP);
            PrintIP("DST IP: ",DST_IP);
            fread(port,sizeof(char),2,fp);
            printf("SRC PORT: %d\n",256*port[0]+port[1]);
            fread(port,sizeof(char),2,fp);
            printf("DST PORT: %d\n",256*port[0]+port[1]);
            packet_pos += 4;
            ans->UDP_num += 1;
        }
        Skip(fp,packet_length - packet_pos);
        printf("Packet Length: %d\n\n",packet_length);
        counter += packet_length;;
        i++;
    }
    printf("Number of Packet: %d\n",i - 1);
    return ans;
}

int main(int argc, char const * argv[]){
    FILE *fp = NULL;
    if(argc != 2) {
        printf("usage: ./hw7 filename\n");
        exit(0);
    }
    fp = fopen(argv[1],"rb");
    if(!fp){
    printf("Can't open file.\n");
      return -1;
    }
    Ans * ans;
    ans = READING(fp);
    printf("Number of TCP Packet: %d\n",ans->TCP_num);
    printf("Number of UDP Packet: %d\n",ans->UDP_num);
    printf("Number of ICMP Packet: %d\n",ans->ICMP_num);
    return 0;
}