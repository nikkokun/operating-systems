#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

unsigned long long int rdtsc(void)
{
	uint32_t ret0[2];
	__asm__ __volatile__("rdtsc" : "=a"(ret0[0]), "=d"(ret0[1]));
	return ((unsigned long long int)ret0[1] << 32) | ret0[0];
}

int main(int argc, const char * argv[])
{
	unsigned long long int startCount = rdtsc();
	sleep(1);
	unsigned long long int endCount = rdtsc();

	printf("Clocks per second: %llu", endCount - startCount);

	return 0;
}