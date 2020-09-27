#include <stdio.h>
#include <stdlib.h>


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
    char accion;
}regNoveCompras;


void mandoArchivoErrores(regNoveCompras nov);
void copia(regNoveCompras * nov,regCompras * nuevo);
int main()
{
    printf("Hello world!\n");
    return 0;
}


void ABM(){
regCompras maes,*nuevo;
regNoveCompras nov;
FILE *maestro,*novedades,*maestemp;
maestro=fopen("maestro.dat","rb");
novedades=fopen("novedades.dat","rb");
maestemp=fopen("maestro.temp","wb");
if(maestro!=NULL && novedades!=NULL)
{
    fread(&maes,sizeof(regCompras),1,maestro);
    fread(&nov,sizeof(regNoveCompras),1,novedades);
    while(!feof(maestro) && !feof(novedades))
    {
        while (!feof(maestro) && maes.factura<nov.factura)
        {
            fwrite(&maes,sizeof(regCompras),1,maestemp);
            fread(&maes,sizeof(regCompras),1,maestro);
        }
        switch(nov.accion)
        {
        case 'a'://alta
            if(maes.factura!=nov.factura)
            {
                nuevo=(regCompras*)malloc(sizeof(regCompras));
                copia(&nov,nuevo);//copia el registro nov en el nuevo sin el campo de accion, de esta manera al archivo final no tiene campos extra
                fwrite(nuevo,sizeof(regCompras),1,maestemp);
                fwrite(&maes,sizeof(regCompras),1,maestemp);
            }
            else
                mandoArchivoErrores(nov);
            break;
        case 'b'://baja
            if(maes.factura!=nov.factura)
                mandoArchivoErrores(nov);
            else
                fread(&maes,sizeof(regCompras),1,maestro);
            break;
        case 'm'://modif
            if(maes.factura==nov.factura)
            {
                nuevo=(regCompras*)malloc(sizeof(regCompras));
                copia(&nov,nuevo);//copia el registro nov en el nuevo sin el campo de accion, de esta manera al archivo final no tiene campos extra
                fwrite(nuevo,sizeof(regCompras),1,maestemp);
                fwrite(&maes,sizeof(regCompras),1,maestemp);
            }
            else
                mandoArchivoErrores(nov);
            break;
        }
        fread(&nov,sizeof(regCompras),1,novedades);
    }
}
}

void copia(regNoveCompras *nov,regCompras * nuevo){

    // copia nov en nuevo
}
void mandoArchivoErrores(regNoveCompras nov){
    // manda el registro nov al archivo errores
}
