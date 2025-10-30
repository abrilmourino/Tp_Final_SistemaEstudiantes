#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sistema.h"
#include "utils.h"

// =======================================================
// Función auxiliar: comparar cadenas sin distinguir mayúsculas
// =======================================================
int contieneCadenaIgnorandoMayusculas(const char *texto, const char *subcadena)
{
    if (!texto || !subcadena)
        return 0;

    char textoMin[100];
    char subMin[100];
    int i;

    for (i = 0; texto[i] && i < 99; i++)
        textoMin[i] = tolower((unsigned char)texto[i]);
    textoMin[i] = '\0';

    for (i = 0; subcadena[i] && i < 99; i++)
        subMin[i] = tolower((unsigned char)subcadena[i]);
    subMin[i] = '\0';

    return strstr(textoMin, subMin) != NULL;
}

// =======================================================
// FUNCIONES DE ARCHIVO
// =======================================================
void guardarEstudiantes(Sistema *sistema)
{
    if (!sistema)
        return;
    FILE *f = fopen("estudiantes.dat", "wb");
    if (!f)
    {
        printf("⚠️ No se pudo guardar el archivo de estudiantes.\n");
        return;
    }
    fwrite(&sistema->cantidadEstudiantes, sizeof(int), 1, f);
    fwrite(sistema->estudiantes, sizeof(Estudiante), sistema->cantidadEstudiantes, f);
    fclose(f);
    // printf("💾 Estudiantes guardados correctamente.\n");
}

void cargarEstudiantes(Sistema *sistema)
{
    if (!sistema)
        return;
    FILE *f = fopen("estudiantes.dat", "rb");
    if (!f)
    {
        sistema->estudiantes = NULL;
        sistema->cantidadEstudiantes = 0;
        return;
    }
    fread(&sistema->cantidadEstudiantes, sizeof(int), 1, f);
    if (sistema->cantidadEstudiantes > 0)
    {
        sistema->estudiantes = malloc(sistema->cantidadEstudiantes * sizeof(Estudiante));
        fread(sistema->estudiantes, sizeof(Estudiante), sistema->cantidadEstudiantes, f);
    }
    else
    {
        sistema->estudiantes = NULL;
    }
    fclose(f);
    printf("✅ Se cargaron %d estudiantes desde archivo.\n", sistema->cantidadEstudiantes);
}

// =======================================================
// CREAR Y LIBERAR SISTEMA
// =======================================================
Sistema *crearSistema()
{
    Sistema *s = malloc(sizeof(Sistema));
    if (!s)
        return NULL;

    s->cantidadEstudiantes = 0;
    s->cantidadMaterias = 0;
    s->estudiantes = NULL;
    s->materias = NULL;

    // Cargar datos desde archivo
    cargarEstudiantes(s);
    return s;
}

void liberarSistema(Sistema *sistema)
{
    if (!sistema)
        return;
    guardarEstudiantes(sistema); // Guardar automáticamente
    free(sistema->estudiantes);
    free(sistema->materias);
    free(sistema);
    printf("💾 Sistema guardado y liberado correctamente.\n");
}

// =======================================================
// GESTIÓN DE ESTUDIANTES
// =======================================================
void altaEstudiante(Sistema *sistema)
{
    if (!sistema)
        return;

    Estudiante nuevo;
    printf("Ingrese ID del estudiante: ");
    scanf("%d", &nuevo.id);
    limpiarBuffer();

    printf("Ingrese nombre: ");
    fgets(nuevo.nombre, sizeof(nuevo.nombre), stdin);
    nuevo.nombre[strcspn(nuevo.nombre, "\n")] = '\0';

    printf("Ingrese apellido: ");
    fgets(nuevo.apellido, sizeof(nuevo.apellido), stdin);
    nuevo.apellido[strcspn(nuevo.apellido, "\n")] = '\0';

    printf("Ingrese edad: ");
    scanf("%d", &nuevo.edad);
    limpiarBuffer();

    sistema->cantidadEstudiantes++;
    sistema->estudiantes = realloc(sistema->estudiantes, sistema->cantidadEstudiantes * sizeof(Estudiante));
    sistema->estudiantes[sistema->cantidadEstudiantes - 1] = nuevo;

    guardarEstudiantes(sistema); // Guardar inmediatamente
    printf("✅ Estudiante agregado correctamente.\n");
}

void listarEstudiantes(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    printf("\n=== LISTA DE ESTUDIANTES ===\n");
    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        Estudiante e = sistema->estudiantes[i];
        printf("ID: %d | %s %s | Edad: %d\n", e.id, e.nombre, e.apellido, e.edad);
    }
}

