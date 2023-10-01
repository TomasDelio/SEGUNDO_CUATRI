#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////
typedef struct
{
    char nombre[25];
    int edad;
    struct nodo* sig;
} nodo;


typedef struct
{
    int num;
    struct slot* sig;
} slot;

typedef struct
{
    slot* lista;
}Pila;
///////////////////////////
nodo* iniciar_lista();
nodo* crear_nodo(char n[25],int edad);
nodo* buscar_ultimo(nodo* lista);
nodo *agregar (nodo*lista,nodo*nuevo);
void escribir(nodo*aux);
void recorrer_mostrar(nodo*lista);
nodo* carga_nodo(nodo*lista);
void cargar_archi(char archis[]);
void ver_archi(char archis[]);
nodo* archi_lista(char archis[],nodo*lista);
nodo* agregar_ordenado(nodo*lista,nodo*n);
nodo* archi_lista_ordenado(char archi[],nodo*lista);
int encontrar_lista(nodo* lista,int num);
nodo* intercalar(nodo* lista1,nodo* lista2);
nodo* invertir_lista(nodo*lista);

///Funciones Pila
void inicpila(Pila* a);
void apilar (Pila* a, int nuevo);
void mostrar(Pila* a);
int tope(Pila* a);
int desapilar(Pila* a);
void leer(Pila* a);


slot* creanodoS(int num);
slot* agregarppioS(slot* a, slot* nuevonodo);
void printea(slot* n);
slot* apilar_pares(Pila* a, slot* n);
slot* inicslot();
slot* borrar_slot(slot* a, int num);
void apilar (Pila* , int);


//////////////////////////////////
int main()
{
    int num;
    char option;
    char yes;
    char the[100];
    char the2[100];
    FILE* archi;
    strcpy(the,"archi.bin");

    nodo* lista;

    nodo* lista1;
    nodo* lista2;

    slot* listaPar;
    nodo* listaIntercalada;
    Pila pilita;

    do
    {
    printf("\nListas Simplemente Enlazadas: seleccione un ejercicio del 1 al 7: ");
    scanf("%i", &num);

    switch(num)
    {
    case 1:
        lista=iniciar_lista();
        cargar_archi(the);
        ver_archi(the);

        lista=archi_lista(the,lista);
        recorrer_mostrar(lista);

        break;
    case 2:
        lista=iniciar_lista();
        cargar_archi(the);
        ver_archi(the);

        lista=archi_lista_ordenado(the,lista);
        recorrer_mostrar(lista);

        break;
    case 3:
        lista=iniciar_lista();
        lista=carga_nodo(lista);
        printf("\nIngrese la edad que desea buscar: ");
        fflush(stdin);
        scanf("%i", &num);

        num=encontrar_lista(lista,num);

        (num==1)?printf("\nEl nuemero se encuantra en la lista "):printf("\nEl numero NOO se encuantra en la lista ");

        break;
    case 4:
        lista1=iniciar_lista();
        lista2=iniciar_lista();
        lista1=carga_nodo(lista1);
        lista2=carga_nodo(lista2);

        listaIntercalada=iniciar_lista();

        listaIntercalada=intercalar(lista1,lista2);
        recorrer_mostrar(lista1);

        break;
    case 5:
        lista=iniciar_lista();
        lista=carga_nodo(lista);
        printf("\n Lista");
        recorrer_mostrar(lista);
        printf("\nLista invertida");
        lista=invertir_lista(lista);

        break;
    case 6:
        inicpila(&pilita);
        num=pilavacia(&pilita);


        apilar(&pilita, 93);
        apilar(&pilita, 65);
        apilar(&pilita, 47);

        num=pilavacia(&pilita);
        mostrar(&pilita);

        break;
    case 7:
        inicpila(&pilita);
        listaPar = inicslot();

        apilar(&pilita, 55);
        apilar(&pilita, 25);
        apilar(&pilita, 23);
        apilar(&pilita, 64); //
        apilar(&pilita, 83);
        apilar(&pilita, 11);
        apilar(&pilita, 2); //
        apilar(&pilita, 4);//
        apilar(&pilita, 6);//
        apilar(&pilita, 8);//
        apilar(&pilita, 24);//
        apilar(&pilita, 28);//
        listaPar = apilar_pares(&pilita, listaPar);

        listaPar=borrar_slot(listaPar, 10);
        while(listaPar!=NULL)
        {
            printea(listaPar);
            listaPar=listaPar->sig;
        }

        break;
    }
        printf("\nDesea hacer otro ejercicio? presione 's' para si ");
        fflush(stdin);
        scanf("%c", &option);
    }
    while(yes=='s'||yes=='S');
        return 0;
}
////////////////////////////////--1--////////////////////////////////
/*Hacer un programa que lea de un archivo datos y los inserte en una lista. */

