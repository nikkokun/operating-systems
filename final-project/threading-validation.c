#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include "rdtsc.h"

int g_counter = 0;

struct sum_runner_struct {
	int id;
	int alloc_limit;
	long double malloc_total_time;
	long double free_total_time;
	long double average_malloc_time;
	long double average_free_time;
};

unsigned long long int measure_clock(void)
{
	uint32_t ret0[2];
	__asm__ __volatile__("rdtsc" : "=a"(ret0[0]), "=d"(ret0[1]));
	return ((unsigned long long int)ret0[1] << 32) | ret0[0];
}

// Thread function to calculate the cost of malloc and free
void* sum_runner(void* arg) {

	struct sum_runner_struct *arg_struct = (struct sum_runner_struct*) arg;
	char* p_temp;

	for (int i = 0; i < arg_struct->alloc_limit; i++) {
		unsigned long long int startclock = 0;
		unsigned long long int endclock = 0;
		unsigned long long int total_cycles = 0;
		long double malloc_time = 0.0;
		long double free_time = 0.0;
		unsigned long long int speed = 2900000000;

		//mesure malloc
		// previous_speed = measure_speed();
		startclock = measure_clock();
		for(int j = 0; j < 100000; j++) {
			g_counter++;
		}
		endclock = measure_clock();
		total_cycles = endclock - startclock;
		malloc_time = ((long double) total_cycles / (long double) speed) * 1000000;
		printf("Thread %d Malloc Time: %.8Lf\n", arg_struct->id, malloc_time);
		arg_struct->malloc_total_time += malloc_time;

		//measure free
		startclock = measure_clock();
		for(int j = 0; j < 100000; j++) {
			g_counter++;
		}
		endclock = measure_clock();
		total_cycles = endclock - startclock;
		free_time = ((long double) total_cycles / (long double) speed) * 1000000;
		printf("Thread %d Free time: %.8Lf\n", arg_struct->id, free_time);
		arg_struct->free_total_time += free_time;
	}

	arg_struct->average_malloc_time = arg_struct->malloc_total_time / (float) arg_struct->alloc_limit;
	arg_struct->average_free_time = arg_struct->free_total_time / (float) arg_struct->alloc_limit;

	pthread_exit(0);
}

int main(int argc, char **argv)
{

	if (argc < 2) {
		printf("Please provide 2 arguments. 1st is the number of threads, 2nd is the number of allocations\n");
		exit(-1);
	}

	int num_threads = atoll(argv[1]);
	int num_allocs = atoll(argv[2]);
	char separator[] = {"===================================================================================================="};
	long double total_malloc_average = 0;
	long double total_free_average = 0;
	FILE *p_output;

	//array of threads
	pthread_t threads[num_threads];
	struct sum_runner_struct args[num_threads];

	for (int i = 0; i < num_threads; i++) {
		args[i].alloc_limit = num_allocs;
		args[i].id = i;
		args[i].free_total_time = 0;
		args[i].malloc_total_time = 0;
		args[i].average_malloc_time = 0;
		args[i].average_free_time = 0;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int thread = pthread_create(&threads[i], &attr, sum_runner, &args[i]);
		if(thread != 0) {
			printf("The max number thread of for your computer is %d\n", i);
			exit(0);
		}
	}

	p_output = fopen("validation-output.txt", "a");
	char *p_header_text = (char*) malloc(sizeof(char) * 100);
	sprintf(p_header_text, "NUMBER OF THREADS: %d\tNUMBER OF RUNS: %d\n", num_threads, num_allocs);
	fprintf(p_output, "%s", p_header_text);
	fprintf(p_output, "%s\n\n", separator);
	free(p_header_text);

	// Wait until thread is done its work
	for (int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
		char *p_average_output = (char *) malloc(sizeof(char) * 100);
		sprintf(p_average_output, "THREAD %d\t\tAVERAGE MALLOC TIME: %.8Lf microseconds"
			"\t\tAVERAGE FREE TIME: %.8Lf microseconds",
			args[i].id, args[i].average_malloc_time, args[i].average_free_time);
		printf("%s\n", p_average_output);
		fprintf(p_output, "%s\n", p_average_output);
		free(p_average_output);

		total_malloc_average += args[i].average_malloc_time;
		total_free_average += args[i].average_free_time;
		// printf("Average malloc time for thread %d is %Lf\n", i, args[i].average_malloc_time);
		// printf("Average free time for thread %d is %Lf\n", i, args[i].average_free_time);
	}
	fprintf(p_output, "\n");
	char *p_total_output = (char*) malloc(sizeof(char) * 100);
	total_malloc_average = total_malloc_average / (float) num_threads;
	total_free_average = total_free_average / (float) num_threads;
	sprintf(p_total_output, "%d THREADS\t\tTOTAL AVERAGE MALLOC TIME: %.8Lf microseconds"
		"\t\tTOTAL AVERAGE FREE TIME: %.8LF microseconds",
		num_threads, total_malloc_average, total_free_average);
	fprintf(p_output, "%s\n", p_total_output);
	free(p_total_output);
	printf("Total average malloc time for %d thread/s is %.8Lf\n", num_threads, total_malloc_average);
	printf("Total average free time for %d thread/s is %.8Lf\n", num_threads, total_free_average);
	fprintf(p_output, "\n");
	fclose(p_output);
	return 0;

}
