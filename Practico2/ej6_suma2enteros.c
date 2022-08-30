#include <stdio.h>

void printBits(short num)
{
    unsigned short num_s;

    for (int bit = 15; bit >= 0; bit--)
    {
        num_s = num >> bit;
        printf("%hd", num_s & 1);
    }
    printf("\n");
}

void printBits_int(int num)
{
    unsigned short num_s;

    for (int bit = 31; bit >= 0; bit--)
    {
        num_s = num >> bit;
        printf("%hd", num_s & 1);
    }
    printf("\n");
}

/*
suma entre dos enteros de 16 bits representados en
complemento a 2 y devuelve una palabra de 19 bits con el siguiente formato:
bit 0: bandera Z
bit 1: bandera V
bit 2: bandera C
bits 18..3: resultado de la suma (16 bits)
*/

int suma_enteros(short n1, short n2)
{
    int z, v, c;
    short sum = n1 + n2;
    v = 0;
    z = 0;

    if (n1 > 0 && n2 > 0 && sum < 0 || n1 < 0 && n2 < 0 && sum > 0)
        v = 1;

    if (sum == 0)
        z = 1;

    int res = (n1 + n2);
    printf("bits Res: \n");
    printBits_int(res);

    int msk = 0x00010000;

    c = (res & msk) >> 16;

    printf("Bit de carry: %hd \n", c);
    printf("Bit de overflow: %hd \n", v);
    printf("Bit de cero: %hd \n", z);

    res = res << 1 & 0x0001FFFE;
    res = res | c;

    res = res << 1 & 0x0003FFFE;
    res = res | v;

    res = res << 1 & 0x0007FFFE;
    res = res | z;

    return res;
};

int main()
{

    short n1 = 0xF21C;
    short n2 = 0X0DE4;

    printBits(n1);
    printBits(n2);

    int sum = suma_enteros(n1, n2);

    printBits_int(sum);
}