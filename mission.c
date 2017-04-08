#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/type.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "mission.h"


void My_Write(struct F_name_type *F)
{
        memset(sbuf,0, sizeof(sbuf));
        fb = open(F->file_name,'r');
        read(fb,sbuf,317070);
        close(fb);
        send(acc_num,sbuf,sizeof(sbuf),0);
        printf("ELSE++%s\n",sbuf);              
}

void Client_Content(struct F_name_type *F)
{
        
         if((strcmp(F->file_type,"html"))==0)
         {
              My_Write(F);
              close(acc_num);
                Write_log_file("close The child program acc_num  \n");
         }else if((strcmp(F->file_type,"png"))==0)
         {
                My_Write(F);
               close(acc_num);
                Write_log_file("close The child program acc_num  \n");
         }else if((strcmp(F->file_type,"gz"))==0)
         {
                My_Write(F);
                close(acc_num);
                Write_log_file("close The child program acc_num  \n");
         }
         else
                close(acc_num);    
                send(acc_num,"\r\n\r\n",4,0);//end
}


void HTTP_Response(struct F_name_type *x)
{
        struct F_name_type *F = x;
        send(acc_num,PATH,strlen(PATH),0);//HTTP/1.1 200 OK
            printf(PATH);
        send(acc_num,TYPE,strlen(TYPE),0);//COntent-Type:
            printf(TYPE);    
        send(acc_num,F->file_type,sizeof(*(F->file_type)),0);//html
                printf("%s\n",(F->file_type));
        send(acc_num,"\r\n\r\n",strlen("\r\n\r\n"),0);//end 
      
        Client_Content(F);       
}

void Write_Page(struct F_name_type *F)
{
        HTTP_Response(F);//write http
        Write_log_file("Sent the http is OK! %d\n");
        Client_Content(F);    //write content
        Write_log_file("Sent the content is OK! %d\n");
}

struct F_name_type * Get_path(char buf[1024]) //GET / HTTP/1.1
{       
        char * rev = buf;       
        F.file_name = malloc(30*sizeof(char));
        F.file_type = malloc(20*sizeof(char));
        memset(F.file_name,0, sizeof(F.file_name));
        memset(F.file_type,0, sizeof(F.file_type));
        for(;i<30;i++)
        {
                if(*(rev+i)!=' ')
                {
                        F.file_name[i-5]=*(rev+i);
                        if(tmp==1)
                        {
                                F.file_type[num++]=*(rev+i);
                        }
                        if(*(rev+i)=='.')
                        {
                                num = 0;
                                tmp=1;
                        }
                }
                else
                break;       
        }
        F.file_type[num]='\0';
	F.file_name[i-5]='\0';
        printf("file_name+====%s \n",F.file_name);
        printf("file_type+====%s \n",F.file_type);
        return (&F);
}



void Do_ClientMission(char *buf)
{
        struct F_name_type *F;
        pid_t t_pid;
        int fork_num;
        fork_num = fork();
        if(fork_num < 0)
        {
                printf("fork is error\n");
        }else if(fork_num == 0)
        {
                close(sock_num);//The child program sock_num mast be close.
                 F = Get_path(buf);
                 Write_Page(F);
                printf("The child num isCCCCCCCCCCCCC %d\n",getpid());
                close(acc_num);
                exit(0);
         }else   
         {  
                 t_pid = wait(NULL);
                 printf("###########################%d",t_pid);
                close(acc_num);
          }
        close(acc_num);//client for do       
}

void Recv(char * buf)
{
        tmp = 0,i=5,num = 0;
        memset(buf,0, 1024);
        re_num = recv(acc_num,buf,1024,0);
        if(re_num < 0)
        {
                printf("_+%d",errno);
                printf("xx%d\n",re_num);
        } 
}

void Mission()
{
        int Lcin;
        char buf[1024];//rev
        Lcin =sizeof(cin);
        while(1)
        {
                acc_num = accept(sock_num,(struct sockaddr *)&cin,(socklen_t*)&Lcin);
                printf("S%d\n",acc_num); 
                Write_log_file("Sokect is accept !  and the new_socket ID is %d\n",acc_num);
                if(acc_num == -1)
                {
                        printf("accept is wrong\n");
                        printf("%d\n",errno);
                        exit (1);
                }     
                Recv(buf);  //error  (buf)
                printf("%s\n",buf); //output The http protocol
                Write_log_file("Recv is successfully ! \n");
getchar();
                Do_ClientMission(buf);
             }
        
}
