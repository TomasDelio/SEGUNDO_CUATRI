#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
      char nombre[30];
      char genero;
      int edad;
}persona;

////////////////////////PILAS/////////////////////////
typedef struct{
     int valores[100];
     int posTope;
} Pila;


////////////////////////////////////////////////
int arreglo_estatico(persona a[],int dim);
void mostrar(persona a[],int val);
int contador_genero(persona a[],int val,char sex);
int cambio_dinamico(persona a[],persona arre[],int val,char sex );
persona* crear_dinamico(int a);

int main()
{
    int option;
    int p;
    char yes;
    char aux;
    persona arr[30];

    Pila pi;


    do
    {
        printf("\n TP N°2 ESTRUCTURAS DE DATOS ESTATICAS Y DINAMICAS, SELECCIONE EL EJERCICIO: ");
        fflush(stdin);
        scanf("%i", &option);
        switch(option)
        {
        case 1:
            /////////////////////////a/////////
            p=arreglo_estatico(arr,30);
            mostrar(arr,p);
            ////////////////////////b//////////
            printf("\n\n Que genero de alumno que tenga en mayor cant desea buscar?");
            fflush(stdin);
            scanf("%c",&aux);

            p=contador_genero(arr,p,aux);
            printf("La cantidad de alumnos con este genero son: %i", p);
            ////////////////////////c//////////
            printf("\n Que genero desea copiar?: ");
            fflush(stdin);
            scanf("%c",&aux);

            p=contador_genero(arr,p,aux);

            persona* arre=crear_dinamico(p);
            cambio_dinamico(arr,arre,p,aux);
            mostrar(arre,p);

            break;
        case 2:
            printf("\n lo hice en el 1 sin querer jijos ,salteate el 2 y anda a cualquier ");
            break;
        case 3:
            inicPila(&pi);
            apilar(&pi, 8);
            desapilar(&pi);
            apilar(&pi, 77);
            tope(&pi);
            pilavacia(&pi);

            break;

        default:
            printf("\nNumero invalido\n");
        break;
        }
        printf("\n Desea realizar otro ejercio precione 's' para si: ");
        fflush(stdin);
        scanf("%c",&yes);
    }
    while(yes=='S'||yes=='s');

    return 0;
}
/////////////////////////////////// --- A ---//////////////////////////////////////////////
int arreglo_estatico(persona a[],int dim)
{
    int cant=0;
    char yes;

    do
    {
        printf("\nIngrese todos los datos de la persona  %i",cant+1);

        printf("\nCarge el nombre que desee: ");
        fflush(stdin);
        gets(a[cant].nombre);

        printf("\nCarge el genero de la persona: ");
        fflush(stdin);
        scanf("%c",&a[cant].genero);

        printf("\nCarge la edad de la persona: ");
        fflush(stdin);
        scanf("%i", &a[cant].edad);

        cant ++;

        printf("\nDesea agregar otra perosna precione 's': ");
        fflush(stdin);
        scanf("%c",&yes);
    }
    while(yes=='S'||yes=='s');

    return cant;
}
void mostrar(persona a[],int val)
{
    int i=0;

    while(i<val)
    {
        printf("\n\n Nombre del alumno: %s",a[i].nombre);
        printf("\n Genero del alumno: %c",a[i].genero);
        printf("\n Edad del alumno: %i",a[i].edad);
        i++;
    }
}

/////////////////////////////////// --- B ---//////////////////////////////////////////////

int contador_genero(persona a[],int val,char sex)//SEX DEL GENERO NO DE SEXOOO ,MENTE SUCIA QUE SOS
{
    int i=0;
    int cont=0;

    while(i<val)
    {
        if(a[i].genero == sex)
        {
            cont++;
        }
        i++;
    }
    return cont;
}
/////////////////////////////////// --- C ---//////////////////////////////////////////////

persona* crear_dinamico(int a)
{
    persona* arr=malloc(sizeof(persona)*a);

    return arr;
}

int cambio_dinamico(persona a[],persona arre[],int val,char sex )
{
    int i=0;
    int j=0;

    while(i<val)
    {
        if(a[i].genero == sex)
        {
            arre[j]=a[i];
            j++;
        }
        i++;
    }
    return j;

}

/////////////////////////////////---3---///////////////////////////

void inicPila(Pila* p)
{
    p->posTope=0;
}

void apilar (Pila *p, int valor)
{
    int aux;
    aux=p->posTope;
    p->valores[aux]=valor;
    p->posTope++;
    printf("\napilar%i", p->posTope);
    printf("\n%i", p->valores[aux]);
}

int desapilar(Pila* p)
{
    int aux;
    aux=p->posTope;
    p->valores[aux]=0;
    p->posTope--;
    printf("\ndesapilar%i", p->posTope);
    printf("\naa%i", p->valores[aux]);
    return aux;

}

int tope(Pila*p)
{
    int aux;
    int pp;
    aux=p->posTope-1;
    pp=p->valores[aux];
        printf("\nTOPE %i", pp);
}

int pilavacia(Pila* p)
{
    int flag=0;
    if(p->posTope==0)
    {
        flag=0;
    }else
    {
        flag=1;
    }
    printf("\nAAAA %i", flag);
    return flag;
}



