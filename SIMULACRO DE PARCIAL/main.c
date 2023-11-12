#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct
{
    char nombreYapellido [30];
    int edad;
    int dni;
} personaje;

typedef struct
{
    personaje dato;
    struct nodoLista* anterior;
    struct nodoLista* siguiente;
} nodoLista;

typedef struct
{
    char nombreEspecie[20]; //vampiro, hombre lobo, hada, medium, cambia formas, humano
    int rankPeligrosidad; //1 el más peligroso, 6 el menos peligroso
    float promedioEdad; // 0
    nodoLista* personajes; //lista de personajes que pertencen a esta especie
} Especie;
/////////////////////////////////////////////////////////////////////////////
typedef struct
{
    char nombreEspecie[20];
    int rankPeligrosidad;
    float promedioEdad;
    char nombreYapellido [30];
    int edad;
    int dni;
} registro;

typedef struct arbol
{
    registro data;
    struct arbol* izq;
    struct arbol* der;
} arbol;

nodoLista* inic_nodo();
nodoLista* nuevo_nodo(personaje nuevo);
nodoLista* agregar_principio(nodoLista* lista,nodoLista* nuevo);
nodoLista* carga_personaje(nodoLista* lista, char nombre[]);


int buscar_especie(Especie arre[], char nombre[], int val);
int carga_especie(Especie arre[], int val, int dim);
int buscar_ranking(Especie arre[], int a, int val, char nombre[]);
void mostrar_criatura(Especie arre[], int val);
void mostrar_personaje(nodoLista* a);

arbol* inic_arbol();
arbol* nuevo_arbol(registro nuevo);
arbol* agregar_ordenado(arbol* arbolito,arbol*nuevo);
void especies_to_arboles(Especie arre[], registro aux[], int val);
arbol* insertar_arbol(registro aux[],int val,arbol* arbolito);
void mostrar_inorder(arbol* arbolito);

int sumar_especies(nodoLista* a,int* i);
float promediar(int cont,int cant);
float promedio_edad(nodoLista* a);

int main()
{
    Especie arrc[99];
    registro res[99];
    int opcion = 0;
    int val=0;
    arbol* arbolito=inic_arbol();
    do
    {
        printf("\n\n--- Menu ---\n");
        printf("1. Cargar especie \n");
        printf("2. Mostrar especie\n");
        printf("3. Mostrar especie\n");
        printf("4. Salir \n");
        printf("Ingrese una opcion: ");
        fflush(stdin);
        scanf("%i", &opcion);

        switch (opcion)
        {
        case 1:
            val=carga_especie(arrc,val,6);
            break;

        case 2:
            mostrar_criatura(arrc,val);
            break;
        case 3:
            especies_to_arboles(arrc,res,val);
            arbolito=insertar_arbol(res,val,arbolito);
            mostrar_criatura(arrc,val);
            printf("\n TOP MAS PELIGROSOS\n");
            mostrar_inorder(arbolito);

            break;

        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }

    }
    while (opcion != 4);

    return 0;
}

/*Hacer una función que me permita cargar especies al arreglo de especies cuya dimensión es 6.
 Primero, debe verificar la existencia de la especie.
Si ya existe, me permite cargar personajes de esa especie.
Si la especie no existía previamente en el arreglo, cargo la especie y luego me pide que cargue personajes.
Por default, el promedio de edad de la especie al momento de cargarla es 0 (no pedírsela al usuario, cargarla manualmente).
Verificar que el ranking de peligrosidad no se repita.Por ejemplo, si el usuario ingresó la especie “vampiro”, y le puso el puesto 1,
si ingresa luego a los hombres lobo, ya no le puede ingresar el 1. En caso de que el usuario ingrese un puesto repetido,
 pedirle que ingrese de nuevo otro puesto hasta que ingrese uno disponible, del 1 al 6.*/

nodoLista* inic_nodo()
{
    return NULL;
}

