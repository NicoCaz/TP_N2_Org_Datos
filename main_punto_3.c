#include <stdio.h>
#include <stdlib.h>
#include "situacion2.h"


int alta(regCompras nuevo);
int baja(regCompras auxh);
int modificaciones(regCompras aux);
float promVen(t_legVen vendedor);
float promFecha(t_fecha fecha);
float promProd(t_codPro prod);
void mayVenLoc(t_codLoc local);




int main() {
    printf("Hello world!\n");
    return 0;
}

int alta(regCompras nuevo) {
    regCompras act;
    int resp=0;
    FILE *temp=fopen("Temp.temp", "wb+");
    FILE *arch=fopen("compras.dat","rb+");
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1 && act.factura<nuevo.factura) {
            fwrite(&act,sizeof(regCompras),1,temp);
            if (act.factura==nuevo.factura)
                resp=1;
        }
        fwrite(&nuevo,sizeof(regCompras),1,temp);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            fwrite(&nuevo,sizeof(regCompras),1,temp);
    } else
        fwrite(&nuevo,sizeof(regCompras),1,temp);
    remove("ComprasF.dat");
    rename("ComprasF.temp","ComprasF.dat");
    fclose(temp);
    fclose(arch);
    return resp;
}


int baja(regCompras aux) {

    regCompras act;
    int resp=0;
    FILE *temp=fopen("Temp.temp", "wb+");
    FILE *arch=fopen("compras.dat","rb+");

    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1 && act.factura<aux.factura)
            fwrite(&act,sizeof(regCompras),1,temp);
        if (act.factura==aux.factura)
            resp=0;
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            fwrite(&act,sizeof(regCompras),1,temp);
    }
    remove("comprasF.dat");
    rename("Temp.temp","comprasF.dat");
    fclose(temp);
    fclose(arch);
    return resp;

}

int modificaciones(regCompras aux) {
    regCompras act;
    int resp=0;
    FILE *temp = fopen("ComprasF.temp", "wb+");
    FILE *arch=fopen("compras.dat","rb+");
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1 && act.factura<aux.factura)
            fwrite(&act,sizeof(regCompras),1,temp);
        if (act.factura==aux.factura)
            fwrite(&aux,sizeof(regCompras),1,temp);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            fwrite(&aux,sizeof(regCompras),1,temp);
    }
    remove("comprasf.dat");
    rename("temp.temp","comprasF.dat");
    fclose(temp);
    fclose(arch);
    return resp;
}


float promVend(t_legVen vend) {
    FILE *arch=fopen("compras.dat","rb+");
    float prom;
    unsigned int cont=0;
    regCompras act;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            if (act.vendedor==vend) {
                cont++;
                prom+=act.total;
            }
    }
    close(arch);
    return (cont==0)?0:prom/cont;
}


float promFecha(t_fecha fecha) {
    FILE * arch=fopen("Compras.dat", "wb+");
    float prom;
    unsigned int cont=0;
    regCompras act;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            if (act.fecha==fecha) {
                cont++;
                prom+=act.total;
            }
    }
    close(arch);
    return (cont==0)?0:prom/cont;
}


float promProd(t_codPro prod) {
    FILE * arch=fopen("ComprasF.temp", "wb+");
    float prom;
    unsigned int cont=0;
    regCompras act;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            if (act.producto==prod) {
                cont++;
                prom+=act.total;
            }
    }
    close(arch);
    return (cont==0)?0:prom/cont;
}


void mayVenLoc(t_codLoc local) {
    FILE * arch=fopen("ComprasF.dat", "wb+");
    regCompras act,maximo;
    maximo.factura=0;
    if (arch!=NULL) {
        fseek(arch,0,0);
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
            if (act.local==local) {
                if (maximo.factura==0)
                    maximo.total=act.total;
                else if (maximo.total<act.total)
                    maximo.total=act.total;
            }
    }
    if(maximo.factura!=0)
        printf("La maxima factura fue de %hu ",maximo.total);
    else
        printf("\n el local no tiene comptras");
    close(arch);
}

