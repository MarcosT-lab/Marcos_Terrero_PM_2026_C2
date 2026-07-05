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

FILE *fp = fopen("Tarea 6/JSON/alumnos.json", "r");
if (!fp){
    fp = fopen("alumnos.json", "r");
}
if (!fp)
{
    printf("Error: No se pudo encontrar el archivo alumnos.json\n");
    return 1;
}

char buffer[4096];
memset(buffer, 0, sizeof(buffer));

size_t bytesLeidos = fread(buffer, 1, sizeof(buffer) -1, fp);
buffer[bytesLeidos] = '\0';
fclose(fp);

int n = 0;
char *contarPtr = buffer;
while((contarPtr = strstr(contarPtr, "\"Nombre\":")) != NULL){
    n++;
    contarPtr++;
}
Alumno *arregloAlumnos = (Alumno*) malloc(n * sizeof(Alumno));
int i = 0;
char *ptr = buffer;

if ((ptr = strstr(ptr, "{")) != NULL){
            ptr++;
}
printf("=================================================================================\n\n");
while((ptr = strstr(ptr, "{")) != NULL && i < n)
    {
                   char *pNombre = strstr(ptr, "\"Nombre\":");
                   char *pApellido = strstr(ptr, "\"Apellido\":");
                   char *pPromedio = strstr(ptr, "\"Promedio\":");
                   char *pMateria = strstr(ptr, "\"Materia\":");
                   if (pNombre && pApellido && pPromedio && pMateria)
        {
            sscanf(pNombre + 11, "%[^\"]", arregloAlumnos[i].nombre);
            sscanf(pApellido + 13, "%[^\"]", arregloAlumnos[i].apellido);
            sscanf(pPromedio + 12, "%f", &arregloAlumnos[i].promedio);
            sscanf(pMateria + 12, "%[^\"]", arregloAlumnos[i].materia);
            printf("Nombre: %s %s | Promedio: %.2f | Materia: %s\n", arregloAlumnos[i].nombre, arregloAlumnos[i].apellido, arregloAlumnos[i].promedio, arregloAlumnos[i].materia);
            i++;
        }
        ptr = strstr(ptr, "}");
        if(ptr) ptr++;
    }

printf("\n=================================================================================");
free(arregloAlumnos);
return 0;

}
