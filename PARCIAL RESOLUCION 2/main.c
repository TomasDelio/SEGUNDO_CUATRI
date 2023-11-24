#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct
{
    char nombrePlaneta [20];
    char estrella [20];
    int cantidadSatelites;
    float masa; ///(se mide en relación a la Tierra, por ejemplo Neptuno es 17,14 Tierras)
    int tempMax;
    int tempMin;
} planeta;


typedef struct
{
    planeta datoPlaneta;
    struct nodoArbolPlaneta * izq;
    struct nodoArbolPlaneta * der;
} nodoArbolPlaneta;

typedef struct
{
    char nombreGalaxia [20];
    char tipoGalaxia [20]; ///elíptica, lenticular, espiral, irregular, etc
    char descubiertoPor [20];
} galaxia;

typedef struct
{
    galaxia datosGalaxia;
    nodoArbolPlaneta * planetas;
} celdaGalaxia;

nodoArbolPlaneta* inic_arbol();
nodoArbolPlaneta*crear_hojas(planeta nuevo);
nodoArbolPlaneta* agregar_arbol(nodoArbolPlaneta * arbolito, nodoArbolPlaneta* nuevo);

planeta cargarPlaneta (); ///Inciso 1
void mostrar_planeta (planeta nuevo); ///Inciso 5
void mostrar_inorder(nodoArbolPlaneta*arbolito);

int buscar_galaxia(celdaGalaxia galaxia[], int val,char nombre[]);
int agregar_galaxia(celdaGalaxia galaxias[],int val,char nombre[]);
galaxia nueva_galaxia(char nombre[]);
int alta_galaxia(celdaGalaxia galaxia[],int val);

int contarPlanetasConLunas(nodoArbolPlaneta* arbolito);
int contarPlanetasGalaxiaConLunas(celdaGalaxia galaxia[],int val);

nodoArbolPlaneta* planetaMayorMasa(nodoArbolPlaneta* arbol);
planeta buscarMayorMasaEnGalaxia( celdaGalaxia galaxia[],int val,int *pos);

void mostrar_galaxia(galaxia nuevo);
void mostrar_galaxia_arreglos(celdaGalaxia galaxias[],int val);

float sumar_temp(nodoArbolPlaneta* arbol);
int contarNodos(nodoArbolPlaneta* arbol);
float calcularTempPromedioArbol(nodoArbolPlaneta* arbol);


int main()
{
    celdaGalaxia arregal[10];
    int val = 0;
    int posPlanetaMayorMasa;
    int busca;
    char galaxiaTemp[20];

            val = alta_galaxia(arregal,val);

            mostrar_galaxia_arreglos(arregal,val);

            printf("\n\nLa cantidad de planetas con mas de una luna en sus galaxias es: %i", contarPlanetasGalaxiaConLunas(arregal,val));

            planeta mayorMasa = buscarMayorMasaEnGalaxia(arregal,val,&posPlanetaMayorMasa);

            printf("\n\nEl planeta con mayor masa es: %s, perteneciente a la galaxia: %s", mayorMasa.nombrePlaneta, arregal[posPlanetaMayorMasa].datosGalaxia.nombreGalaxia);

            printf("\n\nIngrese la galaxia de la cual desea saber la temperatura promedio: ");
            fflush(stdin);
            scanf("%s",galaxiaTemp);

            busca= buscar_galaxia(arregal,val,galaxiaTemp);

            if(busca!= -1)
            {
                printf("LA TEMP PROMEDIO ES DE : %.2f grados ",calcularTempPromedioArbol(arregal[busca].planetas));
            }
            else
            {
                printf("GALAXIA NO ENCONTRADA");
            }

    return 0;
}
////////////////////////==1==////////////////////////
/*Realizar las funciones necesarias parapoder trabajr con el arbol.
En el arbol los elementos estan ordenadossegun sumasa*/

