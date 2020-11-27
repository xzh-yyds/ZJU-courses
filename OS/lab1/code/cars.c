#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define MAXN 100
#define CRXTIME 1

typedef enum{false=0, true=1} bool;
// typedef enum{EAST, WEST, SOUTH, NORTH} Direction;
// typedef int car;

typedef struct carsQueue{
	int *cars;
	int front;
	int rear;
	int size;
	int capacity;
}Queue;

Queue* newQueue(int cap){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->cars = (int*)malloc(sizeof(int)*(1+cap));
	q->front = 0;
	q->rear = 0;
	q->size = 0;
	q->capacity = cap;
	return q;
}
void enQueue(Queue* q, int car_id){
	if(q->size == q->capacity){
		printf("The queue is full!\n");
		return;
	}
	q->cars[q->rear] = car_id;
	q->rear = (q->rear+1)%(q->capacity+1);
	q->size++;
}
void deQueue(Queue* q){
	if(q->size==0){
		printf("The queue is empty.\n");
		return;
	}
	q->front = (q->front+1)%(q->capacity+1);
	q->size--;
}
int getFront(Queue* q){
	if(q->size==0) {
		printf("Error: fetch an empty queue!\n");
		return -1;
	}
	return q->cars[q->front];
}
void destroyQueue(Queue* q){
	free(q);
}

Queue *qFromEast, *qFromWest, *qFromSouth, *qFromNorth;	// cars queue for 4 directions
bool ext_wait_a, ext_wait_b, ext_wait_c, ext_wait_d; 	// whether exist waiting right
bool a_occupied, b_occupied, c_occupied, d_occupied; 	// whether a road is occupied

pthread_cond_t come2a, come2b, come2c, come2d;	//condtions for following cars to go forward
pthread_cond_t cond_deadlock;	// condtion for deadlock occuring
pthread_cond_t firstSouth, firstEast, firstNorth, firstWest;	// conditions for left to go first

pthread_mutex_t mtx_south, mtx_east, mtx_north, mtx_west;	// mutexes for 4 roads
pthread_mutex_t mtx_qE, mtx_qS, mtx_qW, mtx_qN;				// mutexes for 4 queues
pthread_mutex_t mtx_deadlock;	// mutex for deadlock
pthread_mutex_t mtx_crossing;	// mutex for the crossing

void* deadlock_proc(){
	while(1){
		// printf("Deadlock: waiting...\n");
		pthread_mutex_lock(&mtx_crossing);
		// wait for a deadlock occuring
		pthread_cond_wait(&cond_deadlock, &mtx_crossing);
		// printf("Deadlock: Car jam detected, processing...\nDeadlock: Signalling North to go...\n");
		pthread_mutex_lock(&mtx_north);
		// signal the car from North to go first
		pthread_cond_signal(&firstNorth);
		pthread_mutex_unlock(&mtx_north);	
		pthread_mutex_unlock(&mtx_crossing);
		// printf("Deadlock: A car jam has been processed.\n");
	}
}

void* fromWest(void *car_id_ptr){
	int car_id = *(int*)car_id_ptr;

	pthread_mutex_lock(&mtx_qW);
	enQueue(qFromWest, car_id);
	// printf("Car %d in queue West.\n", car_id);
	pthread_mutex_unlock(&mtx_qW);
	
	while(getFront(qFromWest) != car_id);
	
	pthread_mutex_lock(&mtx_west);
	// wait for the front car on the road
	while(d_occupied) pthread_cond_wait(&come2d, &mtx_west);
	d_occupied = true;
	printf("Car %d from West arrives at the crossing.\n", car_id);

	if(qFromSouth->size > 0){
		ext_wait_a = true;
		// printf("Car %d: wait for the right.\n", car_id);
		if(ext_wait_a && ext_wait_b && ext_wait_c && ext_wait_d){
			printf("Car %d: DEADLOCK: car jam detected, signalling North to go.\n", car_id);
			pthread_mutex_lock(&mtx_deadlock);
			pthread_cond_signal(&cond_deadlock);
			pthread_mutex_unlock(&mtx_deadlock);
			// printf("Car %d: DEADLOCK: solved.\n", car_id);
		}
		pthread_cond_wait(&firstWest, &mtx_west);
		// printf("Car %d: right finished, go first.\n", car_id);	
	}
	ext_wait_a = false;
	// printf("Car %d: ready to go. \n", car_id);
	// pthread_mutex_lock(&mtx_crossing);
	sleep(CRXTIME);
	// pthread_mutex_unlock(&mtx_crossing);
	printf("Car %d from West leaves the crossing.\n", car_id);

	if(ext_wait_d){
		pthread_mutex_lock(&mtx_north);
		// let the left to go first
		pthread_cond_signal(&firstNorth);
		pthread_mutex_unlock(&mtx_north);
	}

	pthread_mutex_lock(&mtx_qW);
	deQueue(qFromWest);
	// printf("Car %d: out of the queue West.\n", car_id);
	pthread_mutex_unlock(&mtx_qW);

	d_occupied = false;
	// let following cars to go forward
	pthread_cond_signal(&come2d);

	pthread_mutex_unlock(&mtx_west);
}

