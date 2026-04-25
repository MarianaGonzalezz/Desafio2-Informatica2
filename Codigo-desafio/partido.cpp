#include "partido.h"
#include <iostream>
#include <ctime>
#include<cstdlib>

using namespace std;

const double ALFA=0.4;
const double BETA = 0.6;
const double GAMMA = 1.35;
const double PROB_AMARILLA1 = 0.06;
const double PROB_AMARILLA2 = 0.0115;
const double PROB_FALTA1 = 0.13;
const double PROB_FALTA2 = 0.0275;
const double PROB_FALTA3 = 0.007;
const double PROB_GOL = 0.04;

partido::partido()
    : fecha("20/06/2026"), hora(""), sede(""), prorroga(false),
    participacion1(nullptr), participacion2(nullptr) {
    arbitros[0] = arbitros[1] = arbitros[2] = 0;
}


partido::partido(const string& f, const string& h, const string& s, int arb[3])
    : fecha(f), hora(h), sede(s), prorroga(false),
    participacion1(nullptr), participacion2(nullptr) {
    arbitros[0] = arb[0];
    arbitros[1] = arb[1];
    arbitros[2] = arb[2];
}


partido::~partido() {
    delete participacion1;
    delete participacion2;
}


double partido::calcularGolesEsperados(equipo* eqA, equipo* eqB) const {
    double gfa = (double)eqA->getGolesAFavor() / 26.0;
    double gcb = (double)eqB->getGolesEnContra() / 26.0;
    return ALFA * gfa + BETA * gcb + GAMMA;
}


double partido::calcularPosesion(int r1, int r2) const {
    double pos = (double)(32 - r1) / ((32 - r1) + (32 - r2)) * 100;
    if (pos < 30) pos = 30;
    if (pos > 70) pos = 70;
    return pos;
}



void partido::seleccionarConvocados(int indices1[11], int indices2[11]) const {
    const int TOTAL_JUGADORES = 26;
    bool usado1[TOTAL_JUGADORES] = {false};
    bool usado2[TOTAL_JUGADORES] = {false};

    for (int i = 0; i < 11; i++) {
        int id1, id2;
        do { id1 = rand() % TOTAL_JUGADORES; } while (usado1[id1]);
        usado1[id1] = true;
        indices1[i] = id1;

        do { id2 = rand() % TOTAL_JUGADORES; } while (usado2[id2]);
        usado2[id2] = true;
        indices2[i] = id2;
    }
}


void partido::crearParticipaciones(equipo* eq1, equipo* eq2) {
    participacion1 = new participacion(eq1, this);
    participacion2 = new participacion(eq2, this);
}


void partido::simular() {
    srand((unsigned)time(nullptr));

    // 1. Calcular goles esperados
    int goles1 = (int)calcularGolesEsperados(participacion1->getEquipo(),
                                              participacion2->getEquipo());
    int goles2 = (int)calcularGolesEsperados(participacion2->getEquipo(),
                                              participacion1->getEquipo());

    if (goles1 < 0) goles1 = 0;
    if (goles2 < 0) goles2 = 0;

    // 2. Calcular posesión
    double pos1 = calcularPosesion(participacion1->getEquipo()->getRanking(),
                                   participacion2->getEquipo()->getRanking());
    double pos2 = 100.0 - pos1;

    participacion1->setEstadisticasPartido(goles1, goles2, pos1);
    participacion2->setEstadisticasPartido(goles2, goles1, pos2);

    // 3. Seleccionar convocados
    int idx1[11], idx2[11];
    seleccionarConvocados(idx1, idx2);

    participacion1->asignarConvocados(idx1);
    participacion2->asignarConvocados(idx2);

   // simular tarjetas
    for (int i = 0; i < 11; i++) {
        int amar1 = 0, roj1 = 0, falt1 = 0;
        int amar2 = 0, roj2 = 0, falt2 = 0;

        double r = (double)rand() / RAND_MAX;
        if (r < PROB_FALTA1) {
            falt1++;
            r = (double)rand() / RAND_MAX;
            if (r < PROB_FALTA2) {
                falt1++;
                r = (double)rand() / RAND_MAX;
                if (r < PROB_FALTA3) falt1++;
            }
        }
        r = (double)rand() / RAND_MAX;
        if (r < PROB_AMARILLA1) {
            amar1++;
            r = (double)rand() / RAND_MAX;
            if (r < PROB_AMARILLA2) {
                amar1++;
                roj1 = 1;
            }
        }

        r = (double)rand() / RAND_MAX;
        if (r < PROB_FALTA1) {
            falt2++;
            r = (double)rand() / RAND_MAX;
            if (r < PROB_FALTA2) {
                falt2++;
                r = (double)rand() / RAND_MAX;
                if (r < PROB_FALTA3) falt2++;
            }
        }
        r = (double)rand() / RAND_MAX;
        if (r < PROB_AMARILLA1) {
            amar2++;
            r = (double)rand() / RAND_MAX;
            if (r < PROB_AMARILLA2) {
                amar2++;
                roj2 = 1;
            }
        }

        participacion1->setEstadisticasJugador(i, 0, amar1, roj1, falt1, 90);
        participacion2->setEstadisticasJugador(i, 0, amar2, roj2, falt2, 90);
    }

    // simular goles

    // Para equipo 1
    if (goles1 > 0) {
        for (int g = 0; g < goles1; g++) {
            int jugador = rand() % 11;
            int actual = participacion1->getGolesJugador(jugador);
            participacion1->setEstadisticasJugador(jugador, actual + 1,
                                                   participacion1->getTarjetasAmarillas(jugador),
                                                   participacion1->getTarjetasRojas(jugador),
                                                   participacion1->getFaltasJugador(jugador), 90);
        }
    }

    // Para equipo 2
    if (goles2 > 0) {
        for (int g = 0; g < goles2; g++) {
            int jugador = rand() % 11;
            int actual = participacion2->getGolesJugador(jugador);
            participacion2->setEstadisticasJugador(jugador, actual + 1,
                                                   participacion2->getTarjetasAmarillas(jugador),
                                                   participacion2->getTarjetasRojas(jugador),
                                                   participacion2->getFaltasJugador(jugador), 90);
        }
    }

    int golesFinales1 = 0, golesFinales2 = 0;
    for (int i = 0; i < 11; i++) {
        golesFinales1 += participacion1->getGolesJugador(i);
        golesFinales2 += participacion2->getGolesJugador(i);
    }

    participacion1->setEstadisticasPartido(golesFinales1, golesFinales2, pos1);
    participacion2->setEstadisticasPartido(golesFinales2, golesFinales1, pos2);
}



