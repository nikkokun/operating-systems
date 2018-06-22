//
// Created by Nikko Mizutani on 2018/05/02.
//
/*
Submission notes(5/3):
The program's functionality and logic is already complete.
It lacks the following:

1.) User Input.
2.) Print statements during splitting and merging.

Submission notes(5/5):

1.) Fixed a bug in the merge function.
2.) Added user input.
3.) Cleaned the print statements.

*/

/* buddy-allocator.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#define ARGMAXLENGTH 64

int blockPartitionSize = 1;
int *blockPartitionsArray;
bool *blockStatesArray;
int *blockAddresses;
char blocks[64];
char splitter = '|';
char prompt[47] = "How many blocks do you want to allocate/free?\n";
char help[122] = "TO ALLOCATE MEMORY: a [memory you wish to allocate]\nTO FREE MEMORY: f [address you wish to free]\nTO QUIT THE PROGRAM: q\n";

void regularPrintBlock() {

	for (int i = 0; i < blockPartitionSize; i++) {

		if(i == 0) {
			printf("%c", splitter);
		}

		for(int j = 0; j < blockPartitionsArray[i]; j++) {
			if(blockStatesArray[i] == true) {
				blocks[j] = '#';
			} else {
				blocks[j] = '-';
			}
			printf("%c", blocks[j]);
		}
		printf("%c", splitter);
	}

	printf("\n");
}

void init() {
	blockPartitionsArray = (int*) malloc(blockPartitionSize * sizeof(int));
	blockAddresses = (int*) malloc(blockPartitionSize * sizeof(int));
	blockStatesArray = (bool*) malloc(blockPartitionSize * sizeof(bool));
	blockAddresses[0] = 0;
	blockPartitionsArray[0] = 64;
	blockStatesArray[0] = false;

	regularPrintBlock();
	printf("%s", prompt);
	printf("\n");
	printf("%s", help);
	printf("\n");
}

bool checkIfNeedSplit(int blockSize) {
	bool isNeeded = true;

	for(int i = 0; i < blockPartitionSize; i++) {
		if(blockPartitionsArray[i] == blockSize && blockStatesArray[i] == false) {
			isNeeded = false;
			break;
		} else {
			isNeeded = true;
		}
	}
	return isNeeded;
}

int calculateTotalMemoryConsumed () {
	int totalMemory = 0;

	for(int i = 0; i < blockPartitionSize; i++) {
		if(blockStatesArray[i] == true) {
			totalMemory += blockPartitionsArray[i];
		}
	}
	return totalMemory;
}

void updateAddresses() {
	blockAddresses = realloc(blockAddresses, blockPartitionSize * sizeof(int));

	for(int i = 0; i < blockPartitionSize; i++) {
		if(i == 0) {
			blockAddresses[i] = 0;
			// printf("%d ", blockAddresses[i]);
		} else {
			blockAddresses[i] = blockAddresses[i-1] + blockPartitionsArray[i-1];
			// printf("%d ", blockAddresses[i]);
		}
	}
	// printf("\n");
}

void splitBlocks(int blockSize) {

	bool isSplitNeeded = checkIfNeedSplit(blockSize);
	int totalMemory = calculateTotalMemoryConsumed();

	if(totalMemory >= ARGMAXLENGTH) {
		printf("NO MORE ROOM MEMORY FOR %d BYTES\n", blockSize);
		return;
	}

	if(isSplitNeeded == true) {

		int *tempBlockPartitionsArray = (int*) malloc(blockPartitionSize * sizeof(int));
		bool *tempBlockStatesArray = (bool*) malloc(blockPartitionSize * sizeof(bool));
		int splittableBlockIndex = 0;
		bool isSplittableBlockFound = false;
		int tempBlockPosition = 0;

		for(int i = 0; i < blockPartitionSize; i++) {

			tempBlockPartitionsArray[i] = blockPartitionsArray[i];
			tempBlockStatesArray[i] = blockStatesArray[i];

			if(blockSize < blockPartitionsArray[i] && blockStatesArray[i] == false && isSplittableBlockFound == false) {
				splittableBlockIndex = i;
				isSplittableBlockFound = true;
			}
		}

		if(!isSplittableBlockFound) {
			printf("NO MORE ROOM MEMORY FOR %d BYTES\n", blockSize);
			free(tempBlockPartitionsArray);
			free(tempBlockStatesArray);
			return;
		}

		printf("(splitting %d/%d)\n", blockAddresses[splittableBlockIndex], blockPartitionsArray[splittableBlockIndex]);
		
		blockPartitionSize++;
		blockPartitionsArray = realloc(blockPartitionsArray, blockPartitionSize * sizeof(int));
		blockStatesArray = realloc(blockStatesArray, blockPartitionSize * sizeof(bool));

		for(int i = 0; i < blockPartitionSize; i++) {
			if(i == splittableBlockIndex && blockStatesArray[i] == false) {

				int splitBlockValue = tempBlockPartitionsArray[tempBlockPosition]/2;
				blockPartitionsArray[i] = splitBlockValue;
				blockPartitionsArray[i+1] = splitBlockValue;
				blockStatesArray[i] = false;
				blockStatesArray[i+1] = false;
				i++;
			} else {
				blockPartitionsArray[i] = tempBlockPartitionsArray[tempBlockPosition];
				blockStatesArray[i] = tempBlockStatesArray[tempBlockPosition];
			}
			tempBlockPosition++;
		}

		free(tempBlockPartitionsArray);
		free(tempBlockStatesArray);

		updateAddresses();
		splitBlocks(blockSize); //do recursion until split is no longer necessary

	} else {

		updateAddresses();

		for(int i = 0; i < blockPartitionSize; i++) {
			if(blockPartitionsArray[i] == blockSize && blockStatesArray[i] == false) {
				blockStatesArray[i] = true;
				printf("Blocks %d/%d allocated.\n", blockAddresses[i], blockAddresses[i]+blockPartitionsArray[i]-1);
				break;
			}
		}

		regularPrintBlock();
	}
}

void allocateMemory(int memorySize) {

	if(memorySize > ARGMAXLENGTH) {
		printf("Please provide a value lesser than or equal to 64.\n");
		return;
	}

	int rightBlockSize = 0;

	for (int i = 0; i <= 6; i++) {
		if(memorySize <= pow(2, i)) {
			rightBlockSize = pow(2, i);
			break;
		} else {
			continue;
		}
	}
	splitBlocks(rightBlockSize);
}

bool checkIfBlocksAreMergeable() {
	bool isMergeable = false;

	for(int i = 0; i < blockPartitionSize; i++) {
		if(i+1 < blockPartitionSize) {
			if(blockPartitionsArray[i] == blockPartitionsArray[i+1] && blockStatesArray[i] == false && blockStatesArray[i+1] == false) {
			isMergeable = true;
			break;
			} else {
				isMergeable = false;
			}
		} 
	}

	return isMergeable;
}

void mergeBlocks() {

	bool isBlocksMergeable = checkIfBlocksAreMergeable();

	if(isBlocksMergeable) {

		int *tempBlockPartitionsArray = (int*) malloc(blockPartitionSize * sizeof(int));
		bool *tempBlockStatesArray = (bool*) malloc(blockPartitionSize * sizeof(bool));
		int mergeableBlockIndex = 0;
		int permanentBlockPosition = 0;

		for(int i = 0; i < blockPartitionSize; i++) {
			tempBlockPartitionsArray[i] = blockPartitionsArray[i];
			tempBlockStatesArray[i] = blockStatesArray[i];
		}

		for(int i = 0; i < blockPartitionSize; i++) {
			if(blockPartitionsArray[i] == blockPartitionsArray[i+1] && blockStatesArray[i] == false && blockStatesArray[i+1] == false) {
				mergeableBlockIndex = i;
				break;
			}
		}

		printf("(merging %d/%d and %d/%d)\n", blockAddresses[mergeableBlockIndex], blockPartitionsArray[mergeableBlockIndex], blockAddresses[mergeableBlockIndex + 1], blockPartitionsArray[mergeableBlockIndex + 1]);

		blockPartitionSize--;
		blockPartitionsArray = realloc(blockPartitionsArray, blockPartitionSize * sizeof(int));
		blockStatesArray = realloc(blockStatesArray, blockPartitionSize * sizeof(bool));

		for(int i = 0; i < blockPartitionSize + 1; i++) {
			if(i == mergeableBlockIndex) {
				int mergedBlockValue = tempBlockPartitionsArray[i] + tempBlockPartitionsArray[i + 1];
				blockPartitionsArray[permanentBlockPosition] = mergedBlockValue;
				blockStatesArray[permanentBlockPosition] = false;
				i++;
			} else {
				blockPartitionsArray[permanentBlockPosition] = tempBlockPartitionsArray[i];
				blockStatesArray[permanentBlockPosition] = tempBlockStatesArray[i];
			}
			permanentBlockPosition++;
		}

		free(tempBlockPartitionsArray);
		free(tempBlockStatesArray);

		updateAddresses();
		mergeBlocks(); //do recursion until merge is no longer necessary

	} else {
		updateAddresses();
		regularPrintBlock();
	}
}

void freeMemory(int blockAddress) {
	int rightAddressIndex = -1;

	for (int i = 0; i < blockPartitionSize; i++) {
		if(blockAddresses[i] == blockAddress) {
			rightAddressIndex = i;
			break;
		} else {
			continue;
		}
	}

	if(rightAddressIndex != -1) {
		int freedBlockHead = blockAddresses[rightAddressIndex];
		int freedBlockTail = blockAddresses[rightAddressIndex]+blockPartitionsArray[rightAddressIndex]-1;
		blockStatesArray[rightAddressIndex] = false;
		mergeBlocks();
		printf("Blocks %d/%d freed.\n", freedBlockHead, freedBlockTail);
	}
}

void exitProgram() {
	printf("quitting the program...\n");
	free(blockPartitionsArray);
	free(blockStatesArray);
	free(blockAddresses);
	exit(0);
}


int main() {
	char argument1;
	int argument2;
	char* arguments[1000];
	char input[1000];
	char *separator = " ";
	char *tmp;
	char *word;
	int a = 1;

	init();

	while(a <= 1) {
		printf("buddy-allocator>>");
		scanf(" %[a-z A-Z 0-9 /!@#$%^&*()_+-={}\'\":;<>,.~`]", &input);
		int counter = 0;
		word = strtok_r(input, separator, &tmp);

		while (word != NULL) {
			arguments[counter] = word;
			word = strtok_r(NULL, separator, &tmp);
			counter = counter + 1;
		}

		counter = 0;
		argument1 = arguments[0][0];

		if(arguments[1] != NULL) {
			argument2 = strtol(arguments[1], NULL, 0);
		}

		if(argument1 == 'a') {
			allocateMemory(argument2);
		} else if(argument1 == 'f') {
			freeMemory(argument2);
		} else if(argument1 == 'q') {
			exitProgram();
		} else {
			printf("%s", help);
		}
		printf("%s", prompt);
	}

	// ===== TESTS
	// allocateMemory(4);
	// freeMemory(0);
	// allocateMemory(3);
	// allocateMemory(4);
	// allocateMemory(8);
	// allocateMemory(16);
	// allocateMemory(4);
	// allocateMemory(8);
	// allocateMemory(8);
	// allocateMemory(4);
	// allocateMemory(8);
	// freeMemory(0);
	// freeMemory(4);
	// freeMemory(8);
	// freeMemory(16);
	// freeMemory(32);
	// freeMemory(36);
	// freeMemory(40);
	// freeMemory(48);
	// freeMemory(56);
	// exitProgram();
}

