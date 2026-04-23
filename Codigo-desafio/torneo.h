#ifndef TORNEO_H
#define TORNEO_H

#include "grupo.h"
#include "eliminatorias.h"
#include "equipo.h"


class torneo
{
private:
    grupo* grupos;
    int numGrupos;

    equipo* equipos;
    int numEquipos;

    eliminatorias* fases;
    int numFases;

    void crearBombos(equipo** bombos);
    bool validarGrupo(grupo& g, equipo& e);
    equipo* obtenerMejoresTerceros();

public:

    torneo(); ///constructor

    ~torneo(); ///destructor

    void setEquipos(equipo* lista, int n); ///Setter

    void crearGrupos();
    void simularFaseGrupos();
    void prepararEliminatorias();
    void simularEliminatorias();

    void iniciar();

    void mostrarEstadisticas();
};

#endif // TORNEO_H
