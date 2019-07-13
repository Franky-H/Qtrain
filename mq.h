#ifndef __MQ_H__
#define __MQ_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

#ifdef _GNU_SOURCE
# define __USE_GNU 1    // must add -D_GNU_SOURCE when compile recv.c 
#endif

struct mbuf {
	long mtype;// it is necessary field
	int  	startnum;
	int 	endnum;
};

#endif // __MQ_H__
