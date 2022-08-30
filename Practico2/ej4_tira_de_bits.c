#include <stdio.h>

void printBits(unsigned short num)
{
    unsigned short num_s;

    for (int bit = 15; bit >= 0; bit--)
    {
        num_s = num >> bit;
        printf("%i", num_s & 1);
    }
    printf("\n");
}

int extraerBits(int palabra, int bitAlto, int bitBajo)
{
    palabra = palabra >> bitBajo;
    int msk = (1 << bitAlto - bitBajo + 1) - 1;
    printBits(msk);

    return palabra & msk;
}

int main()
{
    unsigned int a = 0b000111001101;
    printf("input:  ");
    printBits(a);

    printf("result: ");
    printBits(extraerBits(a, 6, 2));
}