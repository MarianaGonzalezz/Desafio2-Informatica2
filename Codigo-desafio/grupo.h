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

    void agregarEquipo(const equipo& e);
    void generarPartidos();
    void simularPartidos();

    void ordenarTabla();

    equipo* obtenerClasificados();
    void mostrarGrupo();
};

#endif // GRUPO_H
