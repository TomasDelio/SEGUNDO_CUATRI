#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[20];
    char posicion[20];
    int curso;
    int puntosGanados;
    char equipo[20];
} stJugador;

typedef struct nodopuntos
{
    char equipo[20];
    int puntosTotales;
    struct nodopuntos* siguiente;
} nodopuntos;

typedef struct nodo
{
    stJugador dato;
    struct nodo* anterior;
    struct nodo* siguiente;
} nodo;

nodo* iniciar_nodo();
nodo* crear_nodo(stJugador nuevo);
nodo* agregar_principio(stJugador nuevo, nodo* lista);
nodo* cargar_jugadores(stJugador jugador, nodo* lista);
void mostrar_jugadores(nodo *lista);
nodo* agregar_ordenado(nodo* lista,nodo* nuevo);
nodo* cargar_jugadores_ordenadospos(stJugador jugador, nodo* lista);
void encontrar_posicion(nodo* lista,char nombre[], int curso, char pos[]);
nodo* borrar_lista_curso(nodo* lista,int curso);
nodopuntos* agregar_equipos_nuevos(nodo* lista,char equipo[],int puntos);


int main()
{
    nodo* lista = iniciar_nodo();
    int num;
    char yes = 's';

    stJugador jugador;

    char buscarequipos[20];
    int puntosgandos;

    char buscarnombre[20];
    int buscarcurso;
    char* pos;

    int numJugadores;
    while (yes == 's' || yes == 'S')
    {
        printf("SELECCIONE UN CASO: ");
        scanf("%i", &num);
        switch (num)
        {
        case 1:
            lista= cargar_jugadores(jugador, lista);
            mostrar_jugadores(lista);
            break;

        case 2:
            lista=cargar_jugadores_ordenadospos(jugador,lista);
            mostrar_jugadores(lista);

            break;

        case 3:
            lista= cargar_jugadores(jugador, lista);
            mostrar_jugadores(lista);

            printf("INGRESE EL EQUPO QUE DESEA SABER SUS PUNTOS TOTALES: ");
            fflush(stdin);
            scanf("%s", &buscarequipos);

            puntosgandos=sumar_puntos(lista,buscarequipos);
            printf("\n Los puntos totales de %s son: %d", buscarequipos,puntosgandos);


            break;

        case 4:
            lista= cargar_jugadores(jugador, lista);
            mostrar_jugadores(lista);

            printf("\n Que jugador desea buscar?: ");
            fflush(stdin);
            scanf("%s", buscarnombre);

            printf("\n Que curso desea buscar?: ");
            fflush(stdin);
            scanf("%d", &buscarcurso);

            encontrar_posicion(lista,buscarnombre,buscarcurso, pos);

            break;

        case 5:
            lista= cargar_jugadores(jugador, lista);
            mostrar_jugadores(lista);

            printf("\n Que jugadores desea borrar?: ");
            fflush(stdin);
            scanf("%d", &buscarcurso);

            lista=borrar_lista_curso(lista,buscarcurso);

            mostrar_jugadores(lista);

            break;
        case 6:
            lista = cargar_jugadores(jugador, lista);
            mostrar_jugadores(lista);

            nodopuntos* listaEquipos = NULL;

            nodo* actual = lista;
            while (actual != NULL)
            {
                listaEquipos = agregar_equipos_nuevos(listaEquipos, actual->dato.equipo, actual->dato.puntosGanados);
                actual = actual->siguiente;
            }

            mostrar_equipos_y_puntos(listaEquipos);

            break;

        default:
            break;
        }

        printf("¿Desea ver otro punto? (s/n): ");
        scanf(" %d", &yes);
    }

    return 0;
}

nodo*iniciar_nodo()
{
    return NULL;
}

nodo* crear_nodo(stJugador nuevo)
{
    nodo* aux;
    aux=(nodo*)malloc(sizeof(nodo));
    aux->dato=nuevo;
    aux->siguiente=NULL;
    aux->anterior=NULL;

    return aux;
}
nodo* agregar_principio(stJugador nuevo, nodo* lista)
{
    nodo* aux = crear_nodo(nuevo);

    if (!lista)
    {
        lista = aux;
    }
    else
    {
        aux->siguiente = lista;
        lista->anterior = aux;
        lista = aux;
    }
    return lista;
}

nodo* cargar_jugadores(stJugador jugador, nodo* lista)
{
    char yes = 's';
    int i=0;

    while (yes == 's' || yes == 'S')
    {
        printf("\n ID: ");
        scanf("%i", &jugador.id);
        printf("\n Nombre: ");
        scanf("%s", &jugador.nombre);
        printf("\n Posicion: ");
        scanf("%s", jugador.posicion);
        printf("\n Curso: ");
        scanf("%i", &jugador.curso);
        printf("\n Puntos Ganados: ");
        scanf("%i", &jugador.puntosGanados);
        printf("\n Equipo: ");
        scanf("%s", &jugador.equipo);


        lista = agregar_principio(jugador,lista);



        printf("\n ¿Desea agregar otro jugador? (s/n): ");
        fflush(stdin);
        scanf(" %c", &yes);
    }
    return lista;
}