nodoLista* nuevo_nodo(personaje nuevo)
{
    nodoLista* aux=(nodoLista*)malloc(sizeof(nodoLista));
    aux->dato.dni=nuevo.dni;
    aux->dato.edad=nuevo.edad;
    strcpy(aux->dato.nombreYapellido,nuevo.nombreYapellido);
    aux->siguiente=NULL;
    aux->anterior=NULL;


    return aux;
}

nodoLista* agregar_principio(nodoLista* lista,nodoLista* nuevo)
{
    nuevo->siguiente=lista;

    if(lista)
    {
         printf("AAAAAA ");
        lista->anterior=nuevo;
        printf("123 ");
    }
    return nuevo;
}

nodoLista* carga_personaje(nodoLista* lista, char nombre[])
{
    personaje aux;
    nodoLista* nuevo=inic_nodo();

    char yes='s';

    while(yes=='s')
    {
        printf("\n Nombre Y Apellido del mounstro: ");
        fflush(stdin);
        gets(aux.nombreYapellido);

        printf("\n DNI del mounstro (wtf): ");
        fflush(stdin);
        scanf("%i", &aux.dni);

        printf("\n Edad del mounstro: ");
        fflush(stdin);
        scanf("%i", &aux.edad);

        nuevo = nuevo_nodo(aux);

        lista = agregar_principio(lista,nuevo);

        printf("\nDesea agregar mas de la especie %s (s/n): ", nombre);
        fflush(stdin);
        scanf("%c", &yes);
    }

    return lista;
}

int buscar_especie(Especie arre[], char nombre[], int val)
{
    int i = 0;
    int pos = -1;
    while (i < val)
    {
        if (strcmp(arre[i].nombreEspecie, nombre) == 0)
        {
            pos = i;
        }
        i++;
    }

    return pos;
}
int carga_especie(Especie arre[], int val, int dim)
{
    int verify;

    if (val < dim)
    {
        printf("\nIngrese el nombre de la especie : ");
        fflush(stdin);
        gets(&arre[val].nombreEspecie);

        verify = buscar_especie(arre, arre[val].nombreEspecie, val);

        if (verify != -1)
        {
            printf("\nLA ESPECIE YA EXISTE. SE VAN A CARGAR PERSONAJES : ");
            carga_personaje(arre[verify].personajes, arre[val].nombreEspecie);
        }
        else
        {
            arre[val].promedioEdad = 0;

            printf("\nIngrese el ranking de peligrosidad del 1 al 6: ");
            fflush(stdin);
            scanf("%i", &arre[val].rankPeligrosidad);

            while (buscar_ranking(arre, arre[val].rankPeligrosidad, val, arre[val].nombreEspecie) != -1)
            {
                printf("\nNO SE PUEDE, RANKING OCUPADO. Ingrese otro: ");
                scanf("%d", &arre[val].rankPeligrosidad);
            }

            if (arre[val].rankPeligrosidad < 1 || arre[val].rankPeligrosidad > 6)
            {
                printf("\nRango no valido, ingrese un rango de peligrosidad valido (1-6): ");
                scanf("%d", &arre[val].rankPeligrosidad);
            }
            arre[val].personajes=inic_nodo();
            arre[val].promedioEdad=promedio_edad(arre[val].personajes);
            arre[val].personajes=carga_personaje(arre[val].personajes, arre[val].nombreEspecie);

            val++;
        }
    }
    else
    {
        printf("\nNO SE PUEDE AGREGAR MÁS. EL ARREGLO ESTÁ COMPLETO.\n");
    }

    return val;
}
int buscar_ranking(Especie arre[], int a, int val, char nombre[])
{
    int i = 0;
    int rta = -1;

    while (i < val && rta == -1)
    {
        if (a == arre[i].rankPeligrosidad && strcmp(arre[i].nombreEspecie, nombre) != 0)
        {
            rta = i;
        }
        i++;
    }
    return rta;
}

/*Hacer una función para mostrar el arreglo de especies con sus respectivos personajes.*/

void mostrar_criatura(Especie arre[], int val)
{
    int i = 0;

    while (i < val)
    {
        printf("\n=======================");
        printf("\n ESPECIE : %s", arre[i].nombreEspecie);
        printf("\n NIVEL DE PELIGROCIDAD : %i", arre[i].rankPeligrosidad);
        printf("\n PROMEDIO DE EDAD : %2.f", arre[i].promedioEdad);
        printf("\n=======================");
        mostrar_personaje(arre[i].personajes);
        i++;
    }
}


