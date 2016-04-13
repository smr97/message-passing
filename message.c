#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h> 
pthread_t t1, t2;

mqd_t createQ()
{
	struct mq_attr buf;        /* buffer for stat info */
    buf.mq_msgsize = 1024;
    buf.mq_maxmsg = 10;
    
    int flag = O_RDWR;
    
	mqd_t m = mq_open("/chut", flag, 0777, &buf);
    return m;
}

void *

int main()
{
    
    
    
    //mq_send();



}

