#include "eliminatorias.h"
#include "utils.h"
#include "participacion.h"
#include "partido.h"
#include <iostream>


using namespace std;

///Constructor
eliminatorias::eliminatorias(string nombreFase) {
    fase = nombreFase;

    partidos = nullptr;
    numPartidos = 0;

    clasificados = nullptr;
    numEquipos = 0;

}

eliminatorias::eliminatorias(){
    fase = "";

    clasificados = nullptr;
    numEquipos = 0;

    partidos = nullptr;
    numPartidos = 0;

}

///Destructor
eliminatorias::~eliminatorias(){
    if(partidos != nullptr){
        delete[] partidos;
        restarMemoriaHeap(sizeof(partido) * numPartidos);
    }

    /*if(clasificados != nullptr){
        delete[] clasificados;
        restarMemoriaHeap(sizeof(equipo) * numEquipos);
    }*/
}

void eliminatorias::setEquipos(equipo* equipos, int n) {
    clasificados = new equipo[n];
    sumarMemoriaHeap(sizeof(equipo) * n);

    for(int i = 0; i < n; i++){
        clasificados[i] = equipos[i];
    }

    numEquipos = n;
}

void eliminatorias::crearCruces(){
    numPartidos = numEquipos/2;
    partidos = new partido[numPartidos];
    sumarMemoriaHeap(sizeof(partido) * numPartidos);

    for (int i = 0; i< numEquipos/2; i++){

        partidos[i].crearParticipaciones(&clasificados[i], &clasificados[numEquipos -1-i]);
    }
}

void eliminatorias::resolverEmpate(partido &p){
    entrarF(sizeof(int)*2 + sizeof(equipo*)*2);

    participacion* p1 = p.getParticipacion1();
    participacion* p2 = p.getParticipacion2();

    int g1 = p1->getGoles();
    int g2 = p2->getGoles();

    equipo* e1 = p1->getEquipo();
    equipo* e2 = p2->getEquipo();

    if(g1==g2){
        if(e1->getRanking() < e2 -> getRanking()){
            g1++;
        }else{
            g2++;
        }
    }

    p1->setEstadisticasPartido(g1, g2, p1->getPosesion());
    p2->setEstadisticasPartido(g2, g1, p2->getPosesion());

    salirF(sizeof(int)*2 + sizeof(equipo*)*2);
}

void eliminatorias::simularFase(){

    cout<<fase<<endl;

    entrarF(sizeof(int)*3 + sizeof(equipo*)*2);

    for (int i = 0; i<numPartidos; i++){
        iteraciones++;

        partidos[i].simular();

        resolverEmpate(partidos[i]);

        participacion* p1 = partidos[i].getParticipacion1();
        participacion* p2 = partidos[i].getParticipacion2();

        equipo* e1 = p1->getEquipo();
        equipo* e2 = p2->getEquipo();

        int g1 = p1->getGoles();
        int g2 = p2->getGoles();



        cout << e1->getpais()<<" "<<g1<<" - "<<g2<<" "<<e2->getpais()<<endl;
    }
    salirF(sizeof(int)*3 + sizeof(equipo*)*2);
}


equipo* eliminatorias::obtenerGanadores(){

    entrarF(sizeof(int)*3 + sizeof(equipo*)*2);

    equipo* ganadores = new equipo [numPartidos];
    sumarMemoriaHeap(sizeof(equipo) * numPartidos);

    for (int i = 0; i<numPartidos; i++){
        iteraciones++;

        participacion* p1 = partidos[i].getParticipacion1();
        participacion* p2= partidos[i].getParticipacion2();

        equipo* e1 = p1->getEquipo();
        equipo* e2 = p2->getEquipo();

        int g1 = p1->getGoles();
        int g2 = p2->getGoles();

        if (g1 >= g2){
            iteraciones++;

            ganadores [i] = *e1;
        }else{
            ganadores[i] = *e2;
        }
    }

    salirF(sizeof(int)*3 + sizeof(equipo*)*2);
    return ganadores;
}

void eliminatorias::generarSiguienteFase(eliminatorias &siguiente){

    entrarF(sizeof(equipo*));
    equipo* ganadores = obtenerGanadores();

    siguiente.setEquipos(ganadores, numPartidos);
    delete[] ganadores;
    restarMemoriaHeap(sizeof(equipo)*numPartidos);

    siguiente.crearCruces();

    salirF(sizeof(equipo*));
}

int eliminatorias::getNumPartidos() const {
    return numPartidos;
}
equipo* eliminatorias::getEquipos() const {
    return clasificados;
}
