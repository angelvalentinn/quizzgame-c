#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jugadores.h"
#include "preguntas.h"
#include "puntaje.h"
#include "iniciarJuego.h"

///El trabajo práctico final de la materia Programación de Computadoras del año 2023, será la creación de un juego
///para múltiples jugadores, dicho juego será de preguntas y respuestas por medio de múltiple choice.
///Aprobar el trabajo práctico es requisito excluyente para aprobar la cursada y tendrá el mismo peso que un examen
///parcial.  El trabajo practico deberá cumplir los siguientes ítems:

///- Al iniciar la partida se debe seleccionar la cantidad de personas que jugarán. De 2 a 4 personas en simultaneo
///por ejemplo.

///Una vez elegido el número de participantes, se pedirán datos básicos de los mismos. Por ejemplo, alias y dni, el
///dni es importante para identificar a las personas que ya jugaron alguna vez. Inicia el juego el jugador 1, le
///tocará una pregunta aleatoria con 4 posibles respuestas.
///Se le asignará un puntaje por pregunta correcta.  Hay preguntas dificiles que suman más puntos que las faciles.

///El jugador 1 seguirá jugando mientras que siga acertando las respuestas, y sumando puntos. Una vez que pierda pasa
///al jugador 3,4, etc. Hasta que todos pierden. Una vez que todos pierden se mostrará el puntaje de cada uno.
///Mostrando quien fue el ganador.

///Las preguntas deberán estar guardadas en un archivo y ser leídas del mismo.

///Las respuestas deberán pertenecer a una pregunta y estar guardadas en un archivo.

///El puntaje máximo de los jugadores deberá estar guardado en un archivo. Dichos puntajes se deben poder consultar
///desde el menú principal.

///En caso de igualdad de puntos en una partida, el desempate es con una pregunta matemática, que el resultado deberá ser tipeado, el que más cerca este sumará un punto extra para desempatar.

///Se espera la utilización del paradigma de TDA en la mayor cantidad de código fuente posible.



int main()
{
    srand(time(NULL));

    cargarMenu();

    //Cargar jugadores

    int c = pedirJugadores();

    JugadorPtr jugadores[c];

    cargarJugadores(jugadores,c);

    //Cargar preguntas

    int p = tamPreguntas();

    PreguntaPtr preguntas[p];

    cargarPreguntas(preguntas,p);

    //Cargar puntajes

    PuntajePtr puntajes[c];

    cargarPuntajes(jugadores,puntajes,c);

    //Iniciar juego

    iniciarJuego(preguntas,jugadores,puntajes,c,p);

    guardarPuntajesMaximosEnTxt(puntajes, c);

    mostrarPuntajes(puntajes,c);

    //------------
    destruirJugadores(jugadores,c);

    destruirPreguntas(preguntas,p);

    destruirPuntajes(puntajes,p);

    return 0;
}









