#include <stdio.h>
#include <stdlib.h>

/*
Enunciado 1

Se quiere registrar todas las notas de un alumno de una facultad.
Para esto se arma un registro con:
Código de la Universidad,
Código de Facultad,
Código de la Asignatura,
Legajo del Alumno,
Edad al momento de rendir,
Código del Docente a cargo,
Nota y Observaciones.

*/
typedef char codFac[7];// Codigo a nivel nacional
typedef char codUni[3];// Codigo a nivel local
typedef unsigned int codMat;// Igual al Siu Guarani
typedef unsigned int legAlum;//
typedef char t_edad[9] ;//
typedef char codDoc[6];// Codigo de docente a nivel nacional
typedef unsigned int t_nota;
typedef char t_obser[200];

typedef struct{
    codFac facultad;
    codUni universidad;
    codMat materia;
    legAlum alumno;
    t_edad edad;
    codDoc docente;
    t_nota nota;
    t_obser observaciones;
}regNotas;

