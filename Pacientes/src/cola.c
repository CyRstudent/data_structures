#include "cola.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

struct Cola * inicializarCola(void) {
	struct Cola* p_cola = malloc(sizeof(struct Cola));
	if(p_cola == NULL) {
		return NULL;
	}
	p_cola ->primero = NULL;
	p_cola -> ultimo = NULL;
	p_cola -> tam = 0;

	return p_cola;
}

unsigned longitudCola(const struct Cola* ptrCola) {
	if(ptrCola == NULL) {
		return 0;
	}
	return ptrCola -> tam;
}

bool encolar(struct Cola* ptrCola, char * nombre, unsigned edad) {
	if(ptrCola == NULL || nombre == NULL || strlen(nombre) > MAX_NAME_LEN) {
		return false;
	}
	// First, lets initialize the patient
	struct Paciente* p_pac = malloc(sizeof(struct Paciente));
	if(p_pac == NULL) {
		return false;
	}
	p_pac -> edad = edad;
	strcpy(p_pac -> nombre, nombre);

	// Now, lets go for the node
	struct Nodo* p_node = malloc(sizeof(struct Nodo));
	if(p_node == NULL) {
		return false;
	}
	p_node -> persona = p_pac;
	p_node -> siguiente = NULL;

	// Now, lets append the node
	if(ptrCola -> tam == 0) {
		ptrCola -> primero = p_node;
		ptrCola -> ultimo = p_node;
	} else {
		ptrCola -> ultimo -> siguiente = p_node;
		ptrCola -> ultimo = p_node;
	}
	ptrCola -> tam++;
	return true;
}

void mostrarCola(const struct Cola* ptrCola) {
	if(ptrCola == NULL) {
		printf("Cola no inicializada\n");
		return;
	}
	if(ptrCola -> tam == 0) {
		printf("Cola vacía\n");
		return;
	}
	unsigned i = 1;
	struct Nodo* p_aux = ptrCola -> primero;
	while(p_aux != NULL) {
		printf("Nombre: %s, Edad: %d, Posición en la lista: %d\n",
			p_aux -> persona ->nombre,
			p_aux -> persona -> edad,
			i);
		i++;
		p_aux = p_aux -> siguiente;
	}

}

bool desencolar(struct Cola* ptrCola) {
	if(ptrCola == NULL || ptrCola -> primero == NULL) {
		return false;
	}
	ptrCola -> primero = ptrCola -> primero -> siguiente;
	ptrCola -> tam = ptrCola -> tam - 1;
	if(ptrCola -> primero == NULL) {
		ptrCola -> ultimo = NULL;
	}
	return true;
}

struct Paciente* primero(const struct Cola* ptrCola) {
	if(ptrCola == NULL||ptrCola -> primero == NULL || ptrCola -> primero -> persona == NULL) {
		return NULL;
	}

	struct Paciente* p_aux = malloc(sizeof(struct Paciente));
	if(p_aux == NULL) {
		return NULL;
	}
	p_aux -> edad = ptrCola -> primero -> persona -> edad;
	strcpy(p_aux -> nombre, ptrCola -> primero -> persona -> nombre);
	return p_aux;
}

/**
 * @brief Elimina el nodo y la persona contenida en dicho nodo
 * @return La dirección del siguiente nodo
 */
struct Nodo* deleteNode(struct Nodo* p_node) {
	if(p_node == NULL) {
		return NULL;
	}
	struct Nodo* p_aux = p_node -> siguiente;
	free(p_node -> persona);
	free(p_node);
	return p_aux;
}

void liberarCola(struct Cola** ptrPtrCola) {
	if(ptrPtrCola != NULL && *ptrPtrCola != NULL) {
		while((*ptrPtrCola) -> primero != NULL) {
			(*ptrPtrCola) -> primero = deleteNode((*ptrPtrCola) -> primero);
		}
		free(*ptrPtrCola);
		*ptrPtrCola = NULL;
	}
}
