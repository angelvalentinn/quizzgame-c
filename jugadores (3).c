#include <stdio.h>
#include <stdlib.h>

#include "jugadores.h"

struct Jugador {

    char* nombre;
    char* dni;

};

int pedirJugadores() {

    int c;

    printf("\nIngrese la cantidad de personas que jugaran: ");
    scanf("%d",&c);

    return c;

};

JugadorPtr cargarJugador(int i) {

    JugadorPtr aux = (JugadorPtr)malloc( sizeof(Jugador) );

    aux->nombre = (char*)malloc( sizeof(char) * 20 );

    aux->dni = (char*)malloc( sizeof(char) * 20 );

    if(aux == NULL || aux->nombre == NULL) {
        printf("\nError al solicitar memoria\n");
        exit(1);
    }

    printf("\n--------- Jugador %d ---------\n", i);
    printf("\nIngresar nombre del jugador: ");
    fflush(stdin);
    gets( getNombre(aux) );

    printf("Ingresar dni del jugador: ");
    fflush(stdin);
    gets( getDni(aux) );

    return aux;

};

void cargarJugadores(JugadorPtr jugadores[], int t) {

    for(int i=0; i<t; i++) {
        jugadores[i] = cargarJugador(i);
    }

};

void destruirJugador(JugadorPtr jugador) {

    free(jugador->nombre);
    free(jugador->dni);
    free(jugador);

};

void destruirJugadores(JugadorPtr jugadores[], int t) {

    for(int i=0; i<t; i++) {
        destruirJugador(jugadores[i]);
    }

};

char* getNombre(JugadorPtr jugador) {
    return jugador->nombre;
};

char* getDni(JugadorPtr jugador) {
    return jugador->dni;
};




