#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
char nombre[50];
char apellido[50];
float promedio;
char materia[50];
}Alumno;

int main()
{
    FILE* fp = fopen("Tarea 6/CVS/alumnos.cvs", "r");
    if (!fp){
        fp = fopen("alumnos.cvs", "r");
    }
    if (!fp)
    {
        printf("Error: No se pudo encontrar el archivo alumnos.cvs\n");
        return 1;
    }
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    size_t bytesLeidos = fread(buffer, 1, sizeof(buffer) -1, fp);
    buffer[bytesLeidos] = '\0';
    fclose(fp);

    Alumno temp;

    printf("============================================================\n");
    char *linea = strtok(buffer, "\n");
    while (linea != NULL)
    {
        char promedioStr[10] = {0};
        int leidos = sscanf(linea, "%[^,],%[^,],%[^,],%[^\r\n]", temp.nombre, temp.apellido, promedioStr, temp.materia);
        if(leidos == 4 && strcmp(temp.nombre, "Nombre") != 0)
        {
            temp.promedio = atof(promedioStr);
            printf("Nombre: %s %s |Promedio: %.2f| Materia: %s\n", temp.nombre, temp.apellido, temp.promedio, temp.materia);
        }
        linea = strtok(NULL, "\n");
    }
    printf("============================================================\n");
    return 0;
}
