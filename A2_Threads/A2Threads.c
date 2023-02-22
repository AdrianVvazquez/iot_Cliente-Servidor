/* Create a finite number of threads to perform an addition action */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define N_THREADS_PARAM 1
/* Data shared by the threads */
int32_t sum, sum2;
/* EVery thread call this function */
void *runner(void *param);
void *runner2(void *param);

int32_t main(int32_t argc, char *argv[])
{
	int32_t n_threads = atoi(argv[N_THREADS_PARAM]);
	sum = 0, sum2=0;
	/* Identifier */
	pthread_t tid;
	/* Attributes */
	pthread_attr_t attr;
	/* Set the default attributes of the thread*/
	pthread_attr_init(&attr);
	
	for(int i=0; i<n_threads; i++){
		/* Create the thread */
		pthread_create(&tid, &attr, runner, argv[N_THREADS_PARAM]);
		//pthread_create(&tid, &attr, runner, argv[N_THREADS_PARAM]);
		/* Wait for the thread to exit */
		//same as sleep(3);
		pthread_join(tid, NULL);
		printf("sum = %d\n", sum);
		printf("sum2 = %d\n", sum2);
	}
}

/* The thread will execute in this function */
void *runner(void *param)
{
	sum += 5;
	pthread_exit(0);
}

void *runner2(void *param)
{
	//puts(param);
	sum2 += 2;
	pthread_exit(0);
}
