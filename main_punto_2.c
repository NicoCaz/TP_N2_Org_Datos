#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "situacion1.h"
#include "situacion2.h"


int altas(regNotas x);
int bajas(regNotas x);
int modificaciones(regNotas x);
void consulta(legAlum alumno);
float promedioA(legAlum alumno);
float promedioSA(legAlum alumno);
int canMaterias(legAlum alumno);
float promedioMat(codMat materia);

int main()
{
    printf("Hello world!\n");
    return 0;
}


int altas(regNotas notas){
    /*
        EN MI CASO DETERMINE QUE EL ARCHIVO ESTE ORDENADO POR ALUMNO PARA FACILITAR LA MAYORIA DE OPERACIONES

    */
    int resp=0;
    regNotas act;
    FILE * arch=fopen("original.dat","rb+");
    FILE * archFinal=fopen("Temp.temp","wb+");
     if(arch!=NULL)
     {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno < notas.alumno) // avanzo hasta encontrar el alumno, copiando todos los registros
        {
            fwrite(&act,sizeof(regNotas),1,archFinal);
            while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia<notas.materia)
            {
                fwrite(&act,sizeof(regNotas),1,archFinal);
                while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)<0)
                {
                    fwrite(&act,sizeof(regNotas),1,archFinal);
                    if (act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)==0)
                        resp=1;
                }
            }
        }
        fwrite(&notas,sizeof(regNotas),1,archFinal);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1)
            fwrite(&notas,sizeof(regNotas),1,archFinal);
    }
    else
        fwrite(&notas,sizeof(regNotas),1,archFinal);

    remove("original.dat");
    rename("Temp.temp","original.dat");
    fclose(arch);
    fclose(archFinal);
    return resp;
}

int bajas(regNotas notas){
    /*
       LAS UNICAS DIFERENCIAS CON EL DE BJAS ES:
                        *CUANDO LO ENCUENTRA NO LO COPIA EN EL NUEVO
                        *DEVUELVE 0 SI NO LO ENCUETRA
    */
    int resp=0;
    regNotas act;
    FILE * arch=fopen("original.dat","rb+");
    FILE * archFinal=fopen("Temp.temp","wb+");
     if(arch!=NULL)
     {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno < notas.alumno) // avanzo hasta encontrar el alumno, copiando todos los registros
        {
            fwrite(&act,sizeof(regNotas),1,archFinal);
            while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia<notas.materia)
            {
                fwrite(&act,sizeof(regNotas),1,archFinal);
                while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)<0)
                {
                    fwrite(&act,sizeof(regNotas),1,archFinal);
                    if (act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)==0)
                        resp=0;
                }
            }
        }
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1)
            fwrite(&notas,sizeof(regNotas),1,archFinal);
    }
    else
        fwrite(&notas,sizeof(regNotas),1,archFinal);

    remove("original.dat");
    rename("Temp.temp","original.dat");
    fclose(arch);
    fclose(archFinal);
    return resp;
}

int modificaciones(regNotas notas){
    /*
       LAS UNICAS DIFERENCIAS CON EL DE BJAS ES:
                        *CUANDO LO ENCUENTRA NO LO COPIA EN EL NUEVO
                        *DEVUELVE 0 SI NO LO ENCUETRA
    */
    int resp=0;
    regNotas act;
    FILE * arch=fopen("original.dat","rb+");
    FILE * archFinal=fopen("Temp.temp","wb+");
     if(arch!=NULL)
     {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno < notas.alumno) // avanzo hasta encontrar el alumno, copiando todos los registros
        {
            fwrite(&act,sizeof(regNotas),1,archFinal);
            while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia<notas.materia)
            {
                fwrite(&act,sizeof(regNotas),1,archFinal);
                while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)<0)
                {
                    if (act.alumno==notas.alumno && act.materia==notas.materia && strcmp(act.edad,notas.edad)==0) {
                        fwrite(&notas,sizeof(regNotas),1,archFinal);
                        resp=0;
                    } else
                        fwrite(&act,sizeof(regNotas),1,archFinal);
                }
            }
        }
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1)
            fwrite(&notas,sizeof(regNotas),1,archFinal);
    }
    else
        fwrite(&notas,sizeof(regNotas),1,archFinal);

    remove("original.dat");
    rename("Temp.temp","original.dat");
    fclose(arch);
    fclose(archFinal);
    return resp;
}


float promedioA(legAlum alumno){
    FILE * arch=fopen("original.dat","rb+");
    regNotas act;
    unsigned int cant=0;
    float acum=0;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno<=alumno)
            if (act.alumno==alumno) {
                cant++;
                acum+=act.nota;
            }
    }
    return (cant>0)?acum/cant:0 ;


}


float promedioSA(legAlum alumno){
    FILE * arch=fopen("original.dat","rb+");
    regNotas act;
    unsigned int cant=0;
    float acum=0;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno<=alumno)
            if (act.alumno==alumno && act.nota>=4) {
                cant++;
                acum+=act.nota;
            }
    }
    return (cant>0)?acum/cant:0 ;
}

int canMaterias(legAlum alumno){
    regNotas act;
    unsigned int cant=0,asignatura=0;
    FILE * arch=fopen("original.dat","rb+");
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1 && act.alumno<=alumno)
            if (act.alumno==alumno && act.materia !=asignatura) {
                asignatura=act.materia;
                cant++;
            }
    }
    return cant;


}


float promedioMat(codMat materia){
    regNotas act;
    unsigned int cant=0;
    float acum=0;
    FILE * arcj=fopen("original.dat","rb+");
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regNotas),1,arch)==1)
            if (act.materia==materia) {
                cant++;
                acum+=act.nota;
            }
    }
    return (cant>0)?acum/cant:0;
}

