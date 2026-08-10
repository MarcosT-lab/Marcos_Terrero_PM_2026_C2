#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO "vehiculos.dat"
#define MAX_NOMBRE 50

typedef struct {
    int id;
    char nombre[MAX_NOMBRE];
    double costo_vehiculo;
    double valor_residual;
    int vida_util_anos;
    double km_anuales;
    double seguro_anual;
    double mantenimiento_anual;
    double neumaticos_anual;
    double consumo_ciudad;
    double consumo_autopista;
} Vehiculo;


typedef struct {
    double precio_combustible;
} Config;


void guardar_configuracion(Config cfg);
Config cargar_configuracion();
void crear_vehiculo();
void listar_vehiculos();
void borrar_vehiculo();
void modificar_vehiculo();
void calcular_viaje();
void modificar_precio_combustible();
void calcular_costos_vehiculo(Vehiculo v, Config cfg);

int main() {
    int opcion;
    Config cfg = cargar_configuracion();

    do {
        printf("\n==========================================\n");
        printf("EL MOCHO AUTO: GESTION DE COSTOS DE VEHICULOS\n");
        printf("==========================================\n");
        printf("Precio actual del combustible: $%.2f / Litro\n", cfg.precio_combustible);
        printf("------------------------------------------\n");
        printf("1. Crear vehiculo y guardar\n");
        printf("2. Listar vehiculos\n");
        printf("3. Modificar parametros de un vehiculo\n");
        printf("4. Borrar vehiculo\n");
        printf("5. Calcular costo de un viaje\n");
        printf("6. Modificar precio del combustible\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: crear_vehiculo(); break;
            case 2: listar_vehiculos(); break;
            case 3: modificar_vehiculo(); break;
            case 4: borrar_vehiculo(); break;
            case 5: calcular_viaje(); break;
            case 6:
                modificar_precio_combustible();
                cfg = cargar_configuracion();
                break;
            case 0: printf("\nSaliendo del programa!\n"); break;
            default: printf("\nOpcion no valida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    return 0;
}


void guardar_configuracion(Config cfg) {
    FILE *f = fopen("config.dat", "wb");
    if (f) {
        fwrite(&cfg, sizeof(Config), 1, f);
        fclose(f);
    }
}

Config cargar_configuracion() {
    Config cfg = {1.50};
    FILE *f = fopen("config.dat", "rb");
    if (f) {
        fread(&cfg, sizeof(Config), 1, f);
        fclose(f);
    } else {
        guardar_configuracion(cfg);
    }
    return cfg;
}

void modificar_precio_combustible() {
    Config cfg;
    printf("\n--- MODIFICAR PRECIO DE COMBUSTIBLE ---\n");
    printf("Ingrese el nuevo precio por litro de combustible: ");
    scanf("%lf", &cfg.precio_combustible);
    guardar_configuracion(cfg);
    printf("Precio del combustible actualizado con exito!\n");
}


void crear_vehiculo() {
    FILE *f = fopen(ARCHIVO, "ab+");
    if (!f) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    Vehiculo v;

    fseek(f, 0, SEEK_END);
    v.id = (int)(ftell(f) / sizeof(Vehiculo)) + 1;

    printf("\n--- CREAR NUEVO VEHICULO (ID: %d) ---\n", v.id);
    printf("Nombre / Modelo: ");
    fgets(v.nombre, MAX_NOMBRE, stdin);
    v.nombre[strcspn(v.nombre, "\n")] = 0;

    printf("Costo inicial del vehiculo ($): ");
    scanf("%lf", &v.costo_vehiculo);
    printf("Valor residual estimado ($): ");
    scanf("%lf", &v.valor_residual);
    printf("Vida util estimada (anos): ");
    scanf("%d", &v.vida_util_anos);
    printf("Kilometros recorridos al ano (promedio): ");
    scanf("%lf", &v.km_anuales);
    printf("Costo del seguro anual ($): ");
    scanf("%lf", &v.seguro_anual);
    printf("Gastos de mantenimiento anuales ($): ");
    scanf("%lf", &v.mantenimiento_anual);
    printf("Gastos de neumaticos anuales ($): ");
    scanf("%lf", &v.neumaticos_anual);
    printf("Consumo de combustible en CIUDAD (L/100km): ");
    scanf("%lf", &v.consumo_ciudad);
    printf("Consumo de combustible en AUTOPISTA (L/100km): ");
    scanf("%lf", &v.consumo_autopista);

    fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);

    printf("\nVehiculo '%s' creado y guardado con exito!\n", v.nombre);
}

void listar_vehiculos() {
    FILE *f = fopen(ARCHIVO, "rb");
    if (!f) {
        printf("\nNo hay vehiculos registrados.\n");
        return;
    }

    Vehiculo v;
    Config cfg = cargar_configuracion();

    printf("\n======================================================\n");
    printf("                LISTA DE VEHICULOS                    \n");
    printf("======================================================\n");

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        printf("\n[ID: %d] Modelo: %s\n", v.id, v.nombre);
        calcular_costos_vehiculo(v, cfg);
    }
    fclose(f);
}

void modificar_vehiculo() {
    FILE *f = fopen(ARCHIVO, "rb+");
    if (!f) {
        printf("\nNo hay vehiculos registrados.\n");
        return;
    }

    int id_buscar, encontrado = 0;
    Vehiculo v;

    printf("\nIngrese el ID del vehiculo a modificar: ");
    scanf("%d", &id_buscar);
    getchar();

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id_buscar) {
            encontrado = 1;
            printf("\n--- MODIFICANDO VEHICULO ID: %d (%s) ---\n", v.id, v.nombre);
            printf("Nuevo Nombre / Modelo: ");
            fgets(v.nombre, MAX_NOMBRE, stdin);
            v.nombre[strcspn(v.nombre, "\n")] = 0;

            printf("Nuevo Costo inicial ($): ");
            scanf("%lf", &v.costo_vehiculo);
            printf("Nuevo Valor residual ($): ");
            scanf("%lf", &v.valor_residual);
            printf("Nueva Vida util (anos): ");
            scanf("%d", &v.vida_util_anos);
            printf("Nuevos Km anuales: ");
            scanf("%lf", &v.km_anuales);
            printf("Nuevo Seguro anual ($): ");
            scanf("%lf", &v.seguro_anual);
            printf("Nuevo Mantenimiento anual ($): ");
            scanf("%lf", &v.mantenimiento_anual);
            printf("Nuevo Costo de neumaticos anual ($): ");
            scanf("%lf", &v.neumaticos_anual);
            printf("Nuevo Consumo en CIUDAD (L/100km): ");
            scanf("%lf", &v.consumo_ciudad);
            printf("Nuevo Consumo en AUTOPISTA (L/100km): ");
            scanf("%lf", &v.consumo_autopista);

            fseek(f, -((long)sizeof(Vehiculo)), SEEK_CUR);
            fwrite(&v, sizeof(Vehiculo), 1, f);
            printf("\nVehiculo actualizado con exito!\n");
            break;
        }
    }

    if (!encontrado) printf("\nNo se encontro un vehiculo con ID %d.\n", id_buscar);
    fclose(f);
}

