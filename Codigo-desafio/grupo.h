#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"
#include "partido.h"

class grupo
{

private:
    char letra;
    equipo* equipos;
    int numEquipos;

    partido* partidos;
    int numPartidos;

public:

///Contructor
    grupo(char letra);

///Destructor
    ~grupo();

    void agregarEquipo(equipo e);
    void generarPartidos();
    void simularPartidos();

    void calcularTabla();
    void ordenarTabla();

    void mostrarGrupo;
};

#endif // GRUPO_H
