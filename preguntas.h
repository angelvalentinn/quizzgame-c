#ifndef PREGUNTAS_H_INCLUDED
#define PREGUNTAS_H_INCLUDED

#define RESPUESTAS 4

struct Pregunta;

typedef struct Pregunta Pregunta;
typedef Pregunta* PreguntaPtr;

int tamPreguntas();

void cargarRespuestasNulas(PreguntaPtr pregunta);

PreguntaPtr cargarPreguntaNula();

void cargarRespuestasDesdeTxt(PreguntaPtr pregunta);

void desordenarPreguntas(PreguntaPtr preguntas[], int t);

void cargarPreguntasDesdeTxt(PreguntaPtr preguntas[], int t);

void cargarPreguntas(PreguntaPtr preguntas[], int t);

void mostrarPregunta(PreguntaPtr preguntas, int i);
                                                        //Procedimientos para verificar q cargaron las preguntas
void mostrarPreguntas(PreguntaPtr preguntas[], int t);

char* getPregunta(PreguntaPtr pregunta);

int getDificultad(PreguntaPtr pregunta);

int getCodigo(PreguntaPtr pregunta);

void setCodigo(PreguntaPtr pregunta, int c);

void setPregunta(PreguntaPtr pregunta, char* p);

void setDificultad(PreguntaPtr pregunta, int d);

void setRespuesta(PreguntaPtr pregunta, int i, char* r);

void setRespuestaCorrecta(PreguntaPtr pregunta, char* rc);

char* getRespuesta(PreguntaPtr pregunta, int i);

char* getRespuestaCorrecta(PreguntaPtr pregunta);

void destruirPregunta(PreguntaPtr pregunta);

void destruirPreguntas(PreguntaPtr preguntas[], int t);

#endif // PREGUNTAS_H_INCLUDED
