#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//////////////////////---ESTRUCTURA NODO SIMPLE---//////////////////////
typedef struct
{
    int num;
    struct snodo* sig;
} snodo;
//////////////////////---ESTRUCTURA NODO DOBLE---//////////////////////

typedef struct
{
    int num;
    struct dnodo* sig;
    struct dnodo* ante;
} dnodo;

////////////////////////PROTOTIPIADO NODO SIMPLE////////////////////////

snodo* iniciar_nodo();
snodo* nuevo_snodo(int n);
snodo* agregar_principio_snodo(snodo* lista, snodo*nuevo);
snodo* buscar_final_snodo(snodo* a);
snodo* agregar_final_snodo(snodo* lista, snodo* nuevo);
snodo* crear_lista_snodo(snodo* a);
void mostrar_snodo(snodo* lista);
void escribir_snodo(snodo* lista);
snodo* borrar_snodo(snodo* lista, int a);

////////////////////////PROTOTIPIADO NODO DOBLE////////////////////////
dnodo* iniciar_dnodo();
dnodo* nuevo_dnodo(int lista);
dnodo* agregar_principio_dnodo(dnodo* lista, dnodo*nuevo);
dnodo* buscar_final_dnodo(dnodo* lista);
dnodo* agregar_final_dnodo(dnodo* lista,dnodo* nuevo);
dnodo* crear_lista_doble(dnodo* lista);
void mostrar_dnodo(dnodo* lista);
void escribir_dnodo(dnodo* a);
dnodo* borrar_dnodo(dnodo* lista,int a);


int main()
{
    int num;
    char yes;

    snodo* lista=iniciar_nodo();
    dnodo* lista2=iniciar_dnodo();

    do
    {
        printf("\n Seleccione \n 1:Nodo Siple\n 2:Nodo Doble\n :");
        fflush(stdin);
        scanf("%i",&num);

        switch(num)
        {
        case 1:
            lista=crear_lista_snodo(lista);
            mostrar_snodo(lista);

            printf("\n Que numero desea borrar??");
            fflush(stdin);
            scanf("%d",&num);

            lista=borrar_snodo(lista,num);
            mostrar_snodo(lista);

            break;
        case 2:
            lista2=crear_lista_doble(lista2);
            mostrar_dnodo(lista2);

            printf("\n Que numero desea borrar??");
            fflush(stdin);
            scanf("%d",&num);

            lista2=borrar_dnodo(lista2,num);
            mostrar_dnodo(lista2);

            break;
        default:
            printf("\nNumero erroneo ");
            break;
        }
        printf("\nQuiere ver el otro caso?Presione S ");
        fflush(stdin);
        scanf("%c", &yes);

    }
    while(yes=='s'||yes=='S');

    return 0;
}
///////////////////////NODO SIMPLE///////////////////////////
snodo* iniciar_nodo()
{
    return NULL;
}
snodo* nuevo_snodo(int n)
{
    snodo* aux;

    aux=(snodo*)malloc(sizeof(snodo));
    aux->num=n;
    aux->sig=NULL;

    return aux;
}
snodo* agregar_principio_snodo(snodo* lista, snodo*nuevo)
{
    nuevo->sig=lista;

    return nuevo;
}
snodo* buscar_final_snodo(snodo* a)
{
    while(a->sig)
    {
        a=a->sig;
    }
    return a;
}
snodo* agregar_final_snodo(snodo* lista, snodo* nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        snodo* aux=buscar_final_snodo(lista);
        aux->sig=nuevo;
    }
    return lista;
}
snodo* crear_lista_snodo(snodo* a)
{
    char yes='s';
    snodo* nuevo;
    int n;

    while(yes=='s')
    {
        printf("\nIngrese un numero: ");
        fflush(stdin);
        scanf("%i", &n);

        nuevo=nuevo_snodo(n);
        a=agregar_final_snodo(a,nuevo);

        printf("\n Desea continuar? : ");
        fflush(stdin);
        scanf("%c",&yes);
    }
    return a;
}
void mostrar_snodo(snodo* lista)
{
    printf("\n\n");
    while(lista)
    {
        escribir_snodo(lista);
        lista=lista->sig;
    }
    printf("\n\n");
}
void escribir_snodo(snodo* lista)
{
    printf("|%i|",lista->num);
}
snodo* borrar_snodo(snodo* lista, int a)
{
    snodo* aux=lista;
    snodo* ante;

    if(lista && lista->num==a)
    {
        lista=lista->sig;
    }
    else
    {
        while(aux && aux->num!=a)
        {
            ante=aux;
            aux=aux->sig;
        }
        if(aux)
        {
            ante->sig=aux->sig;
        }
    }
    return lista;
}
///////////////////////NODO DOBLE///////////////////////////

dnodo* iniciar_dnodo()
{
    return NULL;
}
dnodo* nuevo_dnodo(int lista)
{
    dnodo* aux;
    aux=(dnodo*)malloc(sizeof(dnodo));
    aux->num=lista;
    aux->sig=NULL;
    aux->ante=NULL;

    return aux;
}
dnodo* agregar_principio_dnodo(dnodo* lista, dnodo*nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nuevo->sig=lista;
        lista->ante=nuevo;
        lista=nuevo;
    }
    return lista;
}
dnodo* buscar_final_dnodo(dnodo* lista)
{
    while(lista->sig)
    {
        lista=lista->sig;
    }
    return lista;
}
dnodo* agregar_final_dnodo(dnodo* lista,dnodo* nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        dnodo* aux=buscar_final_dnodo(lista);
        aux->sig=nuevo;
        nuevo->ante=aux;
    }
    return lista;
}
dnodo* crear_lista_doble(dnodo* lista)
{
    int a;
    dnodo* nuevo;
    char yes='s';

    while(yes=='s')
    {
        printf("\n Ingrese un numero: ");
        fflush(stdin);
        scanf("%i",&a);

        nuevo=nuevo_dnodo(a);
        lista=agregar_final_dnodo(lista,nuevo);

        printf("\n Desea continuar?: ");
        fflush(stdin);
        scanf("%c",&yes);

    }
    return lista;
}
void mostrar_dnodo(dnodo* lista)
{
    printf("\n\n");
    while(lista)
    {
        escribir_dnodo(lista);
        lista=lista->sig;
    }
    printf("\n\n");
}
void escribir_dnodo(dnodo* a)
{
    printf("|%i|",a->num);
}

dnodo* borrar_dnodo(dnodo* lista,int a)
{
    dnodo* aux=lista;
    dnodo* ante=NULL;
    dnodo* next=NULL;

    if(lista!=NULL && lista->num==a)
    {
        lista=lista->sig;
    }
    else
    {
        while(aux != NULL && aux->num!=a)
        {
            ante=aux;
            aux=aux->sig;
        }
        ante->sig=aux->sig;
        next=ante->sig;

        if(aux!=NULL)
        {
            next->ante=ante;
        }
    }
    return lista;
}

