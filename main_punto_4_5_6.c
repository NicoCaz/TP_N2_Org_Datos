#include <stdio.h>
#include <stdlib.h>
#include "situacion2.h"
int main()
{
    printf("Hello world!\n");
    return 0;
}


void Interseccion()
{
    regCompras maes,nov;
    FILE *maestro,*novedades,*maestemp;
    maestro=fopen("maestro.dat","rb");
    novedades=fopen("novedades.dat","rb");
    maestemp=fopen("maestro.temp","wb");
    if(maestro!=NULL && novedades!=NULL)
    {
        while(!feof(maestro) && !feof(novedades) && fread(&nov,sizeof(regCompras),1,novedades==1))
        {
            while (!feof(maestro) && fread(&maes,sizeof(regCompras),1,maestro)==1 && maes.factura<nov.factura)
            {
                //LO UTILIZO PARA AVANZAR EN EL ARCHIVO NOVEDADES
            }
            if(maes.factura==nov.factura)
                fwrite(&nov,sizeof(regCompras),1,maestemp);
            else
                ingresaarchivoerores(nov);//estaba en novedades pero no en el maestro
        }
    }
    fclose(maestro);
    fclose(novedades);
    fclose(maestemp);
    remove("maestro.dat");
    rename("maestro.temp","maestro.dat");
}

void Diferencia()
{
    regCompras maes,nov;
    FILE *maestro,*novedades,*maestemp;
    maestro=fopen("maestro.dat","rb");
    novedades=fopen("novedades.dat","rb");
    maestemp=fopen("maestro.temp","wb");
    if(maestro!=NULL && novedades!=NULL)
    {
        while(!feof(maestro) && !feof(novedades) && fread(&nov,sizeof(regCompras),1,novedades==1))
        {
            while (!feof(maestro) && fread(&maes,sizeof(regCompras),1,maestro)==1 && maes.factura<nov.factura)
                fwrite(&maes,sizeof(regCompras),1,maestemp);
            if(maes.factura==nov.factura)
                {
                    // LA INTERSECCION LA DESECHO
                }
        }
    }
    fclose(maestro);
    fclose(novedades);
    fclose(maestemp);
    remove("maestro.dat");
    rename("maestro.temp","maestro.dat");
}



void Union()
{
    regCompras maes,nov;
    FILE *maestro,*novedades,*maestemp;
    maestro=fopen("maestro.dat","rb");
    novedades=fopen("novedades.dat","rb");
    maestemp=fopen("maestro.temp","wb");
    if(maestro!=NULL && novedades!=NULL)
    {
        while(!feof(maestro) && !feof(novedades) && fread(&nov,sizeof(regCompras),1,novedades==1))
        {
            while (!feof(maestro) && fread(&maes,sizeof(regCompras),1,maestro)==1 && maes.factura<nov.factura)
                fwrite(&maes,sizeof(regCompras),1,maestemp);
            if(maes.factura==nov.factura)
                fwrite(&maes,sizeof(regCompras),1,maestemp);
            else
                fwrite(&nov,sizeof(regCompras),1,maestemp);
        }
        while(!feof(maestro)&& fread(&maes,sizeof(regCompras),1,maestro==1))
            fwrite(&maes,sizeof(regCompras),1,maestemp);
        while(!feof(novedades)&& fread(&nov,sizeof(regCompras),1,novedades==1))
            fwrite(&nov,sizeof(regCompras),1,maestemp);
    }
    fclose(maestro);
    fclose(novedades);
    fclose(maestemp);
    remove("maestro.dat");
    rename("maestro.temp","maestro.dat");
}

void ingresaarchivoerores(nov){
}
