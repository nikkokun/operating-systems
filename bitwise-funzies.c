#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Print an int as a binary number
// Second arg is how many bits to print; 0 means size of int.
void binaryprintf(unsigned int number, int len) {
    int shiftlen = (sizeof(int) * CHAR_BIT) - 1;
    unsigned int mask;

    if (len)
        shiftlen = len - 1;
    // else start at far left end (maximum number of bits) in int
    mask = 1 << shiftlen;
    // Iterate until mask is 0
    int count = 0;
    while(mask) {
        // Insert a space every 8 chars for readability
        if (count % CHAR_BIT == 0) {
            printf(" ");
        }
        // Print 1 or 0 based on value of number and mask
        printf("%d", (number &mask ? 1 : 0));
        // Shift mask to the right
        mask >>= 1;
        count++;
    }
    // Print newline at the end
    printf("\n");
}

int main(int argc, char **argv) {
    printf("CHAR_BIT on your system: %d\n", CHAR_BIT);

    binaryprintf(0xFFFFFFFF, 0); // maximum = 2^32 = 11111111111111111111111111111111
    binaryprintf(4294967295, 0); // maximum = 2^32 = 11111111111111111111111111111111
    binaryprintf(0x00000000, 0); // minimum = 0    = 00000000000000000000000000000000
    binaryprintf(0, 0);          //           0    = 00000000000000000000000000000000
    printf("\n");

    // Basic bitwise left and right shift operations
    unsigned int x = 0x00000001; // x = 1
    x = x << 1;
    printf("Start with 1, shift it left.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    x = x << 0x00000001; // Shift left again
    printf("Shift it left again.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    // Bitwise or
    x = x | 0x00000001;
    printf("OR our value with another number, 0x00000001.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");


    // Bitwise or
    x = x & 0x00000004;
    printf("AND our value with another number, 0x00000004.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    x = x >> 0x00000001;
    printf("Shift right.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    x = x >> 0x00000001;
    printf("Shift right again.\n");
    printf("Decimal value of x is\n%u\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    printf("\n------------ now with more bits set! --------------\n\n");

    x = 0x9ABCDEF0;
    printf("Decimal value of x is\n%u\n", x);
    printf("Hex value of x is \n0x%x\n", x);
    printf("Binary value of x is\n");
    binaryprintf(x, 0);
    printf("\n");

    printf("The low-order six bits:\n");
    binaryprintf(x & 0x3f, 6); printf("\n");

    printf("Masking to keep the high-order six bits (on a 32-bit system):\n");
    binaryprintf(x & (0x3f << 26), 0); printf("\n");

    printf("Those six bits as a six-bit field:\n");
    binaryprintf((x >> 26) & 0x3f, 6); printf("\n");

    printf("The 20 bits in between:\n");
    binaryprintf(x & (0xfffff << 6), 0); printf("\n");

    printf("Shifted down as a field:\n");
    binaryprintf((x >> 6) & 0xfffff, 20); printf("\n");

}