void mostrar_jugadores(nodo*lista)
{
    nodo* aux = lista;
    printf("\n | Lista de jugadores cargados|\n ");
    while(aux)
    {
        printf("ID: %d\n", aux->dato.id);
        printf("Nombre: %s\n", aux->dato.nombre);
        printf("Posicion: %s\n", aux->dato.posicion);
        printf("Curso: %d\n", aux->dato.curso);
        printf("Puntos Ganados: %d\n", aux->dato.puntosGanados);
        printf("Equipo: %s\n", aux->dato.equipo);
        printf("\n");
        aux=aux->siguiente;

    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

nodo* agregar_ordenado(nodo* lista, nodo* nuevo)
{
    nodo* aux = lista;
    nodo* ante = NULL;

    if (!lista)
    {
        lista = nuevo;
    }
    else
    {
        while (aux != NULL && strcmp(nuevo->dato.posicion, aux->dato.posicion) > 0)
        {
            ante = aux;
            aux = aux->siguiente;
        }

        if (ante == NULL)
        {
            // El nuevo nodo debe ir al principio de la lista.
            nuevo->siguiente = lista;
            lista = nuevo;
        }
        else
        {
            // El nuevo nodo debe ir entre "ante" y "aux".
            ante->siguiente = nuevo;
            nuevo->siguiente = aux;
        }
    }

    return lista;
}

nodo* cargar_jugadores_ordenadospos(stJugador jugador, nodo* lista)
{
    char yes = 's';

    while (yes == 's' || yes == 'S')
    {
        nodo* nuevoNodo = crear_nodo(jugador); // Crea un nuevo nodo para cada jugador

        printf("\n ID: ");
        scanf("%i", &nuevoNodo->dato.id);
        printf("\n Nombre: ");
        scanf("%19s", nuevoNodo->dato.nombre);
        printf("\n Posicion: ");
        scanf("%19s", nuevoNodo->dato.posicion);
        printf("\n Curso: ");
        scanf("%i", &nuevoNodo->dato.curso);
        printf("\n Puntos Ganados: ");
        scanf("%i", &nuevoNodo->dato.puntosGanados);
        printf("\n Equipo: ");
        scanf("%19s", nuevoNodo->dato.equipo);

        lista = agregar_ordenado(lista, nuevoNodo);

        printf("\n ¿Desea agregar otro jugador? (s/n): ");
        fflush(stdin);
        scanf(" %c", &yes);
    }

    return lista;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int sumar_puntos(nodo* lista, char equipo[])
{
    int suma=0;
    if(lista!=NULL)
    {
        if(strcmp(lista->dato.equipo,equipo)==0)
        {
            suma=lista->dato.puntosGanados;
        }

        suma+= sumar_puntos(lista->siguiente,equipo);
    }
    return suma;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void encontrar_posicion(nodo* lista,char nombre[], int curso, char pos[])
{

    int flag=0;
    if(lista!=NULL)
    {
        if(strcmp(lista->dato.nombre,nombre)==0 && lista->dato.curso==curso)
        {
            printf("%s",lista->dato.posicion );
            strcpy(pos,lista->dato.posicion);
            flag=1;
        }
        else if(flag==0)
            encontrar_posicion(lista->siguiente, nombre, curso, pos);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
nodo* borrar_lista_curso(nodo* lista, int curso)
{
    nodo* aux = lista;
    nodo* ante = NULL;
    nodo* next=NULL;

    while (aux != NULL)
    {
        if (aux->dato.curso == curso)
        {
            next = aux->siguiente;
            if (ante != NULL)
            {
                ante->siguiente = next;
                if (next != NULL)
                {
                    next->anterior = ante;
                }
                free(aux); // Liberar la memoria del nodo que se borra.
                aux = next;
            }
            else
            {
                lista = next; // Si el primer nodo cumple la condición, actualiza la lista.
                free(aux); // Liberar la memoria del nodo que se borra.
                aux = next;
            }
        }
        else
        {
            ante = aux;
            aux = aux->siguiente;
        }
    }

    return lista;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
nodopuntos* iniciar_nodopuntos(char equipo[],int puntos)
{
    nodopuntos* aux;
    aux=(nodopuntos*)malloc(sizeof(nodopuntos));

    if(aux!=NULL)
    {
        strcpy(aux->equipo, equipo);
        aux->puntosTotales = puntos;
        aux->siguiente = NULL;
    }
    return aux;

}

nodopuntos* agregar_equipos_nuevos(nodo* lista,char equipo[],int puntos)
{
    nodopuntos* actual = lista;
    nodopuntos* anterior = NULL;
    nodopuntos*aux;
    nodopuntos* nuevo;

    if(lista!=NULL)
    {
        while(actual!=NULL)
        {
            if(strcmp(actual->equipo,equipo)==0)
            {
                actual->puntosTotales+=puntos;
                return lista;
            }
            anterior=actual;
            actual=actual->siguiente;
        }
        nuevo=iniciar_nodopuntos(equipo,puntos);
        if(nuevo!=NULL)
        {
            if(anterior==NULL)
            {
            nuevo->siguiente=lista;
            lista=nuevo;
            }
                else
                {
                    anterior->siguiente=nuevo;
                }
        }

    }
    return aux;
}

void mostrar_equipos_y_puntos(nodopuntos* lista)
{
    printf("Equipos y Puntos Totales:\n");

    nodopuntos* actual = lista;

    while (actual != NULL)
    {
        printf("Equipo: %s, Puntos Totales: %d\n", actual->equipo, actual->puntosTotales);
        actual = actual->siguiente;

    }
}