void borrar_vehiculo() {
    FILE *f = fopen(ARCHIVO, "rb");
    if (!f) {
        printf("\nNo hay vehiculos registrados.\n");
        return;
    }

    FILE *f_temp = fopen("temp.dat", "wb");
    if (!f_temp) {
        fclose(f);
        return;
    }

    int id_borrar, borrado = 0;
    Vehiculo v;

    printf("\nIngrese el ID del vehiculo a eliminar: ");
    scanf("%d", &id_borrar);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id_borrar) {
            borrado = 1;
        } else {
            fwrite(&v, sizeof(Vehiculo), 1, f_temp);
        }
    }

    fclose(f);
    fclose(f_temp);

    remove(ARCHIVO);
    rename("temp.dat", ARCHIVO);

    if (borrado)
        printf("\nVehiculo eliminado correctamente!\n");
    else
        printf("\nNo se encontro un vehiculo con ID %d.\n", id_borrar);
}


void calcular_costos_vehiculo(Vehiculo v, Config cfg) {

    double amortizacion_anual = (v.costo_vehiculo - v.valor_residual) / v.vida_util_anos;
    double amortizacion_total_vida_util = amortizacion_anual * v.vida_util_anos;


    double mantenimiento_total = v.mantenimiento_anual * v.vida_util_anos;


    double costos_fijos_anuales = amortizacion_anual + v.seguro_anual + v.mantenimiento_anual + v.neumaticos_anual;
    double costo_fijo_por_km = (v.km_anuales > 0) ? (costos_fijos_anuales / v.km_anuales) : 0;


    double costo_comb_ciudad_km = (v.consumo_ciudad / 100.0) * cfg.precio_combustible;
    double costo_comb_autopista_km = (v.consumo_autopista / 100.0) * cfg.precio_combustible;


    double costo_total_ciudad_km = costo_fijo_por_km + costo_comb_ciudad_km;
    double costo_total_autopista_km = costo_fijo_por_km + costo_comb_autopista_km;

    printf("------------------------------------------------------\n");
    printf("   * Amortizacion anual: $%.2f (Total en vida util: $%.2f)\n", amortizacion_anual, amortizacion_total_vida_util);
    printf("   * Mantenimiento estimado en vida util: $%.2f\n", mantenimiento_total);
    printf("   * Costo fijo prorrateado (sin combustible): $%.3f / km\n", costo_fijo_por_km);
    printf("   * Costo total por km en CIUDAD:    $%.3f / km\n", costo_total_ciudad_km);
    printf("   * Costo total por km en AUTOPISTA: $%.3f / km\n", costo_total_autopista_km);
    printf("------------------------------------------------------\n");
}

