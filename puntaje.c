#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jugadores.h"
#include "puntaje.h"

struct Puntaje {

    char* nombre;
    int dni;
    int puntaje;

};

PuntajePtr cargarPuntajeNulo() {

    PuntajePtr aux = (PuntajePtr)malloc(sizeof(Puntaje));

    aux->nombre = (char*)malloc(sizeof(Puntaje) * 30);

    if(aux == NULL) {
        printf("\nError al pedir memoria\n\n");
        exit(1);
    }

    setPNombre(aux, "VACIO");

    setPDni(aux, 0);

    setPuntaje(aux, 0);

    return aux;
};

void cargarPuntajes(JugadorPtr jugadores[],PuntajePtr puntajes[], int t) {

    for(int i=0; i<t; i++) {

        puntajes[i] = cargarPuntajeNulo(jugadores[i]);

        setPNombre(puntajes[i], getNombre(jugadores[i]));
        setPDni(puntajes[i], getDni(jugadores[i]));

    }


};
void mostrarPuntaje(PuntajePtr puntaje) {

    printf("    -Nombre: %s , Dni: %d , Puntos: %d\n",getPNombre(puntaje), getPDni(puntaje), getPuntaje(puntaje) );

};

PuntajePtr buscarMaxPuntaje(PuntajePtr puntajes[], int t) {

    PuntajePtr aux = (PuntajePtr)malloc(sizeof(Puntaje));

    if(aux==NULL) {
        printf("\nError al pedir memoria\n");
        exit(1);
    }

    aux = puntajes[0];

    for(int i=0; i<t; i++) {
        if( getPuntaje(puntajes[i]) > getPuntaje(aux) ) {
            aux = puntajes[i];
        }
    }

    return aux;

};

void mostrarPuntajes(PuntajePtr puntajes[], int t) {

    printf("\n\n------------------- Tabla de puntajes -------------------\n\n");
    for(int i=0; i<t; i++) {
        mostrarPuntaje(puntajes[i]);
    }

    PuntajePtr pm = buscarMaxPuntaje(puntajes, t);
    printf("\n    ¡ El ganador fue %s con %dptos !",getPNombre(pm),getPuntaje(pm));
    printf("\n\n----------------------------------------------------------\n");

    //guardarPuntajesMaximosEnTxt(puntajes, t);

    free(pm);
};

