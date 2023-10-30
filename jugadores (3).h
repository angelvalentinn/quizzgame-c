#ifndef JUGADORES_H_INCLUDED
#define JUGADORES_H_INCLUDED

struct Jugador;

typedef struct Jugador Jugador;
typedef Jugador* JugadorPtr;

int pedirJugadores();

JugadorPtr cargarJugador(int i);

void cargarJugadores(JugadorPtr jugadores[], int t);

void destruirJugador(JugadorPtr jugador);

void destruirJugadores(JugadorPtr jugadores[], int t);

char* getNombre(JugadorPtr jugador);

char* getDni(JugadorPtr jugador);

#endif // JUGADORES_H_INCLUDED
