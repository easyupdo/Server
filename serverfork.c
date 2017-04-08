#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/type.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

//#include "init.h"
//#include "mission.h"
int main(int argc,char *argv[])
{
        init();
        Mission();
}
