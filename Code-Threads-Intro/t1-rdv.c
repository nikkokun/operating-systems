#include <stdio.h>
#include "mythreads.h"
#include <stdlib.h>
#include <pthread.h>
#include "rdtsc.h"

int max;
volatile int counter = 0; // shared global variable

/* max number of clock cycles we *expect* the increment to take */
#define SLEW 20

void * mythread(void *arg) {
	char *letter = arg;
	int i; // stack (private per thread)
	unsigned long long int lastval = rdtsc(), thisval;
	int slew, slewcount = 0;
	int maxslew = 0, totslew = 0;

	printf("%s: begin [addr of i: %p]\n", letter, &i);
	for (i = 0; i < max; i++) {
	counter = counter + 1; // shared: only one
	thisval = rdtsc();
	slew = thisval - lastval;
	if (slew > SLEW)
		slewcount++;
	if (slew > maxslew)
		maxslew = slew;
	totslew += slew;
	lastval = thisval;
	}
	printf("%s: done; slewcount %d maxslew %d avg. slew %d\n", letter, slewcount, maxslew, totslew / max);
	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
	fprintf(stderr, "usage: main-first <loopcount>\n");
	exit(1);
	}
	max = atoi(argv[1]);

	pthread_t p1, p2;
	printf("main: begin [counter = %d] [%x]\n", counter, (unsigned int) &counter);
	Pthread_create(&p1, NULL, mythread, "A"); 
	Pthread_create(&p2, NULL, mythread, "B");
	// join waits for the threads to finish
	Pthread_join(p1, NULL); 
	Pthread_join(p2, NULL); 
	printf("main: done\n [counter: %d]\n [should: %d]\n", counter, max*2);
	return 0;
}