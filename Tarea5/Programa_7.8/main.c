#include <stdio.h>
#include <string.h>
#include <ctype.h>

void minymay(char *cadena);

void main(void)
{
    int I, N;
    char FRA[20][50];

    printf("\nIngrese el numero de filas del arreglo: ");
    scanf("%d", &N);
    getchar();
    for (I=0; I<N; I++)
    {
        printf("Ingrese la linea %d de texto: ", I+1);
        fflush(stdin);
        gets(FRA[I]);
    }
    printf("\n\n");
    for (I=0; I<N; I++)
        minymay(FRA[I]);
}

void minymay(char *cadena)
{
    int I = 0, MI = 0, MA = 0;
    while (cadena[I] != '\0')
    {
        if (islower(cadena[I]))
            MI++;
        else
            if (isupper(cadena[I]))
            MA++;
        I++;
    }
    printf("\n\nNumero de letras minusculas: %d", MI);
    printf("\nNumero de letras mayusculas: %d", MA);
}
