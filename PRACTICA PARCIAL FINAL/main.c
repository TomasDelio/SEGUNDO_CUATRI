#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct {
	int codigoProducto;
	char marca[50]; // Nintendo Switch, Xbox, Playstation
	float precioEnMiles;
    int stock;
	char modelo[50];// Común, Pro, Slim
}stConsola;

typedef struct nodoConsola{
	stConsola dato ;
	struct nodoConsola * siguiente;
}nodoConsola;


typedef struct {

   char Nombre[50];
  int mediodepago; //1 efectivo, 2 patacones, 3 dolar     ahorro
    float totalCompra;
}stCliente ;

typedef struct nodoCliente{
	stCliente dato;
	struct nodoCliente* siguiente;
	struct nodoCliente* anterior;
}nodoCliente;

nodoConsola* iniciar_nodo();
nodoConsola* crear_consola(stConsola a);
stConsola ingresar_consola(stConsola dato);
void mostrar_consola(nodoConsola* a);
nodoConsola* agregar_ordenado (nodoConsola*lista, nodoConsola*nuevo);
nodoConsola* crear_lista(nodoConsola* lista, stConsola aux);
void mostrar_precio(nodoConsola* lista, int num);
int control_stock(nodoConsola*a,char marca[],char modelo[],int cant);


nodoCliente* inicnodocliente();
nodoCliente* crear_cliente(stCliente a);
stCliente nuevo_cliente(stCliente a);
void mostrar_cliente(nodoCliente* a,int alreves);
nodoCliente* agregar_final(nodoCliente* lista, nodoCliente* nuevo);
nodoCliente* buscar_final(nodoCliente* lista);
nodoCliente* software_de_ventas(nodoConsola* consolas, char cliente[], int modopago, nodoCliente* nuevo);
nodoConsola* buscar_modelo(nodoConsola* consola, char nombre[]);
nodoCliente* crea_lista_cliente(nodoCliente* lista, char cliente[],int modopago,float comprat);
nodoCliente* make_a_client(nodoCliente* a);

int main()
{

    int num;
    char yes='s';
    stConsola aux;
    nodoConsola* lista=iniciar_nodo;
    nodoConsola* a;
    char nombre[100];
    char marca[100];
    nodoCliente* lista2=inicnodocliente();
    float recaudacion=10;
    nodoCliente* primero=inicnodocliente;
    do
    {
        printf("\nSELECCIONE UN CASO: ");
        fflush(stdin);
        scanf("%i",&num);
        switch(num)
        {
        case 1:
            aux=ingresar_consola(aux);
            a=crear_consola(aux);
            mostrar_consola(a);
            break;
        case 2:
            lista=crear_lista(lista, aux);
            while(lista!=NULL)
        {
            mostrar_consola(lista);
            lista=lista->siguiente;
        }
            break;
        case 3:
            lista=crear_lista(lista, aux);
            printf("\nIngrese el precio en miles que desea buscar: ");
            scanf("%d", &num);
            mostrar_consola(lista);
            mostrar_precio(lista, num);
            break;
        case 4:
            lista=crear_lista(lista, aux);

            printf("\nIngrese la marca que busca: ");
            fflush(stdin);
            gets(marca);

            printf("\nIngrese el modelo que busca: ");
            fflush(stdin);
            gets(nombre);

            printf("\nIngrese la cantidad que busca: ");
            fflush(stdin);
            scanf("%d", &num);

            num=control_stock(lista,marca,nombre,num);

            if(num==1)
            {
                printf("\n hay stock");
            }
            else
            {
                printf("\nUnidades insuficientes");
            }
            break;
        case 5:
            lista=crear_lista(lista, aux);
            printf("\nIngrese el nombre del cliente: ");
            fflush(stdin);
            gets(nombre);
            printf("\nIngrese el medio de pago: ");
            fflush(stdin);
            scanf("%d", &num);
            lista2=software_de_ventas(lista, nombre, num, lista2);
            if(lista2)
            {
                printf("----------TICKET----------");
                mostrar_cliente(lista2,1);
            }
            else
            printf("\nNo se ha realizado ninguna venta!");
            break;
        case 6:
            lista=crear_lista(lista, aux);

        while(yes=='s')
        {
            lista2=inicnodocliente();
            printf("\nIngrese el nombre del cliente: ");
            fflush(stdin);
            gets(nombre);
            printf("\nIngrese el medio de pago: ");
            fflush(stdin);
            scanf("%d", &num);
            lista2=software_de_ventas(lista, nombre, num, lista2);
            if(lista2)
            {
                printf("----------TICKET----------");
                mostrar_cliente(lista2,1);
                recaudacion=lista2->dato.totalCompra+recaudacion;
            }
            else
                printf("\nNo se ha realizado ninguna venta!");

            printf("\nDesea atender un nuevo cliente? presione s ");
            fflush(stdin);
            scanf("%c", &yes);
        }


        printf("\n---------------------------------------");
        printf("\nRecaudacion en Miles: %.2f", recaudacion);
        printf("\n---------------------------------------");
            break;
        case 7:
            printf("\n Cliente en orden inverso(osea que empieza desde el ultimo hasta a final: ");
            mostrar_cliente(lista2,1);
            while(yes=='s')
            {
            lista2=make_a_client(lista2);
            printf("\n Desea continuar?: ");
            fflush(stdin);
            scanf("%c",&yes);
            }
            mostrar_cliente(lista2,1);
            break;
        case 8:
            break;

        default:
            break;
        }
        printf("\nQuiere ver otro punto?:");
        fflush(stdin);
        scanf("%c",&yes);

    }
    while(yes=='s'||yes=='S');


    return 0;
}


