//
// Created by Nico Roble on 2018/05/02.
//

/* scope-example.c */
#include <stdio.h>
#include <stdlib.h>
int i = 1; /* global */
void f1(){
	int i = 100; /* f1 local */
	for(;;){
		int i = 1000; /* for local */
		printf("i = %d (in for in f1)\n",i);
		{
			i = 2000;
			int i;
			i = 10000;
			printf("i = %d (in for in f1-2)\n",i);
		}
		printf("i = %d (in for in f1)\n",i);
		break;
}
	printf("i = %d (in f1)\n",i);
}
void f2(){
	printf("i = %d (in f2)\n",i);
}
int main(){
	int i;
	i = 10;
	printf("i = %d (in main)\n",i);
	f1();
	f2();
	printf("i = %d (in main)\n",i);
	exit(0);
}