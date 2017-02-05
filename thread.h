#ifndef 	THREAD_H_
#define 	THREAD_H_

#include 	<stdlib.h>
#include 	<stdio.h>
#include 	<pthread.h>

typedef struct s_store
{
	int 	stock;
	pthread_mutex_t mutex_stock;
	pthread_cond_t 	cond_stock;
	pthread_cond_t 	cond_wait_clients;
} t_store;

#endif 		/*!THREAD_H_*/