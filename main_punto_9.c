#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "string.h"
//9) Corte de Control: Del enunciado 2 realizar el informe de ventas por local agrupados por provincia y por ciudad.

typedef char  t_codProv[4];
typedef char  t_codCiu[6];
typedef char  t_codLoc[4];
typedef char  t_legVen[5];
typedef char  t_codFac[11];
typedef char  t_codPro[11] ;
typedef unsigned int t_can;
typedef unsigned int  t_valUni;
typedef unsigned int  t_total;
typedef char  t_obs[200];

typedef struct{
    t_codProv codPro;
    t_codCiu  ciudad;
    t_codLoc  local;
    t_legVen  vendedor;
    t_codFac  factura;
    t_codPro  producto;
    t_can     cantidad;
    t_valUni  valorUnitario;
    t_total   total;
    t_obs     observaciones;
}regCompras;



int main()
{
    //Apareo de archivos
    FILE *arch;
    arch = fopen("Libro_Contable.dat","rb+");
    fclose(arch);

    return 0;
}


void reporteVentas(FILE *arch)
{
    regCompras actual;
    int codPro,codCiu,Local;
    float acumProv,acumCiudad,acumLocal;
    if (arch!=NULL)
    {
        fseek(arch,0,0);
        fread(&actual,sizeof(regCompras),1,arch);
        acumProv = 0;
        acumCiudad = 0;
        acumLocal = 0;
        while (!feof(arch))
        {
            codPro = actual.codPro;
            printf("\nProvincia: %d",codPro);
            while (!feof(arch) && (actual.codPro == codPro))
            {
                codCiu = actual.ciudad;
                printf("\n\tCiudad: %d",codCiu);
                while (!feof(arch) && (actual.codPro == codPro) && (actual.ciudad==codCiu)){
                    Local = actual.local;
                    printf("\n\t\tLocal: %d",Local);
                    while (!feof(arch) && (actual.codPro == codPro) && (actual.ciudad==codCiu) && (actual.local == Local))
                    {
                        acumLocal++;
                        fread(&actual,sizeof(regCompras),1,arch);
                    }
                    acumCiudad+=acumLocal;
                    printf("\nTotal local: %0.4f",acumLocal);
                    acumLocal = 0;
                }
                acumProv+=acumCiudad;
                printf("\nTotal de la ciudad: %0.4f",acumCiudad);
                acumCiudad = 0;
            }
            printf("\nTotal de la provincia: %.4f",acumProv);
            acumProv=0;
        }
    }
    else
        printf("Archivo no existe o está vacio");
}

