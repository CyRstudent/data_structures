#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cola.h"

/*
  Objetivo de las pruebas:
  - Verificar comportamiento con cola NO inicializada (puntero NULL).
  - Verificar comportamiento con cola vacía.
  - Encolar 3 pacientes, comprobar orden FIFO y tamaño.
  - Probar primero() y que el llamador libere la copia devuelta.
  - Desencolar hasta vaciar, comprobando tamaño y punteros.
  - Repetir pruebas de cola vacía tras vaciar.
  - Liberar correctamente toda la memoria al final (cola vacía y con contenido).
*/

static void print_sep(const char* title) {
    printf("\n================ %s ================\n", title);
}

int main(void) {
    struct Cola *ptrCola;
    struct Paciente *paciente;
    bool ok;

    print_sep("PRUEBA 1: COLA INICIALIZADA PERO VACIA");
    ptrCola = inicializarCola();
    if (ptrCola == NULL) {
        printf("[FATAL] inicializarCola() devolvió NULL. No se puede continuar.\n");
        return 1;
    }
    printf("[INFO] tras inicializar: tam=%d (esp=0), primero=%s, ultimo=%s\n",
           longitudCola(ptrCola),
           ptrCola->primero == NULL ? "NULL" : "NO-NULL",
           ptrCola->ultimo  == NULL ? "NULL" : "NO-NULL");
    mostrarCola(ptrCola);
    paciente = primero(ptrCola);
    printf("[INFO] primero(c vacia) -> %s (esp=NULL)\n", paciente == NULL ? "NULL" : "NO-NULL");
    if (paciente) free(paciente);
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar(c vacia) -> %s (esp=false)\n", ok ? "true" : "false");

    free(ptrCola);
    
    ptrCola= NULL;

    print_sep("PRUEBA 2: COLA NO INICIALIZADA (ptr NULL)");
    mostrarCola(ptrCola);

    longitudCola(ptrCola);
    printf("[INFO] longitudCola(NULL) -> %s (esperado: false)\n", ok ? "true" : "false");


    paciente = primero(ptrCola);
    if (paciente == NULL) {
        printf("[OK] primero(NULL) -> NULL\n");
    } else {
        printf("[WARN] primero(NULL) devolvió algo inesperado\n");
        free(paciente);
    }
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar(NULL) -> %s (esperado: false)\n", ok ? "true" : "false");

    ptrCola = inicializarCola();

    print_sep("PRUEBA 2: ENCOLAR TRES PACIENTES");
    ok = encolar(ptrCola, "Ana Perez", 30);
    printf("[INFO] encolar(Ana,30) -> %s (esp=true), tam=%d (esp=1)\n", ok ? "true" : "false", longitudCola(ptrCola));
    ok = encolar(ptrCola, "Luis Gomez", 45);
    printf("[INFO] encolar(Luis,45) -> %s (esp=true), tam=%d (esp=2)\n", ok ? "true" : "false", longitudCola(ptrCola));
    ok = encolar(ptrCola, "Maria Lopez", 25);
    printf("[INFO] encolar(Maria,25) -> %s (esp=true), tam=%d (esp=3)\n", ok ? "true" : "false", longitudCola(ptrCola));
    mostrarCola(ptrCola);
    paciente = primero(ptrCola);
    if (paciente) {
        printf("[INFO] primero() -> %s %d (esp=Ana Perez,30)\n", paciente->nombre, paciente->edad);
        free(paciente);
    } else {
        printf("[WARN] primero() devolvió NULL con cola no vacia\n");
    }

    print_sep("PRUEBA 4: DESENCOLAR EN ORDEN HASTA VACIAR");
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar() #1 -> %s (esp=true), tam=%d (esp=2)\n", ok ? "true" : "false", longitudCola(ptrCola));
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar() #2 -> %s (esp=true), tam=%d (esp=1)\n", ok ? "true" : "false", longitudCola(ptrCola));
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar() #3 -> %s (esp=true), tam=%d (esp=0)\n", ok ? "true" : "false", longitudCola(ptrCola));
    printf("[INFO] tras vaciar: primero=%s, ultimo=%s (esp=ambos NULL)\n",
           ptrCola->primero == NULL ? "NULL" : "NO-NULL",
           ptrCola->ultimo  == NULL ? "NULL" : "NO-NULL");
    mostrarCola(ptrCola);
    paciente = primero(ptrCola);
    printf("[INFO] primero() tras vaciar -> %s (esp=NULL)\n", paciente == NULL ? "NULL" : "NO-NULL");
    if (paciente) free(paciente);
    ok = desencolar(ptrCola);
    printf("[INFO] desencolar() tras vaciar -> %s (esp=false)\n", ok ? "true" : "false");

    print_sep("PRUEBA 5: LIMPIEZA FINAL CON COLA VACIA");
    liberarCola(&ptrCola);
    if (ptrCola == NULL) {
        printf("[INFO] liberarCola(&c) -> c == NULL (cola vacia liberada correctamente)\n");
    } else {
        printf("[INFO] liberarCola(&c) -> c != NULL; tam=%d\n", longitudCola(ptrCola));
        free(ptrCola);
        ptrCola = NULL;
    }

    print_sep("PRUEBA 6: LIBERAR COLA CON CONTENIDO");
    ptrCola = inicializarCola();
    encolar(ptrCola, "Paciente1", 50);
    encolar(ptrCola, "Paciente2", 60);
    encolar(ptrCola, "Paciente3", 70);
    printf("[INFO] Antes de liberar: tam=%d (esp=3)\n", longitudCola(ptrCola));
    mostrarCola(ptrCola);
    liberarCola(&ptrCola);
    if (ptrCola == NULL) {
        printf("[INFO] liberarCola(&c) -> c == NULL (cola vacia liberada correctamente)\n");
    } else {
        printf("[INFO] liberarCola(&c) -> c != NULL; tam=%d\n", longitudCola(ptrCola));
        free(ptrCola);
        ptrCola = NULL;
    }
    

    print_sep("FIN DE PRUEBAS");
    return 0;
}
