#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <stdlib.h>

// =======================================================
// Estructuras
// =======================================================
typedef struct
{
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
} Estudiante;

typedef struct
{
    int id;
    char nombre[50];
} Materia;

typedef struct
{
    Estudiante *estudiantes;
    Materia *materias;
    int cantidadEstudiantes;
    int cantidadMaterias;
} Sistema;

// =======================================================
// Crear / liberar sistema
// =======================================================
Sistema *crearSistema();
void liberarSistema(Sistema *sistema);

// =======================================================
// Guardar / cargar estudiantes
// =======================================================
void guardarEstudiantes(Sistema *sistema);
void cargarEstudiantes(Sistema *sistema);

// =======================================================
// Gestión de estudiantes
// =======================================================
void altaEstudiante(Sistema *sistema);
void bajaEstudiante(Sistema *sistema);
void modificarEstudianteSistema(Sistema *sistema);
void listarEstudiantes(Sistema *sistema);

// =======================================================
// Búsquedas y filtros
// =======================================================
void buscarEstudiantePorNombre(Sistema *sistema);
void buscarEstudiantePorApellido(Sistema *sistema);
void listarEstudiantesPorRangoEdad(Sistema *sistema);

// =======================================================
// Materias (sin implementar aún)
// =======================================================
void altaMateria(Sistema *sistema);
void bajaMateria(Sistema *sistema);
void modificarMateriaSistema(Sistema *sistema);
void listarMaterias(Sistema *sistema);
void inscribirEnMateria(Sistema *sistema);
void rendirMateria(Sistema *sistema);
void verNotasEstudiante(Sistema *sistema);

#endif // SISTEMA_H
