//
// Created by Nico Roble on 2018/04/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


int main() {
	char *str;

	str = (char *) malloc(12 * sizeof(char));
	strcpy(str, "Hello World");
	printf("%s\n", str);


	free(str);

	// char *str = "Hello World!";
	// printf("%s\n", str);

	return(0);
}