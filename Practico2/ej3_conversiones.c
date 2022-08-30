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

unsigned short comp1_to_magYsigno(short c)
{
    short msk = 0x8000;
    unsigned short signo = c & msk; // me quedo con el bit mas significativo
    short res;

    if (signo > 0)
    {
        res = (~c & 0x7FFF) | signo;
    }
    else
    {
        res = c;
    }

    return res;
}

unsigned short comp2_to_despD(short c)
{
    // Desplazamiento D= 128
    short D = 0x0100;

    short sg_magnitud = comp1_to_magYsigno(c);
    short res;

    res = (sg_magnitud & 0x7FFF) + D;

    short sg = sg_magnitud & 0x8000;
    if (sg > 0)
    {
        res = -(sg_magnitud & 0x7FFF) + D;
    }

    return res;
}

int main()
{
}