void calcular_viaje() {
    FILE *f = fopen(ARCHIVO, "rb");
    if (!f) {
        printf("\nNo hay vehiculos registrados.\n");
        return;
    }

    int id_buscar, encontrado = 0;
    Vehiculo v;

    printf("\nIngrese el ID del vehiculo a utilizar: ");
    scanf("%d", &id_buscar);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (v.id == id_buscar) {
            encontrado = 1;
            break;
        }
    }
    fclose(f);

    if (!encontrado) {
        printf("\nNo se encontro el vehiculo.\n");
        return;
    }

    double km_ciudad, km_autopista;
    Config cfg = cargar_configuracion();

    printf("\n--- CALCULAR COSTO DE VIAJE (%s) ---\n", v.nombre);
    printf("Kilometros a recorrer en CIUDAD: ");
    scanf("%lf", &km_ciudad);
    printf("Kilometros a recorrer en AUTOPISTA: ");
    scanf("%lf", &km_autopista);


    double litros_ciudad = (km_ciudad * v.consumo_ciudad) / 100.0;
    double litros_autopista = (km_autopista * v.consumo_autopista) / 100.0;
    double total_litros = litros_ciudad + litros_autopista;


    double costo_combustible = total_litros * cfg.precio_combustible;


    double costos_fijos_anuales = ((v.costo_vehiculo - v.valor_residual) / v.vida_util_anos)
                                 + v.seguro_anual + v.mantenimiento_anual + v.neumaticos_anual;
    double costo_fijo_km = (v.km_anuales > 0) ? (costos_fijos_anuales / v.km_anuales) : 0;
    double costo_desgaste_viaje = (km_ciudad + km_autopista) * costo_fijo_km;

    double costo_total_viaje = costo_combustible + costo_desgaste_viaje;

    printf("\n======================================================\n");
    printf("               RESUMEN DEL VIAJE                      \n");
    printf("======================================================\n");
    printf("* Distancia Total:            %.2f km (%.2f km Ciudad / %.2f km Autopista)\n",
           km_ciudad + km_autopista, km_ciudad, km_autopista);
    printf("* Consumo Total de Gasolina:  %.2f Litros\n", total_litros);
    printf("* Costo de Combustible:       $%.2f\n", costo_combustible);
    printf("* Costo de Desgaste y Fijos:  $%.2f\n", costo_desgaste_viaje);
    printf("------------------------------------------------------\n");
    printf("* COSTO REAL TOTAL DEL VIAJE: $%.2f\n", costo_total_viaje);
    printf("======================================================\n");
}
