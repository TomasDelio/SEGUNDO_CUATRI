#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
} notaAlumno;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    int idMateria;
    char materia[40];
} registroArchivo;

typedef struct nodo
{
    notaAlumno dato;
    struct nodo* siguiente;
} nodo;

typedef struct
{
    int idMateria;
    char materia[40];
    nodo* listaDeNotas;
} celda;

int agregarCelda(celda[100], int, celda);
int existeMateria(celda[100], int, int);
int agregarTodo(celda[100], int, int, int, int, char[40], char[40]);
int menu_celdas(celda[100], int);

nodo* inic_nodo();
nodo* crearNodo(int nota, int legajo, char nombreApe[40]);
nodo* agregar_principio(nodo*, nodo*);
nodo* buscar_celda(celda[100], int, int, notaAlumno);
nodo* buscar_nodo(nodo*, notaAlumno);

int pasar_archivo_a_arreglo(char[30], celda[100], int);
void pasar_arreglo_a_archivo(char[30], celda[100], int);
void mostrar_arreglo(celda[100], int);
void mostrar_lista(nodo*);
void escribir_lista(nodo*);
void mostrar_archivo(char[30]);

int main()
{
    int selector=0;
    char continuar='s';
    char prueba[30];
    strcpy(prueba, "archivin.bin");
    celda prueba2[100];
    int validos=0;
    do
    {
        printf("\nEscriba el numero del ejercicio\n");
        scanf("%i", &selector);

        switch(selector)
        {
        case 1:
            validos=menu_celdas(prueba2,  validos);
            break;

        case 2:
            mostrar_arreglo(prueba2, validos);
            break;

        case 3:
            pasar_arreglo_a_archivo(prueba, prueba2, validos);
            break;

        case 4:
            validos=pasar_archivo_a_arreglo(prueba, prueba2, validos);
            break;

        case 5:
            mostrar_archivo(prueba);
            break;

        default:
            printf("\nEste ejercicio no existe\n");
            break;
        }

        printf("\nAprete s para continuar\n");
        fflush(stdin);
        scanf("%c", &continuar);
    }
    while(continuar=='s');

    return 0;
}
nodo* inic_nodo()
{
    return NULL;
}
nodo* crearNodo(int nota, int legajo, char nombreApe[40])
{
    nodo* aux=(nodo*)malloc(sizeof(nodo));

    aux->dato.legajo=legajo;
    strcpy(aux->dato.nombreApe, nombreApe);
    aux->dato.nota=nota;
    aux->siguiente=NULL;

    return aux;
}

nodo* agregar_principio(nodo* original, nodo* nuevoNodo)
{
    nuevoNodo->siguiente=original;

    return nuevoNodo;
}

nodo* buscar_celda(celda arreglo[100], int validos, int idMateria, notaAlumno datos)
{
    nodo* aux=NULL;
    int pos=existeMateria(arreglo, validos, idMateria);

    if(pos!=-1)
    {
        aux=buscar_nodo(arreglo[pos].listaDeNotas, datos);
    }

    return aux;
}

nodo* buscar_nodo(nodo* lista, notaAlumno datos)
{
    nodo* aux=lista;
    if(lista!=NULL)
    {
        while(lista!=NULL && lista->dato.legajo==datos.legajo)
        {
            aux=lista;
            lista=lista->siguiente;
        }
    }

    return aux;
}

int agregarCelda(celda arreglo[100], int validos, celda nuevoArreglo)
{

    if(validos<100)
    {
        arreglo[validos]=nuevoArreglo;
        validos++;
    }

    return validos;
}

int existeMateria(celda arreglo[100], int validos, int idMateria)
{
    int rta=-1;
    int i=0;

    while(i<validos && rta==-1)
    {
        if(arreglo[i].idMateria==idMateria)
        {
            rta=i;
        }

        i++;
    }

    return rta;
}

