#include <stdio.h>
#include <math.h>

void hanoi(int n, char inicio, char medio, char fin);
FILE *archivo;
int mov = 1;

int main()
{
    int D;
    do
    {
        printf("Cantidad de discos(Minimo 3): ");
        scanf("%d", &D);
        if (D <= 2)
            printf("MINIMO 3\n");
    }
    while (D <= 2);
    archivo = fopen("movimientos.txt", "w");
    hanoi(D, 'A', 'B', 'C');
    int total_movimiento = (1<<D)-1;
    printf("Total de movimientos: %d\n", (int)pow(2, D) - 1);
    fclose(archivo);
    return 0;
}

void hanoi(int n, char inicio, char medio, char fin)
{
    if (n == 1)
    {
        fprintf(archivo, "%d. Mover disco 1 de %c a %c\n", mov++, inicio, fin);
        return;
    }

    hanoi(n-1, inicio, fin, medio);
    fprintf(archivo, "%d. Mover disco %d de %c a %c\n", mov++, n, inicio, fin);
    hanoi(n-1, medio, inicio, fin);
}
