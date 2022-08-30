#include <stdbool.h>
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

char paridad(int palabra)
{

    int msk = 0x00000001;
    char cont = 0;
    for (int i = 0; i <= 31; i++)
    {
        cont = cont ^ palabra & msk;
        palabra = palabra >> 1;
    }
    return cont;
}

int main()
{
    int a = 0b0001010010111001;
    char par = paridad(a);

    if (par == 0)
        printf("El nro es par");
    else
        printf("El nro es impar");
}