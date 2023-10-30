#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jugadores.h"

struct Jugador {

    char* nombre;
    int dni;

};

int pedirJugadores() {

    int c;

    printf("\nIngrese la cantidad de personas que jugaran: ");
    scanf("%d",&c);

    return c;

};

JugadorPtr cargarJugador(int i) {

    JugadorPtr aux = (JugadorPtr)malloc( sizeof(Jugador) );

    aux->nombre = (char*)malloc( sizeof(char) * 30 );


    if(aux == NULL || getNombre(aux) == NULL) {
        printf("\nError al solicitar memoria\n");
        exit(1);
    }

    printf("\n--------- Jugador %d ---------\n", i);
    char n[30];
    printf("\nIngresar nombre del jugador: ");
    fflush(stdin);
    gets(n);
    setNombre(aux,n);

    int d;
    printf("Ingresar dni del jugador: ");
    scanf("%d",&d);
    setDni(aux,d);

    return aux;

};

void cargarJugadores(JugadorPtr jugadores[], int t) {

    for(int i=0; i<t; i++) {
        jugadores[i] = cargarJugador(i);
    }

};

void destruirJugador(JugadorPtr jugador) {

    free(getNombre(jugador));
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

int getDni(JugadorPtr jugador) {
    return jugador->dni;
};

void setNombre(JugadorPtr jugador, char* n) {
    strcpy(jugador->nombre, n);
};

void setDni(JugadorPtr jugador, int d) {
    jugador->dni = d;
};




