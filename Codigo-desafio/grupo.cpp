#include "grupo.h"
#include "utils.h"
#include "participacion.h"
#include <iostream>

using namespace std;

//////Constructor

grupo:: grupo(){
    letra = ' ';

    equipos = new equipo[4];
    sumarMemoriaHeap(sizeof(equipo) * 4);
    numEquipos = 0;

    partidos = new partido[6];
    sumarMemoriaHeap(sizeof(partido)*6);
    numPartidos = 0;

}
grupo::grupo(char letra) {
    this -> letra = letra;

    equipos = new equipo [4];
    sumarMemoriaHeap(sizeof(equipo) * 4);
    numEquipos = 0;

    partidos = new partido[6];
    sumarMemoriaHeap(sizeof(partido) * 6);
    numPartidos = 0;
}

grupo::grupo(const grupo& otro){
    letra = otro.letra;
    numEquipos=otro.numEquipos;
    numPartidos = otro.numPartidos;

    equipos = new equipo[4];
    sumarMemoriaHeap(sizeof(equipo) * 4);
    for(int i = 0; i < numEquipos; i++){
        equipos[i] = otro.equipos[i];
    }

    partidos = new partido[6];
    sumarMemoriaHeap(sizeof(partido) * 6);
    for(int i = 0; i < numPartidos; i++){
        partidos[i] = otro.partidos[i];
    }
}
grupo& grupo::operator=(const grupo& otro){

    if(this == &otro) return *this; // evitar autoasignación

    // Liberar memoria actual
    delete[] equipos;
    restarMemoriaHeap(sizeof(equipo) * 4);

    delete[] partidos;
    restarMemoriaHeap(sizeof(partido) * 6);

    // Copiar datos básicos
    letra = otro.letra;
    numEquipos = otro.numEquipos;
    numPartidos = otro.numPartidos;

    // Copiar equipos
    equipos = new equipo[4];
    sumarMemoriaHeap(sizeof(equipo) * 4);
    for(int i = 0; i < numEquipos; i++){
        equipos[i] = otro.equipos[i];
    }

    // Copiar partidos
    partidos = new partido[6];
    sumarMemoriaHeap(sizeof(partido) * 6);
    for(int i = 0; i < numPartidos; i++){
        partidos[i] = otro.partidos[i];
    }

    return *this;
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

            int arb[3] = {1,2,3};
            partidos[numPartidos] = partido("2026", "12:00", "Estadio", arb);
            partidos[numPartidos].crearParticipaciones(&equipos[i], &equipos[j]);

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

        participacion* p1 = partidos[i].getParticipacion1();
        participacion* p2 = partidos[i].getParticipacion2();

        equipo* e1 = p1->getEquipo();
        equipo* e2 = p2->getEquipo();


        int g1 = p1->getGoles();
        int g2 = p2->getGoles();


        e1 -> actualizarResultado(g1,g2);
        e2 -> actualizarResultado(g2,g1);
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

                (equipos[j].getPuntos() == equipos[j+1].getPuntos() &&
                equipos[j].getDiferenciaGoles()<equipos[j+1].getDiferenciaGoles()) ||

                (equipos[j].getPuntos()==equipos[j+1].getPuntos() &&
                 equipos[j].getDiferenciaGoles() == equipos[j+1].getDiferenciaGoles() &&
                 equipos[j].getGolesAFavor()<equipos[j+1].getGolesAFavor())
                )
            {
                iteraciones++;

                equipo temp = equipos[j];
                equipos [j] = equipos[j+1];
                equipos [j+1] =temp;

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

equipo* grupo::getEquipos() const {
    return equipos;
}

int grupo::getNumEquipos() const {
    return numEquipos;
}

void grupo::mostrarGrupo(){
    cout<<"Grupo "<<letra<<endl;

    for (int i=0;i<numEquipos; i++){
        cout<<i+1<<". "
        <<equipos[i].getpais()
        <<" - Puntos: "<<equipos[i].getPuntos()
        <<" - Diferencia de goles: "<<equipos[i].getDiferenciaGoles()
        <<" - Goles a favor: "<<equipos[i].getGolesAFavor()
        <<endl;
    }

}