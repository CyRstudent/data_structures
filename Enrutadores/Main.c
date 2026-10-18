#include "Enrutador.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
	ptrEnrutador test1 = NULL;

	bool res = iniciarEnrutador(&test1);
	assert(res && "Fallo en la función iniciarEnrutador");
	mostrarPaquetes(test1); // Se espera simplemente una linea vacia

	bool f1 = insertarPaquete(&test1, 13, "Jaja broma graciosa", 2);
	bool f2 = insertarPaquete(&test1, 13, "Que ha dicho el de arriba este?", 1);
	bool f3 = insertarPaquete(&test1, 14, "jijijaja ahora soy yo el que está encima", 5);
	bool f4 = insertarPaquete(&test1, 2, "Soy shikitillo", 9);
	assert(f1 && f2 && f3 && f4 && "Fallo en la función insertarPaquete");

	mostrarPaquetes(test1);

	char* delStr = NULL;
	int del = extraerSiguientePaquete(&test1, &delStr);
	assert(del == 5 && "Fallo en la función extraerSiguientePaquete");
	printf("%s\n", delStr); // Se espera lo que hay puesto en f1
	mostrarPaquetes(test1); // Se espera todos los paquetes menos ese

	destruirEnrutador(&test1);
	assert(test1 == NULL && "Fallo en la función destruirEnrutador");

	return 0;
}
