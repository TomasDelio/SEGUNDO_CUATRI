#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int potencia (int pote,int num);
int factorial(int num);
int arreglo_recursivo(int num[],int val);
int mostrar_arreglo(int num[],int val);
int mostrar_arreglo_alreves(int num[],int val);
int capicua (int num[],int val,int i);
int suma (int num[], int val, int i);
int menor (int a[],int val,int i);
void cargar_archi(char theArchies[]);
void ver_archi(char theArchies[]);
int buscar_menor(FILE *archi);
char inverso_recursivo(char yes, char num);
int arr_buscador(int arr[], int i, int val, int num);

int main()
{
    int a;
    int a2;
    int val=100;
    char option;
    int arre[30];
    char aux;

    char the[100];
    FILE*archi;
    fflush(stdin);
    strcpy(the, "theArchies.bin");
    do
    {
        printf(" \n Bienvenido al tp de recusion, seleccione el punto que quiera ver:  ");
        fflush(stdin);
        scanf("%i", &a);
        switch(a)
        {
        case 1:

            printf("\nIngrese un numero : ");
            scanf("%i", &val);
            a=factorial(val);
            printf("\n El factorial de %i es: %i ",val, a );

            break;
        case 2:
            printf("\nIngrese un numero : ");
            scanf("%i", &a);
            printf("\nIngrese una potencia: ");
            scanf("%i", &val);
            a2=potencia(val,a);
            printf("\n La potencia de %i a la %i es : %i ",a,val, a2 );

            break;
        case 3:
            a=arreglo_recursivo(arre, 100);
            mostrar_arreglo(arre, a-1);
            break;
        case 4:
            a2=arreglo_recursivo(arre,100);
            mostrar_arreglo_alreves(arre, a2-1);
            break;
        case 5:
            a2=arreglo_recursivo(arre,100);
            a=0;
            a2=capicua(arre,a2-1,a);
            printf("\n SI DA 0 NO ES CAPICUA SI DA 1 ES CAPICUA |%i|",a);
            break;
        case 6:
            a2=arreglo_recursivo(arre, 100);
            a=0;
            a=suma(arre,a2-1,a );
            printf("\n El resultado es : %i ",a);

            break;
        case 7:
            a2=arreglo_recursivo(arre, 100);
            a=0;
            a=menor(arre,a2-1,a);
            printf("\n El resultado es : %i ",a);

            break;
        case 8:
            cargar_archi(the);
            archi=fopen(the,"rb");
            a=buscar_menor(archi);
            fclose(archi);

            printf("\n El resultado es : %i ",a);
            break;

        case 9:
            printf("\nPunto en construccion, por favor vuelva mas tarde \n");
            break;

        case 10:
            cargar_archi(the);

            archi=fopen(the, "rb");
            a=inversor(archi);
            fclose(archi);
            break;

        case 11:
            option ='s';
            inverso_recursivo(option, aux);
            break;
        case 12:
            val=arreglo_recursivo(arre,100);
            a2=0;
            printf("\nIngrese el numero que desea buscaren el arreglo: ");
            scanf("%i", &a);

            a=arr_buscador(arre,a2,val-1,a);
            if(a==1)
            {
                printf("El elemento se encuentra en el arreglo");
            }
            else
            {
                printf("El elemento NO se encuentra en el arreglo");

            }
            break;

        }
        printf("\nDesea hacer otro ejercicio? presione 's' para si ");
        fflush(stdin);
        scanf("%c", &option);
    }

    while(option=='s'||option=='S');
    return 0;
}
////////////////////////////////--1--////////////////////////////////
/*Calcular el factorial de un número en forma recursiva.*/
int factorial(int num)
{
    int i;
    if(num==0)
    {
        i=1;
    }
    else
    {
        i=num*factorial(num-1);
    }
    return i;
}
////////////////////////////////--2--////////////////////////////////
/* Calcular la potencia de un número en forma recursiva. */
int potencia (int pote,int num)
{
    int i;
    if(pote==1)
    {
        i=num;
    }
    else{
        i=num*potencia(pote-1,num);
    }
    return i;
}
////////////////////////////////--3--////////////////////////////////
/* Recorrer un arreglo y mostrar sus elementos en forma recursiva. */
int arreglo_recursivo(int num[],int val)
{
    int i=0;
    char yes='s';
    while(yes=='s'&& i<val)
    {
        printf("\n Cargue un elemento al arreglo : ");
        fflush(stdin);
        scanf("%i",&num[i]);

        i++;

        printf("\n Desea agregar otro numero?");
        fflush(stdin);
        scanf("%c",&yes);
    }
    return i;
}

int mostrar_arreglo(int num[],int val)
{
    int i=val;

    if(i==0)
    {
        printf("\n |%i| ",num[i]);
    }
    else{
        mostrar_arreglo(num,i-1);
        printf("\n |%i|",num[i]);
    }
    return i;
}
////////////////////////////////--4--////////////////////////////////
/*Recorrer un arreglo comenzando desde la posición 0 y mostrar sus elementos en
forma invertida (recursivo). */
int mostrar_arreglo_alreves(int num[],int val)
{
    int i=val;

    if(i==0)
    {
        printf("\n |%i|",num[i]);
    }
    else
    {
        printf("\n |%i|",num[i]);
        mostrar_arreglo_alreves(num,i-1);
    }

    return i;
}
////////////////////////////////--5--////////////////////////////////
/*Determinar en forma recursiva si un arreglo es capicúa.*/

