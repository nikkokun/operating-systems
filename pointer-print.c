#include <stdio.h>
#include <stdlib.h>

int globalA = 317;

void indent(int d)
{
	for ( ; d ; d-- )
		printf("  ");
}

void f(int localA, int originalDepth)
{
	if (localA) {
		indent(originalDepth - localA); printf("Inside function f()\n");
		indent(originalDepth - localA); printf("local A: %d pointer to local A: %p\n",localA,&localA);
		f(localA-1, originalDepth);
		indent(originalDepth - localA); printf("exiting f()\n");
	}
}

int main(int argc, char **argv)
{
	printf("Pointer to function main(): %p\n", main);
	printf("global A: %d pointer to global A: %p\n",globalA,&globalA);
	printf("Pointer to function f(): %p\n", f);
	printf("Pointer to function printf(): %p\n", printf);
	// printf("Pointer to function write(): %p\n", write);
	f(10,10);
	exit(0);
}