#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/msg.h>

#include "share.h"

#define MAX_PASSENGER 100
#define MAX_PASSENGER_IN_TRAIN 5
#define MAX_TICKET 20
#define MAX_TRAIN_THREAD 5
#define MIN_START_TRAIN 10

void *ticket2_thread(int *);
void *ticket_thread(int *);
void *train_thread(int *);

void msgsend(int id,struct msgbuf msg);

pthread_mutex_t gTicketMutex;
int gTicket[MAX_TICKET];
int gTicketIn;
int gTicketOut;

sem_t gStartTrainSem;
sem_t gInAvailableSem;
sem_t gOutAvailableSem;

pthread_t gTicketThread;
pthread_t gTrainThread[MAX_TRAIN_THREAD];
int gTicketThreadID;
int gTrainThreadID[MAX_TRAIN_THREAD];

int	msgqkey;
int	msgqid;



void msgsend(int id,struct msgbuf msg)
{
		int	msgqkey1;
		int	msgqid1;
		msgqkey1=ftok("mq.h",0);
		msgqid1=msgget(msgqkey1,IPC_CREAT);

		msg.mtype=id+1;
		msg.msg=MSG_REQ_RUNNING;
		msg.passengers=5;
		msgsnd(msgqid1,(void *)&msg,MSIZE,0);
		msgrcv(msgqid1,&msg,MSIZE,id+21,0);
			
}

void msgrecv(int id ,struct msgbuf msg,int broken) 
{
		int	msgqkey2;
		int	msgqid2;
		msgqkey2=ftok("mq.h",0);
		msgqid2=msgget(msgqkey2,IPC_CREAT);

		msg.mtype=id+1;
		if(broken==1)
		msg.msg=3; 
		else
			msg.msg=1;
		msg.passengers=5;
		msgsnd(msgqid2,(void *)&msg,MSIZE,0);
		msgrcv(msgqid2,&msg,MSIZE,id+21,0);
}



int main(void)
{
	int i;
	size_t sz;

		msgqkey=ftok("mq.h",0);
		msgqid=msgget(msgqkey,IPC_CREAT);



	/* initialize mutex */
	pthread_mutex_init(&gTicketMutex, NULL); // 글로벌변수에 대한 상호배제 위해 뮤텍스 선언. 

	/* initialize semaphore */
	sem_init(&gStartTrainSem, 0, 0); 
	sem_init(&gInAvailableSem, 0, 20);// platform 에 대기 할 수 있는 인원의 사람수에 대한 세마포어 
	sem_init(&gOutAvailableSem, 0, 0);

	/* create threads */
	gTicketThreadID = 0;
	pthread_create(&gTicketThread, NULL, (void *(*)(void *))ticket_thread, (void *)&gTicketThreadID);
	pthread_create(&gTicketThread, NULL, (void *(*)(void *))ticket2_thread, (void *)&gTicketThreadID);

	for(i=0; i<MAX_TRAIN_THREAD; i++) 
         {
		gTrainThreadID[i] = i;
		pthread_create(&gTrainThread[i], NULL, (void *(*)(void *))train_thread, (void *)&gTrainThreadID[i]);
	}

	pthread_exit(0);
}

void *ticket_thread(int *arg)
{
	int id = *arg;
	int i, j;

	for(i=0; i<MAX_PASSENGER; i++) {
		
		usleep((rand()%200+300)*1000);

		sem_wait(&gInAvailableSem);

		pthread_mutex_lock(&gTicketMutex);
			if(gTicketIn>99)
				{

				pthread_mutex_unlock(&gTicketMutex);
					pthread_exit(0);
				}
		gTicket[gTicketIn % MAX_TICKET] = gTicketIn + 1; 
		gTicketIn++;
		printf("ticket 0: passenger %d got ticket\n", gTicketIn);
		if(gTicketIn == MIN_START_TRAIN) 
                  {
 			for(j=0; j<MAX_TRAIN_THREAD; j++) 
   			{
				sem_post(&gStartTrainSem);
			}
		}
		
		
		pthread_mutex_unlock(&gTicketMutex);
			sem_post(&gOutAvailableSem);
	}

	return (void *)0;
}
void *ticket2_thread(int *arg)
{
	int id = *arg;
	int i, j;

	for(i=0; i<MAX_PASSENGER; i++) {

		usleep((rand()%200+300)*1000);

		sem_wait(&gInAvailableSem);

		pthread_mutex_lock(&gTicketMutex);
				if(gTicketIn>99)
				{
						
				pthread_mutex_unlock(&gTicketMutex);
					pthread_exit(0);
				}
		gTicket[gTicketIn % MAX_TICKET] = gTicketIn + 1;
		gTicketIn++;
		printf("ticket 1: passenger %d got ticket\n", gTicketIn);
		if(gTicketIn == MIN_START_TRAIN) 
                  {
 			for(j=0; j<MAX_TRAIN_THREAD; j++) 
   			{
		//		sem_post(&gStartTrainSem);
			}
		}
	
	
		pthread_mutex_unlock(&gTicketMutex);
			sem_post(&gOutAvailableSem);
	}

	return (void *)0;
}

void *train_thread(int *arg)
{
	int broken=0;
	int id = *arg;
	int passengers = 0;
	int passengers_all = 0;
	struct timespec ts; 
	int train_start_flag = 0;

	int accident;

	struct msgbuf msg;



	printf("======> train %d: wait\n", id);
	sem_wait(&gStartTrainSem);
	printf("======> train %d: ready\n", id);

	while(1) {
		accident= rand()%10;

		sem_wait(&gOutAvailableSem);
		pthread_mutex_lock(&gTicketMutex);
		if(gTicketOut == MAX_PASSENGER) {
			train_start_flag  = 1;
			pthread_mutex_unlock(&gTicketMutex);
		} 
		else {
			passengers++;
			passengers_all++;
			printf("==> train %d: passenger %d returned ticket\n", id, gTicket[gTicketOut++ % MAX_TICKET]);
			if(passengers == MAX_PASSENGER_IN_TRAIN) {
				train_start_flag  = 1;
			}
			if(gTicketOut == MAX_PASSENGER) {
				train_start_flag  = 1;
			}
			pthread_mutex_unlock(&gTicketMutex);
			sem_post(&gInAvailableSem);
		}

		if((train_start_flag == 1) && passengers) {
		
			msgsend(id,msg);

			printf("======> train %d: start with %d passengers\n", id, passengers);
			usleep(5000000);
			printf("======> train %d: stop\n", id);
			passengers = 0;
			train_start_flag = 0;
			if(accident==id)
				broken=1;
			msgrecv(id,msg,broken);
		}


		pthread_mutex_lock(&gTicketMutex);
		if(gTicketOut == MAX_PASSENGER||broken==1) {
			pthread_mutex_unlock(&gTicketMutex);
			printf("======> train %d: exit (total %d passengers)\n", id, passengers_all);
			sem_post(&gOutAvailableSem);
			if(broken!=1)
			{
			msg.mtype=id+1;
			msg.msg=END;
			msgsnd(msgqid,(void *)&msg,MSIZE,0);
			}
			pthread_exit(0);
		}
		pthread_mutex_unlock(&gTicketMutex);
	}
}


