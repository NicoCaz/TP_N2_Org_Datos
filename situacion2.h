#include <stdio.h>
#include <stdlib.h>
/*
Se quiere registrar todas las compras de un local nacional de electrodom�sticos.
Para esto se realiza un registro de la siguiente manera:
Fecha,
Hora,
C�digo de Provincia,
C�digo de Ciudad,
C�digo del Local,
Legajo del Vendedor,
Factura,
C�digo del Producto,
Cantidad,
Valor Unitario,
Total Rengl�n y Observaciones.
*/
typedef unsigned short int t_fecha;
typedef unsigned short int t_hora;
typedef char  t_codProv[4];
typedef char  t_codCiu[6];
typedef unsigned int  t_codLoc;
typedef unsigned int  t_legVen;
typedef unsigned int  t_codFac;
typedef unsigned int  t_codPro ;
typedef unsigned int t_can;
typedef unsigned int  t_valUni;
typedef unsigned int  t_total;
typedef char  t_obs[200];

typedef struct{
    t_fecha fecha;
    t_hora hora;
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


