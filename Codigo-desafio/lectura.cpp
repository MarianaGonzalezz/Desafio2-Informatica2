#include "lectura.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

equipo* cargarEquipos(string archivo, int &n){

    ifstream miArchivo(archivo);

    if (!miArchivo.is_open()){
        cout<< "Error abriendo el archivo\";
        n = 0;
        return nullptr;
    }

    int capacidad = 10;
    equipo* lista = new equipo [capacidad];
    n = 0;

    string linea;

    while(getlinea(file, linea)){
        if(linea.empty()) continue;

        if(n==capacidad){
            capacidad *=2;

            equipo* nuevo = new equipo [capacidad];
            for (int i = 0; i < n; i++){
                nuevo [i] = lista [i];
            }
            delete [] lista;
            lista = nuevo;
        }

        stringstream ss (linea);
        string nombre, pais, conf, dato;
        int ranking, gf, gc;

        getline(ss,nombre, ',');
        getline(ss,pais, ',');
        getline(ss,conf, ',');
        getline(ss,dato, ','); ranking = stoi(dato);
        getline(ss,dato, ','); gf = stoi (dato);
        getline(ss,dato, ','); gc = stoi (dato);

        lista[n] = equipo (nombre, pais, ranking, conf);
        lista[n].actualizarGoles(gf,gc);

        n++;
    }
    miArchivo.close();
    return lista;
}