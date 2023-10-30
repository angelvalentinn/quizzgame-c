#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "preguntas.h"

struct Pregunta {

    char* pregunta;
    int dificultad;
    int codigo;
    char* respuestaCorrecta;
    char* respuesta[RESPUESTAS];

};

int tamPreguntas() {

    FILE* archivo = fopen("preguntas.txt","r");

    if(archivo == NULL) {
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

void cargarRespuestasNulas(PreguntaPtr pregunta) {

    for(int i=0; i<RESPUESTAS; i++) {

        pregunta->respuesta[i] = (char*)malloc( sizeof(char) * 30);
        setRespuesta(pregunta,i,"VACIO");

    }

};

PreguntaPtr cargarPreguntaNula() {

    PreguntaPtr aux = (PreguntaPtr)malloc(sizeof(Pregunta));

    if(aux == NULL) {
        printf("\nError al solicitar memoria\n");
        exit(1);
    }

    aux->pregunta = (char*)malloc(sizeof(char) * 80);
    aux->respuestaCorrecta = (char*)malloc(sizeof(char) * 80);

    setPregunta(aux, "VACIO");
    setRespuestaCorrecta(aux, "VACIO");

    cargarRespuestasNulas(aux);

    return aux;

};

void cargarRespuestasDesdeTxt(PreguntaPtr pregunta) {

    FILE* archivo = fopen("respuestas.txt","r");

    if(archivo == NULL) {
        printf("\nError al abrir archivo\n");
        exit(1);
    }


    while( !feof(archivo) ) {

        char r1[80];
        char r2[80];
        char r3[80];
        char r4[80];
        char rcorrecta[80];
        int cod;

        fscanf(archivo,"%[a-z-A-Z],%[a-z-A-Z],%[a-z-A-Z],%[a-zA-Z],%d,%[a-zA-Z]\n",r1,r2,r3,r4,&cod,rcorrecta);

        if( cod == pregunta->codigo ) {

            setRespuesta(pregunta,0,r1);
            setRespuesta(pregunta,1,r2);
            setRespuesta(pregunta,2,r3);
            setRespuesta(pregunta,3,r4);

            setCodigo(pregunta, cod);

            setRespuestaCorrecta(pregunta, rcorrecta);

           return;

        }

    }

    fclose(archivo);

};

void desordenarPreguntas(PreguntaPtr preguntas[], int t) {

    PreguntaPtr aux;
    for (int i = t - 1; i > 0; i--) {

        int j = rand() % (i + 1);

        aux = preguntas[i];
        preguntas[i] = preguntas[j];
        preguntas[j] = aux;

    }

};

void cargarPreguntasDesdeTxt(PreguntaPtr preguntas[], int t) {

    FILE* archivo = fopen("preguntas.txt","r");

    if(archivo == NULL) {
        printf("\nError al abrir archivo\n");
        exit(1);
    }

    int i=0;
    while( !feof(archivo) ) {

        char p[80];
        int d;
        int c;

        fscanf(archivo,"%[^,],%d,%d\n",p, &d, &c);

        setPregunta(preguntas[i], p);
        setDificultad(preguntas[i], d);
        setCodigo(preguntas[i], c);

        i++;
    }

    fclose(archivo);

    for(int i=0; i<t; i++) {
       cargarRespuestasDesdeTxt(preguntas[i]);
    }

    desordenarPreguntas(preguntas, t); //Desordeno para hacer las preguntas aleatorias

};

void cargarPreguntas(PreguntaPtr preguntas[], int t) {

    for(int i=0; i<t; i++) {
       preguntas[i] = cargarPreguntaNula();
    }

   cargarPreguntasDesdeTxt(preguntas,t);

};

void mostrarPregunta(PreguntaPtr pregunta, int i) {

    printf("\n--------------- Pregunta %d ---------------\n", i);
    printf("    %s\n",getPregunta(pregunta));
    printf("    %d\n",getCodigo(pregunta));

    printf("\n---- Posibles respuestas ----\n");

    for(int i=0; i<RESPUESTAS; i++) {
        printf("    %s",getRespuesta(pregunta,i));
    }

    printf("\n");

};

void mostrarPreguntas(PreguntaPtr preguntas[], int t) {

    for(int i=0; i<t; i++) {
        mostrarPregunta(preguntas[i], i);
    }

};

void destruirPregunta(PreguntaPtr pregunta) {

    free(getPregunta(pregunta));

    for(int i=0;i<RESPUESTAS; i++) {
        free(getRespuesta(pregunta,i));
    }

    free(pregunta);

};

void destruirPreguntas(PreguntaPtr preguntas[], int t) {

    for(int i=0; i<t; i++) {
        destruirPregunta(preguntas[i]);
    }
};

char* getPregunta(PreguntaPtr pregunta) {
    return pregunta->pregunta;
};

int getDificultad(PreguntaPtr pregunta) {
    return pregunta->dificultad;
};

int getCodigo(PreguntaPtr pregunta) {
    return pregunta->codigo;
};

void setPregunta(PreguntaPtr pregunta, char* p) {
    strcpy(pregunta->pregunta, p);
}

void setDificultad(PreguntaPtr pregunta, int d) {
    pregunta->dificultad = d;
}

void setCodigo(PreguntaPtr pregunta, int c) {
    pregunta->codigo = c;
};

void setRespuesta(PreguntaPtr pregunta, int i, char* r) {
    strcpy(pregunta->respuesta[i], r);
};

void setRespuestaCorrecta(PreguntaPtr pregunta, char* rc) {
    strcpy(pregunta->respuestaCorrecta, rc);
};

char* getRespuesta(PreguntaPtr pregunta, int i) {
    return pregunta->respuesta[i];
}

char* getRespuestaCorrecta(PreguntaPtr pregunta) {
    return pregunta->respuestaCorrecta;
};









