#include "grupo.h"
#include <iostream>

using namespace std;

//////Constructor
grupo::grupo(char letra) {
    this -> letra = letra;

    equipos = new equipo [4];
    numEquipos = 0;

    partidos = new partido[6];
    numPartidos = 0;
}

//////Destructor
grupo::~grupo(){
    delete [] equipos;
    delete [] partidos;
}

void grupo::agregarEquipo(equipo e){
    if (numEquipos<4){
        equipos[numEquipos] = e;
        numEquipos++;
    }
}

void grupo::generarPartidos(){
    numPartidos = 0;

    for (int i = 0; i<numEquipos; i++){
        for (int j = i+1; j<numEquipos; j++){
            partidos[numPartidos] = partido(&equipos[i], &equipos[j]);
            numPartidos++;
        }
    }
}