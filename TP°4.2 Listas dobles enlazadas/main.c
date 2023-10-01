#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int num;
    struct nodo*sig;
    struct nodo*ante;
} nodo;

nodo* inicnodo();
nodo* carga_doble_nodo(nodo* lista);
nodo* nuevoNodo(int num);
nodo* agregarppio(nodo* lista, nodo* nuevo);
void muestra_nodo(nodo* lista);
void escribe(nodo* lista);
nodo* borra_doble(nodo*lista, int num);
nodo* buscar_ultimo(nodo* lista);
void muestra_nodo2(nodo* lista);
int es_capicua(nodo* a, nodo* b);
nodo * borra_medio (nodo* list, nodo*ultimo);
nodo* agregarFinal(nodo* lista, nodo* nuevo);


typedef struct
{
      nodo* pri;
      nodo* ulti;
} Fila;

void inicfila(Fila* a);
void agregar(Fila* a, int n);
int extraer (Fila * a);
void mostrar(Fila* a);
void leer(Fila* a);
int primero(Fila* a);



int main()
{
    int num;
    nodo* list;
    nodo* aux;
    Fila fabri;

    printf("Bienvenido a la Guia de Listas Doblemente enlazadas seleccione un ejercicio del 1 al 4: ");
    fflush(stdin);
    scanf("%d", &num);
    switch(num)
    {
    case 1:
        list=inicnodo();
        list=carga_doble_nodo(list);
        muestra_nodo(list);

        printf("Que numero desea borrar?: ");
        scanf("%d", &num);

        list=borra_doble(list, num);
        muestra_nodo(list);
        break;

    case 2:
        list=inicnodo();
        aux=inicnodo();
        list= carga_doble_nodo(list);
        aux=buscar_ultimo(list);
        num=es_capicua(list,aux);
        (num==1)?printf("\nEl elemento es capicua"):printf("\nEl elemento NO es capicua");

        break;

    case 3:
        list=inicnodo();
        aux=inicnodo();
        list= carga_doble_nodo(list);
        //muestra_nodo(list);
        aux=buscar_ultimo(list);
        list=borra_medio(list,aux);
        muestra_nodo(list);
        break;

    case 4:
        inicfila(&fabri);
        (filavacia(&fabri)==1)?printf("\nLa Fila esta Vacia\n"):printf("\nLa Fila NO esta Vacia\n");
        agregar(&fabri, 1);

        leer(&fabri);
        leer(&fabri);
        leer(&fabri);
        leer(&fabri);
        leer(&fabri);
        (filavacia(&fabri)==1)?printf("\nLa Fila esta Vacia\n"):printf("\nLa Fila NO esta Vacia\n");
        mostrar(&fabri);

        num=extraer(&fabri);
        mostrar(&fabri);
        printf("\nESTE SE EXTRAJO: %i", num);

        num=primero(&fabri);
        printf("\nPRIMER NUMERO: %i", num);
        break;

    default:
        printf("ERROR FATAL, LA COMPU SE AUTODESTRUIRA EN 3...2...1");
        break;
    }
    return 0;
}
/////////////////////////////////////////--1--/////////////////////////////////////////////////
/*Modificar la función borrarNodo() de listas simples y transformarla para el caso de una lista doblemente vinculada.*/
nodo* inicnodo()
{
    return NULL;
}

nodo* carga_doble_nodo(nodo* lista)
{
    int n;
    nodo* nuevo;
    char yes='s';

    while(yes=='s')
    {
        printf("\nCargue un elemento: ");
        fflush(stdin);
        scanf("%d", &n);

        nuevo=nuevoNodo(n);
        lista=agregarppio(lista, nuevo);

        printf("Presione 's' para continuar: ");
        fflush(stdin);
        scanf("%c", &yes);
    }
    return lista;
}

nodo* nuevoNodo(int num)
{

    nodo* aux=(nodo*)malloc(sizeof(nodo));
    aux->num=num;
    aux->ante=NULL;
    aux->sig=NULL;

    return aux;
}

