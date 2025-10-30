#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materia.h"
#include "utils.h"

// =======================================================
// Alta materia
// =======================================================
void altaMateria(Sistema *sistema)
{
    if (!sistema)
        return;

    Materia nueva;
    printf("Ingrese ID de la materia: ");
    scanf("%d", &nueva.id);
    limpiarBuffer();

    printf("Ingrese nombre de la materia: ");
    fgets(nueva.nombre, sizeof(nueva.nombre), stdin);
    nueva.nombre[strcspn(nueva.nombre, "\n")] = '\0';

    sistema->cantidadMaterias++;
    sistema->materias = realloc(sistema->materias, sistema->cantidadMaterias * sizeof(Materia));
    sistema->materias[sistema->cantidadMaterias - 1] = nueva;

    printf("✅ Materia agregada correctamente.\n");
}

// =======================================================
// Baja materia
// =======================================================
void bajaMateria(Sistema *sistema)
{
    if (!sistema || sistema->cantidadMaterias == 0)
    {
        printf("No hay materias para eliminar.\n");
        return;
    }

    int id;
    printf("Ingrese ID de la materia a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();

    int pos = -1;
    for (int i = 0; i < sistema->cantidadMaterias; i++)
        if (sistema->materias[i].id == id)
        {
            pos = i;
            break;
        }

    if (pos == -1)
    {
        printf("No se encontró materia con ese ID.\n");
        return;
    }

    for (int i = pos; i < sistema->cantidadMaterias - 1; i++)
        sistema->materias[i] = sistema->materias[i + 1];

    sistema->cantidadMaterias--;
    sistema->materias = realloc(sistema->materias, sistema->cantidadMaterias * sizeof(Materia));

    printf("✅ Materia eliminada correctamente.\n");
}

// =======================================================
// Modificar materia
// =======================================================
void modificarMateriaSistema(Sistema *sistema)
{
    if (!sistema || sistema->cantidadMaterias == 0)
    {
        printf("No hay materias para modificar.\n");
        return;
    }

    int id;
    printf("Ingrese ID de la materia a modificar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < sistema->cantidadMaterias; i++)
    {
        if (sistema->materias[i].id == id)
        {
            printf("Modificar nombre (%s): ", sistema->materias[i].nombre);
            fgets(sistema->materias[i].nombre, sizeof(sistema->materias[i].nombre), stdin);
            sistema->materias[i].nombre[strcspn(sistema->materias[i].nombre, "\n")] = '\0';

            printf("✅ Materia modificada correctamente.\n");
            return;
        }
    }

    printf("No se encontró materia con ese ID.\n");
}

// =======================================================
// Listar materias
// =======================================================
void listarMaterias(Sistema *sistema)
{
    if (!sistema || sistema->cantidadMaterias == 0)
    {
        printf("No hay materias registradas.\n");
        return;
    }

    printf("\n=== LISTA DE MATERIAS ===\n");
    for (int i = 0; i < sistema->cantidadMaterias; i++)
    {
        Materia m = sistema->materias[i];
        printf("ID: %d | %s\n", m.id, m.nombre);
    }
}

// =======================================================
// Funciones dummy
// =======================================================
void inscribirEnMateria(Sistema *sistema)
{
    printf("Función de inscripción aún no implementada.\n");
}

void rendirMateria(Sistema *sistema)
{
    printf("Función de rendir materia aún no implementada.\n");
}

void verNotasEstudiante(Sistema *sistema)
{
    printf("Función de ver notas aún no implementada.\n");
}
