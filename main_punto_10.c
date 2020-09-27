#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"
//10) Corte de Control: Del enunciado 1 realizar el informe de promedio de notas, agrupado por alumnos y facultad.

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



int main()
{
    //Apareo de archivos
    FILE *arch;
    arch = fopen("Alumnos.dat","rb+");
    fclose(arch);
    return 0;
}

void promedios(FILE *arch)
{
    regNotas actual;
    int codFacul,legajo,contAlumno,contFacultad;
    float acumAlumno,acumFacultad;
    if (arch!=NULL)
    {
        fseek(arch,0,0);
        fread(&actual,sizeof(regNotas),1,arch);
        acumAlumno = 0;
        acumFacultad = 0;
        contAlumno = 0;
        contFacultad = 0;
        while (!feof(arch))
        {
            strcpy(codFacul, actual.facultad);
            printf("\nFacultad: %d",codFacul);
            while (!feof(arch) && strcmp(actual.facultad,codFacul)==0) {
                contFacultad++;
                legajo = actual.alumno;
                printf("\n\tLegajo: %d",legajo);
                while (!feof(arch) && strcmp(actual.facultad,codFacul)==0 && (actual.alumno == legajo))
                {
                    acumAlumno+=actual.nota;
                    contAlumno++;
                    fread(&actual,sizeof(regNotas),1,arch);
                }
                acumFacultad+=acumAlumno;
                if (contAlumno!=0)
                    printf("\nPromedio del alumno: %0.4f",acumAlumno/contAlumno);
                acumAlumno=0;
                contAlumno=0;
            }
            if (contFacultad!=0)
                printf("\nPromedio de la facultad: %.4f",acumFacultad/contFacultad);
            acumFacultad=0;
            contFacultad=0;
        }
    }
    else
        printf("Archivo no existe o está vacio");
}



