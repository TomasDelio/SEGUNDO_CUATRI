#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

typedef struct
{
    int codigoProducto;
    char marca[50]; // Nintendo Switch, Xbox, Playstation
    float precioEnMiles;
    int stock;
    char modelo[50];// Común, Pro, Slim
} stConsola;

typedef struct nodoConsola
{
    stConsola dato;
    struct nodoConsola * siguiente;
} nodoConsola;

typedef struct
{
    char Nombre[50];
    int mediodepago; //1 efectivo, 2 patacones, 3 dolar     ahorro
    float totalCompra;
} stCliente;

typedef struct nodoCliente
{
    stCliente dato;
    struct nodoCliente* siguiente;
    struct nodoCliente* anterior;
} nodoCliente;

//Funciones Consolas
nodoConsola * crear_consola(stConsola a);
stConsola nueva_consola(stConsola a);
nodoConsola* agregar_ordenado(nodoConsola* lista, nodoConsola* nuevo);
nodoConsola* inicnodoconsola();
nodoConsola* crea_lista_consola(nodoConsola* lista, stConsola aux);
void mostrar_precio(nodoConsola* a, int num);
int control_stock(nodoConsola* a, char marca[], char modelo[], int cantidad);
nodoConsola* buscar_modelo(nodoConsola* consola, char nombre[]);

//Funciones Clientes
nodoCliente* inicnodocliente();
nodoCliente* crear_cliente(stCliente a);
stCliente nuevo_cliente(stCliente a);
void mostrar_cliente(nodoCliente* a,int alreves);
nodoCliente* agregar_final(nodoCliente* lista, nodoCliente* nuevo);
nodoCliente* buscar_final(nodoCliente* lista);
nodoCliente* crea_lista_cliente(nodoCliente* lista, char cliente[],int modopago,float comprat);
nodoCliente* software_de_ventas(nodoConsola* consolas, char cliente[], int modopago, nodoCliente* nuevo);
nodoCliente* make_a_client(nodoCliente* a);

