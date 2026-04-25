#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <fstream>
#include <string>


class equipo {
private:
    int ranking;
    string pais;
    string federacion;
    string confederacion;

    // estadisticas

    int golesFavor;
    int golesEnContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

    jugador*jugadores;
    int cantidad;

public:

    // constructores y destructores

    equipo();
    equipo(int rank, const string& pais, const string& fed, const string& conf,
           int gf, int gc, int pg, int pe, int pp);
    equipo(const equipo& otro);
    ~equipo();

    // operador de asignacion

    equipo& operator=(const equipo& otro);

    // metodos funcionales

    void actualizarEstadisticas(int gf, int gc, int amarillas, int rojas,
                                int faltasPartido, bool ganado, bool empatado, bool perdido);
    void repartirGolesHistoricos();

    void mostrar() const;

    void guardarHistorial(std::ofstream& archivo) const;

    jugador* getJugadores() const { return jugadores; }
    jugador& getJugador(int idx);


    // Getters

    int getRanking() const;
    string getpais() const;
    string getFederacion() const;
    string getConfederacion() const;
    int getGolesAFavor() const;
    int getGolesEnContra() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;
    int getCantidad() const;


};

#endif // EQUIPO_H
