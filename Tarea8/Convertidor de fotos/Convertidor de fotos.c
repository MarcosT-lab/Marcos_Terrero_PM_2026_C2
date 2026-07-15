#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void convertirABlancoYNegro(const char *archivo)
{
    int width, height, channels;
    unsigned char *img = stbi_load(archivo, &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Error al cargar imagen.\n");
        return;
    }
    unsigned char *bw_img = malloc(width * height);
    for (int i = 0; i < width * height; i++)
    {
        unsigned char r = img[i * channels];
        unsigned char g = img[i * channels + 1];
        unsigned char b = img[i * channels + 2];
        bw_img[i] = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
    }
    char nombreSalida[100];
    sprintf(nombreSalida, "bw_%s", archivo);
    stbi_write_png(nombreSalida, width, height, 1, bw_img, width);
    printf("Imagen guardada como: %s\n", nombreSalida);
    stbi_image_free(img);
    free(bw_img);
}

int main()
{
    struct dirent *de;
    DIR *dr = opendir(".");
    char archivos[50][100];
    int contador = 0;
    printf("Archivos encontrados:\n");
    while ((de = readdir(dr)) != NULL)
    {
        if (strstr(de->d_name, ".jpg") || strstr(de->d_name, ".png") || strstr(de->d_name, ".bmp"))
        {
            printf("%d. %s\n", contador + 1, de->d_name);
            strcpy(archivos[contador], de->d_name);
            contador++;
        }
    }
    closedir(dr);
    if(contador == 0)
    {
        printf("No se encontraron imagenes.\n");
        return 0;
    }
    printf("\nSeleccione el numero de archivo a convertir: ");
    int opcion;
    scanf("%d", &opcion);
    if (opcion > 0 && opcion <= contador)
    {
        convertirABlancoYNegro(archivos[opcion - 1]);
    }
    else
    {
        printf("Opcion Invalida.\n");
    }
    return 0;
}