void bajaEstudiante(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes para eliminar.\n");
        return;
    }

    int id;
    printf("Ingrese ID del estudiante a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();

    int pos = -1;
    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        if (sistema->estudiantes[i].id == id)
        {
            pos = i;
            break;
        }
    }

    if (pos == -1)
    {
        printf("No se encontró estudiante con ese ID.\n");
        return;
    }

    for (int i = pos; i < sistema->cantidadEstudiantes - 1; i++)
    {
        sistema->estudiantes[i] = sistema->estudiantes[i + 1];
    }

    sistema->cantidadEstudiantes--;
    sistema->estudiantes = realloc(sistema->estudiantes, sistema->cantidadEstudiantes * sizeof(Estudiante));

    guardarEstudiantes(sistema);
    printf("✅ Estudiante eliminado correctamente.\n");
}

void modificarEstudianteSistema(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes para modificar.\n");
        return;
    }

    int id;
    printf("Ingrese ID del estudiante a modificar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        if (sistema->estudiantes[i].id == id)
        {
            printf("Modificar nombre (%s): ", sistema->estudiantes[i].nombre);
            fgets(sistema->estudiantes[i].nombre, 50, stdin);
            sistema->estudiantes[i].nombre[strcspn(sistema->estudiantes[i].nombre, "\n")] = '\0';

            printf("Modificar apellido (%s): ", sistema->estudiantes[i].apellido);
            fgets(sistema->estudiantes[i].apellido, 50, stdin);
            sistema->estudiantes[i].apellido[strcspn(sistema->estudiantes[i].apellido, "\n")] = '\0';

            printf("Modificar edad (%d): ", sistema->estudiantes[i].edad);
            scanf("%d", &sistema->estudiantes[i].edad);
            limpiarBuffer();

            guardarEstudiantes(sistema);
            printf("✅ Estudiante modificado correctamente.\n");
            return;
        }
    }

    printf("No se encontró estudiante con ese ID.\n");
}

// =======================================================
// FUNCIONES DE BÚSQUEDA Y FILTRO
// =======================================================
void buscarEstudiantePorNombre(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    char nombre[50];
    printf("Ingrese el nombre a buscar: ");
    fgets(nombre, sizeof(nombre), stdin);
    nombre[strcspn(nombre, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        if (contieneCadenaIgnorandoMayusculas(sistema->estudiantes[i].nombre, nombre))
        {
            printf("ID: %d | %s %s | Edad: %d\n",
                   sistema->estudiantes[i].id,
                   sistema->estudiantes[i].nombre,
                   sistema->estudiantes[i].apellido,
                   sistema->estudiantes[i].edad);
            encontrados++;
        }
    }

    if (!encontrados)
        printf("No se encontraron estudiantes con ese nombre.\n");
}

void buscarEstudiantePorApellido(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    char apellido[50];
    printf("Ingrese el apellido a buscar: ");
    fgets(apellido, sizeof(apellido), stdin);
    apellido[strcspn(apellido, "\n")] = '\0';

    int encontrados = 0;
    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        if (contieneCadenaIgnorandoMayusculas(sistema->estudiantes[i].apellido, apellido))
        {
            printf("ID: %d | %s %s | Edad: %d\n",
                   sistema->estudiantes[i].id,
                   sistema->estudiantes[i].nombre,
                   sistema->estudiantes[i].apellido,
                   sistema->estudiantes[i].edad);
            encontrados++;
        }
    }

    if (!encontrados)
        printf("No se encontraron estudiantes con ese apellido.\n");
}

void listarEstudiantesPorRangoEdad(Sistema *sistema)
{
    if (!sistema || sistema->cantidadEstudiantes == 0)
    {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    int min, max;
    printf("Ingrese edad mínima: ");
    scanf("%d", &min);
    printf("Ingrese edad máxima: ");
    scanf("%d", &max);
    limpiarBuffer();

    if (min > max)
    {
        printf("Error: la edad mínima no puede ser mayor que la máxima.\n");
        return;
    }

    int encontrados = 0;
    for (int i = 0; i < sistema->cantidadEstudiantes; i++)
    {
        int edad = sistema->estudiantes[i].edad;
        if (edad >= min && edad <= max)
        {
            printf("ID: %d | %s %s | Edad: %d\n",
                   sistema->estudiantes[i].id,
                   sistema->estudiantes[i].nombre,
                   sistema->estudiantes[i].apellido,
                   edad);
            encontrados++;
        }
    }

    if (!encontrados)
        printf("No se encontraron estudiantes en ese rango de edad.\n");
}

// =======================================================
// MATERIAS (aún sin implementar)
// =======================================================
/*void altaMateria(Sistema *sistema) { printf("(Función altaMateria sin implementar)\n"); }
void bajaMateria(Sistema *sistema) { printf("(Función bajaMateria sin implementar)\n"); }
void modificarMateriaSistema(Sistema *sistema) { printf("(Función modificarMateria sin implementar)\n"); }
void listarMaterias(Sistema *sistema) { printf("(Función listarMaterias sin implementar)\n"); }
void inscribirEnMateria(Sistema *sistema) { printf("(Función inscribirEnMateria sin implementar)\n"); }
void rendirMateria(Sistema *sistema) { printf("(Función rendirMateria sin implementar)\n"); }
void verNotasEstudiante(Sistema *sistema) { printf("(Función verNotasEstudiante sin implementar)\n"); }*/
