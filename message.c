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

void *t1(void *arg)
{
	mqd_t q1 = createQ();
	if(mq_send(q1, "Thread 1 says hi", 16, 0))
	perror("mq_send()");
}

int main()
{
    pthread_create(&t1, 0, t1, NULL);
    pthread_create(&t2, 0, t2, NULL);
    
    
    
    
    //mq_send();



}

