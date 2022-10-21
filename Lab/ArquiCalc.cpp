#define PUERTO_SALIDA_DEFECTO 8
#define PUERTO_LOG_DEFECTO 1
#define ENTRADA 22

#include <stdio.h>

short in(short port)
{
    short n = 0;
    scanf("%hu", &n);
    return n;
}
void out(short port, short val)
{
}

short fact(short n)
{
    if (n > 1)
        return n * fact(n - 1);
    else
        return 1;
}

int main()
{
    short port_exit = PUERTO_SALIDA_DEFECTO;
    short port_logs = PUERTO_LOG_DEFECTO;

    short MEM[31]; // simulo la pila en memoria como un arreglo
    for (short i = 0; i < 31; i++)
        MEM[i] = 0;

    short posPila = -1;

    short cod = in(ENTRADA);
    while (cod != 255)
    {
        out(port_logs, 0);
        out(port_logs, cod); // mando a la bitacora: 0 'cod_operacion'

        if (cod == 1) // inserto nro a la pila
        {
            short dato = in(ENTRADA); // recordar pasar a complemento a 2
            out(port_logs, dato);     // mando a la bitacora el parametro

            if (posPila < 30)
            {
                posPila++;
                MEM[posPila] = dato;
                out(port_logs, 16); // op realiada con exito
            }
            else
            {
                out(port_logs, 4); // error desbordamiento de la pila
            }
        }
        else if (cod == 2) // seteo el puerto de salida
        {
            short dato = in(ENTRADA);
            out(port_logs, dato); // mando a la bitacora el parametro

            PUERTO_SALIDA_DEFECTO = dato;
            out(port_logs, 16); // op realiada con exito
        }
        else if (cod == 3) // seteo el puerto de bitacora
        {
            short dato = in(ENTRADA);
            out(port_logs, dato); // mando a la bitacora el parametro

            port_logs = dato;
            out(port_logs, 16); // op realiada con exito
        }
        else if (cod == 4) // muestro tope de pila en puerto de salida sin perderlo
        {
            if (posPila >= 0)
            {
                short dato = MEM[posPila];
                out(port_exit, dato);
                out(port_logs, 16); // op realiada con exito
            }
            else
                out(port_logs, 8); // error: falta de operandos
        }
        else if (cod == 5) // muestro la pila en puerto salida sin perderla
        {
            short i = posPila;

            while (i > -1)
            {
                out(port_exit, MEM[i]);
                i--;
            }
            out(port_logs, 16); // op realiada con exito
        }
        else if (cod == 6) // Duplico el tope de la pila: insert_pila(tope_pila);
        {
            if (posPila < 31)
            {
                if (posPila > 0)
                {
                    short i = posPila - 1;
                    MEM[posPila] = MEM[i];
                    posPila++;
                    out(port_logs, 16); // op realiada con exito
                }
                else
                    out(port_logs, 8); // falta de operandos
            }
            else
                out(port_logs, 4); // overflow en la pila
        }
        else if (cod == 7) // shortercambiar tope de la pila con el elem debajo
        {
            if (posPila > 0)
            {
                short i = posPila;
                short aux1 = MEM[i];
                short j = i - 1;
                short aux2 = MEM[j];
                MEM[i] = aux2;
                MEM[j] = aux1;

                out(port_logs, 16); // op realiada con exito
            }
            else
                out(port_logs, 8); // falta de operandos
        }
        else if (cod == 8) // Calculo el opuesto
        {
            if (posPila >= 0)
            {
                short num = -MEM[posPila];
                MEM[posPila] = num;

                out(port_logs, 16); // op realiada con exito
            }
            else
                out(port_logs, 8); // falta de operandos
        }
        else if (cod == 9) // calculo factorial de forma recursiva
        {
            if (posPila >= 0)
            {
                short num = MEM[posPila];
                num = fact(num);
                MEM[posPila] = num;
                out(port_logs, 16); // op realiada con exito
            }
            else
                out(port_logs, 8); // falta de operandos
        }
        else if (cod == 10) // Sumatoria de los elem de la pila y solo queda el resu en ella
        {
            if (posPila >= 0)
            {
                short sum = 0;
                do
                {
                    sum = sum + MEM[posPila];
                    posPila--;
                } while (posPila >= 0);
                posPila++;
                MEM[posPila] = sum;
                out(port_exit, sum); // muestro la suma
                out(port_logs, 16);  // op realiada con exito
            }
            else
                out(port_logs, 8); // falta de operandos
        }
        else if (cod > 10 && cod < 20)
        {
            // como son operaciones binarias, solo se hacen si hay por lo menos 2 elem en la pila
            if (posPila > 0)
            {
                short n1 = MEM[posPila];
                posPila--;
                short n2 = MEM[posPila];
                short res = 0;
                if (cod == 11) // +
                {
                    res = n2 + n1;
                }
                else if (cod == 12) // -
                {
                    res = n2 - n1;
                }
                else if (cod == 13) // *
                {
                    res = n2 * n1;
                }
                else if (cod == 14) // div
                {
                    res = n2 / n1;
                }
                else if (cod == 15) // %
                {
                    res = n2 % n1;
                }
                else if (cod == 16) // &
                {
                    res = n2 & n1;
                }
                else if (cod == 17) // |
                {
                    res = n2 | n1;
                }
                else if (cod == 18) // <<
                {
                    res = n2 << n1;
                }
                else if (cod == 19) // >>
                {
                    res = n2 >> n1;
                }
                MEM[posPila] = res;
                out(port_logs, 16); // op realiada con exito
            }
            else
            {
                out(port_logs, 8); // falta de operandos
                posPila--;         // se debe eliminar el operando de la pila
            }
        }
        else if (cod == 254) // vaciar pila
        {
            if (posPila > -1) // necesito al menos un elem
            {
                while (posPila > -1)
                    posPila--;
                out(port_logs, 16); // op realiada con exito
            }
            else
                out(port_logs, 8); // falta de operandos
        }
        else
            out(port_logs, 2); // comando invalido

        cod = in(ENTRADA);
    }

    out(PUERTO_LOG_DEFECTO, 16); // se termina de leer la entrada con exito
    return 0;
}