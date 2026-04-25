#include "participacion.h"
#include "partido.h"
#include <iostream>

using namespace std;

// Cosntructores y Destructores

participacion::participacion()
    : equipo(nullptr), partido(nullptr), goles(0), golesContra(0), posesion(0) {
    for (int i = 0; i < 11; i++) {
        convocados[i] = nullptr;
        golesJugador[i] = 0;
        tarjetasAmarillas[i] = 0;
        tarjetasRojas[i] = 0;
        faltasJugador[i] = 0;
        minutosJugador[i] = 90;
    }
}

participacion::participacion(equipo* eq, partido* p)
    : equipo(eq), partido(p), goles(0), golesContra(0), posesion(0) {
    for (int i = 0; i < 11; i++) {
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
    for (int i = 0; i < 11; i++) {
        if (indices[i] >= 0 && indices[i] < 26) {
            convocados[i] = equipo->getJugadores() + indices[i];
        }
    }
}

void participacion::setEstadisticasPartido(int g, int gc, double pos) {
    goles = g;
    golesContra = gc;
    posesion = pos;
}


void participacion::setEstadisticasJugador(int idx, int goles, int amarillas, int rojas,
                                           int faltas, int minutos) {
    if (idx >= 0 && idx < 11) {
        golesJugador[idx] = goles;
        tarjetasAmarillas[idx] = amarillas;
        tarjetasRojas[idx] = rojas;
        faltasJugador[idx] = faltas;
        minutosJugador[idx] = minutos;
    }
}

void participacion::actualizarHistoricos() {
    for (int i = 0; i < 11; i++) {
        if (convocados[i] != nullptr) {
            convocados[i]->actualizarEstadisticas(
                golesJugador[i], 0, minutosJugador[i],
                tarjetasAmarillas[i], tarjetasRojas[i], faltasJugador[i]
                );
        }
    }
}

void participacion::mostrar() const {
    cout << "  " << equipo->getPais() << " - Goles: " << goles
         << " | Goles Contra: " << golesContra
         << " | Posesion: " << posesion << "%\n";
    cout << "  Jugadores convocados:\n";
    for (int i = 0; i < 11; i++) {
        if (convocados[i] != nullptr) {
        cout<< "    #" << convocados[i]->getNumeroCamiseta()
            << " | G:" << golesJugador[i]
            << " | A:" << tarjetasAmarillas[i]
            << " | R:" << tarjetasRojas[i]
            << " | F:" << faltasJugador[i]
            << " | M:" << minutosJugador[i] << "\n";
        }
    }
}


// Getters

int participacion::getGoles() const {return goles; }
int participacion::getGolesContra() const { return golesContra; }
double participacion::getPosesion() const { return posesion; }
equipo* participacion::getEquipo() const { return equipo; }
jugador* participacion::getJugadorConvocado(int idx) const { return convocados[idx]; }
int participacion::getGolesJugador(int idx) const { return golesJugador[idx]; }
int participacion::getTarjetasAmarillas(int idx) const { return tarjetasAmarillas[idx]; }
int participacion::getTarjetasRojas(int idx) const { return tarjetasRojas[idx]; }
int participacion::getFaltasJugador(int idx) const { return faltasJugador[idx]; }