int pedirTamanioPM() {

    FILE * archivo = fopen("puntajesMaximos.txt", "r");

    if(archivo == NULL) {
        printf("\nOcurrio un error en el archivo\n");
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

}

void traerPuntajesDelTxt(PuntajePtr puntajes[]) {

    FILE * archivoR = fopen("puntajesMaximos.txt", "r");

    int i=0;
    while( !feof(archivoR) ) {

        puntajes[i] = cargarPuntajeNulo();

        char n[80];
        int d,p;

        fscanf(archivoR,"%[^,],%d,%d\n",n,&d,&p);

        setPNombre(puntajes[i], n);
        setPDni(puntajes[i], d);
        setPuntaje(puntajes[i], p);

        i++;
    }

    fclose(archivoR);

};

void verPuntajesMaximos() {

     FILE * archivo = fopen("puntajesMaximos.txt","r");

     int t = pedirTamanioPM() - 1;

     PuntajePtr aux[t];

     int i=0;
    while( !feof(archivo) ) {

        aux[i] = cargarPuntajeNulo();

        char n[80];
        int d,p;

        fscanf(archivo,"%[^,],%d,%d\n",n,&d,&p);

        setPNombre(aux[i], n);
        setPDni(aux[i], d);
        setPuntaje(aux[i], p);

        i++;
    }

    for(int i=0; i<t; i++) {
        printf("Nombre: %s , Dni: %d , Puntos: %d\n",getPNombre(aux[i]), getPDni(aux[i]), getPuntaje(aux[i]));
    }

    for(int i=0; i<t; i++) {
        free(getPNombre(aux[i]));
        free(aux[i]);
    }


    fclose(archivo);

};

void cargarMenu() {

    printf("---------------------------------------------\n");
    printf("           Juego de preguntas - MENU");
    printf("\n---------------------------------------------\n\n");

    int c;
    printf("Queres ver la tabla de puntuacion?\n\n 1:SI   2:NO :");
    scanf("%d",&c);

    printf("\n");
    if(c==1) {
        verPuntajesMaximos();
    }


};

void actualizarPuntajesAlTxt(PuntajePtr aux[], int t, int tpm) {

    FILE * archivo = fopen("puntajesMaximos.txt","w");

    for(int i=0; i<t+tpm; i++) {

        if( strcmp(getPNombre(aux[i]), "VACIO") != 0 ) {
            fprintf(archivo,"%s,%d,%d\n", getPNombre(aux[i]), getPDni(aux[i]), getPuntaje(aux[i]));
        }

    }

    fclose(archivo);

}

void guardarPuntajesMaximosEnTxt(PuntajePtr puntajes[], int t) {

    int tpm = pedirTamanioPM() - 1; //Le resto 1 pq el txt deja siempre un espacio, para no leer el espacio

    PuntajePtr puntajesDelTxt[tpm];

    traerPuntajesDelTxt(puntajesDelTxt);


    PuntajePtr aux[t+tpm]; //array donde uno los puntajes del juego actual con los del txt para mandarlos al txt

    for(int i=0; i<t+tpm; i++) {
        aux[i] = cargarPuntajeNulo(); //Creo un array auxiliar para unir las puntuaciones actuales con la del txt, para luego
                                     //verificar si se supero el record y sobreescribir todo el txt
    }

    for(int i=0; i<t; i++) {
        aux[i] = puntajes[i]; //cargo los puntajes actuales en array aux
    }

    int z=t;
    for(int i=0; i<tpm; i++) {
        aux[z] = puntajesDelTxt[i]; //cargo puntuaciones del txt al aux a apartir de la pos del tamaño de puntuaciones actuales
        z++;
    }

    for(int i=0; i<t+tpm; i++) {

        for(int j=0; j<t+tpm; j++) {

            if( getPDni(aux[i]) == getPDni(aux[j]) && getPuntaje(aux[i]) < getPuntaje(aux[j]) ) {
                aux[i] = cargarPuntajeNulo();
            }

        }

    }

    PuntajePtr cambiar;
    for(int i=0; i<t+tpm-1; i++) {

        for(int j=i+1; j<t+tpm; j++) {

            if( getPuntaje(aux[i]) < getPuntaje(aux[j]) ) { //Ordeno el txt asi queda la tabla de mayor a menor
                cambiar = aux[i];
                aux[i] = aux[j];
                aux[j] = cambiar;
            }

        }

    }

    actualizarPuntajesAlTxt(aux,t,tpm);


    for(int i=0; i<tpm; i++) {
        free(getPNombre(puntajesDelTxt[i])); //libero el array q use para traer las puntuaciones deñ txt
        free(puntajesDelTxt[i]);
    }


};

void destruirPuntajes(PuntajePtr puntajes[], int t) {

    for(int i=0; i<t; i++) {

        free(getPNombre(puntajes[i]));

        free(puntajes[i]);
    }

};

int getPuntaje(PuntajePtr puntaje) {
    return puntaje->puntaje;
};

char* getPNombre(PuntajePtr puntaje) {
    return puntaje->nombre;
};

int getPDni(PuntajePtr puntaje) {
    return puntaje->dni;
};

void setPNombre(PuntajePtr puntaje, char* n) {
    strcpy(puntaje->nombre, n);
}

void setPDni(PuntajePtr puntaje, int d) {
    puntaje->dni = d;
};

void setPuntaje(PuntajePtr puntaje, int d) {
    puntaje->puntaje = d;
};






