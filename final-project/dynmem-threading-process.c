#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <time.h>
#include "rdtsc.h"


struct alloc_runner_struct {
	int id;
	int alloc_limit;
	long malloc_total_time;
	long free_total_time;
	long average_malloc_time;
	long average_free_time;
};

struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// call this function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}

// Thread function to calculate the cost of malloc and free
void* alloc_runner(void* arg) {

	struct alloc_runner_struct *arg_struct = (struct alloc_runner_struct*) arg;
	char* p_temp;
	for (int i = 0; i < arg_struct->alloc_limit; i++) {
		long malloc_time = 0.0;
		long free_time = 0.0;
		struct timespec start_time_malloc, start_time_free;

		//mesure malloc
		start_time_malloc = timer_start();
		p_temp = (char *) malloc(1 * sizeof(char));
		malloc_time = timer_end(start_time_malloc);
		printf("Thread %d Malloc Time: %ld\n", arg_struct->id, malloc_time);
		arg_struct->malloc_total_time += malloc_time;

		//measure free
		start_time_free = timer_start();
		free(p_temp);
		free_time = timer_end(start_time_free);
		printf("Thread %d Free time: %ld\n", arg_struct->id, free_time);
		arg_struct->free_total_time += free_time;
	}

	arg_struct->average_malloc_time = arg_struct->malloc_total_time / arg_struct->alloc_limit;
	arg_struct->average_free_time = arg_struct->free_total_time / arg_struct->alloc_limit;

	pthread_exit(0);
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Please provide 2 arguments. 1st is the number of threads, 2nd is the number of allocations\n");
		exit(0);
	}

	int num_threads = atoll(argv[1]);
	int num_allocs = atoll(argv[2]);
	char separator[] = {"===================================================================================================="};
	long total_malloc_average = 0;
	long total_free_average = 0;
	FILE *p_output;

	//array of threads
	pthread_t threads[num_threads];
	//array to contain thread information
	struct alloc_runner_struct info_threads[num_threads];

	for (int i = 0; i < num_threads; i++) {
		info_threads[i].alloc_limit = num_allocs;
		info_threads[i].id = i;
		info_threads[i].free_total_time = 0;
		info_threads[i].malloc_total_time = 0;
		info_threads[i].average_malloc_time = 0;
		info_threads[i].average_free_time = 0;

		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int thread = pthread_create(&threads[i], &attr, alloc_runner, &info_threads[i]);
		if(thread != 0) {
			printf("The max number thread of for your computer is %d\n", i);
			exit(0);
		}
	}

	p_output = fopen("dynmem-process-output.txt", "a");
	char *p_header_text = (char*) malloc(sizeof(char) * 150);
	sprintf(p_header_text, "NUMBER OF THREADS: %d\tNUMBER OF RUNS: %d\n", num_threads, num_allocs);
	fprintf(p_output, "%s", p_header_text);
	fprintf(p_output, "%s\n\n", separator);
	free(p_header_text);

	// Wait until thread is done its work
	for (int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
		char *p_average_output = (char *) malloc(sizeof(char) * 200);
		sprintf(p_average_output, "THREAD %d\t\tAVERAGE MALLOC TIME: %ld nanoseconds"
			"\t\tAVERAGE FREE TIME: %ld nanoseconds",
			info_threads[i].id, info_threads[i].average_malloc_time, info_threads[i].average_free_time);
		printf("%s\n", p_average_output);
		fprintf(p_output, "%s\n", p_average_output);
		free(p_average_output);

		total_malloc_average += info_threads[i].average_malloc_time;
		total_free_average += info_threads[i].average_free_time;
	}

	fprintf(p_output, "\n");
	char *p_total_output = (char*) malloc(sizeof(char) * 200);
	total_malloc_average = total_malloc_average / num_threads;
	total_free_average = total_free_average / num_threads;
	sprintf(p_total_output, "%d THREADS\t\tTOTAL AVERAGE MALLOC TIME: %ld nanoseconds"
		"\t\tTOTAL AVERAGE FREE TIME: %ld nanoseconds",
		num_threads, total_malloc_average, total_free_average);
	fprintf(p_output, "%s\n", p_total_output);
	free(p_total_output);
	printf("Total average malloc time for %d thread/s is %ld\n", num_threads, total_malloc_average);
	printf("Total average free time for %d thread/s is %ld\n", num_threads, total_free_average);
	fprintf(p_output, "\n");
	fclose(p_output);
	return 0;

}