nodoArbolPlaneta* inic_arbol()
{
    return NULL;
}
nodoArbolPlaneta*crear_hojas(planeta nuevo)
{
    nodoArbolPlaneta* aux=malloc(sizeof(nodoArbolPlaneta));
    aux->datoPlaneta=nuevo;
    aux->der=NULL;
    aux->izq=NULL;

    return aux;
}
nodoArbolPlaneta* agregar_arbol(nodoArbolPlaneta * arbolito, nodoArbolPlaneta* nuevo)
{
    if(arbolito==NULL)
    {
        arbolito=nuevo;
    }
    else
    {
        if(nuevo->datoPlaneta.masa>arbolito->datoPlaneta.masa)
        {
            arbolito->der=agregar_arbol(arbolito->der,nuevo);
        }
        else
        {
            arbolito->izq=agregar_arbol(arbolito->izq,nuevo);

        }
    }
    return arbolito;
}
planeta cargarPlaneta () ///Inciso 1
{
    planeta nuevo;
    printf("Nombre planeta: ");
    fflush(stdin);
    scanf("%s", nuevo.nombrePlaneta);
    printf("Estrella: ");
    fflush(stdin);
    scanf("%s", nuevo.estrella);
    printf("Cantidad de satelites: ");
    scanf("%i", &nuevo.cantidadSatelites);
    printf("Masa: ");
    scanf("%f", &nuevo.masa);
    printf("Temperatura maxima: ");
    scanf("%i", &nuevo.tempMax);
    printf("Temperatura minima: ");
    scanf("%i", &nuevo.tempMin);
    return nuevo;
}
void mostrar_planeta (planeta nuevo) ///Inciso 5
{
    printf("\n\nNombre planeta: %s",nuevo.nombrePlaneta);
    printf("\nEstrella: %s", nuevo.estrella);
    printf("\nCantidad de satelites: %i", nuevo.cantidadSatelites);
    printf("\nMasa: %.2f", nuevo.masa);
    printf("\nTemperatura maxima: %i",nuevo.tempMax);
    printf("\nTemperatura minima: %i", nuevo.tempMin);

}
void mostrar_inorder(nodoArbolPlaneta*arbolito)
{
    if(arbolito)
    {
        mostrar_inorder(arbolito->izq);
        mostrar_planeta(arbolito->datoPlaneta);
        mostrar_inorder(arbolito->der);
    }
}

////////////////////////==2==////////////////////////
/*Generar una funcion que nos permite agregar eleentos al arreglo de galaxias
.El usuario debe ingresar el nombre de la galaxia ,el programa debe buscar la celdad
correspondiente y solicitar los datos del planeta.En el caso de que la galaxia
no exista, debe solicitarle los datos de la galaixa para agregarla al arreglo
antes de pediorle los datos el planeta*/

