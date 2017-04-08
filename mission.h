
#define PATH "HTTP/1.1 200 OK\r\n"
#define TYPE "Content-Type: "
//localhost:8000/index.html

struct F_name_type
{
        char *file_name;//[30];//file-path
        char *file_type;//[10];//file-type

}F;

 extern int sock_num;
extern  struct sockaddr_in sin,cin;
extern sock_num; 
int send_len,fb;
int acc_num = 1000;
int re_num;

char sbuf[317070];
int i=5,tmp=0,num=0;
 
void My_Write(struct F_name_type *F);
void Client_Content(struct F_name_type *F);
void HTTP_Response(struct F_name_type *x);
void Write_Page(struct F_name_type *F);
struct F_name_type * Get_path(char buf[1024]); //GET / HTTP/1.1
void Do_ClientMission(char *buf);
void Recv(char * buf);
void Mission();






