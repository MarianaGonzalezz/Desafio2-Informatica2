#ifndef PARTICIPACION_H
#define PARTICIPACION_H

#include "equipo.h"
#include "jugador.h"

class partido;

class participacion{
private:
    equipo* equipo;
    partido* partido;
    int goles;
    int golesContra;
    double posesion;

    // jugadores convocados

    jugador* convocados[11];
    int golesJugador[11];
    int tarjetasAmarillas[11];
    int tarjetasRojas[11];
    int faltasJugador[11];
    int minutosJugador[11];

public:

    // Constructores y Destructores

    participacion();
    participacion(equipo*eq, partido*p);
    ~participacion();

    void asignarConvocados(int indices[11]);
    void setEstadisticasPartido(int g, int gc, double pos);
    void setEstadisticasJugador(int idx, int goles, int amarillas, int rojas, int faltas, int minutos);
    void actualizarHistoricos();
    void mostrar() const;


    // Getters

    int getGoles() const;
    int getGolesContra() const;
    double getPosesion() const;
    equipo* getEquipo() const;
    jugador* getJugadorConvocado(int idx) const;
    int getGolesJugador(int idx) const;
    int getTarjetasAmarillas(int idx) const;
    int getTarjetasRojas(int idx) const;
    int getFaltasJugador(int idx) const;

};

#endif // PARTICIPACION_H
