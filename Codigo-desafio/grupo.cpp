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

void grupo::simularPartidos(){
    for(int i = 0; i < numPartidos; i++){
        partidos[i].simular();

        equipo* e1 = partidos[i].getEquipo1();
        equipo* e2 = partidos [i].getEquipo2();

        int g1 = partidos[i].getGoles1();
        int g2 = partidos[i].getGoles2();

        e1 -> actualizarEstadisticas(g1,g2);
        e2 -> actualizarEstadisticas(g2,g1);
    }
}


void grupo::ordenarTabla(){
    for (int i = 0; i<numEquipos-1; i++){
        for(int j =0; j<numEquipos-i-1;j++){
            if(
                equipos[j].getPuntos()<equipos[j+1].getPuntos() ||

                (equipos[j].getPuntos() == equipos[j+1].getPuntos &&
                equipos[j].getDiferenciaGoles()<equipos[j+1].getDiferenciaGoles()) ||

                (equipos[j].getPuntos()==equipos[j+1].getPuntos() &&
                 equipos[j].getDiferenciaGoles() == equipos[j+1].getDiferenciaGoles() &&
                 equipos[j].getGolesFavor()<equipos[j+1].getGolesFavor())
                )
            {

                equipo temp = equipos[j];
                equipos [j] = equipos[j+1];
                equipos [j+1] =temp;
            }
        }
    }
}

equipo* grupo::obtenerClasificados(){

    ordenarTabla();
    equipo* top = new equipo[3];

    for(int i = 0;i<3;i++){
        top[i] = equipos [i];
    }
    return top;
}

void grupo::mostrarGrupo(){
    cout<<"Grupo "<<letra<<endl;

    for (int i=0;i<numEquipos; i++){
        cout<<i+1<<". "
        <<equipos[i].getNombre()
        <<" - Puntos: "<<equipos[i].getPuntos()
        <<" - Diferencia de goles: "<<equipos[i].getDiferenciaGoles()
        <<" - Goles a favor: "<<equipos[i].getGolesFavor()
        <<endl;
    }

}