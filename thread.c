#include 	"thread.h"

void 		*storeStock(void *data) {
	t_store *store;

	store = (t_store*) data;
	
	while (1) {
		int destock;

		destock = 25;
		sleep(1);
		pthread_mutex_lock(&store->mutex_stock);
		pthread_cond_wait(&store->cond_stock, &store->mutex_stock);
		store->stock+=destock;
		printf("ajout de 25 stock => %d\n", store->stock);
		pthread_cond_broadcast(&store->cond_wait_clients);
		pthread_mutex_unlock(&store->mutex_stock);
	}
	return;
}

void 		*clientStock(void *data) {
	t_store *store;

	store = (t_store*) data;


	while (1) {
		int destock;

		destock = 4;
		sleep(1);
		pthread_mutex_lock(&store->mutex_stock);
		if (4 > store->stock) {
			pthread_cond_broadcast(&store->cond_stock);
			pthread_cond_wait(&store->cond_wait_clients, &store->mutex_stock);
		}
		store->stock-=destock;
		printf("suppression de 1 stock => %d\n", store->stock);
		pthread_mutex_unlock(& store->mutex_stock);
	}
	printf("%d\n", store->stock);
	return;
}

int 		main(int ac, char *av) { 
	int 		returnValue;
	pthread_t 	threadStore;
	pthread_t 	threadClients[5];
	t_store 	store;
	int 		i;

	i = 0;
	store.stock = 15;
	pthread_mutex_init(&store.mutex_stock, NULL);
	pthread_cond_init(&store.cond_stock, NULL);
   	pthread_cond_init(&store.cond_wait_clients, NULL);
	if ((returnValue = pthread_create(&threadStore, NULL, storeStock, (void*) &store)) != 0)
		return (-1);

	while (i < 5) {
		sleep(1);
		if ((returnValue = pthread_create(&threadClients[i], NULL, clientStock, (void*) &store)) != 0)
			return (-1);
		i++;
	}

	pthread_join(threadStore, NULL);
	i = 0;
	while (i < 5) {
		pthread_join(threadClients[i], NULL);
		i++;
	}
}