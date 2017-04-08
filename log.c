#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <stdarg.h>
#include "log.h"

void System_time()//
{
        
        time_t System_time,tmp;
        time(&System_time);
        D = localtime(&System_time);
        printf("[%d-%d-%d 星期%d %d:%d:%d]",D->tm_year+1900,D->tm_mon+1,D->tm_mday,D->tm_wday,D->tm_hour,D->tm_min,D->tm_sec);
;
        printf("\n");
}
void Write_log_file(const char *format,...)
{
        FILE *fd;
        int t;
        va_list ap;
        va_start(ap,format);
        System_time();
        fd = fopen("error.log","a+");
	if (NULL == fd)
		printf ("open file failed!\n");
        fprintf(fd,"[%d-%d-%d 星期%d %d:%d:%d]",D->tm_year+1900,D->tm_mon+1,D->tm_mday,D->tm_wday,D->tm_hour,D->tm_min,D->tm_sec);
        vfprintf(fd,format,ap);
        va_end(ap);
        fclose(fd);
}




