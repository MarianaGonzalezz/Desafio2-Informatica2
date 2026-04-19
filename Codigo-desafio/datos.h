#ifndef DATOS_H
#define DATOS_H

#include <string>
#include "equipo.h"

using namespace std;

class datos
{
private:

    string archivoEquipos;
    equipo* equipos;
    int numEquipos;

public:

    datos(string nombreArchivo); //Constructor
    ~datos(); //destructor

//Getters
    equipo* getEquipos();
    int getNumEquipos();
    string getArchivo();

//Setters
    void setArchivo(string nombreArchivo);

    void cargarEquipos();
    void generarJugadores();

    void guardarJugadores();
    void cargarJugadores();

    void actualizarDatos();

};

#endif // DATOS_H
