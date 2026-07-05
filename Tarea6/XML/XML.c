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
FILE* fp = fopen("Tarea 6/XML/alumnos.xml", "r");
if (!fp){
 fp = fopen("alumnos.xml", "r");
}
if (!fp)
{
        printf("Error: No se pudo encontrar el archivo alumnos.xml\n");
    return 1;
}

char buffer[4096];
memset(buffer, 0, sizeof(buffer));

size_t bytesLeidos = fread(buffer, 1, sizeof(buffer) - 1, fp);
buffer[bytesLeidos] = '\0';
fclose(fp);

char *ptr = buffer;
Alumno temp;

printf("========================================================\n");
while((ptr = strstr(ptr, "<Alumno>")) !=NULL)
{
    char *pNombre = strstr(ptr, "<Nombre>");
    char *pApellido = strstr(ptr, "<Apellido>");
    char *pPromedio = strstr(ptr, "<Promedio>");
    char *pMateria = strstr(ptr, "<Materia>");
     if (pNombre && pApellido && pPromedio && pMateria)

     {

    sscanf(pNombre +8, "%[^<]", temp.nombre);
    sscanf(pApellido +10, "%[^<]", temp.apellido);
    sscanf(pPromedio +10, "%f", &temp.promedio);
    sscanf(pMateria +9, "%[^<]", temp.materia);

    printf("Nombre: %s %s |Promedio: %.2f| Materia: %s\n", temp.nombre, temp.apellido, temp.promedio, temp.materia);
    }

    ptr += 8;
}
printf("========================================================\n");
return 0;
}