nodo* agregarppio(nodo* lista, nodo* nuevo)
{
    nuevo->sig=lista;
    if(lista!=NULL)
    {
        lista->ante=nuevo;
    }

return nuevo;
}

void muestra_nodo(nodo* lista)
{
    nodo* seg=lista;

    while(seg!=NULL)
    {
        escribe(seg);
        seg=seg->sig;
    }
    printf("\n\n");
}

void muestra_nodo2(nodo* lista)
{
    nodo* seg=lista;

    while(seg!=NULL)
    {
        escribe(seg);
        seg=seg->ante;
    }
    printf("\n\n");
}

void escribe(nodo* lista)
{
    printf("|%d|", lista->num);
}

nodo* borra_doble(nodo*lista, int num)
{
    nodo* aux;
    nodo* ante;
    nodo* next;

    if(lista!=NULL && lista->num==num)
    {
        aux=lista;
        lista=lista->sig;
        free(aux);
    }
    else
    {
        aux=lista;
        while((aux!=NULL) && aux->num!=num)
        {
            ante=aux;
            aux=aux->sig;

        }
            ante->sig=aux->sig;
            next=ante->sig;
        if(aux!=NULL)
        {

            next->ante=ante;
            free(aux);
        }
    }
    return lista;
}

nodo* buscar_ultimo(nodo* lista)
{
    while(lista->sig!=NULL)
    {
        lista=lista->sig;
    }
    return lista;
}
/////////////////////////////////////////--2--/////////////////////////////////////////////////
/*Crear una función recursiva que determine si una lista doblemente vinculada es capicúa.*/
int es_capicua(nodo* a, nodo* b)
{
    int flag=0;

    if(a==NULL && b==NULL)
    {
       flag=1;
    }
    else
    {
        if(a->num==b->num)
        {
            flag=es_capicua(a->sig,b->ante);
        }
    }

    return flag;
}
/////////////////////////////////////////--3--/////////////////////////////////////////////////
/*Dada una lista doblemente enlazada ordenada de enteros, eliminar el  nodo que se encuentra en el punto medio de la lista, si la cantidad de nodos es par, eliminar el inmediatamente superior.*/
nodo * borra_medio (nodo* list, nodo*ultimo)
{
    nodo*seg=list;
    nodo* aux=list;
    int flag=0;

  while(seg->sig!=NULL && flag==0)
  {
      if(aux->num==ultimo->num)
      {
          list=borra_doble(list, aux->num);
          flag=1;

      }
      else if(aux->sig==ultimo && ultimo->ante==aux)
      {
          list=borra_doble(list, ultimo->num);
          flag=1;
      }
      seg=seg->sig;
      aux=aux->sig;
      ultimo=ultimo->ante;
  }

    return list;
}


nodo* agregarFinal(nodo* lista, nodo* nuevo)
{
    nodo* ultimo;
    if(!lista)
        lista = nuevo;
    else
    {
        ultimo = buscar_ultimo(lista);
        nuevo->ante=ultimo;
        ultimo->sig = nuevo;
    }
    return lista;
}
/////////////////////////////////////////--4--/////////////////////////////////////////////////

/*Crear el TDA Fila, implementada con listas doblemente vinculadas. Se puede trabajar con librerías separadas, una para la lista doble y otra para el TDA Fila.*/
void inicfila(Fila* a)
{
    a->pri=NULL;
    a->ulti=NULL;
}

void agregar(Fila* a, int n)
{
    nodo* aux=nuevoNodo(n);
    a->pri=agregarFinal(a->pri,aux);
    a->ulti=aux;
}

void mostrar(Fila* a)
{
    muestra_nodo(a->pri);
}

int extraer (Fila * a)
{
    int aux = a->pri->num;

   a->pri=borra_doble(a->pri,a->pri->num);

   return aux;
}

void leer(Fila* a)
{
    int num;

    printf("\nQue numero desea ingresar: ");
    fflush(stdin);
    scanf("%i", &num);

    agregar(a, num);
}

int primero(Fila* a)
{
    return a->pri->num;
}

int filavacia(Fila* a)
{
    return(a->pri==NULL)?1:0;
}