nodo* iniciar_lista()
{
    return NULL;
}

nodo* crear_nodo(char n[25],int edad)
{
    nodo* aux=(nodo*)malloc(sizeof(nodo));
    aux->edad=edad;
    strcpy(aux->nombre,n);
    return aux;

}

nodo *agregar (nodo*lista,nodo*nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
     nuevo->sig=lista;
    lista=nuevo;
    }
    return lista;
}

void escribir(nodo*aux)
{
    printf("\n Nombre : %s\n",aux->nombre);
    printf("\n Edad : %s\n",aux->edad);

}
void recorrer_mostrar(nodo*lista)
{
    nodo* seg=lista;

    while(seg!=NULL)
    {
        escribir(seg);
        seg=seg->sig;
    }
}

nodo* buscar_ultimo(nodo* lista)
{
    return(!lista || !lista->sig)? lista:buscar_ultimo(lista->sig);
}

nodo* agregar_final(nodo* lista,nodo*nuevo)
{
    if(!lista)
    {
        lista=nuevo;
    }
    else
    {
        nodo* ultimo=buscar_ultimo(lista);
        ultimo->sig=nuevo;
    }
    return lista;
}


nodo* carga_nodo(nodo*lista)
{
    nodo*n;
    char yes='s';
    int edad;
    char nombre[25];

    while(yes=='s'||yes=='S')
    {
        printf("\n Ingrese el nombre del alumno: ");
        fflush(stdin);
        gets(nombre);

        printf("\nIngrese la edad del alumno: ");
        fflush(stdin);
        scanf("%d", &edad);

        n=crear_nodo(nombre,edad);

        lista=agregar_final(lista,n);

        printf("\nDesea agregar un nuevo elemento a la lista? presiona 's' para hacerlo: ");
        fflush(stdin);
        scanf("%c", &yes);
    }

    return lista;
}



void cargar_archi(char archis[])
{
    FILE* archi;
    nodo lista;
    archi=fopen(archis,"ab");
    char yes='s';

    if(archi !=NULL)
    {
        while(yes=='s')
        {
            printf("\n INGRESE EL NOMBRE DEL ALUMNO: ");
            fflush(stdin);
            gets(lista.nombre);

            printf("\n INGRESE LA EDAD DEL ALUMNO: ");
            fflush(stdin);
            scanf("%d",&lista.edad);

            printf("\n\n");

            fwrite(&lista,sizeof(nodo),1,archi);

            printf("\n Desea agregar otro elemento ? Press 's': ");
            fflush(stdin);
            scanf("%c",&yes);
        }
        fclose(archi);
    }
}

void ver_archi(char archis[])
{
    FILE *archi;
    archi=fopen(archis,"rb");
    nodo lista;
    if(archi !=NULL)
    {
        while(!feof(archi))
        {
            fread(&lista, sizeof(nodo),1,archi);

            if(!feof(archi))
            {
                printf("\n----------------------------------------------\n");
                printf("\nNombre Y Apellido: %s", lista.nombre);
                printf("\nEdad: %i", lista.edad);
                printf("\n----------------------------------------------");

            }
        }
        fclose(archi);
    }

}

nodo* archi_lista(char archis[],nodo*lista)
{
    FILE*archi;
    archi=fopen(archi,"rb");
    nodo aux;
    nodo* nodo2;

    while(fread(&aux,sizeof(nodo),1,archi)>0)
    {
        nodo2=crear_nodo(aux.nombre,aux.edad);
        lista=agregar_final(lista,nodo2);
    }
    fclose(archi);
    return lista;
}
////////////////////////////////--2--////////////////////////////////
/*Hacer un programa que lea de un archivo datos y los inserte en una lista en forma ordenada. */


nodo* agregar_ordenado(nodo*lista,nodo*n)
{
    if(lista==NULL)
    {
        lista=n;
    }
    else
    {
        if(n->edad<lista->edad)
        {
            lista=agregar(lista,n);
        }
        else
        {
            nodo*ante=lista;
            nodo*aux=lista;

            while(aux!=NULL && n->edad>aux->edad)
            {
                ante=aux;
                aux=aux->sig;
            }
            ante->sig=n;
            n->sig=aux;
        }
    }
    return lista;
}



nodo* archi_lista_ordenado(char archis[],nodo*lista)
{
    FILE*archi;
    archi=fopen(archi,"rb");
    nodo aux;
    nodo* nodo2;

    while(fread(&aux,sizeof(nodo),1,archi>0))
    {
        nodo2=crear_nodo(aux.nombre,aux.edad);
        lista=agregar_ordenado(lista,nodo2);
    }
    fclose(archi);

    return lista;
}

////////////////////////////////--3--////////////////////////////////
/* Hacer una función que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada. */

