#include "datos.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


//Contructor
datos::datos(string nombreArchivo) {
    archivoEquipos = nombreArchivo;
    equipos = nullptr;
    numEquipos = 0;
}

//Destructor
datos::~datos(){
    delete [] equipos;
}

//Getters
equipo* datos::getEquipos(){
    return equipos;
}

int datos::getNumEquipos(){
    return numEquipos;
}

string datos::getArchivo(){
    return archivoEquipos;
}

//Setters
void datos::setArchivo(string nombreArchivo){
    archivoEquipos = nombreArchivo;
}

void datos::cargarEquipos(){

    ifstream archivo (archivoEquipos);

    if (!archivo.is_open()){
        cout<<"Error abriendo el archivo\n";
        return;
    }
    string linea;

    int capacidad = 10;
    equipo* equiposTemp = new equipo[capacidad];

    numEquipos = 0;

    while (getline(archivo, linea)){
        if (linea.empty()) continue;

        if(numEquipos == capacidad){
            capacidad *= 2;

            equipo* nuevo = new equipo[capacidad];

            for (int i = 0; i < numEquipos; i++){
                nuevo [i] = equiposTemp[i];
            }
            delete [] equiposTemp;
            equiposTemp = nuevo;
        }

        stringstream ss (linea);
        string nombre, pais, conf, dato;
        int ranking = 0, gf = 0, gc = 0;

        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, conf, ',');
        getline(ss, dato, ','); ranking = stoi(dato);
        getline(ss, dato, ','); gf = stoi(dato);
        getline(ss, dato, ','); gc = stoi (dato);

        equiposTemp[numEquipos] = equipo(nombre, pais, ranking, conf);
        equiposTemp[numEquipos].actualizarGoles(gf,gc);

        numEquipos++
    }
    archivo.close();

    equipos = new equipo[numEquipos];
    for (int i = 0; i<numEquipos;i++){
        equipos[i] = equiposTemp[i];
    }
    delete [] equiposTemp;

}

void datos::generarJugadores(){

    for (int i=0; i<numEquipos; i++){
        int golesEquipo = equipos[i].getGolesFavor();

        int base = golesEquipo/26;
        int extra = golesEquipo % 26;

        for (int j = 0; j<26; j++){
            string nombre = "nombre" + to_string(j+1);
            string apellido = "apellido" + to_string(j+1);

            jugador jugador (nombre, apellido, j+1);

            int goles = base;
            if (j<extra) goles++;

            for (int k = 0; k<goles; k++){
                jugador.anotarGol();
            }
            for (int k = 0; k < goles; k++){
                jugador.anotarGol();
            }
            equipos [i].agregarJugador(jugador);
        }
    }
}

void datos::guardarJugadores(){

}

void datos::cargarJugadores(){

}

void datos::actualizarDatos(){

}



