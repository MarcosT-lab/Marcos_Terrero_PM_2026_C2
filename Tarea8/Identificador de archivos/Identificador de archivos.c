#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    const char *ext;
    unsigned char firma [4];
    size_t len;
} FormatoImagen;

const FormatoImagen formatos[] =
{
    {".png", {0x89, 0x50, 0x4E, 0x47}, 4},
    {".jpg", {0xFF, 0xD8}, 2},
    {".jpeg", {0xFF, 0xD8}, 2},
    {".bmp", {0x42, 0x4D}, 2}
};

void analizar_archivo(const char *nombre)
{
    FILE *f = fopen(nombre, "rb");
    if (!f)
    {
        printf("!! Error al abrir el archivo.\n");
        return;
    }
    const char *punto = strrchr(nombre, '.');
    if (!punto)
    {
        printf("-> Archivo sin extension.\n");
        fclose(f);
        return;
    }
    unsigned char header[4] = {0};
    fread(header, 1, 4, f);
    fclose(f);
    bool encontrado = false;
    for (int i = 0; i < 4; i++)
    {
        if (strcasecmp(punto, formatos[i].ext) == 0)
        {
            encontrado = true;
            if(memcmp(header, formatos[i].firma, formatos[i].len) == 0)
            {
                printf(">> ESTADO: [AUTENTICO] %S validado correctamente.\n", punto);
            }
            else
            {
                printf(">> ESTADO: [ALERTA] Incoherencia detectada en %s.\n", punto);
            }
            break;
        }
    }
    if (!encontrado) printf(">> INFO: Formato no soportado. \n");
}

int main ()
{
    struct dirent *de;
    DIR *dr = opendir(".");
    char archivos[100][260];
    int count = 0;
    int indice_visual = 1;

    if (!dr)
    {
        printf("Error: No se puede abrir el directorio.\n");
        return 1;
    }
    printf("--- IDENTIFICADOR DE ARCHIVOS ---\n");
    while ((de = readdir(dr)) != NULL && count < 100)
    {
        if (de->d_name[0] != '.')
        {
            strcpy(archivos[count], de->d_name);
            printf("[%d] %s\n", indice_visual, archivos[count]);
            count++;
            indice_visual++;
        }
    }
    closedir(dr);
    if (count == 0)
    {
        printf("No se encontraron archivos.\n");
        return 0;
    }
    int sel;
    printf("\nSeleccione ID (0 para salir): ");
    if (scanf("%d", &sel) == 1 && sel > 0 && sel > 0 && sel <= count)
    {
        analizar_archivo(archivos[sel - 1]);
    }
    else
    {
        printf("Saliendo...\n");
    }
    return 0;
}