void partido::actualizarHistoricos() {
    participacion1->actualizarHistoricos();
    participacion2->actualizarHistoricos();

    equipo* eq1 = participacion1->getEquipo();
    equipo* eq2 = participacion2->getEquipo();
    int g1 = participacion1->getGoles();
    int g2 = participacion2->getGoles();

    int a1 = 0, r1 = 0, f1 = 0, a2 = 0, r2 = 0, f2 = 0;
    for (int i = 0; i < 11; i++) {
        a1 += participacion1->getTarjetasAmarillas(i);
        r1 += participacion1->getTarjetasRojas(i);
        f1 += participacion1->getFaltasJugador(i);
        a2 += participacion2->getTarjetasAmarillas(i);
        r2 += participacion2->getTarjetasRojas(i);
        f2 += participacion2->getFaltasJugador(i);
    }

    eq1->actualizarEstadisticasEquipo(g1, g2, a1, r1, f1, g1 > g2, g1 == g2, g1 < g2);
    eq2->actualizarEstadisticasEquipo(g2, g1, a2, r2, f2, g2 > g1, g2 == g1, g2 < g1);
}

void partido::mostrarResultado() const {
    cout << "\n========================================\n";
    cout << "FECHA: " << fecha;
    if (!hora.empty()) cout << " - HORA: " << hora;
    cout << "\n";
    cout << "SEDE: " << sede << "\n";
    cout << "ARBITROS: " << arbitros[0] << ", " << arbitros[1] << ", " << arbitros[2] << "\n";
    cout << "========================================\n";

    participacion1->mostrar();
    cout << "\n";
    participacion2->mostrar();

    cout << "\nRESULTADO: " << participacion1->getGoles() << " - " << participacion2->getGoles();
    if (prorroga) cout << " (prórroga)";
    cout << "\n";

    equipo* ganador = getGanador();
    if (ganador) {
        cout << "GANADOR: " << ganador->getPais() << "\n";
    } else {
        cout << "EMPATE\n";
    }
    cout << "========================================\n";
}

void partido::mostrarGoleadores() const {
    cout << "\n--- GOLEADORES DEL PARTIDO ---\n";
    cout << participacion1->getEquipo()->getPais() << ":\n";
    for (int i = 0; i < 11; i++) {
        if (participacion1->getGolesJugador(i) > 0) {
            jugador* j = participacion1->getJugadorConvocado(i);
            cout << "  #" << j->getNumeroCamiseta() << " - "
                 << participacion1->getGolesJugador(i) << " gol(es)\n";
        }
    }
    cout << participacion2->getEquipo()->getPais() << ":\n";
    for (int i = 0; i < 11; i++) {
        if (participacion2->getGolesJugador(i) > 0) {
            jugador* j = participacion2->getJugadorConvocado(i);
            cout << "  #" << j->getNumeroCamiseta() << " - "
                 << participacion2->getGolesJugador(i) << " gol(es)\n";
        }
    }
}

// Getters

equipo* partido::getGanador() const {
    int g1 = participacion1->getGoles();
    int g2 = participacion2->getGoles();
    if (g1 > g2) return participacion1->getEquipo();
    if (g2 > g1) return participacion2->getEquipo();
    return nullptr;
}

participacion* partido::getParticipacion1() const { return participacion1; }
participacion* partido::getParticipacion2() const { return participacion2; }
bool partido::getProrroga() const { return prorroga; }







