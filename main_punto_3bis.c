#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "situacion2.h"
int main()
{   printf("Hello world!\n");
    return 0;
}


void MergeSort(char * archivo)
{   regCompras ant,act;
    int ordenado, numArchivo;
    ordenado=numArchivo=0;
    FILE *temp1,*temp2;
    FILE *arch=fopen(*archivo, "rb+");
    while (arch!=NULL && !ordenado)
    {   temp1 = fopen("temp1.temp", "wb+");
        temp2 = fopen("temp2.temp", "wb+");
        fseek(arch,0,0);
        fseek(temp1,0,0);
        fseek(temp2,0,0);
        fread(&act,sizeof(regCompras),1,arch);
        fwrite(&act,sizeof(regCompras),1,temp1);
        copio(&ant,&act); // copio los struct
        while (!feof(arch) && fread(&act,sizeof(regCompras),1,arch)==1)
        {   if(iguales(&act,&ant)<0)
                numArchivo= -numArchivo +1; //si numArchivo es cero(primer archivo) lo apunto al segundo archivo, si es 1(segundo archivo) lo apunto al primero
            if (numArchivo)
                fwrite(&act,sizeof(regCompras),1,temp2);
            else// como los registros on se pueden copiar por numero de factura no se repiten
                fwrite(&act,sizeof(regCompras),1,temp1);
            copio(&ant,&act);// copio los struct        }
            fseek(temp1,0,0);
            fseek(temp2,0,0);
            fseek(arch,0,0);
            if(!feof(temp2))
            {   fread(&act,sizeof(regCompras),1,temp1);
                fread(&ant,sizeof(regCompras),1,temp2);
                while (!feof(temp1) && !feof(temp2))
                {   if(iguales(&act,&ant)<0)
                    {   fwrite(&act,sizeof(regCompras),1,arch);
                        fread(&act,sizeof(regCompras),1,temp1);
                    }
                    else
                    {   fwrite(&ant,sizeof(regCompras),1,arch);
                        fread(&act,sizeof(regCompras),1,temp2);
                    }
                }
                while (!feof(temp1))
                {   fwrite(&act,sizeof(regCompras),1,arch);
                    fread(&act,sizeof(regCompras),1,temp1);
                }
                while (!feof(temp2))
                {   fwrite(&ant,sizeof(regCompras),1,arch);
                    fread(&ant,sizeof(regCompras),1,temp2);
                }
            }
            else
                ordenado=1;
            fclose(temp1);
            fclose(temp2);
            fclose(arch);
        }
    }
}