void* fromNorth(void *car_id_ptr){
	int car_id = *(int*)car_id_ptr;

	pthread_mutex_lock(&mtx_qN);
	enQueue(qFromNorth, car_id);
	// printf("Car %d in queue North.\n", car_id);
	pthread_mutex_unlock(&mtx_qN);

	while(getFront(qFromNorth)!=car_id);

	pthread_mutex_lock(&mtx_north);
	while(c_occupied) pthread_cond_wait(&come2c, &mtx_north);
	c_occupied = true;
	printf("Car %d from North arrives at the crossing.\n", car_id);

	if(qFromWest->size > 0){
		ext_wait_d = true;
		// printf("Car %d: wait for the right.\n", car_id);
		if(ext_wait_a && ext_wait_b && ext_wait_c &&ext_wait_d){
			printf("Car %d: DEADLOCK: car jam detected, signalling North to go.\n", car_id);
			pthread_mutex_lock(&mtx_deadlock);
			pthread_cond_signal(&cond_deadlock);
			pthread_mutex_unlock(&mtx_deadlock);
			// printf("Car %d: DEADLOCK: solved.\n", car_id);
		}
		pthread_cond_wait(&firstNorth, &mtx_north);
		// printf("Car %d: right finished, go first.\n", car_id);
	}
	ext_wait_d = false;
	// printf("Car %d: ready to go.\n", car_id);
	// pthread_mutex_lock(&mtx_crossing);
	sleep(CRXTIME);
	// pthread_mutex_unlock(&mtx_crossing);
	printf("Car %d from North leaves the crossing.\n", car_id);

	if(ext_wait_c){
		pthread_mutex_lock(&mtx_east);
		// let the left to go first
		pthread_cond_signal(&firstEast);
		pthread_mutex_unlock(&mtx_east);
	}

	pthread_mutex_lock(&mtx_qN);
	deQueue(qFromNorth);
	// printf("Car %d: out of the queue North.\n", car_id);
	pthread_mutex_unlock(&mtx_qN);

	c_occupied = false;
	// let following cars to go forward
	pthread_cond_signal(&come2c);

	pthread_mutex_unlock(&mtx_north);
}

void* fromEast(void *car_id_ptr){
	int car_id = *(int*)car_id_ptr;

	pthread_mutex_lock(&mtx_qE);
	enQueue(qFromEast, car_id);
	// printf("Car %d in queue East.\n", car_id);
	pthread_mutex_unlock(&mtx_qE);

	while(getFront(qFromEast)!=car_id);

	pthread_mutex_lock(&mtx_east);
	// wait for the front car on the road
	while(b_occupied) pthread_cond_wait(&come2b, &mtx_east);
	b_occupied = true;
	printf("Car %d from East arrives at the crossing.\n", car_id);

	if(qFromNorth->size > 0){
		ext_wait_c = true;
		// printf("Car %d: wait for the right.\n", car_id);
		if(ext_wait_a && ext_wait_b && ext_wait_c &&ext_wait_d){
			printf("Car %d: DEADLOCK: car jam detected, signalling North to go.\n", car_id);
			pthread_mutex_lock(&mtx_deadlock);
			pthread_cond_signal(&cond_deadlock);
			pthread_mutex_unlock(&mtx_deadlock);
			// printf("Car %d: DEADLOCK: solved.\n", car_id);
		}
		pthread_cond_wait(&firstEast, &mtx_east);
		// printf("Car %d: right finished, go first.\n", car_id);	
	}
	ext_wait_c = false;
	// printf("Car %d: ready to go. \n", car_id);
	// pthread_mutex_lock(&mtx_crossing);
	sleep(CRXTIME);
	// pthread_mutex_unlock(&mtx_crossing);
	printf("Car %d from East leaves the crossing.\n", car_id);

	if(ext_wait_b){
		pthread_mutex_lock(&mtx_south);
		// let the left to go first
		pthread_cond_signal(&firstSouth);
		pthread_mutex_unlock(&mtx_south);
	}

	pthread_mutex_lock(&mtx_qE);
	deQueue(qFromEast);
	// printf("Car %d: out of the queue East.\n", car_id);
	pthread_mutex_unlock(&mtx_qE);

	b_occupied = false;
	// let following cars to go forward
	pthread_cond_signal(&come2b);

	pthread_mutex_unlock(&mtx_east);
}

