#include "grupo.h"
#include <iostream>

using namespace std;

//////Constructor
grupo::grupo(char letra) {
    this -> letra = letra;

    equipos = new equipo [4];
    sumarMemoriaHeap(sizeof(equipo) * 4);
    numEquipos = 0;

    partidos = new partido[6];
    sumarMemoriaHeap(sizeof(partido) * 6);
    numPartidos = 0;
}

//////Destructor
grupo::~grupo(){
    delete [] equipos;
    restarMemoriaHeap(sizeof(equipo) * 4);

    delete [] partidos;
    restarMemoriaHeap(sizeof(partido) * 6);

}

void grupo::agregarEquipo(const equipo& e){
    iteraciones++;
    if (numEquipos<4){
        equipos[numEquipos] = e;
        numEquipos++;
    }
}

void grupo::generarPartidos(){
    entrarF(sizeof(int)*2);
    numPartidos = 0;

    for (int i = 0; i<numEquipos; i++){
        iteraciones++;

        for (int j = i+1; j<numEquipos; j++){
            iteraciones++;
            partidos[numPartidos] = partido(&equipos[i], &equipos[j]);
            numPartidos++;
        }
    }
    salirF(sizeof(int)*2);
}

void grupo::simularPartidos(){
    entrarF(sizeof(int)*3 + sizeof(equipo*)*2);
    for(int i = 0; i < numPartidos; i++){
        iteraciones++;

        partidos[i].simular();

        equipo* e1 = partidos[i].getEquipo1();
        equipo* e2 = partidos [i].getEquipo2();


        int g1 = partidos[i].getGoles1();
        int g2 = partidos[i].getGoles2();


        e1 -> actualizarEstadisticas(g1,g2);
        e2 -> actualizarEstadisticas(g2,g1);
    }
    salirF(sizeof(int)*3 + sizeof(equipo*)*2);
}


void grupo::ordenarTabla(){
    entrarF(sizeof(int)*2 + sizeof(equipo));

    for (int i = 0; i<numEquipos-1; i++){
        iteraciones++;

        for(int j =0; j<numEquipos-i-1;j++){
            iteraciones++;
            if(
                equipos[j].getPuntos()<equipos[j+1].getPuntos() ||

                (equipos[j].getPuntos() == equipos[j+1].getPuntos &&
                equipos[j].getDiferenciaGoles()<equipos[j+1].getDiferenciaGoles()) ||

                (equipos[j].getPuntos()==equipos[j+1].getPuntos() &&
                 equipos[j].getDiferenciaGoles() == equipos[j+1].getDiferenciaGoles() &&
                 equipos[j].getGolesFavor()<equipos[j+1].getGolesFavor())
                )
            {
                iteraciones++;

                sumarMemoriaHeap(sizeof(equipo));

                equipo temp = equipos[j];
                equipos [j] = equipos[j+1];
                equipos [j+1] =temp;

                restarMemoriaHeap(sizeof(equipo));
            }
        }
    }
    salirF(sizeof(int)*2 + sizeof(equipo));
}

equipo* grupo::obtenerClasificados(){

    entrarF(sizeof(int) + sizeof(equipo*));

    ordenarTabla();
    equipo* top = new equipo[3];
    sumarMemoriaHeap(sizeof(equipo) * 3);

    for(int i = 0;i<3;i++){
        top[i] = equipos [i];
    }
    salirF(sizeof(int) + sizeof(equipo*));
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