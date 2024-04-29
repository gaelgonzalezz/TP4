#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERSONAS 100

struct Persona {
    char nombre[50];
    char apellido[50];
    int dni;
};

struct Persona personas[MAX_PERSONAS];
int numPersonas = 0;

int existePersona(const char *nombre, const char *apellido, int dni) {
    for (int i = 0; i < numPersonas; i++) {
        if (strcmp(personas[i].nombre, nombre) == 0 &&
            strcmp(personas[i].apellido, apellido) == 0 &&
            personas[i].dni == dni) {
            return 1;
        }
    }
    return 0;
}

void ingresarDatos() {
    struct Persona p;

    printf("Ingrese el nombre: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);
    p.nombre[strcspn(p.nombre, "\n")] = '\0';

    printf("Ingrese el apellido: ");
    fgets(p.apellido, sizeof(p.apellido), stdin);
    p.apellido[strcspn(p.apellido, "\n")] = '\0';

    printf("Ingrese el DNI: ");
    scanf("%d", &p.dni);
    getchar();

    if (existePersona(p.nombre, p.apellido, p.dni)) {
        printf("Ya existe una persona con esos datos.\n");
    } else {
        personas[numPersonas++] = p;
        printf("Datos ingresados correctamente.\n");
    }
}

void buscarPorDNI() {
    int dni, encontrado = 0;

    printf("Ingrese el DNI a buscar: ");
    scanf("%d", &dni);
    getchar();

    for (int i = 0; i < numPersonas; i++) {
        if (personas[i].dni == dni) {
            printf("Nombre: %s\nApellido: %s\n", personas[i].nombre, personas[i].apellido);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontro el DNI\n");
    }
}

void buscarPorNombreYApellido() {
    char nombre[50], apellido[50];
    int encontrado = 0;

    printf("Ingrese el nombre a buscar: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    printf("Ingrese el apellido a buscar: ");
    fgets(apellido, sizeof(apellido), stdin);
    apellido[strcspn(apellido, "\n")] = '\0';

    for (int i = 0; i < numPersonas; i++) {
        if (strcmp(personas[i].nombre, nombre) == 0 && strcmp(personas[i].apellido, apellido) == 0) {
            printf("DNI: %d\n", personas[i].dni);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("No se encontro la persona\n");
    }
}

void ordenarPorNombreYApellido() {
    struct Persona temp;
    for (int i = 0; i < numPersonas - 1; i++) {
        for (int j = 0; j < numPersonas - i - 1; j++) {
            if (strcmp(personas[j].apellido, personas[j + 1].apellido) > 0 ||
                (strcmp(personas[j].apellido, personas[j + 1].apellido) == 0 &&
                 strcmp(personas[j].nombre, personas[j + 1].nombre) > 0)) {
                temp = personas[j];
                personas[j] = personas[j + 1];
                personas[j + 1] = temp;
            }
        }
    }
}

void ordenarPorDNI() {
    struct Persona temp;
    for (int i = 0; i < numPersonas - 1; i++) {
        for (int j = 0; j < numPersonas - i - 1; j++) {
            if (personas[j].dni > personas[j + 1].dni) {
                temp = personas[j];
                personas[j] = personas[j + 1];
                personas[j + 1] = temp;
            }
        }
    }
}

void mostrarDatos() {
    char opcion;

    printf("¿Cómo desea ordenar los datos?\n");
    printf("a. Por nombre y apellido\n");
    printf("b. Por DNI\n");
    printf("Ingrese una opcion: ");
    scanf("%c", &opcion);
    getchar();

    switch (opcion) {
        case 'a':
            ordenarPorNombreYApellido();
            break;
        case 'b':
            ordenarPorDNI();
            break;
        default:
            printf("Opcion invalida\n");
            return;
    }

    printf("Datos ordenados:\n");
    for (int i = 0; i < numPersonas; i++) {
        printf("Nombre: %s\nApellido: %s\nDNI: %d\n\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
}

void guardarDatos() {
    FILE *archivo = fopen("personas_modificadas.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }

    fwrite(personas, sizeof(struct Persona), numPersonas, archivo);
    fclose(archivo);
    printf("Datos guardados en personas_modificadas.dat\n");
}

void cargarDatos() {
    FILE *archivo = fopen("personas_modificadas.dat", "rb");
    if (archivo == NULL) {
        printf("No se encontro el archivo\n");
        return;
    }

    numPersonas = 0;
    struct Persona p;
    while (fread(&p, sizeof(struct Persona), 1, archivo) == 1) {
        personas[numPersonas++] = p;
    }
    fclose(archivo);
    printf("Datos cargados desde personas_modificadas.dat\n");
}

int main() {
    int opcion;

    do {
        printf("\n1. Ingresar datos\n2. Buscar por DNI\n3. Buscar por nombre y apellido\n4. Mostrar datos\n5. Guardar datos\n6. Cargar datos\n7. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                ingresarDatos();
                break;
            case 2:
                buscarPorDNI();
                break;
            case 3:
                buscarPorNombreYApellido();
                break;
            case 4:
                mostrarDatos();
                break;
            case 5:
                guardarDatos();
                break;
            case 6:
                cargarDatos();
                break;
            case 7:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 7);

    return 0;
}
