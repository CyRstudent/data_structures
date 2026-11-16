#include "Enrutador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool iniciarEnrutador(ptrEnrutador *ptrPtrEnru) {
	if(ptrPtrEnru == NULL) return false;
	*ptrPtrEnru = malloc(sizeof(struct Lista));
	if(*ptrPtrEnru == NULL) return false;
	(*ptrPtrEnru) -> primero = NULL;
	(*ptrPtrEnru) -> tam = 0;
	return true;
}

void mostrarNodo(struct Nodo* p) {
	if(p == NULL) return;

	printf("Prioridad: %d\n", p -> prioridad);
	printf("Datos: %s\n", p -> datos);
	printf("Puerto: %d\n", p -> puerto);
}

void mostrarPaquetes(ptrEnrutador ptrEnru) {
	if(ptrEnru == NULL) return;

	struct Nodo* p_aux = ptrEnru -> primero;
	for(size_t i = 0; i < ptrEnru -> tam; i++) {
		mostrarNodo(p_aux);
		printf("\n");
		p_aux = p_aux -> siguiente;
	}
}

bool insertarPaquete(ptrEnrutador *ptrPtrEnru, int prioridad, const char *datos, int puerto) {
	if(ptrPtrEnru == NULL
	|| *ptrPtrEnru == NULL
	|| datos == NULL
	|| prioridad < 0
	|| puerto < 0) return false;

	struct Nodo* p_new = malloc(sizeof(struct Nodo));
	if(p_new == NULL) return false;

	p_new -> prioridad = prioridad;
	p_new -> datos = malloc(strlen(datos) + 1);
	if(p_new -> datos == NULL) {
		free(p_new);
		return false;
	}
	strcpy(p_new -> datos, datos);
	p_new -> puerto = puerto;

	if((*ptrPtrEnru) -> tam == 0 || prioridad > (*ptrPtrEnru) -> primero -> prioridad) {
		p_new -> siguiente = (*ptrPtrEnru) -> primero;
		(*ptrPtrEnru) -> primero = p_new;
	} else {
		struct Nodo* p_aux = (*ptrPtrEnru) -> primero;
		while(p_aux -> siguiente != NULL && p_aux -> siguiente -> prioridad >= prioridad) {
			p_aux = p_aux -> siguiente;
		}
		p_new -> siguiente = p_aux -> siguiente;
		p_aux -> siguiente = p_new;
	}

	(*ptrPtrEnru) -> tam++;
	return true;
}

int extraerSiguientePaquete(ptrEnrutador *ptrPtrEnru, char **datosExtraidos) {
	if(ptrPtrEnru == NULL || *ptrPtrEnru == NULL||(*ptrPtrEnru) -> tam == 0 || datosExtraidos == NULL) {
		return -1;
	}
	*datosExtraidos = malloc(strlen((*ptrPtrEnru) -> primero -> datos) + 1);
	if(*datosExtraidos == NULL) return -1;

	int res = (*ptrPtrEnru) -> primero -> puerto;
	strcpy(*datosExtraidos, (*ptrPtrEnru) -> primero -> datos);
	struct Nodo* p_aux = (*ptrPtrEnru) -> primero -> siguiente;

	free((*ptrPtrEnru) -> primero -> datos);
	free((*ptrPtrEnru) -> primero);
	(*ptrPtrEnru) -> primero = p_aux;
	(*ptrPtrEnru) -> tam--;
	return res;
}

void destruirEnrutador(ptrEnrutador *ptrPtrEnru) {
	if(ptrPtrEnru == NULL || *ptrPtrEnru == NULL) return;
	while((*ptrPtrEnru) -> tam > 0) {
		struct Nodo* p_aux = (*ptrPtrEnru) -> primero -> siguiente;
		free((*ptrPtrEnru) -> primero -> datos);
		free((*ptrPtrEnru) -> primero);
		(*ptrPtrEnru) -> primero = p_aux;
		(*ptrPtrEnru) -> tam--;
	}
	free(*ptrPtrEnru);
	*ptrPtrEnru = NULL;
}
