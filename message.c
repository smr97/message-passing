#include <stdio.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <errno.h> 
#include <stdlib.h>
#include <string.h>
pthread_t t1, t2;
pthread_mutex_t m1;
pthread_cond_t c1;
pthread_barrier_t b;

#define QUEUE_PERMISSIONS 0760
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

mqd_t global;

createQ()
{
	struct mq_attr buf;        /* buffer for stat info */
    buf.mq_msgsize = MAX_MSG_SIZE;
    buf.mq_maxmsg = MAX_MESSAGES;
    
    int flag = O_RDWR | O_NONBLOCK | O_CREAT;
    
	global = mq_open("/path", flag, QUEUE_PERMISSIONS, &buf);
	
	//printf("queue opened\n");
	
	if(global<0)
	perror("mq_open()");
//    return m;
}

void *f1(void *arg)
{
	//printf("f1 called\n");
	
	pthread_mutex_lock(&m1);
	
	//printf("m locked\n");
	
	createQ();
	
	//printf("t1 opened q\n");
	
	char *msg;
	msg = (char*) malloc(MAX_MSG_SIZE);
	
	printf("Type the message below. This will be sent to thread #2 that will print it\n");
	
	scanf("%s", msg);
	if(mq_send(global, msg, strlen(msg), 1)==-1)
	perror("mq_send()");
	
	
	//mq_close(global);
	//mq_unlink("/chut");
	
	pthread_mutex_unlock(&m1);
	
	pthread_barrier_wait(&b);
	
	free(msg);
	
}

void *f2(void *arg)
{

	
	char *msg;
	msg = (char *) malloc(MAX_MSG_SIZE);
	
	struct mq_attr at;	
	int pri;
	//printf("t2 spawned and waiting\n");
	
	pri = 1;
	
	pthread_barrier_wait(&b);
	
	pthread_mutex_lock(&m1);
	
	//printf("t2 got mutex\n");
	
	//createQ();
	while(1){
	int ret = mq_receive(global, msg, MSG_BUFFER_SIZE, &pri); 
	if(ret<0)
	{perror("mq_receive()");}
	
	else
	break;
	}
	
	//mq_close(global);
	//mq_unlink("/chut");
	pthread_mutex_unlock(&m1);
	
    printf("The message is: %s\n", msg);
	
	free(msg);
}

int main()
{
	pthread_mutex_init(&m1, 0);
    pthread_cond_init(&c1, 0);
    pthread_barrier_init(&b, 0, 2);
    pthread_create(&t1, 0, f1, NULL);
    pthread_create(&t2, 0, f2, NULL);
    //pthread_barrier_wait(&b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    
    
    //mq_send();



}

