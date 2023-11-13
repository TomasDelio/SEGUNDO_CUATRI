#include <stdio.h>
#include <stdlib.h>
#include "string.h"
//ARREGLO DE ARBOLES
typedef struct
{
    char animal[30];
    int cant;
    int habitat;
    int idEspecie;
    char especie[20];
} registroArchivo;

typedef struct
{
    char nombreAnimal [30];
    int cantidad;
    int habitat;// 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;

typedef struct
{
    animal dato;
    struct nodoArbol * izq;
    struct nodoArbol * der;
} nodoArbol;

typedef struct
{
    int idEspecie;// "Mamiferos", "Aves"
    char especie [20];// "Reptiles", "Peces",”Anfibios”
    nodoArbol * arbolDeAnimales;
} celdaEspecie;

nodoArbol* inic_arbol();
nodoArbol* nuevo_arbol(registroArchivo nuevo);
nodoArbol* agregar_ordenado(nodoArbol* arbolito, nodoArbol* nuevo);
int anadir_especie(registroArchivo nuevo, celdaEspecie zoo[],int val);
int buscar_especie(registroArchivo nuevo,celdaEspecie zoo[],int val);
int archivo_al_arbol(char archivito[],celdaEspecie zoo[],int dim);
int alta(registroArchivo nuevo,celdaEspecie zoo[],int val);
void mostrar_inorder(nodoArbol* nuevo);
void mostrar_archivo(char archivito[]);
void mostrar_estructuras(celdaEspecie zoo[],int val);


int main()
{
    char archivito[20]="animales.dat";
    int option=0;
    celdaEspecie zoo[25];
    int val;
    nodoArbol* nuevo=NULL;
    do
    {
        printf("\n=========Bienvenido a ARREGLO DE ARBOLES=========");
        printf("\n 1) Para buscar los animales ");
        printf("\n 2) para salir:");
        fflush(stdin);
        scanf("%i",&option);

        switch(option)
        {
        case 1:
            val=archivo_al_arbol(archivito,zoo,25);
            mostrar_estructuras(zoo,val);
            mostrar_archivo(archivito);
            break;

        default:
            printf("\nOpcion invalida");
            break;
        }
    }
    while(option != 2);

    return 0;
}

nodoArbol* inic_arbol()
{
    return NULL;
}

nodoArbol* nuevo_arbol(registroArchivo nuevo)
{
    nodoArbol*aux=malloc(sizeof(nodoArbol));
    strcpy(aux->dato.nombreAnimal,nuevo.animal);
    aux->dato.cantidad=nuevo.cant;
    aux->dato.habitat=nuevo.habitat;
    aux->der=NULL;
    aux->izq=NULL;

    return aux;
}

nodoArbol* agregar_ordenado(nodoArbol* arbolito, nodoArbol* nuevo)
{
    if(!arbolito)
    {
        arbolito=nuevo;
    }
    else
    {
        if(nuevo->dato.cantidad<arbolito->dato.cantidad)
        {
            arbolito->izq=agregar_ordenado(arbolito->izq,nuevo);
        }
        else
        {
            arbolito->der=agregar_ordenado(arbolito->der,nuevo);
        }
    }
    return arbolito;
}

int anadir_especie(registroArchivo nuevo, celdaEspecie zoo[],int val)
{
    strcpy(zoo[val].especie,nuevo.especie);
    zoo[val].idEspecie=nuevo.idEspecie;
    zoo[val].arbolDeAnimales=inic_arbol();
    val++;

    return val;
}

int buscar_especie(registroArchivo nuevo,celdaEspecie zoo[],int val)
{
    int rta=-1;
    int i=0;

    while(i<val && rta==-1)
    {
        if(strcmp(zoo[i].especie,nuevo.especie)==0)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int archivo_al_arbol(char archivito[],celdaEspecie zoo[],int dim)
{
    FILE* archi=fopen(archivito,"rb");
    registroArchivo aux;
    int val=0;

    if(archi)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
        {
            val=alta(aux,zoo,val);
        }
        fclose(archi);
    }
    return val;
}

int alta(registroArchivo nuevo,celdaEspecie zoo[],int val)
{
    nodoArbol* aux=nuevo_arbol(nuevo);
    int pos=buscar_especie(nuevo,zoo,val);

    if(pos==-1)
    {
        val=anadir_especie(nuevo,zoo,val);
        pos=val-1;
    }
    zoo[pos].arbolDeAnimales=agregar_ordenado(zoo[pos].arbolDeAnimales,aux);

    return val;
}

void mostrar_inorder(nodoArbol* nuevo)
{
    if(nuevo)
    {
        mostrar_inorder(nuevo->izq);
        printf("\n===========================");
        printf("\nNombre: %s",nuevo->dato.nombreAnimal);
        printf("\nHabitad: %i",nuevo->dato.habitat);
        printf("\nCantidad: %i",nuevo->dato.cantidad);
        printf("\n===========================");
        mostrar_inorder(nuevo->der);
    }
}
void mostrar_archivo(char archivito[])
{
    FILE* archi=fopen(archivito,"rb");
    registroArchivo aux;

    if(archi)
    {
        while(fread(&aux,sizeof(registroArchivo),1,archi)>0)
        {
            printf("\n ANIMAL: %s",aux.animal);
        }
        fclose(archi);
    }
}

void mostrar_estructuras(celdaEspecie zoo[],int val)
{
    int i=0;
    char especie[20];
    int flag=0;

    printf("\n Escriba el nombre de la especie quede sea buscar: ");
    fflush(stdin);
    scanf("%s",&especie);

    while(i<val && flag==0)
    {
        if(strcmp(especie,zoo[i].especie)==0)
        {
            printf("\n====================");
            printf("\nESPECIE: %s",zoo[i].especie);
            printf("\nESPECIE: %i",zoo[i].idEspecie);
            printf("\n====================");
            mostrar_inorder(zoo[i].arbolDeAnimales);
        }
        else
        {
        printf("\NO SE ENCONTRO EL ESPECIMEN");
        }

        i++;
    }
}



