#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct arbol
{
    int dato;
    struct arbol* izq;
    struct arbol* der;
} arbol;
/////////////////////////////////////
typedef struct
{
    int num;
    struct nodo* sig;
    struct nodo* ante;
} nodo;

typedef struct
{
    nodo* ini;
    nodo* fin;
}fila;



int main()
{
    int num=0;
    char yes='s';
    do
    {
        printf("\n probemos aveeer :");
        fflush(stdin);
        scanf("%i",&num);

        switch(num)
        {
        case 1:
            break;
        case 2:
            break;

        default:
            break;

        }
        printf("\nQuiere ver el otro caso?Presione S ");
        fflush(stdin);
        scanf("%c",&yes);

    }
    while(yes=='s'||yes=='S');
    return 0;
}

//////////////////////////////////////////////////////////////////
arbol * iniciar_arbol()
{
    return NULL;
}

arbol* crear_hoja(int nuevo)
{
    arbol* aux=malloc(sizeof(arbol));
    aux->dato=nuevo;
    aux->der=NULL;
    aux->izq=NULL;

    return aux;
}

arbol* agregar_ordenado(arbol* arbolito,int nuevo)
{
    if(!arbolito)
    {
        arbolito=crear_hoja(nuevo);
    }
    else
    {
        if(nuevo<arbolito->dato)
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

arbol* crear_arbol(arbol* arbolito)
{
    int nuevo=0;
    char yes='s';

    while(yes=='s' && yes=='S')
    {
        printf("\n Ingrese elnumero quedesea agregar: ");
        fflush(stdin);
        scanf("%i", &nuevo);

        arbolito=agregar_ordenado(arbolito,nuevo);

        printf("\n Desea agregar otro?: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return arbolito;
}

void mostrar_inorden(arbol* arbolito)
{
    if(arbolito)
    {
        mostrar_inorden(arbolito->izq);
        printf("|%i|",arbolito->dato);
        mostrar_inorden(arbolito->der);
    }
}

arbol* menor_derecha(arbol* arbolito)
{
    arbol* arbolote;
    if(arbolito->izq)
    {
        arbolote=menor_derecha(arbolito->izq);
    }
    else
    {
        arbolote=arbolito;
    }
    return arbolote;
}

arbol* borrar_hoja(arbol* arbolito,int nuevo)
{
    arbol* arbolote=arbolito;

    if(arbolito)
    {
        if(nuevo==arbolito->dato)
        {
            if(arbolito->der==NULL && arbolito->izq==NULL)
            {
                arbolito=NULL;
                free(arbolote);
            }
            else if(arbolito->der!=NULL && arbolito->izq==NULL)
            {
                arbolito=arbolito->der;
                free(arbolote);
            }
            else if(arbolito->der==NULL && arbolito->izq!=NULL)
            {
                arbolito=arbolito->izq;
                free(arbolote);
            }
            else
            {
                arbolote=menor_derecha(arbolito->der);
                arbolito->dato=arbolote->dato;
                arbolote=borrar_hoja(arbolito->der,arbolote->dato);
            }
        }
        else
        {
            if(nuevo<arbolito->dato)
            {
                arbolito->izq=borrar_hoja(arbolito->izq,nuevo);
            }
            else
            {
                arbolito->der=borrar_hoja(arbolito->der,nuevo);

            }
        }
    }
return arbolito;
}

int contar_hojas(arbol* arbolito)
{
    int flag=0;

    if(arbolito)
    {
        if(arbolito->der==NULL && arbolito->izq==NULL)
        {
            flag=1;
        }
        else
        {
            flag=flag+contar_hojas(arbolito->der)+contar_hojas(arbolito->izq);
        }

    }
    return flag;
}

//////////////////////////////////////////////////////////////////////////////

nodo* inciar_nodo()
{
    return NULL;
}

nodo*nuevo_nodo(int nuevo)
{
    nodo*aux=(nodo*)malloc(sizeof(nodo));
    aux->num=nuevo;
    aux->sig=NULL;
    aux->ante=NULL;
}

nodo* buscar_final(nodo* lista)
{
    nodo*aux=lista;
    while(lista)
    {
        aux=lista;
        lista=lista->sig;
    }
    return aux;
}

nodo* agregar_final(nodo* nuevo,nodo* lista)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo*aux=buscar_final(lista);
        aux->sig=nuevo;
        nuevo->ante=aux;
    }
    return lista;
}

void mostrar_lista(nodo* lista)
{
    printf("\n");

    while(lista)
    {
        escribir_lista(lista);
        lista=lista->sig;
    }
}

void escribir_lista(nodo* a)
{
    printf("\n |%i|",a->num);
}

//////////////////////////////////////////////////////////////////

void iniciar_fila(fila* f)
{
    f->ini=NULL;
    f->fin=NULL;
}

void agregar(fila* f, int n)
{
    nodo* nuevo=nuevo_nodo(n);
    f->ini=agregar_final(nuevo,f->ini);
    f->fin=nuevo;
}

void mostrar_fila(fila* f)
{
    mostrar_fila(f->ini);
}

void leer(fila* f)
{
    int n;

    printf("\n Ingrese un numero para agregar: ");
    fflush(stdin);
    scanf("%i", &n);

    agregar(f,n);
}

int primero(fila* f)
{
    int n=f->ini->num;

    return n;
}

int extraer(fila* f)
{
    nodo* aux=f->ini;
    f->ini=f->ini->sig;

    return aux->num;
}
