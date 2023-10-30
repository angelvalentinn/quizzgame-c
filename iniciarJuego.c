#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puntaje.h"
#include "preguntas.h"
#include "iniciarJuego.h"

struct PreguntaDesempate {

    char* preguntaD;
    int respuestaCorrecta;

};

int pedirTamanioPD() {

    FILE * archivo = fopen("preguntasDesempate.txt","r");

    if(archivo==NULL) {
        printf("\nError al abrir archivo\n\n");
        exit(1);
    }

    int i=0;
    char renglon[100];

    while( !feof(archivo) ) {

            fgets(renglon,100,archivo);
            i++;

    }

    fclose(archivo);

    return i;

};

PreguntaDesempatePtr cargarPreguntaDesempateNula() {

    PreguntaDesempatePtr aux = (PreguntaDesempatePtr)malloc(sizeof(PreguntaDesempate));

    aux->preguntaD = (char*)malloc(sizeof(char) * 80);

    if(aux==NULL) {
        printf("\nError al pedir memoria\n");
        exit(1);
    }

    return aux;

};

void cargarPreguntasDesempateDesdeTxt(PreguntaDesempatePtr q[]) {

    FILE * archivo = fopen("preguntasDesempate.txt","r");

    if(archivo==NULL) {
        printf("\nError al abrir archivo\n\n");
        exit(1);
    }

    int i=0;
    while( !feof(archivo) ) {

        char  pr[80];
        int rc;

        fscanf(archivo,"%[^,],%d\n", pr, &rc);

        setPreguntaD(q[i], pr);
        setRespuestaCorrectaD(q[i], rc);


        i++;

    }

    fclose(archivo);

};

void iniciarJuego(PreguntaPtr preguntas[], JugadorPtr jugadores[], PuntajePtr puntajes[], int ct, int pt) {

    int check=1, z=0;
    char resp[30];

    printf("\n------------------------------------------------------------\n");
    printf("                   Comienza el juego");
    printf("\n------------------------------------------------------------\n\n");

    for(int i=0; i<ct; i++) {

        check=1;
        printf("    Turno del jugador: %s\n", getNombre(jugadores[i]));

        while( check==1 ) {

            printf("\n- Pregunta %d, vale %dptos: %s?\n",i,getDificultad(preguntas[z]), //Las preguntas se desordenan cuando las traigo del txt
                                                        getPregunta(preguntas[z]));

            printf("\n  Opciones: ");

            for(int j=0; j<RESPUESTAS; j++) {
                printf("%s - ",getRespuesta(preguntas[z],j));
            }

            printf("\n\n  Ingrese su respuesta: ");
            fflush(stdin);
            gets(resp);

            if( strcmp(resp, getRespuestaCorrecta(preguntas[z])) == 0 ){

                int puntajeAntiguo = getPuntaje(puntajes[i]);
                int puntajeDeLaPregunta = getDificultad(preguntas[z]);

                int puntajeNuevo = puntajeAntiguo + puntajeDeLaPregunta;

                setPuntaje(puntajes[i], puntajeNuevo);

                printf("\n\n    ¡ Respuesta correcta +%dptos !",getDificultad(preguntas[z]));
                printf("\n\n    | Puntos Actuales: %dptos |\n", getPuntaje(puntajes[i]));

            } else {

                printf("\n\nRespuesta incorrecta\n\n");
                check = -1;
            }

            z++;

        }

    }


    //Desempate
    int tpd = pedirTamanioPD(); //tamanio de preguntas de desempate

    PreguntaDesempatePtr q[tpd];

    for(int i=0; i<tpd; i++) {
        q[i] = cargarPreguntaDesempateNula();  //Cargamos todas las preguntas de desempate
    }

    cargarPreguntasDesempateDesdeTxt(q);

    //verificamos q haya empate y lo desempatamos
    int y=0;
    for(int i=0; i<ct-1; i++) {

        for(int j=i+1; j<ct; j++) {

            if( getPuntaje(puntajes[i]) == getPuntaje(puntajes[j]) ) {


                    int j1, j2, respD;

                    printf("\n\n-----------------------------------------------------\n");
                    printf("        Desempate entre %s y %s",getPNombre(puntajes[i]), getPNombre(puntajes[j]));
                    printf("\n-----------------------------------------------------\n\n");

                    printf("    - Pregunta de desempate, ganara el que acierte o se acerque mas: %s? \n",getPreguntaD(q[y]) );

                    do {
                        printf("\nTurno de %s: ",getPNombre(puntajes[i]));
                        scanf("%d",&j1);

                        printf("\nTurno de %s: ",getPNombre(puntajes[j]));
                        scanf("%d",&j2);

                    } while(j1 == j2);

                    respD = q[y]->respuestaCorrecta;

                    j1 = abs(respD - j1);
                                            //abs funcion  devuelve el valor absoluto de un entero
                    j2 = abs(respD - j2);

                    if( (j1 == 0 && j2 != 0) || (j1 < j2 && j2 != 0) ) {

                        printf("\nEl ganador del desempate es %s", getPNombre(puntajes[i]));
                        setPuntaje(puntajes[i], getPuntaje(puntajes[i]) + 1);

                    } else if( (j2 == 0 && j1 != 0) || (j2 < j1  && j1 != 0) )  {

                        printf("\nEl ganador del desempate es %s", getPNombre(puntajes[j]));
                        setPuntaje(puntajes[j], getPuntaje(puntajes[j]) + 1);
                    }

                    i=0;
                    y++; //Si hay mas de 1 empate se elige la sig pregunta de desempate

            }

        }

    }

    for(int i=0; i<tpd; i++) {
        free(q[i]->preguntaD);

        free(q[i]); //Libear preguntas de desempate
    }

};

char* getPreguntaD(PreguntaDesempatePtr p) {
    return p->preguntaD;
};

int getRespuestaCorrectaD(PreguntaDesempatePtr p) {
    return p->respuestaCorrecta;
};

void setPreguntaD(PreguntaDesempatePtr p, char* pr) {
    strcpy(p->preguntaD, pr);
};

void setRespuestaCorrectaD(PreguntaDesempatePtr p, int rc) {
    p->respuestaCorrecta = rc;
};