int agregarTodo(celda arreglo[100], int validos, int idMateria, int nota, int legajo, char nombreApe[40], char materia[40])
{
    nodo* aux=crearNodo(nota, legajo, nombreApe);
    int i=existeMateria(arreglo, validos, idMateria);

    if(i==-1)
    {
        celda uno;
        uno.idMateria=idMateria;
        strcpy(uno.materia, materia);
        uno.listaDeNotas=NULL;
        validos=agregarCelda(arreglo, validos, uno);
        i=validos-1;
    }

    arreglo[i].listaDeNotas=agregar_principio(arreglo[i].listaDeNotas, aux);

    return validos;
}

int menu_celdas(celda arreglo[100], int validos)
{
    int id=0;
    int nota2=0;
    int legajo2=0;
    char nombreApe2[40];
    char materia[40];

    printf("\ningrese el id de la materia\n");
    scanf("%i", &id);

    printf("\ningrese la materia\n");
    fflush(stdin);
    gets(materia);

    printf("\ningrese la nota\n");
    scanf("%i", &nota2);

    printf("\ningrese el legajo del alumno\n");
    scanf("%i", &legajo2);

    printf("\ningrese el nombre y apellido del alumno\n");
    fflush(stdin);
    gets(nombreApe2);

    validos=agregarTodo(arreglo, validos, id, nota2, legajo2, nombreApe2, materia);

    return validos;
}

int pasar_archivo_a_arreglo(char archivo[30], celda arreglo[100], int validos)
{
    FILE* archi=fopen(archivo, "rb");
    registroArchivo unreg;

    while(fread(&unreg, sizeof(registroArchivo), 1, archi)>0)
    {
        validos=agregarTodo(arreglo, validos, unreg.idMateria, unreg.nota, unreg.legajo, unreg.nombreApe, unreg.materia);
    }
    fclose(archi);

    return validos;
}

void pasar_arreglo_a_archivo(char archivo[30], celda arreglo[100], int validos)
{
    nodo* seg;
    registroArchivo unreg;
    FILE* archi=fopen(archivo, "ab");

    for(int i=0; i<validos; i++)
    {
        seg=arreglo[i].listaDeNotas;
        unreg.idMateria=arreglo[i].idMateria;
        strcpy(unreg.materia, arreglo[i].materia);

        while(seg!=NULL)
        {
            if(seg->dato.nota>=6)
            {
                unreg.nota=seg->dato.nota;
                unreg.legajo=seg->dato.legajo;
                strcpy(unreg.nombreApe, seg->dato.nombreApe);
                fwrite(&unreg, sizeof(registroArchivo), 1, archi);
            }
            seg=seg->siguiente;
        }
    }
    fclose(archi);
}

void mostrar_arreglo(celda arreglo[100], int validos)
{
    int i=0;

    while(i<validos)
    {
        printf("\nel id de la materia es: %i", arreglo[i].idMateria);
        printf("\nla materia es: %s", arreglo[i].materia);
        mostrar_lista(arreglo[i].listaDeNotas);
        i++;
    }
}

void mostrar_lista(nodo* lista)
{
    if(lista!=NULL)
    {
        mostrar_lista(lista->siguiente);
        escribir_lista(lista);
    }
}

void escribir_lista(nodo* lista)
{
    if(lista!=NULL)
    {
        printf("\nla nota es: %i", lista->dato.nota);
        printf("\nel legajo es: %i", lista->dato.legajo);
        printf("\nel nombre y el apellido son: %s\n", lista->dato.nombreApe);
    }
}

void mostrar_archivo(char archivo[30])
{
    FILE* archi;
    registroArchivo prueba;
    archi=fopen(archivo, "rb");

    if(archi!=NULL)
    {
        while(!feof(archi))
        {
            fread(&prueba, sizeof(registroArchivo), 1, archi);
            if(!feof(archi))
            {
                printf("\nid de la materia: %i", prueba.idMateria);
                printf("\nmateria: %s", prueba.materia);
                printf("\nnota: %i", prueba.nota);
                printf("\nlegajo: %i", prueba.legajo);
                printf("\nnombre y apellido: %s\n", prueba.nombreApe);
            }
        }

        fclose(archi);
    }
    else
    {
        printf("\nNo se encontro el archivo\n");
    }
}