////////////////////////////////////////--1--////////////////////////////////////////

nodoConsola* iniciar_nodo()
{
    return NULL;
}
nodoConsola* crear_consola(stConsola a)
{
    nodoConsola*aux;
    aux=(nodoConsola*)malloc(sizeof(nodoConsola));
    aux->dato=a;
    aux->siguiente=NULL;

    return aux;
}

stConsola ingresar_consola(stConsola dato)
{

    printf("\n\n Ingrese codigo del producto: ");
    fflush(stdin);
    scanf("%i",&dato.codigoProducto);
    printf("\n\n Ingrese marca del producto: ");
    fflush(stdin);
    gets(dato.marca);
    printf("\n\n Ingrese modelo del producto: ");
    fflush(stdin);
    gets(dato.modelo);
    printf("\n\n Ingrese precio del producto: ");
    fflush(stdin);
    scanf("%f",&dato.precioEnMiles);
    printf("\n\n Ingrese stock del producto que desea comprar: ");
    fflush(stdin);
    scanf("%i",&dato.stock);

    return dato;
}

void mostrar_consola(nodoConsola* a)
{
    printf("\n--------------------------------------------------");
    printf("\nCODIGO DEL PRODUCTO: %i",a->dato.codigoProducto);
    printf("\nMARCA DEL PRODUCTO: %s",a->dato.marca);
    printf("\nPRECIO EN MILES: %.2f",a->dato.precioEnMiles);
    printf("\nSTOCK: %i",a->dato.stock);
    printf("\nMODELO: %s",a->dato.modelo);
    printf("\n--------------------------------------------------\n");
}

////////////////////////////////////////--2--////////////////////////////////////////

