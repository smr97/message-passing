#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h> 

pthread_t t1, t2;
pthread_mutex_t m1;
pthread_cond_t c1;

mqd_t global;

createQ()
{
	struct mq_attr buf;        /* buffer for stat info */
    buf.mq_msgsize = 10;
    buf.mq_maxmsg = 20;
    
    int flag = O_RDWR|O_NONBLOCK;
    
	global = mq_open("/chut", flag, 0777, &buf);
	
	printf("queue opened\n");
	
	/*if(global<0)
	perror("mq_open()");*/
//    return m;
}

void *f1(void *arg)
{
	//printf("f1 called\n");
	pthread_mutex_lock(&m1);
	
	printf("m locked\n");
	
	createQ();
	
	printf("t1 opened q\n");
	
	if(!mq_send(global, "1", 1, 0))
	perror("mq_send()");
	
	mq_close(global);
	//mq_unlink("/chut");
	printf("message sent\n");
	pthread_mutex_unlock(&m1);
	pthread_cond_signal(&c1);
	
	
	
}

void *f2(void *arg)
{
	char msg[50];
	struct mq_attr at;	
	int pri;
	printf("t2 spawned\n");
	
	pthread_cond_wait(&c1, &m1);
	//pthread_mutex_lock(&m1);
	
	printf("t2 got mutex\n");
	
	createQ();
	
	int ret = mq_receive(global, msg, 50, &pri); 
	if(ret<0)
	{perror("mq_receive()");}
	
	//mq_close(global);
	//mq_unlink("/chut");
	pthread_mutex_unlock(&m1);
	
	printf("%s\n", msg);
	
	
}

int main()
{
	pthread_mutex_init(&m1, 0);
    pthread_cond_init(&c1, 0);
    pthread_create(&t1, 0, f1, NULL);
    pthread_create(&t2, 0, f2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    
    
    //mq_send();



}
