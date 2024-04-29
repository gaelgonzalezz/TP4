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

    personas[numPersonas++] = p;
    printf("Datos ingresados correctamente.\n");
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

int main() {
    int opcion;

    do {
        printf("\n1. Ingresar datos\n2. Buscar por DNI\n3. Salir\n");
        printf("Ingrese una opcion: ");
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
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 3);

    return 0;
}
