#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/type.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "init.h"
 

void init()
{
        
        //socklen_t 
        bzero(&sin,sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_port=htons(8000);
        sin.sin_addr.s_addr=INADDR_ANY;
        //inet_addr("192.168.65.129");
        
        sock_num = socket(AF_INET,SOCK_STREAM,0);
        if(sock_num ==-1)
        {
                printf("error create sock_num\n");
                
                exit(1);
        }     
        printf("\n");
        printf("Socket id is %d\n",sock_num);
         Write_log_file("Sokect is created!  The socket ID is %d\n",sock_num);
         //fprintf("AAAAAAAAAAA\n");
        if(bind(sock_num,(struct sockaddr*)&sin,sizeof(sin))==-1)
        {
                printf("error create sock_num\n");
                exit(1);
        }
        Write_log_file("Sokect is bind successfully! \n");
        printf("lisening ...\n");
        if(listen(sock_num,10)==-1)
        {
                printf("error create sock_num\n");
                exit(1);
        }
        Write_log_file("Lisening ...! \n");  
}
