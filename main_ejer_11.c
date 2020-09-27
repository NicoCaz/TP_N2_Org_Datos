#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
 unsigned int ID_Producto;
 char pro[50];
 char Des[200];
}registro;

void creaArch();
void MergeSort();
void copio(registro * ant,registro * act);
int iguales(registro act,registro ant);
int main()
{
    creaArch();
    MergeSort();
    printf("Hello world!\n");
    return 0;
}

void creaArch(){
    srand (time(NULL));
    registro *nuevo;
    FILE * arch=fopen("original.dat","wb+");
    for(int i=0;i<100000;i++ ){
        nuevo=(registro*)malloc(sizeof(registro));
        nuevo->ID_Producto=rand();
        fwrite(nuevo,sizeof(registro),1,arch);
       // printf("%i \n",nuevo->ID_Producto);
    }
}

void MergeSort()
{
    registro ant,act;
    int ordenado, numArchivo;
    ordenado=numArchivo=0;
    FILE *temp1,*temp2;
    FILE *arch=fopen("original.dat", "rb+");
    while (!ordenado)
    {   temp1 = fopen("temp1.temp", "wb+");
        temp2 = fopen("temp2.temp", "wb+");
        fseek(arch,0,0);
        fseek(temp1,0,0);
        fseek(temp2,0,0);
        fread(&act,sizeof(registro),1,arch);
        fwrite(&act,sizeof(registro),1,temp1);
        copio(&ant,&act); // copio los struct
        while (fread(&act,sizeof(registro),1,arch)==1 && !feof(arch) )
        {   if(iguales(act,ant)<=0)
                numArchivo= -numArchivo +1; //si numArchivo es cero(primer archivo) lo apunto al segundo archivo, si es 1(segundo archivo) lo apunto al primero
            if (numArchivo)
                fwrite(&act,sizeof(registro),1,temp2);
            else// como los registros on se pueden copiar por numero de factura no se repiten
                fwrite(&act,sizeof(registro),1,temp1);
            copio(&ant,&act);
         }
            // copio los struct
            fseek(temp1,0,0);
            fseek(temp2,0,0);
            fseek(arch,0,0);
            if(!feof(temp2))
            {   fread(&act,sizeof(registro),1,temp1);
                fread(&ant,sizeof(registro),1,temp2);
                while (!feof(temp1) && !feof(temp2))
                {   if(iguales(act,ant)<=0)
                    {   fwrite(&act,sizeof(registro),1,arch);
                        fread(&act,sizeof(registro),1,temp1);
                    }
                    else
                    {   fwrite(&ant,sizeof(registro),1,arch);
                        fread(&act,sizeof(registro),1,temp2);
                    }
                }
                while (!feof(temp1))
                {   fwrite(&act,sizeof(registro),1,arch);
                    fread(&act,sizeof(registro),1,temp1);
                }
                while (!feof(temp2))
                {   fwrite(&ant,sizeof(registro),1,arch);
                    fread(&ant,sizeof(registro),1,temp2);
                }
            }
            else
                ordenado=1;
            fclose(temp1);
            fclose(temp2);
            fclose(arch);
        }
    }



void copio(registro * ant,registro * act){
    (ant)->ID_Producto=(act)->ID_Producto;
    strcpy((ant)->Des,(act)->Des);
    strcpy((ant)->pro ,(act)->pro);
}
int iguales(registro act,registro ant){
    if(act.ID_Producto>= ant.ID_Producto)
        return 1;
    else
        return 0;
}
