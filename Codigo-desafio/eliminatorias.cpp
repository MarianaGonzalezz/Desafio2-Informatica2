#include "eliminatorias.h"
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

///Destructor
eliminatorias::~eliminatorias(){
    if(partidos != nullptr)
        delete[] partidos;
}

void eliminatorias::setEquipos(equipo* equipos, int n) {
    clasificados = equipos;
    numEquipos = n;
}

void eliminatorias::crearCruces(){
    numPartidos = numEquipos/2;
    partidos = new partido[numPartidos];

    for (int i = 0; i< numEquipos/2; i++){
        partidos[i] = partido(&clasificados[i], &clasificados[numEquipos -1-i]);
    }
}

void eliminatorias::resolverEmpate(partido &p){
    int g1 = p.getGoles1();
    int g2 = p.getGoles2();

    equipo* e1 = p.getEquipo1();
    equipo* e2 = p.getEquipo2();

    if(g1==g2){
        if(e1->getRanking() < e2 -> getRanking()){
            g1++;
        }else{
            g2++;
        }
    }
    p.setGoles(g1,g2);
}

void eliminatorias::simularFase(){
    cout<<"Fase: "<<fase<<endl;

    for (int i = 0; i<numPartidos; i++){
        partidos[i].simular();

        resolverEmpate(partidos[i]);

        equipo* e1 = partidos[i].getEquipo1();
        equipo* e2 = partidos[i].getEquipo2();

        int g1 = partidos[i].getGoles1();
        int g2 = partidos[i].getGoles2();

        e1 -> actualizarEstadisticas(g1,g2);
        e2 -> actualizarEstadisticas(g2,g1);

        cout << e1->getNombre()<<" "<<g1<<" - "<<g2<<" "<<e2->getNombre()<<endl;
    }
}


equipo* eliminatorias::obtenerGanadores(){

    equipo* ganadores = new equipo [numPartidos];

    for (int i = 0; i<numPartidos; i++){

        equipo* e1 = partidos[i].getEquipo1();
        equipo* e2 = partidos[i].getEquipo2();

        int g1 = partidos[i].getGoles1();
        int g2 = partidos[i].getGoles2();

        if (g1 >= g2){
            ganadores [i] = *e1;
        }else{
            ganadores[i] = *e2;
        }
    }
    return ganadores;
}

void eliminatorias::generarSiguienteFase(eliminatorias &siguiente){
    equipo* ganadores = obtenerGanadores();

    siguiente.setEquipos(ganadores, numPartidos);
    siguiente.crearCruces();

    delete[] ganadores;
}

void eliminatorias::mostrarFase(){
    cout<<"Fase: "<< fase<< endl;

    for (int i = 0; i<numPartidos; i++){
        cout << partidos[i].getEquipo1()->getNombre()<<" vs "<< partidos[i].getEquipo2()->getNombre() << endl;
    }
}