nodoConsola* agregar_ordenado (nodoConsola*lista, nodoConsola*nuevo)
{
    nodoConsola* ante;
    nodoConsola* aux;
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
        if(nuevo->dato.stock<lista->dato.stock)
        {
            nuevo->siguiente=lista;
            lista=nuevo;
        }
        else
        {
            ante=lista;
            aux=lista;
            while(aux && nuevo->dato.stock>aux->dato.stock)
            {
                ante=aux;
                aux=aux->siguiente;
            }
            ante->siguiente=nuevo;
            nuevo->siguiente=aux;

        }
    }
    return lista;
}
nodoConsola* crear_lista(nodoConsola* lista, stConsola aux)
{
    nodoConsola* a;
    char yes='s';
    while(yes=='s')
    {
        aux=ingresar_consola(aux);
        a=crear_consola(aux);
        lista=agregar_ordenado(lista,a);

        printf("\nDesea continuar: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return lista;

}

////////////////////////////////////////--3--////////////////////////////////////////

void mostrar_precio(nodoConsola* lista, int num)
{

    if(lista->siguiente==NULL && lista->dato.precioEnMiles==num)
    {
        mostrar_consola(lista);
    }
    else
    {
        if(lista->dato.precioEnMiles==num)
        {
            mostrar_consola(lista);
            mostrar_precio(lista->siguiente,num);
        }
    }
}

////////////////////////////////////////--4--////////////////////////////////////////

int control_stock(nodoConsola*a,char marca[],char modelo[],int cant)
{
    int flag=0;

    while(a && flag==0)
    {
        if(strcmp(a->dato.marca,marca)==0 && strcmp(a->dato.modelo,modelo)==0 && a->dato.stock>=cant)
        {
          flag=1;
        }
        a=a->siguiente;
    }
    return flag;
}
////////////////////////////////////////--5--////////////////////////////////////////

nodoCliente* inicnodocliente()
{
    return NULL;
}

nodoCliente* crear_cliente(stCliente a)
{
    nodoCliente* aux=(nodoCliente*)malloc(sizeof(nodoCliente));
    aux->dato=a;
    aux->siguiente=NULL;
    aux->anterior=NULL;
    return aux;
}

stCliente nuevo_cliente(stCliente a)
{
    printf("\nIngrese el nombre del Cliente: ");
    fflush(stdin);
    gets(a.Nombre);

    printf("\nIngrese el medio de pago: ");
    fflush(stdin);
    scanf("%d",&a.mediodepago);

    printf("\nIngrese el total de la compra: ");
    fflush(stdin);
    scanf("%f", &a.totalCompra);

    return a;
}

void mostrar_cliente(nodoCliente* a,int alreves)
{
    if(a)
    {
        if(alreves){
        mostrar_cliente(a->siguiente, alreves);
        printf("\n--------------------------------------------------");
        printf("\nNOMBRE DEL CLIENTE: %s",a->dato.Nombre);
        printf("\nMEDIO DE PAGO: %i",a->dato.mediodepago);
        printf("\nTOTAL DE LA COMPRA: %.2f",a->dato.totalCompra);
        printf("\n--------------------------------------------------\n");

        }
        else
        {
        printf("\n--------------------------------------------------");
        printf("\nNOMBRE DEL CLIENTE: %s",a->dato.Nombre);
        printf("\nMEDIO DE PAGO: %i",a->dato.mediodepago);
        printf("\nTOTAL DE LA COMPRA: %.2f",a->dato.totalCompra);
        printf("\n--------------------------------------------------\n");
        mostrar_cliente(a->siguiente,alreves);
        }
    }
    else
        {
        return;
    }
}

nodoCliente* agregar_final(nodoCliente* lista, nodoCliente* nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodoCliente* aux=buscar_final(lista);
        aux->siguiente=nuevo;
        nuevo->anterior=aux;
    }
    return lista;
}

nodoCliente* buscar_final(nodoCliente* lista)
{
    while(lista->siguiente)//es lo mismo que preguntar si existe
    {
        lista=lista->siguiente;
    }
    return lista;
}
nodoCliente* crea_lista_cliente(nodoCliente* lista, char cliente[],int modopago,float comprat)
{
    nodoCliente* a;
    stCliente name;
    strcpy(name.Nombre,cliente);
    name.mediodepago=modopago;
    name.totalCompra=comprat;

    a=crear_cliente(name);
    lista=agregar_final(lista,a);


    return lista;
}

nodoCliente* software_de_ventas(nodoConsola* consolas, char cliente[], int modopago, nodoCliente* nuevo)
{
    char compra[100];
    char marca[100];
    int cant;
    int num;
    float total=0;
    char yes='s';
    system("cls");

    while(yes=='s')
    {
        printf("\nQue producto desea comprar: ");
        fflush(stdin);
        gets(compra);

        printf("\nQue marca es?: ");
        fflush(stdin);
        gets(marca);

        printf("\n Que cantidad desea comprar?: ");
        fflush(stdin);
        scanf("%d",&cant);

        num=control_stock(consolas,marca,compra,cant);

        if(num==1)
        {
            consolas=buscar_modelo(consolas,compra);
            consolas->dato.stock=consolas->dato.stock-cant;

            cant=cant*consolas->dato.precioEnMiles;
            total=total+(float)cant;

        }
        else
        {
            printf("\n No hay stock disponible jiji ");

        }
        printf("\n Desea continuar con su compra?: ");
        fflush(stdin);
        scanf("%c",&yes);
    }
    if(total!=0)
    {
        nuevo=crea_lista_cliente(nuevo,cliente,modopago,total);
    }

    return nuevo;
}

nodoConsola* buscar_modelo(nodoConsola* consola, char nombre[])
{
    nodoConsola* aux=iniciar_nodo;

    while(consola)
    {
        if(strcmp(consola->dato.modelo,nombre)==0)
        {
            aux=consola;
        }
        consola=consola->siguiente;
    }

    return aux;
}

nodoCliente* make_a_client(nodoCliente* a)
{
    stCliente aux;
    aux=nuevo_cliente(aux);
    nodoCliente* nuevo=crear_cliente(aux);

    if(a)
    {
        nodoCliente* ultimo=buscar_final(a);
        nuevo->anterior=ultimo;
        ultimo->siguiente=nuevo;

    return a;
    }
    else
    {
        return nuevo;
    }

}
