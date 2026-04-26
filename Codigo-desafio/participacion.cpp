#include "participacion.h"
#include "partido.h"
#include "utils.h"
#include <iostream>

using namespace std;

// Cosntructores y Destructores

participacion::participacion()
    : equipoPtr(nullptr), partidoPtr(nullptr), goles(0), golesContra(0), posesion(0) {
    for (int i = 0; i < 11; i++) {
        iteraciones++;

        convocados[i] = nullptr;
        golesJugador[i] = 0;
        tarjetasAmarillas[i] = 0;
        tarjetasRojas[i] = 0;
        faltasJugador[i] = 0;
        minutosJugador[i] = 90;
    }
}

participacion::participacion(equipo* eq, partido* p)
    : equipoPtr(eq), partidoPtr(p), goles(0), golesContra(0), posesion(0) {
    for (int i = 0; i < 11; i++) {
        iteraciones++;

        convocados[i] = nullptr;
        golesJugador[i] = 0;
        tarjetasAmarillas[i] = 0;
        tarjetasRojas[i] = 0;
        faltasJugador[i] = 0;
        minutosJugador[i] = 90;
    }
}

participacion::~participacion() {}

// Metodos

void participacion::asignarConvocados(int indices[11]) {
    entrarF(sizeof(int)*11);

    for (int i = 0; i < 11; i++) {
        iteraciones++;

        if (equipoPtr != nullptr && indices[i] >= 0 && indices[i] < 26) {
            convocados[i] = equipoPtr->getJugadores() + indices[i];
        }

    }
    salirF(sizeof(int)*11);
}

void participacion::setEstadisticasPartido(int g, int gc, double pos) {
    entrarF(sizeof(int)*2 + sizeof(double));

    goles = g;
    golesContra = gc;
    posesion = pos;

    salirF(sizeof(int)*2 + sizeof(double));
}


void participacion::setEstadisticasJugador(int idx, int goles, int amarillas, int rojas,
                                           int faltas, int minutos) {
    entrarF(sizeof(int)*6);

    if (idx >= 0 && idx < 11) {
        iteraciones++;

        golesJugador[idx] = goles;
        tarjetasAmarillas[idx] = amarillas;
        tarjetasRojas[idx] = rojas;
        faltasJugador[idx] = faltas;
        minutosJugador[idx] = minutos;
    }

    salirF(sizeof(int)*6);
}

void participacion::actualizarHistoricos() {
    entrarF(sizeof(int));

    for (int i = 0; i < 11; i++) {
        iteraciones++;
        if (convocados[i] != nullptr) {
            convocados[i]->actualizarEstadisticas(
                golesJugador[i], 0, minutosJugador[i],
                tarjetasAmarillas[i], tarjetasRojas[i], faltasJugador[i]
                );
        }
    }

    salirF(sizeof(int));
}

void participacion::mostrar() const {
    entrarF(sizeof(int));

    cout << "  " << equipoPtr->getpais() << " - Goles: " << goles
         << " | Goles Contra: " << golesContra
         << " | Posesion: " << posesion << "%\n";
    cout << "  Jugadores convocados:\n";
    for (int i = 0; i < 11; i++) {
        iteraciones++;

        if (convocados[i] != nullptr) {
        cout<< "    #" << convocados[i]->getnumeroCamiseta()
            << " | G:" << golesJugador[i]
            << " | A:" << tarjetasAmarillas[i]
            << " | R:" << tarjetasRojas[i]
            << " | F:" << faltasJugador[i]
            << " | M:" << minutosJugador[i] << "\n";
        }
    }

    salirF(sizeof(int));
}


// Getters

int participacion::getGoles() const {return goles; }
int participacion::getGolesContra() const { return golesContra; }
double participacion::getPosesion() const { return posesion; }
equipo* participacion::getEquipo() const { return equipoPtr; }
jugador* participacion::getJugadorConvocado(int idx) const { return convocados[idx]; }
int participacion::getGolesJugador(int idx) const { return golesJugador[idx]; }
int participacion::getTarjetasAmarillas(int idx) const { return tarjetasAmarillas[idx]; }
int participacion::getTarjetasRojas(int idx) const { return tarjetasRojas[idx]; }
int participacion::getFaltasJugador(int idx) const { return faltasJugador[idx]; }