int buscar_galaxia(celdaGalaxia galaxia[], int val,char nombre[])
{
    int rta=-1;
    int i=0;
    while(i<val)
    {
        if(strcmpi(galaxia[i].datosGalaxia.nombreGalaxia,nombre)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}
int agregar_galaxia(celdaGalaxia galaxias[],int val,char nombre[])
{
    galaxias[val].datosGalaxia=nueva_galaxia(nombre);
    galaxias[val].planetas=inic_arbol();
    val++;

    return val;
}
galaxia nueva_galaxia(char nombre[])
{
    galaxia nueva;

    strcpy(nueva.nombreGalaxia,nombre);
    printf("\nCargando datos de galaxia %s\n", nombre);

    printf("Ingrese tipo de galaxia: ");
    fflush(stdin);
    scanf("%s", nueva.tipoGalaxia);

    printf("Ingrese quien la descubrio: ");
    fflush(stdin);
    scanf("%s", nueva.descubiertoPor);

    return nueva;
}
int alta_galaxia(celdaGalaxia galaxia[],int val)
{
    char galaxiaBuscada[99];
    char yes='s';
    int posGalaxia;
    while(yes=='s')
    {
        printf("\n Que galaxia desea cargarle un planeta?: ");
        fflush(stdin);
        scanf("%s",galaxiaBuscada);

        posGalaxia=buscar_galaxia(galaxia,val,galaxiaBuscada);
        if(posGalaxia==-1)
        {
            printf("\n NO SE ENCONTRO LA GALAXIA");
            val=agregar_galaxia(galaxia,val,galaxiaBuscada);
            posGalaxia=val-1;
        }

        nodoArbolPlaneta* nuevo=crear_hojas(cargarPlaneta());
        galaxia[posGalaxia].planetas=agregar_arbol(galaxia[posGalaxia].planetas,nuevo);

        printf("\nDesea seguir cargando planetas? Presione s");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return val;
}
////////////////////////==3==////////////////////////
/*Diseñar una funcion que perita contar la cantidad total de planetas que hay entre
todas las galaxias,no mas de una luna */

int contarPlanetasConLunas(nodoArbolPlaneta* arbolito)
{
    int cant=0;
    if(arbolito)
    {
        if(arbolito->datoPlaneta.cantidadSatelites>1)
        {
            cant++;
        }
        cant+= contarPlanetasConLunas(arbolito->der)+ contarPlanetasConLunas(arbolito->izq);
    }
    return cant;
}

int contarPlanetasGalaxiaConLunas(celdaGalaxia galaxia[],int val)
{
    int cont=0;
    int i=0;

    while(i<val)
    {
        cont+=contarPlanetasConLunas(galaxia[i].planetas);
        i++;
    }
    return cont;
}
////////////////////////==4==////////////////////////
/*Escribiruna funcion que encuentre el planeta con mayor masa de todo el arreglo
y me lo devuelva*/

nodoArbolPlaneta* planetaMayorMasa(nodoArbolPlaneta* arbol)
{
    if(arbol && arbol->der)
    {
        arbol=planetaMayorMasa(arbol->der);
        //A LA DERECHA POR QUE EL ARBOL ESTA ORDENADO POR MASA INORDER
        //ES DECIR A LA IZQ ESTAN LO MAS CHICOS A LA DER LOS MAS GRANDES
    }
    return arbol;
}

planeta buscarMayorMasaEnGalaxia( celdaGalaxia galaxia[],int val,int *pos)
{
    nodoArbolPlaneta* mayorMasa= planetaMayorMasa(galaxia[0].planetas);
    nodoArbolPlaneta* rta=inic_arbol();
    int i=0;
    while(i<val)
    {
        rta= planetaMayorMasa(galaxia[i].planetas);

        if(mayorMasa->datoPlaneta.masa> rta->datoPlaneta.masa);
        {
            mayorMasa= rta;
            *pos=i;
        }
        i++;
    }
    return mayorMasa->datoPlaneta;
}
////////////////////////==5==////////////////////////
/* Hacer unafuncion que muestre el arreglo de galaxia*/
void mostrar_galaxia(galaxia nuevo)
{
    printf("\n NOMBRE DE LA GALAXIA: %s", nuevo.nombreGalaxia);
    printf("\n TIPO DE GALAXIA: %s", nuevo.tipoGalaxia);
    printf("\n DESCUBIERTO POR: %s", nuevo.descubiertoPor);
}

void mostrar_galaxia_arreglos(celdaGalaxia galaxias[],int val)
{
    int i=0;

    while (i<val)
    {
        mostrar_galaxia(galaxias[i].datosGalaxia);
        mostrar_inorder(galaxias[i].planetas);
        i++;
    }

}
////////////////////////==6==////////////////////////
/*HACER UNAFUNCION QUE DEVUEVA LA TEMPERATURA PROEDIO DE UN ARBOL*/

float sumar_temp(nodoArbolPlaneta* arbol)
{
    float sumar=0;
    if(arbol)
    {
        sumar=(float)(arbol->datoPlaneta.tempMax+ arbol->datoPlaneta.tempMin)/2;
        sumar += sumar_temp(arbol->der)+ sumar_temp(arbol->izq);
    }
    return sumar;
}
int contarNodos(nodoArbolPlaneta* arbol)
{
    int cant=0;
    if(arbol)
    {
        cant=1+ contarNodos(arbol->der) + contarNodos(arbol->izq);
    }
    return cant;
}
float calcularTempPromedioArbol(nodoArbolPlaneta* arbol)
{
    float prom=0;
    if(arbol)
    {
        prom=sumar_temp(arbol)/contarNodos(arbol);
    }
    return prom;
}
