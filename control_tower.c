#include "share.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int cnt;
	int msgqkey;
	int msgqid;
	size_t sz;
	pid_t pid[5];
	int i;
	int status; 
	int pidd;
	struct msgbuf msg;


	msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);

	 


	printf("CT: message queue created (myqid=%d , key=%d\n)",msgqid,msgqkey);

	pidd=getpid(); 

	for(i=0;i<5;i++)
	{	
		if(pidd==getpid())
		pid[i]=fork();
	} 

if(pid[0]==0)
	{	cnt =0;
			int msgqkey;
	int msgqid;

		msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);
			struct msgbuf wmsg;
		while(1)	
		{
			if(cnt==100)break;
		msgrcv(msgqid,&msg,MSIZE,1,0);
				if(msg.msg==100)
				{
					exit(0);
				}
		printf("Got MSG_REQ_RUNNING from train 0\n");
		if((msg.passengers==5) && (msg.msg=MSG_REQ_RUNNING))
		{
		printf("Send MSG_ACK_RUNNING from train 0\n");
		msg.mtype=21;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}

		msgrcv(msgqid,&msg,MSIZE,1,0);
		if(msg.msg==MSG_REQ_READY)
		{
		printf("Got MSG_REQ_READY from train 0\n");
		printf("Send MSG_REQ_READY from train 0\n");
		msg.mtype=21;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}
		else if(msg.msg==3)
		{
			printf("Got MSG_NAK_READY from train 0\n");
					msg.mtype=21;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		exit(0);
		}
		l

		}
		exit(1);
	}
 
 
	if(pid[1]==0)
	{	cnt =0;
			int msgqkey;
	int msgqid;

		msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);
			struct msgbuf wmsg;
		while(1)	
		{
			if(cnt==100)break;
		msgrcv(msgqid,&msg,MSIZE,2,0);
		if(msg.msg==100)
				{
					exit(0);
				}
		printf("Got MSG_REQ_RUNNING from train 1\n");
		if((msg.passengers==5) && (msg.msg=MSG_REQ_RUNNING))
		{
		printf("Send MSG_ACK_RUNNING from train 1\n");
		msg.mtype=22;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}

		msgrcv(msgqid,&msg,MSIZE,2,0);
		if(msg.msg==MSG_REQ_READY)
		{
		printf("Got MSG_REQ_READY from train 1\n");
		printf("Send MSG_REQ_READY from train 1\n");
		msg.mtype=22;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}
		else if(msg.msg==3)
		{
			printf("Got MSG_NAK_READY from train 1\n");
					msg.mtype=22;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		exit(0);
		}
			cnt++;

		}
		exit(1);
	}
 
	if(pid[2]==0)
	{	cnt =0;
			int msgqkey;
	int msgqid;

		msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);
			struct msgbuf wmsg;
		while(1)
		{
			if(cnt==100)break;
		msgrcv(msgqid,&msg,MSIZE,3,0);
					if(msg.msg==100)
				{
					exit(0);
				}
		printf("Got MSG_REQ_RUNNING from train 2\n");
			if((msg.passengers==5) && (msg.msg=MSG_REQ_RUNNING))
		{
		printf("Send MSG_ACK_RUNNING from train 2\n");
		msg.mtype=23;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
	}

		msgrcv(msgqid,&msg,MSIZE,3,0);
		if(msg.msg==MSG_REQ_READY)
		{
		printf("Got MSG_REQ_READY from train 2\n");
		printf("Send MSG_REQ_READY from train 2\n");
		msg.mtype=23;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}
		else if(msg.msg==3)
		{
			printf("Got MSG_NAK_READY from train 2\n");
					msg.mtype=23;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		exit(0);
		}

				cnt++;
		}
		exit(1);
	}

	if(pid[3]==0)
	{	cnt =0;
			int msgqkey;
	int msgqid;

		msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);
			struct msgbuf msg;
		while(1)
		{
			if(cnt==100)break;
		msgrcv(msgqid,&msg,MSIZE,4,0);
					if(msg.msg==100)
				{
					exit(0);
				}
		printf("Got MSG_REQ_RUNNING from train 3\n");
				if((msg.passengers==5) && (msg.msg=MSG_REQ_RUNNING))
		{
		printf("Send MSG_ACK_RUNNING from train 3\n");
		msg.mtype=24;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
	}

		msgrcv(msgqid,&msg,MSIZE,4,0);
		if(msg.msg==MSG_REQ_READY)
		{ 
		printf("Got MSG_REQ_READY from train 3\n");
		printf("Send MSG_REQ_READY from train 3\n");
		msg.mtype=24;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}
		else if(msg.msg==3)
		{
			printf("Got MSG_NAK_READY from train 3\n");
					msg.mtype=24;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		exit(0);
		}
				cnt++;
		}
		exit(1);
	}

	if(pid[4]==0)
	{	cnt =0;
	int msgqkey;
	int msgqid;

		msgqkey=ftok("mq.h",0);
	msgqid=msgget(msgqkey,IPC_CREAT);
			struct msgbuf msg;
		while(1) 
		{
			if(cnt==100)break;
		msgrcv(msgqid,&msg,MSIZE,5,0);
				if(msg.msg==100)
				{
					exit(0);
				}

		printf("Got MSG_REQ_RUNNING from train 4\n");
			if((msg.passengers==5) && (msg.msg=MSG_REQ_RUNNING))
		{
		printf("Send MSG_ACK_RUNNING from train 4\n");
		msg.mtype=25;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}

		msgrcv(msgqid,&msg,MSIZE,5,0);
		if(msg.msg==MSG_REQ_READY)
		{
		printf("Got MSG_REQ_READY from train 4\n");
		printf("Send MSG_REQ_READY from train 4\n");
		msg.mtype=25;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		}
		else if(msg.msg==3)
		{
			printf("Got MSG_NAK_READY from train 4\n");
					msg.mtype=25;
		msgsnd(msgqid,(void *)&msg,MSIZE,0);
		exit(0);
		}
 
			cnt++;
		}
		exit(1);

	}

 	int num;
 	for(num=0;num<5;num++)
 	{
 		wait(&status);
 	}
	

} 