int encontrar_lista(nodo* lista,int num)
{
    nodo* seg=lista;
    int flag=0;

    while(seg!=NULL)
    {
        if(lista->edad=num)
        {
            flag=1;
        }
        seg=seg->sig;
    }
    return flag;
}

////////////////////////////////--4--////////////////////////////////
/*Hacer una función que intercale en orden los elementos de dos listas ordenadas generando una nueva lista.
Se deben redireccionar los punteros, no se deben crear nuevos nodos con la función crearNodo().
*/

nodo* intercalar(nodo* lista1,nodo* lista2)
{
    nodo* nuevalista=iniciar_lista();
    nodo* aux;

    while(lista1!=NULL && lista2!=NULL)
    {
        if(lista1->edad < lista2->edad)
        {
            aux=lista1;
            lista1=lista2->sig;
        }
        aux->sig=NULL;
        nuevalista=agregar_final(nuevalista,aux);
    }

    if(lista1!=NULL)
    {
        aux=lista1;
    }
    else
    {
        aux=lista2;
    }
    nuevalista=agregar_final(nuevalista,aux);

    return nuevalista;
}

////////////////////////////////--5--////////////////////////////////
/*Invertir los elementos de una lista redireccionando solamente los punteros.
(No se deben crear nuevos nodos con la función crearNodo())*/

nodo* invertir_lista(nodo*lista)
{
    nodo* primero=iniciar_lista();
    nodo* aux=iniciar_lista();

    while(lista!=NULL)
    {
        aux=lista;
        lista=lista->sig;
        aux->sig=NULL;
        primero=agregar(primero,aux);
    }
    return primero;
}
////////////////////////////////--6--////////////////////////////////
/*Codificar el TDA Pila con las funciones necesarias,
 implementada con una lista enlazada (Similar al ejercicio hecho con arreglo). */

 //////////////////////////////////--PILAS--/////////////////////////
void inicpila(Pila* a)
{
    a->lista=NULL;
}

void apilar(Pila* a, int nuevo)
{
    slot* n;

        n=creanodoS(nuevo);
       a->lista = agregarppioS(a->lista, n);

}
slot* cargaslot(slot* lista, int num)
{
    slot* n;
    char yes ='s';

        n=creanodoS(num);

        lista = agregarppioS(lista, n);


    return lista;
}

slot* creanodoS(int num)
{
    slot* aux=(slot*)malloc(sizeof(slot));
    aux->num= num;
    aux->sig = NULL;
    return aux;
}

slot* agregarppioS(slot* a, slot* nuevonodo)
{

    if(a==NULL)
    {
        a=nuevonodo;
    }
    else
    {
        nuevonodo->sig=a;
        a=nuevonodo;
    }

    return a;
}

void mostrar(Pila* a)
{
    slot* seg= a->lista;
    printf("\nTOPE---------------------BASE\n");
    while(seg!=NULL)
    {
        printea(seg);

        seg=seg->sig;
    }
    printf("\n\n");
}

void printea(slot* n)
{
    printf("|%i|", n->num);
}

int tope(Pila* a)
{
    return a->lista->num;
}

int desapilar(Pila* a)
{

    int aux;
    aux=a->lista->num;
    a->lista=a->lista->sig;

    return aux;
}

void leer(Pila* a)
{
    int aux;

    printf("\nIngrese un elemento: ");
    scanf("%d", &aux);

    apilar(a,aux);
}

int pilavacia(Pila* a)
{
    return(a->lista==NULL)?1:0;
}

slot* inicslot()
{
    return NULL;
}

slot* apilar_pares(Pila* a, slot* n)
{
    Pila aux;
    inicpila(&aux);
    slot* nuevo;

    while(!pilavacia(a))
    {
        if(tope(a)%2==0)
        {
            nuevo=creanodoS(tope(a));

            n=agregarppioS(n, nuevo);
        }
        apilar(&aux, desapilar(a));

    }

    while(!pilavacia(&aux))
    {
        apilar(a, desapilar(&aux));
    }

return n;
}

slot* borrar_slot(slot* a, int num)
{
    slot* aux;
    slot* ante;
    slot* seg=a;
     while(seg->sig!=NULL)
    {
    if(a!=NULL && a->num<num)
    {
        nodo*aux=a;
        a=a->sig;
        free(aux);

    }
    else
    {
        aux=a;
        while((aux!=NULL) && aux->num>num)
        {
            ante=aux;
            aux=aux->sig;
        }
        if(aux!=NULL)
        {
            ante->sig=aux->sig;
            free(aux);
        }
    }
    seg=seg->sig;
    }
    return a;
}


slot* borrar_menores(slot* a)
{
    slot* seg=a;
    slot* aux;
    while(seg->sig!=NULL)
    {
        if(a->num>10)
        {
             a=a->sig;
        }
        else
        {
           a=borrar_slot(a,a->num);
        }

        seg=seg->sig;

    }
    return a;
}


