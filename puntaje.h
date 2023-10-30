#ifndef PUNTAJE_H_INCLUDED
#define PUNTAJE_H_INCLUDED

#include "jugadores.h"

struct Puntaje;

typedef struct Puntaje Puntaje;
typedef struct Puntaje* PuntajePtr;

PuntajePtr cargarPuntajeNulo();

void cargarPuntajes(JugadorPtr jugadores[],PuntajePtr puntajes[], int t);

void mostrarPuntaje(PuntajePtr puntaje);

void mostrarPuntajes(PuntajePtr puntajes[], int t);

PuntajePtr buscarMaxPuntaje(PuntajePtr puntajes[], int t);

void destruirPuntajes(PuntajePtr puntajes[], int t);

void guardarPuntajesMaximosEnTxt(PuntajePtr puntajes[], int t);

void actualizarPuntajesAlTxt(PuntajePtr aux[], int t, int tpm) ;

void traerPuntajesDelTxt(PuntajePtr puntajes[]);

void verPuntajesMaximos();

void cargarMenu();

int getPuntaje(PuntajePtr puntaje);

char* getPNombre(PuntajePtr puntaje);

int getPDni(PuntajePtr puntaje);

void setPNombre(PuntajePtr puntaje, char* n);

void setPDni(PuntajePtr puntaje, int d);

void setPuntaje(PuntajePtr puntaje, int d);

#endif // PUNTAJE_H_INCLUDED
