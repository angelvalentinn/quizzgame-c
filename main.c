#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jugadores.h"
#include "preguntas.h"
#include "puntaje.h"
#include "iniciarJuego.h"

///El trabajo pr�ctico final de la materia Programaci�n de Computadoras del a�o 2023, ser� la creaci�n de un juego
///para m�ltiples jugadores, dicho juego ser� de preguntas y respuestas por medio de m�ltiple choice.
///Aprobar el trabajo pr�ctico es requisito excluyente para aprobar la cursada y tendr� el mismo peso que un examen
///parcial.  El trabajo practico deber� cumplir los siguientes �tems:

///- Al iniciar la partida se debe seleccionar la cantidad de personas que jugar�n. De 2 a 4 personas en simultaneo
///por ejemplo.

///Una vez elegido el n�mero de participantes, se pedir�n datos b�sicos de los mismos. Por ejemplo, alias y dni, el
///dni es importante para identificar a las personas que ya jugaron alguna vez. Inicia el juego el jugador 1, le
///tocar� una pregunta aleatoria con 4 posibles respuestas.
///Se le asignar� un puntaje por pregunta correcta.  Hay preguntas dificiles que suman m�s puntos que las faciles.

///El jugador 1 seguir� jugando mientras que siga acertando las respuestas, y sumando puntos. Una vez que pierda pasa
///al jugador 3,4, etc. Hasta que todos pierden. Una vez que todos pierden se mostrar� el puntaje de cada uno.
///Mostrando quien fue el ganador.

///Las preguntas deber�n estar guardadas en un archivo y ser le�das del mismo.

///Las respuestas deber�n pertenecer a una pregunta y estar guardadas en un archivo.

///El puntaje m�ximo de los jugadores deber� estar guardado en un archivo. Dichos puntajes se deben poder consultar
///desde el men� principal.

///En caso de igualdad de puntos en una partida, el desempate es con una pregunta matem�tica, que el resultado deber� ser tipeado, el que m�s cerca este sumar� un punto extra para desempatar.

///Se espera la utilizaci�n del paradigma de TDA en la mayor cantidad de c�digo fuente posible.



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