int capicua (int num[],int val,int i)
{
    int flag=1;
    if(i>val || i==val)
    {
        printf("\n ES CAPICUA");
    }
    else
    {
      if(num[i]== num[val])
      {
          capicua(num,val-1,i+1);
          flag=1;
      }
      else
      {
          flag=0;
      }

    }
    return flag;
}

////////////////////////////////--6--////////////////////////////////
/*Sumar en forma recursiva los elementos de un arreglo de enteros y retornar el total de la suma. */

int suma (int num[], int val, int i)
{
    int a=0;
    if (i==val)
    {
        a=0;
    }
    else
    {
        a=a+num[i]+suma(num,val,i+1);
    }
    return a;
}
////////////////////////////////--7--////////////////////////////////
/*Buscar el menor elemento de un arreglo en forma recursiva. */

int menor (int a[],int val,int i)
{
    int b;

    if(i==val)
    {
        b=a[val];
    }
    else
    {
        b=menor(a,val,i+1);
    if(a[i]<b)
    {
        b=a[i];
    }
    }
    return b;
}
////////////////////////////////--8--////////////////////////////////
/*Buscar el menor elemento de un archivo de números enteros de forma recursiva. (desde el mismo archivo)
*/
void cargar_archi(char theArchies[])
{
    FILE*archi;
    archi=fopen(theArchies,"ab");
    int a;
    char yes='s';

    if(archi !=NULL)
    {
        while(yes=='s')
        {
            printf("\nCargue un elemento : ");
            fflush(stdin);
            scanf("%i",&a);

            printf("\n\n");

            fwrite(&a, sizeof(int),1,archi);

            printf("\nDesea agregar otro elemento? presione 's' pasa si: ");
            fflush(stdin);
            scanf("%c", &yes);

        }
        fclose(archi);
    }
}

void ver_archi(char theArchies[])
{
    int a;
    FILE *archi;
    archi = fopen("theArchies.bin", "rb");

    if(archi != NULL)
    {
        while(!feof(archi))
        {
            fread(&a, sizeof(int),1,archi);

            if(!feof(archi))
            {
                printf("\n-------------------------------\n");
                printf("\nLegajo: %i", a);
                printf("\n-------------------------------");
            }
        }
        fclose(archi);
    }
}

int buscar_menor(FILE *archi)
{
    int num;
    int menor;

    if(archi!=NULL)
    {
        if(fread(&num, sizeof(int),1,archi)>0)
        {
            menor=buscar_menor(archi);

            if(menor>num)
            {
                menor=num;
            }
        }
        else
        {
            fseek(archi,sizeof(int)*(-1),SEEK_END);
            fread(&menor,sizeof(int),1,archi);
        }
    }
    else
    {
        printf("NO ESTA CARGADO");
    }
    return menor;
}
////////////////////////////////--9--////////////////////////////////
/*Invertir los elementos de un archivo de números enteros de forma recursiva.
 (si no te sale, primero proba con invertir los elementos de un arreglo de int)


TU MAMA VA A HACER EL NUEVE MAMAHUEVO*/


////////////////////////////////--10--////////////////////////////////
/*Recorrer un archivo y mostrar sus elementos en forma invertida de forma recursiva.*/

void inversor(FILE *archi)
{
    int num;

    if(archi!=NULL)
    {
        if(fread(&num, sizeof(int),1,archi)>0)
        {
            inversor(archi);
            printf("|%i|", num);
        }
    }
    else
    {
        printf("NO ESTA CARGADO");
    }
}

////////////////////////////////--11--////////////////////////////////
/* Ingresar valores a una variable de tipo char (por teclado)
y mostrarlo en el orden inverso (hasta ingresar un ‘*’)
de forma recursiva. NO usar arreglos. */


char inverso_recursivo(char yes, char num)
{
    if(yes=='n')
    {
    }
    else
    {
        printf("ingrese una letra:  ");
        fflush(stdin);
        scanf("%c", &num);

        printf("desea continuar? presiones 's' para si 'n' para no:  ");
        fflush(stdin);
        scanf("%c", &yes);

        inverso_recursivo(yes, num);
        printf("|%c|", num);

    }
    return num;
}

////////////////////////////////--12--////////////////////////////////
/*Determinar si un arreglo contiene un determinado elemento de forma recursiva.
(Pueden intentarlo también con una función void)
(Tener en cuenta para un arreglo desordenado y el caso para un arreglo ordenado)*/


int arr_buscador(int arr[], int i, int val, int num)
{
    int flag=0;
    printf("\n-----------------------\n");
    printf("\n|%i|\n", arr[i]);
    printf("\n|%i|\n", i);
    printf("\n-----------------------\n");


    if( i==val)
    {

    }
    else
    {
        if(num==arr[i])
        {
            flag=1;
        }
        else
        {
            flag=arr_buscador(arr, i+1, val,num);

        }
    }

    return flag;
}