int main()
{
    int num;
    stConsola aux;
    nodoConsola* lista;
    nodoConsola *a;
    lista=inicnodoconsola();
    char yes='s';
    char nombres[100];
    char marcas[100];
    nodoCliente* clayton;
    clayton=inicnodocliente();
    float recaudacion=10;
    nodoCliente* primero=inicnodocliente;

    printf("\nWelcome al simulador del primer parcial del segundo cuatri selecciones un ejercicio: ");
    scanf("%i",&num);
    switch(num)
    {
    case 1:
        aux=nueva_consola(aux);
        a=crear_consola(aux);
        mostrar_consola(a);
        break;

    case 2:
        lista=crea_lista_consola(lista, aux);

        while(lista!=NULL)
        {
            mostrar_consola(lista);
            lista=lista->siguiente;
        }
        break;

    case 3:
        lista=crea_lista_consola(lista, aux);
        printf("\nIngrese el precio en miles que desea buscar: ");
        scanf("%d", &num);
        mostrar_consola(lista);
        mostrar_precio(lista, num);
        break;

    case 4:
        lista=crea_lista_consola(lista,aux);

        printf("\nIngrese la marca que busca: ");
        fflush(stdin);
        gets(marcas);

        printf("\nIngrese el modelo que busca: ");
        fflush(stdin);
        gets(nombres);

        printf("\nIngrese la cantidad que busca: ");
        fflush(stdin);
        scanf("%d", &num);

        num=control_stock(lista,marcas,nombres,num);

        (num==1)?printf("\nHay stock"):printf("\nUnidades insuficientes");
        break;

    case 5:
        lista=crea_lista_consola(lista,aux);
        printf("\nIngrese el nombre del cliente: ");
        fflush(stdin);
        gets(nombres);
        printf("\nIngrese el medio de pago: ");
        fflush(stdin);
        scanf("%d", &num);
        clayton=software_de_ventas(lista, nombres, num, clayton);
        if(clayton)
        {
            printf("----------TICKET----------");
            mostrar_cliente(clayton,1);
        }
        else
            printf("\nNo se ha realizado ninguna venta!");
        break;

    case 6:
        lista=crea_lista_consola(lista,aux);

        while(yes=='s')
        {
            clayton=inicnodocliente();
            printf("\nIngrese el nombre del cliente: ");
            fflush(stdin);
            gets(nombres);
            printf("\nIngrese el medio de pago: ");
            fflush(stdin);
            scanf("%d", &num);
            clayton=software_de_ventas(lista, nombres, num, clayton);
            if(clayton)
            {
                printf("----------TICKET----------");
                mostrar_cliente(clayton,1);
                recaudacion=clayton->dato.totalCompra+recaudacion;
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
        mostrar_cliente(clayton,1);
        while(yes=='s')
        {
            clayton=make_a_client(clayton);
            printf("\n Desea continuar?: ");
            fflush(stdin);
            scanf("%c",&yes);
        }
        mostrar_cliente(clayton,1);

        break;
    default:
        printf("\nNumero erroneo campeon");
        break;
    }



    return 0;
}

nodoConsola* inicnodoconsola()
{
    return NULL;
}

nodoConsola * crear_consola(stConsola a)
{
    nodoConsola *aux=(nodoConsola*)malloc(sizeof(nodoConsola));
    aux->dato=a;
    aux->siguiente=NULL;

    return aux;
}

stConsola nueva_consola(stConsola a)
{
    printf("\nCODIGO DEL PRODUCTO: ");
    fflush(stdin);
    scanf("%i",&a.codigoProducto);

    printf("\nMARCA DEL PRODUCTO: ");
    fflush(stdin);
    gets(a.marca);

    printf("\nPRECIO MILES: ");
    fflush(stdin);
    scanf("%f",&a.precioEnMiles);

    printf("\nSTOCK: ");
    fflush(stdin);
    scanf("%i",&a.stock);

    printf("\nMODELO: ");
    fflush(stdin);
    gets(a.modelo);

    return a;
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

nodoConsola* agregar_ordenado(nodoConsola* lista, nodoConsola* nuevo)
{
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
            nodoConsola* ante=lista;
            nodoConsola* aux=lista;
            while(aux!=NULL && nuevo->dato.stock>aux->dato.stock)
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

nodoConsola* crea_lista_consola(nodoConsola* lista, stConsola aux)
{
    nodoConsola* a;
    char yes='s';
    while(yes=='s')
    {
        aux=nueva_consola(aux);
        a=crear_consola(aux);
        lista=agregar_ordenado(lista,a);
        printf("\nDesea continuar: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return lista;
}

void mostrar_precio(nodoConsola* a, int num)
{

    if(a->siguiente==NULL && a->dato.precioEnMiles==num)
    {
        mostrar_consola(a);
    }
    else
    {
        if(a->dato.precioEnMiles==num)
        {
            mostrar_consola(a);
            mostrar_precio(a->siguiente,num);
        }
    }
}

int control_stock(nodoConsola* a, char marca[], char modelo[], int cantidad)
{
    int flag=0;


    while(a && flag==0)
    {
        if(strcmp(a->dato.marca,marca)==0 && strcmp(a->dato.modelo,modelo)==0 && a->dato.stock>=cantidad)
        {
            flag=1;
        }
        a=a->siguiente;
    }
    return flag;
}

/* printf("\n---|%s||%s||%d|---", marca, modelo, cantidad);
                printf("\n|%s||%s||%d|", a->dato.marca, a->dato.modelo, a->dato.stock);*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    nodoConsola* aux=inicnodoconsola;

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


/*void mostrar_cliente(nodoCliente* a)
{
    while(a)
    {
        printf("\n--------------------------------------------------");
        printf("\nNOMBRE DEL CLIENTE: %s",a->dato.Nombre);
        printf("\nMEDIO DE PAGO: %i",a->dato.mediodepago);
        printf("\nTOTAL DE LA COMPRA: %.2f",a->dato.totalCompra);
        printf("\n--------------------------------------------------\n");
        a=a->siguiente;
    }
}
*/
