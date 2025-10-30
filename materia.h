#ifndef MATERIAS_H
#define MATERIAS_H

// Tamaño máximo para el nombre de la materia
#define MAX_NOMBRE 100

// Estructura Materia
typedef struct
{
    int id;
    char nombre[MAX_NOMBRE];
} Materia;

// Estructura Sistema
typedef struct
{
    Materia *materias;    // Arreglo dinámico de materias
    int cantidadMaterias; // Cantidad de materias registradas
} Sistema;

// =======================================================
// Prototipos de funciones de materias
// =======================================================

// Alta, baja y modificación
void altaMateria(Sistema *sistema);
void bajaMateria(Sistema *sistema);
void modificarMateriaSistema(Sistema *sistema);
void listarMaterias(Sistema *sistema);

// Funciones dummy
void inscribirEnMateria(Sistema *sistema);
void rendirMateria(Sistema *sistema);
void verNotasEstudiante(Sistema *sistema);

#endif // MATERIAS_H
