#ifndef INICIARJUEGO_H_INCLUDED
#define INICIARJUEGO_H_INCLUDED

#include "jugadores.h"
#include "preguntas.h"
#include "puntaje.h"

struct PreguntaDesempate;

typedef struct PreguntaDesempate PreguntaDesempate;
typedef PreguntaDesempate* PreguntaDesempatePtr;

int pedirTamanioPD();

PreguntaDesempatePtr cargarPreguntaDesempateNula();

void cargarPreguntasDesempateDesdeTxt(PreguntaDesempatePtr q[]);

void iniciarJuego(PreguntaPtr preguntas[], JugadorPtr jugadores[], PuntajePtr puntajes[], int ct, int pt);

char* getPreguntaD(PreguntaDesempatePtr p);

int getRespuestaCorrectaD(PreguntaDesempatePtr p);

void setPreguntaD(PreguntaDesempatePtr p, char* pr);

void setRespuestaCorrectaD(PreguntaDesempatePtr p, int rc);

#endif // INICIARJUEGO_H_INCLUDED
