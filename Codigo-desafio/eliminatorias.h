#ifndef ELIMINATORIAS_H
#define ELIMINATORIAS_H

#include "partido.h"
#include "equipo.h"
#include <string>

class eliminatorias
{
private:
    partido* partidos;
    int numPartidos;

    equipo* clasificados;
    int numEquipos;

    string fase;

public:

    eliminatorias(string nombreFase); //Constructor
    ~eliminatorias(); //Destructor

    void setEquipos(equipo* equipos, int n); //Setters

    void crearCruces();
    void simularFase();
    void generarSiguienteFase (eliminatorias& siguiente);

    void resolverEmpate(partido& p);

    void mostrarFase();
    equipo* obtenerGanadores();

};

#endif // ELIMINATORIAS_H
