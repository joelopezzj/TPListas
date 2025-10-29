#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estructura según el teórico
typedef struct
{
    char nombre[20];
    int edad;
} persona;

typedef struct nodo
{
    persona dato;
    struct nodo *siguiente;
} nodo;
///Prototipos
nodo *iniNULL();
nodo *crearNodo(persona p);
nodo *archivoAlista(char archivo[], nodo *lista);
nodo * agregarPlista (nodo *lista, nodo *persona);
void mostrarLista(nodo *lista);
nodo *archivoAlistaOrdenada (char archivo[], nodo *lista);
nodo *agregarEnOrden(nodo *lista, nodo *nuevo);
int buscarElemento(nodo *lista, int edadBuscada);
nodo *borrarPrimerNodo(nodo *lista);
nodo *borrarUltimoNodo(nodo *lista);
int contarCondicion(nodo *lista, int condicion);
void mostrarListaInversa(nodo *lista);
nodo *eliminarNodoCondicion(nodo *lista, int condicion);


int main()
{
    char archivo[] = "personas.dat";
    nodo *lista = iniNULL();
    lista = archivoAlistaOrdenada(archivo, lista);
    mostrarLista(lista);
    system("pause");
    printf("\n===================\n");
    lista = eliminarNodoCondicion(lista, 40);
    mostrarLista(lista);

}

///Funciones///
nodo *iniNULL()
{
    return NULL;
}

//Crear Nodo
nodo *crearNodo(persona p)
{
    nodo *nuevo = (nodo*) malloc (sizeof(nodo));
    nuevo -> dato = p;
    nuevo ->siguiente = NULL;
    return nuevo;
}

/* 1  Leer archivo y pasarlo a lista */
nodo *archivoAlista(char archivo[], nodo *lista)
{
    FILE *arch = fopen(archivo, "rb");
    persona p;

    if(arch != NULL)
    {
        while(fread(&p, sizeof(persona), 1, arch) > 0)
        {
            nodo * nuevo = crearNodo(p);
            lista = agregarPlista(lista, nuevo);
        }
        fclose(arch);
    }
    else
    {
        printf("No se pudo abrir el archivo.");
    }
    return lista;
}

nodo * agregarPlista (nodo *lista, nodo *persona)
{
    if(lista == NULL)
    {
        lista = persona;
    }
    else
    {
        nodo *aux = lista;
        while(aux ->siguiente != NULL)
        {
            aux = aux->siguiente;
        }
        aux->siguiente = persona;
    }
    return lista;
}

void mostrarLista(nodo *lista)
{
    while(lista != NULL)
    {
        printf("Nombre: %s\n", lista->dato.nombre);
        printf("Edad: %d\n", lista->dato.edad);
        printf("------------\n");
        lista = lista->siguiente;
    }
}

/* 2 Agregar en Orden de archivo a lista */
nodo *archivoAlistaOrdenada (char archivo[], nodo *lista)
{
    FILE *arch = fopen(archivo, "rb");
    persona p;

    if(arch != NULL)
    {
        while(fread(&p, sizeof(persona), 1, arch) > 0)
        {
            nodo * nuevo = crearNodo(p);
            lista = agregarEnOrden(lista, nuevo);
        }
        fclose(arch);
    }
    return lista;
}
/* Agregar nodo en orden por edad (menor a mayor) */
nodo *agregarEnOrden(nodo *lista, nodo *nuevo)
{
    if(lista == NULL || nuevo->dato.edad < lista->dato.edad) //Si la lista esta vacia se agrega el nodo
    {
        lista = nuevo;
        return nuevo;
    }

    //Si la lista contiene elementos, buscar la posicion correcta
    nodo *actual = lista;
    nodo *anterior = NULL;

    while(actual != NULL && actual->dato.edad < nuevo->dato.edad)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    // Insertar el nuevo nodo entre anterior y actual
    nuevo->siguiente = actual;
    anterior->siguiente = nuevo;

    return lista;
}

/* 3 Buscar elemento y retornar 1 si lo encontro o 0 si no existe */
int buscarElemento(nodo *lista, int edadBuscada)
{
    while(lista!=NULL)
    {
        if(lista->dato.edad == edadBuscada)
        {
            return 1;
        }
        lista = lista->siguiente;
    }
    return 0;
}

/* 4 Borrar primer nodo de la lista */
nodo *borrarPrimerNodo(nodo *lista)
{
    nodo *aux = lista;
    lista = lista->siguiente;
    free(aux);
    return lista;
}

/* 5 Eliminar el ultimo nodo de la lista */
nodo *borrarUltimoNodo(nodo *lista)
{
    nodo *actual = lista;
    nodo *anterior = NULL;

    while(actual->siguiente != NULL)
    {
        anterior = actual;
        actual = actual->siguiente;
    }
    anterior->siguiente = NULL;
    free(actual);
    return lista;
}

/* 6 Contar nodos que cumplan una condicion */
int contarCondicion(nodo *lista, int condicion)
{
    nodo *aux = lista;
    int contador = 0;

    while(aux != NULL)
    {
        if(aux->dato.edad > condicion)
        {
            contador++;
        }
        aux = aux->siguiente;
    }
    return contador;
}

/* 7 Mostrar lista de manera inversa */
void mostrarListaInversa(nodo *lista)
{
    if(lista != NULL)
    {
        mostrarListaInversa(lista->siguiente);
        printf("Nombre: %s\n", lista->dato.nombre);
        printf("Edad: %d\n", lista->dato.edad);
        printf("------------\n");

    }
}

/* 8 Eliminar nodo con condicion */
nodo *eliminarNodoCondicion(nodo *lista, int condicion)
{
    if(lista == NULL)
    {
        return NULL;
    }

    nodo *act = lista;
    nodo *ant = NULL;
    nodo *aux = NULL;

    while(act != NULL)
    {
        if(act->dato.edad < condicion)
        {
            aux = ant;
            if(ant == NULL) //Si el primer nodo cumple con la condicion
            {
                lista = lista->siguiente;
                act = lista;
            }
            else
            {
            //Si el nodo a eliminar es intermedio
                ant = act;
                act = act->siguiente;
            }
            free(aux);
        }
        else
        {
            ant = act;
            act = act->siguiente;
        }
    }
    return lista;
}
