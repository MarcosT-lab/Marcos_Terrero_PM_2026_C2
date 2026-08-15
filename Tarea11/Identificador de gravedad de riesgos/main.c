#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 100
#define MAX_RUTA 260

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];


    int F;
    int S;
    int P;
    int E;
    int A;
    int V;


    int C;
    int PB;
    int ER;
    char clasificacion[20];
} Riesgo;


void calcularMoslerVideo(Riesgo *r);
void crearRiesgo(Riesgo **lista, int *tamano);
void modificarRiesgo(Riesgo *lista, int tamano);
void calcularTodosLosRiesgos(Riesgo *lista, int tamano);
void imprimirRiesgos(const Riesgo *lista, int tamano);
void borrarRiesgo(Riesgo **lista, int *tamano);
void guardarJSON(const Riesgo *lista, int tamano, const char *nombreArchivo);
void cargarJSON(Riesgo **lista, int *tamano, const char *nombreArchivo);
void limpiarBuffer(void);
void procesarNombreArchivo(char *archivoActual);

int main(void) {
    Riesgo *lista = NULL;
    int tamano = 0;
    int opcion;
    char archivoActual[MAX_RUTA] = "riesgos_mosler.json";

    do {
        printf("\n==========================================\n");
        printf("    GESTION DE RIESGOS - METODO MOSLER\n");
        printf("==========================================\n");


        printf("1. Crear riesgo\n");
        printf("2. Modificar parametros de un riesgo\n");
        printf("3. Calcular/Recalcular riesgos\n");
        printf("4. Imprimir los riesgos\n");
        printf("5. Borrar riesgo\n");
        printf("6. Seleccionar/Cargar desde archivo JSON\n");
        printf("7. Crear/Guardar en archivo JSON especificado\n");
        printf("8. Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            limpiarBuffer();
            printf("Entrada invalida. Intente de nuevo.\n");
            continue;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1:
                crearRiesgo(&lista, &tamano);
                break;
            case 2:
                modificarRiesgo(lista, tamano);
                break;
            case 3:
                calcularTodosLosRiesgos(lista, tamano);
                printf(">> Todos los riesgos recalculados correctamente.\n");
                break;
            case 4:
                imprimirRiesgos(lista, tamano);
                break;
            case 5:
                borrarRiesgo(&lista, &tamano);
                break;
            case 6: {
                printf("Ingrese el nombre o ruta del archivo a cargar (ej. mis_datos): ");
                if (fgets(archivoActual, sizeof(archivoActual), stdin)) {
                    procesarNombreArchivo(archivoActual);
                    cargarJSON(&lista, &tamano, archivoActual);
                }
                break;
            }
            case 7: {
                printf("Ingrese el nombre o ruta del archivo para guardar (ej. mis_datos): ");
                if (fgets(archivoActual, sizeof(archivoActual), stdin)) {
                    procesarNombreArchivo(archivoActual);
                    guardarJSON(lista, tamano, archivoActual);
                }
                break;
            }
            case 8:
                printf("Liberando memoria dinamica y saliendo...\n");
                free(lista);
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 8);

    return 0;
}


void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void procesarNombreArchivo(char *archivoActual) {
    archivoActual[strcspn(archivoActual, "\n")] = 0; // Elimina el \n


    if(strlen(archivoActual) == 0) {
        strcpy(archivoActual, "riesgos_mosler.json");
        printf(">> Nombre vacio. Se usara por defecto: %s\n", archivoActual);
    }


    if(strstr(archivoActual, ".json") == NULL) {
        strcat(archivoActual, ".json");
    }
}


void calcularMoslerVideo(Riesgo *r) {
    int importancia_suceso = r->F * r->S;  // F x S
    int danos_ocasionados  = r->P * r->E;  // P x E

    r->C  = importancia_suceso + danos_ocasionados;
    r->PB = r->A * r->V;
    r->ER = r->C * r->PB;


    if (r->ER <= 250) {
        strcpy(r->clasificacion, "Muy Pequeno");
    } else if (r->ER <= 500) {
        strcpy(r->clasificacion, "Pequeno");
    } else if (r->ER <= 750) {
        strcpy(r->clasificacion, "Normal");
    } else if (r->ER <= 1000) {
        strcpy(r->clasificacion, "Grande");
    } else {
        strcpy(r->clasificacion, "Elevado");
    }
}

int pedirCriterio(const char *mensaje) {
    int val;
    do {
        printf("%s (1-5): ", mensaje);
        if (scanf("%d", &val) != 1) {
            limpiarBuffer();
            val = 0;
        }
    } while (val < 1 || val > 5);
    limpiarBuffer();
    return val;
}



void crearRiesgo(Riesgo **lista, int *tamano) {
    Riesgo *temp = realloc(*lista, (*tamano + 1) * sizeof(Riesgo));
    if (!temp) {
        printf("Error: No se pudo asignar memoria.\n");
        return;
    }
    *lista = temp;
    Riesgo *r = &((*lista)[*tamano]);

    r->id = *tamano + 1;
    printf("\n--- Crear Nuevo Riesgo (ID: %d) ---\n", r->id);
    printf("Nombre/Descripcion del Riesgo: ");
    fgets(r->nombre, sizeof(r->nombre), stdin);
    r->nombre[strcspn(r->nombre, "\n")] = 0;

    printf("\nValoracion de Criterios (1-5):\n");
    r->F = pedirCriterio("F - Funcion (Gravedad del dano)");
    r->S = pedirCriterio("S - Sustitucion (Dificultad de reemplazo)");
    r->P = pedirCriterio("P - Profundidad (Afectacion psicologica)");
    r->E = pedirCriterio("E - Extension (Alcance territorial)");
    r->A = pedirCriterio("A - Agresion (Probabilidad de manifestacion)");
    r->V = pedirCriterio("V - Vulnerabilidad (Probabilidad de danos)");

    calcularMoslerVideo(r);
    (*tamano)++;
    printf(">> Riesgo agregado exitosamente. ER = %d (%s)\n", r->ER, r->clasificacion);
}

void modificarRiesgo(Riesgo *lista, int tamano) {
    if (tamano == 0) {
        printf(">> No hay riesgos registrados.\n");
        return;
    }

    int id;
    printf("Ingrese el ID del riesgo a modificar: ");
    if (scanf("%d", &id) != 1) {
        limpiarBuffer();
        printf("ID invalido.\n");
        return;
    }
    limpiarBuffer();

    int idx = -1;
    for (int i = 0; i < tamano; i++) {
        if (lista[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf(">> No se encontro el riesgo con ID %d.\n", id);
        return;
    }

    Riesgo *r = &lista[idx];
    printf("\nModificando riesgo ID %d: %s\n", r->id, r->nombre);
    printf("Nuevo nombre (Enter para mantener '%s'): ", r->nombre);

    char tempNombre[MAX_NOMBRE];
    fgets(tempNombre, sizeof(tempNombre), stdin);
    tempNombre[strcspn(tempNombre, "\n")] = 0;
    if (strlen(tempNombre) > 0) {
        strcpy(r->nombre, tempNombre);
    }

    r->F = pedirCriterio("F - Funcion");
    r->S = pedirCriterio("S - Sustitucion");
    r->P = pedirCriterio("P - Profundidad");
    r->E = pedirCriterio("E - Extension");
    r->A = pedirCriterio("A - Agresion");
    r->V = pedirCriterio("V - Vulnerabilidad");

    calcularMoslerVideo(r);
    printf(">> Riesgo actualizado correctamente.\n");
}

void calcularTodosLosRiesgos(Riesgo *lista, int tamano) {
    for (int i = 0; i < tamano; i++) {
        calcularMoslerVideo(&lista[i]);
    }
}

void imprimirRiesgos(const Riesgo *lista, int tamano) {
    if (tamano == 0) {
        printf(">> No hay riesgos en memoria. Crea uno o carga un archivo.\n");
        return;
    }

    printf("\n%-4s | %-20s | %-12s | %-4s | %-4s | %-5s | %-12s\n",
           "ID", "Nombre", "F S P E A V", "C", "PB", "ER", "Clasificacion");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < tamano; i++) {
        const Riesgo *r = &lista[i];
        printf("%-4d | %-20.20s | %d %d %d %d %d %d  | %-4d | %-4d | %-5d | %-12s\n",
               r->id, r->nombre, r->F, r->S, r->P, r->E, r->A, r->V,
               r->C, r->PB, r->ER, r->clasificacion);
    }
}

void borrarRiesgo(Riesgo **lista, int *tamano) {
    if (*tamano == 0) {
        printf(">> No hay riesgos para eliminar.\n");
        return;
    }

    int id;
    printf("Ingrese el ID del riesgo a eliminar: ");
    if (scanf("%d", &id) != 1) {
        limpiarBuffer();
        printf("ID invalido.\n");
        return;
    }
    limpiarBuffer();

    int idx = -1;
    for (int i = 0; i < *tamano; i++) {
        if ((*lista)[i].id == id) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf(">> Riesgo no encontrado.\n");
        return;
    }


    for (int i = idx; i < *tamano - 1; i++) {
        (*lista)[i] = (*lista)[i + 1];
        (*lista)[i].id = i + 1;
    }

    (*tamano)--;
    if (*tamano == 0) {
        free(*lista);
        *lista = NULL;
    } else {
        Riesgo *temp = realloc(*lista, (*tamano) * sizeof(Riesgo));
        if (temp) *lista = temp;
    }

    printf(">> Riesgo borrado y memoria reubicada.\n");
}



void guardarJSON(const Riesgo *lista, int tamano, const char *nombreArchivo) {
    FILE *fp = fopen(nombreArchivo, "w");
    if (!fp) {
        printf("\n[ERROR CRITICO]: No se pudo guardar el archivo '%s'.\n", nombreArchivo);
        printf("Causas posibles:\n");
        printf("1. La ruta especificada no existe (las carpetas deben estar creadas).\n");
        printf("2. No tienes permisos de escritura en ese directorio.\n");
        printf("3. El nombre del archivo contiene caracteres prohibidos (ej: \\ / : * ? \" < > |).\n\n");
        return;
    }

    fprintf(fp, "[\n");
    for (int i = 0; i < tamano; i++) {
        const Riesgo *r = &lista[i];
        fprintf(fp, "  {\n");
        fprintf(fp, "    \"id\": %d,\n", r->id);
        fprintf(fp, "    \"nombre\": \"%s\",\n", r->nombre);
        fprintf(fp, "    \"F\": %d,\n", r->F);
        fprintf(fp, "    \"S\": %d,\n", r->S);
        fprintf(fp, "    \"P\": %d,\n", r->P);
        fprintf(fp, "    \"E\": %d,\n", r->E);
        fprintf(fp, "    \"A\": %d,\n", r->A);
        fprintf(fp, "    \"V\": %d,\n", r->V);
        fprintf(fp, "    \"C\": %d,\n", r->C);
        fprintf(fp, "    \"PB\": %d,\n", r->PB);
        fprintf(fp, "    \"ER\": %d,\n", r->ER);
        fprintf(fp, "    \"clasificacion\": \"%s\"\n", r->clasificacion);
        fprintf(fp, "  }%s\n", (i < tamano - 1) ? "," : "");
    }
    fprintf(fp, "]\n");

    fclose(fp);
    printf("\n>> EXITO: Datos guardados correctamente en '%s'.\n", nombreArchivo);
}

void cargarJSON(Riesgo **lista, int *tamano, const char *nombreArchivo) {
    FILE *fp = fopen(nombreArchivo, "r");
    if (!fp) {
        printf("\n[ERROR]: No existe el archivo '%s' o no se encontro en esta ubicacion.\n", nombreArchivo);
        return;
    }

    if (*lista) {
        free(*lista);
        *lista = NULL;
    }
    *tamano = 0;

    char linea[512];
    Riesgo r;
    memset(&r, 0, sizeof(Riesgo));

    while (fgets(linea, sizeof(linea), fp)) {
        if (strstr(linea, "\"id\":")) {
            sscanf(linea, " \"id\": %d,", &r.id);
        } else if (strstr(linea, "\"nombre\":")) {
            char *start = strchr(linea, ':');
            if (start) {
                sscanf(start, ": \"%[^\"]\",", r.nombre);
            }
        } else if (strstr(linea, "\"F\":")) {
            sscanf(linea, " \"F\": %d,", &r.F);
        } else if (strstr(linea, "\"S\":")) {
            sscanf(linea, " \"S\": %d,", &r.S);
        } else if (strstr(linea, "\"P\":")) {
            sscanf(linea, " \"P\": %d,", &r.P);
        } else if (strstr(linea, "\"E\":")) {
            sscanf(linea, " \"E\": %d,", &r.E);
        } else if (strstr(linea, "\"A\":")) {
            sscanf(linea, " \"A\": %d,", &r.A);
        } else if (strstr(linea, "\"V\":")) {
            sscanf(linea, " \"V\": %d,", &r.V);
        } else if (strstr(linea, "}") || strstr(linea, "},")) {
            if (r.id > 0) {
                calcularMoslerVideo(&r);
                Riesgo *temp = realloc(*lista, (*tamano + 1) * sizeof(Riesgo));
                if (temp) {
                    *lista = temp;
                    (*lista)[*tamano] = r;
                    (*tamano)++;
                }
                memset(&r, 0, sizeof(Riesgo));
            }
        }
    }

    fclose(fp);
    printf("\n>> EXITO: Se cargaron %d riesgos desde '%s'.\n", *tamano, nombreArchivo);
}
