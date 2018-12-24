#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char*argv[]){
        FILE *hw7 = fopen(argv[1],"rb");
        if(hw7!=NULL)
        {
                int i,a,j=0;
                int k=0, l=0, n=0;

                while(!feof(hw7))
                {
                        struct data{
                                unsigned char ethernet[14];
                                unsigned char IP[20];
                                unsigned char port[4];
                                unsigned char TCP[2000];
                                unsigned char UDP[2000];
                                unsigned char ICMP[2000];
                        }packet;

                        printf("#%d\n", j+1);

                        fread(packet.ethernet, sizeof(char), 6, hw7);
                        printf("DST MAC: ");
                        for(i=0;i<5;i++)
                                printf("%02x:", packet.ethernet[i]);
                        printf("%02x\n", packet.ethernet[5]);

                        fread(packet.ethernet, sizeof(char), 6, hw7);
                        printf("SRC MAC: ");
                        for(i=0;i<5;i++)
                                printf("%02x:", packet.ethernet[i]);
                        printf("%02x\n", packet.ethernet[5]);

                        fread(packet.ethernet, sizeof(char), 2, hw7);
                        fread(packet.IP, sizeof(char), 20, hw7);

                        a = 256*packet.IP[2]+packet.IP[3]+14;

                        if(packet.IP[9]==0x06)
                        {
                                printf("Protocol: TCP\n");
                                printf("SRC IP: ");
                                for(i=12; i<15; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[15]);
                                printf("DST IP: ");
                                for(i=16; i<19; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[19]);
                                fread(packet.port, sizeof(char), 2, hw7);
                                printf("SRC Port: %d\n", 256*packet.port[0]+packet.port[1]);
                                fread(packet.port, sizeof(char), 2, hw7);
                                printf("DST Port: %d\n", 256*packet.port[0]+packet.port[1]);
                                fread(packet.TCP, sizeof(char), (a-38), hw7);
                                k++;
                        }
                        else if(packet.IP[9]==0x11)
                        {
                                printf("Protocol: UDP\n");
                                printf("SRC IP: ");
                                for(i=12; i<15; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[15]);
                                printf("DST IP: ");
                                for(i=16; i<19; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[19]);
                                fread(packet.port, sizeof(char), 2, hw7);
                                printf("SRC Port: %d\n", 256*packet.port[0]+packet.port[1]);
                                fread(packet.port, sizeof(char), 2, hw7);
                                printf("DST Port: %d\n", 256*packet.port[0]+packet.port[1]);
                                fread(packet.UDP, sizeof(char), (a-38), hw7);
                                l++;
                        }
                        else if(packet.IP[9]==0x01)
                        {
                                printf("Protocol: ICMP\n");
                                printf("SRC IP: ");
                                for(i=12; i<15; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[15]);
                                printf("DST IP: ");
                                for(i=16; i<19; i++)
                                        printf("%d.", packet.IP[i]);
                                printf("%d\n", packet.IP[19]);
                                fread(packet.ICMP, sizeof(char), (a-34), hw7);
                                n++;
                        }
                        printf("Packet Length: %d\n", a);
                        printf("\n");
                        j++;
                        fscanf(hw7," ");
                }
                printf("Number of Packet: %d\n", j);
                printf("Number of TCP Packet: %d\n", k);
                printf("Number of UDP Packet: %d\n", l);
                printf("Number of ICMP Packet: %d\n", n);
        }else{
                printf("Could not open the file.\n");
        }
        return 0;
}