void mostrar_personaje(nodoLista* a)
{
    while (a)
    {
        printf("\n=======================");
        printf("\n Nombre: %s", a->dato.nombreYapellido);
        printf("\n Edad: %i", a->dato.edad);
        printf("\n DNI: %i", a->dato.dni);
        printf("\n=======================");
        a = a->siguiente;
    }
}
/*Insertar en un árbol binario un personaje de cada especie, ordenado por ranking de peligrosidad*/


arbol* inic_arbol()
{
    return NULL;
}

arbol* nuevo_arbol(registro nuevo)
{
    arbol* aux = malloc(sizeof(arbol));
    aux->data.dni = nuevo.dni;
    aux->data.edad = nuevo.edad;

    strcpy(aux->data.nombreYapellido, nuevo.nombreYapellido);
    strcpy(aux->data.nombreEspecie, nuevo.nombreEspecie);

    aux->data.rankPeligrosidad = nuevo.rankPeligrosidad;
    aux->data.promedioEdad = nuevo.promedioEdad;

    aux->der = NULL;
    aux->izq = NULL;

    return aux;
}


arbol* agregar_ordenado(arbol* arbolito,arbol*nuevo)
{
    if(!arbolito)
    {
        arbolito=nuevo;
    }
    else
    {
        if(nuevo->data.rankPeligrosidad<arbolito->data.rankPeligrosidad)
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

void especies_to_arboles(Especie arre[], registro aux[], int val)
{
    int i=0;
    while(i<val)
    {
        aux[i].rankPeligrosidad = arre[i].rankPeligrosidad;
        aux[i].dni = arre[i].personajes->dato.dni;
        aux[i].edad = arre[i].personajes->dato.edad;
        aux[i].promedioEdad = arre[i].promedioEdad;
        strcpy(aux[i].nombreEspecie, arre[i].nombreEspecie);
        strcpy(aux[i].nombreYapellido, arre[i].personajes->dato.nombreYapellido);
        i++;
    }

}

arbol* insertar_arbol(registro aux[],int val,arbol* arbolito)
{
    int i=0;
    arbol* nuevo=inic_arbol();

    while(i<val)
    {
        nuevo=nuevo_arbol(aux[i]);

        arbolito=agregar_ordenado(arbolito,nuevo);
        i++;
    }
    return arbolito;
}

void mostrar_inorder(arbol* arbolito)
{
    if (arbolito)
    {
        mostrar_inorder(arbolito->izq);
        printf("\n==========================");
        printf("\n RANKING DE PELIGROSIDAD TOP |%i|",arbolito->data.rankPeligrosidad);
        printf("\n Nombre: %s ",arbolito->data.nombreYapellido);
        printf("\n Edad: %i",arbolito->data.edad);
        printf("\n DNI: %i",arbolito->data.dni);
        printf("\n Promedio de edad: %f",arbolito->data.promedioEdad);
        printf("\n Nombre de especie: %s",arbolito->data.nombreEspecie);
        printf("\n==========================");
        mostrar_inorder(arbolito->der);
    }
}

/*Cargar el campo de promedio de edades de cada celda del arreglo,
calculando el promedio de edades de todos los personajes que pertenezcan a esa especie.
Hacer una función que busque la especie con mayor promedio de edad y muestre a dicha especie*/

int sumar_especies(nodoLista* a,int* i)
{
    int cont=0;
    nodoLista* seguidora=a;
    (*i)=0;
    while(seguidora)
    {
        cont=cont+seguidora->dato.edad;
        (*i)++;
        seguidora=seguidora->siguiente;
    }
    return cont;
}

float promediar(int cont,int cant)
{
    float promedio;
    promedio=(float)cont/(float)cant;

    return promedio;
}

float promedio_edad(nodoLista* a)
{
    int i=0;
    int cont=sumar_especies(a,&i);
    float rta=promediar(cont,i);

    return rta;
}
