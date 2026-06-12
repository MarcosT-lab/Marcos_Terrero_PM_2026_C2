#include <stdio.h>
#define MAX_JUGADAS 5

int main()
{
    int numero_aleatorio = 9;
    int op = 0;
    int jugadas = 5;
    int numeros_jugados[MAX_JUGADAS];
    float dinero_jugado[MAX_JUGADAS];
    int I;
    int numero_ganador;
    int ganador;
    float premio;
    do
    {
        numero_aleatorio = numero_aleatorio + op;
        printf("\nLoteria\n");
        printf("1. Cantidad de jugadas (Actual: %d)\n", jugadas);
        printf("2. Jugar\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("\nElige la cantidad de jugadas: ");
            scanf("%d", &jugadas);

            if (jugadas > MAX_JUGADAS || jugadas <=0 )
            {
                 printf("Cantidad invalida. Elige 5 jugadas.\n");
                 jugadas = 5;
            }
            else
                 {
                     printf("Cantidad seleccionada: %d jugadas\n", jugadas);
                 }
            break;
        case 2:
            numero_ganador = (numero_aleatorio + 9) - 2;
            while (numero_ganador > 40)
            {
                numero_ganador = numero_ganador -40;
            }
                 if (numero_ganador <=0)
                 {
                     numero_ganador = 1;
                 }
                 printf("\n==============Jugadas===============\n");
                 for(I = 0; I < jugadas; I++)
                 {
                     printf("\nJugada #%d de %d:\n", I + 1, jugadas);
                     do
                     {
                         printf("Ingrese el numero que desea jugar del 1 al 40: ");
                         scanf("%d", &numeros_jugados[I]);

                         if (numeros_jugados[I] < 1 || numeros_jugados[I] > 40)
                         {
                             printf("Error: El numero debe estar entre 1 y 40.\n");
                         }
                     }
                     while (numeros_jugados[I] < 1 || numeros_jugados [I] > 40);
                        printf("Ingrese la cantidad de dinero: ");
                     scanf("%f", &dinero_jugado[I]);
                     while(dinero_jugado[I] <= 0)
                     {
                         printf("El dinero debe ser mayor a 0. Intente nuevamente: ");
                         scanf("%f", &dinero_jugado[I]);
                     }
                 }
                 printf("\n====================\n");
                 printf("El numero ganador es: %d\n", numero_ganador);
                 printf("\n====================\n");

                 ganador = 0;
                 for (I = 0; I < jugadas; I++)
                 {
                     if (numeros_jugados[I] == numero_ganador)
                     {
                         premio = dinero_jugado[I] * 1000;
                         printf("Jugada #%d: Numero ganador %d. Gano: $%.2f\n", I + 1, numeros_jugados[I], premio);
                         ganador = 1;
                     }
                     else
                     {
                         printf("Jugada #%d: No gano. El numero seleccionado fue %d y el ganador fue %d.\n", I + 1, numeros_jugados[I], numero_ganador);
                     }
                 }
                 if (ganador == 0)
                 {
                     printf("\nNadie salio como ganador.\n");
                 }
        break;
        case 3:
            printf("\nSaliendo. Hasta la proxima\n");
            break;

        default:
            printf("\nOpcion invalida. Intente nuevamente.\n");
            break;
    }
    }
while (op != 3);

return 0;
    }
