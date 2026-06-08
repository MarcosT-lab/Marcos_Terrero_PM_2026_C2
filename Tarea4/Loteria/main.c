#include <stdio.h>
#define MAX_JUGADAS 20

int main()
{
    int op;
    int jugadas = 5;
    int numeros_jugados[MAX_JUGADAS];
    float dinero_jugado[MAX_JUGADAS];
    int I;
    int numero_ganador;
    int ganador;
    float premio;
    do
    {
        printf("\nLoteria\n");
        printf("1. Cantidad de jugadas (Actual: %d)\n", jugadas);
        printf("2. Jugar\n");
        printf("3. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            printf("\nElege la cantidad de jugadas: ");
            scanf("%d", &jugadas);
            if (jugadas <= 0 || jugadas > MAX_JUGADAS)
            {
                printf("Cantidad invalida. Selecione 5.\n");
                    jugadas = 5;
            }
            else
            {
                printf("Cantidad seleccionada: %d jugadas\n", jugadas);
            }
            break;

        case 2:
            printf("Ingrese el numero ganador (1 a 40): ");
            scanf("%d", &numero_ganador);

            while(numero_ganador < 1 || numero_ganador > 40)
            {
                printf("Numero invalido debe ser del 1 al 40: ");
                scanf("%d", &numero_ganador);
            }
            printf("\n---------- jugadas ----------\n");
            for(I= 0; I < jugadas; I++)
            {
                printf("\nJugada #%d de  %d:\n", I+1, jugadas);
                printf("Ingrese el numero que desea jugar (1 al 40): ");
                scanf("%d",&numeros_jugados[I]);

            printf("Ingrese la cantidad de dinero: ");
            scanf("%f", &dinero_jugado[I]);
            while(dinero_jugado[I] <= 0)
            {
                printf("El dinero debe ser mayor a 0. Intente nuevamente: ");
                scanf("%f", &dinero_jugado[I]);
            }
            }
        printf("\n=============================\n");
        printf("EL NUMERO GANADOR ES: %d\n", numero_ganador);
        printf("\n=============================\n");

        ganador = 0;
        for (I= 0; I < jugadas; I++)
        {
            if (numeros_jugados[I] == numero_ganador)
            {
                premio = dinero_jugado[I] * 1000;
                printf("Jugada #%d: Numero ganador %d. Gano: $%.2f\n", I+1, numeros_jugados[I], premio);
                ganador = 1;
            }
            else
            {
                printf("Jugada #%d: No gano. El numero selecionado fue %d y el ganador fue %d.\n", I + 1, numeros_jugados[I],numero_ganador);
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
