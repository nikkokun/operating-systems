#include <stdio.h>
#include <time.h>

#if defined(__i386__)

static __inline__ unsigned long long rdtsc(void)
{
	unsigned long long int x;
	 __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
	 return x;
}
#elif defined(__x86_64__)


static __inline__ unsigned long long rdtsc(void)
{
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
	return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#elif defined(__powerpc__)


static __inline__ unsigned long long rdtsc(void)
{
	unsigned long long int result=0;
	unsigned long int upper, lower,tmp;
	__asm__ volatile(
				"0:                  \n"
				"\tmftbu   %0           \n"
				"\tmftb    %1           \n"
				"\tmftbu   %2           \n"
				"\tcmpw    %2,%0        \n"
				"\tbne     0b         \n"
				: "=r"(upper),"=r"(lower),"=r"(tmp)
				);
	result = upper;
	result = result<<32;
	result = result|lower;
	return(result);
}

#endif

int main()
{
	int i;
#define MAX 100
	unsigned long long int vals[MAX];
	unsigned long long int lastval = 0, thisval;
	unsigned long long int total;

	lastval = rdtsc();
	sleep(1);
	thisval = rdtsc();
	total = thisval - lastval;
	printf("%llu\n", total);

	// for ( i = 0 ; i < MAX ; i++ )
	// 	vals[i] = 1;
	// for ( i = 0 ; i < MAX ; i++ )
	// 	vals[i] = rdtsc();
	// for ( i = 0 ; i < MAX ; i++ )
	// 	printf("value: %llu delta: %llu\n",vals[i],
	// 	 i ? vals[i]-vals[i-1] : 0);

	// printf("=====\n");

	// for ( i = 0 ; i < 100 ; i++ ) {
	// 	thisval = rdtsc();
	// 	printf("value: %llu delta: %llu\n",
	// 		thisval, thisval - lastval);
	// 	lastval = thisval;
	// }

}