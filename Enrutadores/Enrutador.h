#ifndef ENRUTADOR_RED_L
#define ENRUTADOR_RED_L

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

struct Nodo {
	int prioridad;
	char* datos;
	int puerto;
	struct Nodo* siguiente;
};

struct Lista {
	struct Nodo* primero;
	size_t tam;
};

typedef struct Lista* ptrEnrutador;

/*Inicializa la estructura para comenzar a registrar paquetes*/
/* 0.5 puntos */
bool iniciarEnrutador(ptrEnrutador * ptrPtrEnru);
/*Muestra por pantalla todos los paquetes en orden de prioridad*/
/* 1.5 puntos */
void mostrarPaquetes(ptrEnrutador ptrEnru);
/*Inserta un paquete con su prioridad, datos y su puerto de salida. Realiza una copia de los
datos*/
/* 3 puntos */
bool insertarPaquete(ptrEnrutador * ptrPtrEnru, int prioridad, const char * datos, int
puerto);
/*Elimina el paquete con mayor prioridad, además, devuelve una copia de sus datos
(datosExtraidos) y su puerto de salida como valor de retorno.
Si no se puede extraer, devuelve -1.*/
/* 2 puntos */
int extraerSiguientePaquete(ptrEnrutador * ptrPtrEnru, char ** datosExtraidos);
/*Libera toda la memoria asignada en la estructura */
/* 1 puntos */
void destruirEnrutador(ptrEnrutador * ptrPtrEnru);

#endif