void* fromSouth(void *car_id_ptr){
	int car_id = *(int*)car_id_ptr;

	pthread_mutex_lock(&mtx_qS);
	enQueue(qFromSouth, car_id);
	// printf("Car %d in queue South.\n", car_id);
	pthread_mutex_unlock(&mtx_qS);

	while(getFront(qFromSouth) != car_id);

	pthread_mutex_lock(&mtx_south);
	// wait for the front car on the road
	while(a_occupied) pthread_cond_wait(&come2a, &mtx_south);
	a_occupied = true;
	printf("Car %d from South arrives at the crossing.\n", car_id);

	// pthread_mutex_lock(&mtx_east);
	if(qFromEast->size > 0){
		ext_wait_b = true;
		// printf("Car %d: wait for the right.\n", car_id);
		if(a_occupied && b_occupied && c_occupied && d_occupied){
			printf("Car %d: DEADLOCK: car jam detected, signalling North to go.\n", car_id);
			pthread_mutex_lock(&mtx_crossing);
			pthread_cond_signal(&cond_deadlock);
			pthread_mutex_unlock(&mtx_crossing);
			// printf("Car %d: DEADLOCK: solved.\n", car_id);
		}
		pthread_cond_wait(&firstSouth, &mtx_south);
		// printf("Car %d: right finished, go first.\n", car_id);	
	}
	ext_wait_b = false;
	// b_occupied = true;
	// printf("Car %d: ready to go. \n", car_id);
	// pthread_mutex_lock(&mtx_crossing);
	sleep(CRXTIME);
	// pthread_mutex_unlock(&mtx_crossing);
	printf("Car %d from East leaves the crossing.\n", car_id);

	// b_occupied = false;
	// pthread_mutex_unlock(&mtx_east);
	if(ext_wait_a){
		pthread_mutex_lock(&mtx_west);
		// let the left to go first
		pthread_cond_signal(&firstWest);
		pthread_mutex_unlock(&mtx_west);
	}
	
	pthread_mutex_lock(&mtx_qS);
	deQueue(qFromSouth);
	// printf("Car %d: out of the queue South.\n", car_id);
	pthread_mutex_unlock(&mtx_qS);

	a_occupied = false;
	// let the following to go forward
	pthread_cond_signal(&come2a);
	pthread_mutex_unlock(&mtx_south);
}

int main(int argc, char **argv){
	int n = 10;
	char dircs[MAXN];
	// char dircs[] = "senwssnwse";
	printf("directions string:\n");
	scanf("%s", dircs);
	n = strlen(dircs);
	
	// initilization
	pthread_cond_init(&firstSouth, NULL);
	pthread_cond_init(&firstEast, NULL);
	pthread_cond_init(&firstNorth, NULL);
	pthread_cond_init(&firstWest, NULL);

	pthread_cond_init(&come2a, NULL);
	pthread_cond_init(&come2b, NULL);
	pthread_cond_init(&come2c, NULL);
	pthread_cond_init(&come2d, NULL);
	
	pthread_mutex_init(&mtx_south, NULL);
	pthread_mutex_init(&mtx_east, NULL);
	pthread_mutex_init(&mtx_north, NULL);
	pthread_mutex_init(&mtx_west, NULL);

	pthread_mutex_init(&mtx_qS, NULL);
	pthread_mutex_init(&mtx_qE, NULL);
	pthread_mutex_init(&mtx_qN, NULL);
	pthread_mutex_init(&mtx_qW, NULL);

	pthread_mutex_init(&mtx_crossing, NULL);
	pthread_mutex_init(&mtx_deadlock, NULL);
	pthread_cond_init(&cond_deadlock, NULL);

	ext_wait_a = ext_wait_b = ext_wait_c = ext_wait_d = false;
	a_occupied = b_occupied = c_occupied = d_occupied = false;

	qFromSouth = newQueue(n);
	qFromEast = newQueue(n);
	qFromNorth = newQueue(n);
	qFromWest = newQueue(n);

	// create the deadlock processing thread
	pthread_t deadlock;
	if(pthread_create(&deadlock, NULL, deadlock_proc, NULL)!=0)
		printf("cannot create the deadlock thread.\n");
	
	// create car threads
	int car_no = 0;
	pthread_t cars[MAXN];
	// pthread_t *cars = (car*)malloc(sizeof(pthread_t)*n);
	int car_ids[MAXN];
	for(int i=0; i<n; i++){ car_ids[i] = i+1; }
	for(int i=0; i<n; i++){
		car_no++;
		if(dircs[i]=='s'){
			if(pthread_create(&cars[i], NULL, fromSouth, car_ids+i)!=0)
				printf("Creating car thread failed.\n");
		}else if(dircs[i]=='e'){
			if(pthread_create(&cars[i], NULL, fromEast, car_ids+i)!=0)
				printf("Creating car thread failed.\n");
		}else if(dircs[i]=='n'){
			if(pthread_create(&cars[i], NULL, fromNorth, car_ids+i)!=0)
				printf("Creating car thread failed.\n");
		}else if(dircs[i]=='w'){
			if(pthread_create(&cars[i], NULL, fromWest, car_ids+i)!=0)
				printf("Creating car thread failed.\n");
		}
	}
	for(int i=0; i<n; i++){ pthread_join(cars[i], NULL); }
	destroyQueue(qFromSouth);
	destroyQueue(qFromEast);
	destroyQueue(qFromNorth);
	destroyQueue(qFromWest);

	return 0;
}