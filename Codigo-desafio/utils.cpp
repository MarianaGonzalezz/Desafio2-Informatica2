#include "utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


unsigned long long iteraciones = 0;
unsigned long long memoriaHeap = 0;
unsigned long long memoriaStack = 0;


void resetearMedidor(){
    iteraciones = 0;
    memoriaHeap = 0;
    memoriaStack = 0;
}

void mostrarMedidor(){
    cout<<"=== MEDICION ===\n";
    cout<<"ITERACIONES: "<< iteraciones<<endl;
    cout<<"MEMORIA TOTAL (bytes): "<< (memoriaHeap + memoriaStack)<<endl;
    cout<<" - Heap: "<<memoriaHeap<<endl;
    cout<<" - Stack: "<<memoriaStack<<endl;
}

void sumarMemoriaHeap(unsigned long long bytes){
    memoriaHeap += bytes;
}

void restarMemoriaHeap(unsigned long long bytes){
    memoriaHeap -= bytes;
}

void entrarF(unsigned long long bytes){
    memoriaStack += bytes;
}

void salirF(unsigned long long bytes){
    memoriaStack -= bytes;
}

void guardarHistorialEquipos(equipo* equipos, int n){

    entrarF(sizeof(ofstream) + sizeof(int));

    ofstream archivo("historial_jugadores.csv");

    if(!archivo.is_open()){
        cout<<"Error creando archivo\n";
        return;
    }

    archivo<<"equipo,jugador,goles,partidos\n";

    for(int i = 0; i<n; i++){
        iteraciones++;

        equipos[i].guardarHistorial(archivo);
    }
    archivo.close();
    salirF(sizeof(ofstream) + sizeof(int));
}

equipo* cargarEquipos(string archivo, int &n){

    entrarF(sizeof(string) + sizeof(string)*4 + sizeof(stringstream) + sizeof(int)*3);

    ifstream miArchivo(archivo);

    if (!miArchivo.is_open()){
        cout<< "Error abriendo el archivo\n";
        n = 0;
        salirF(sizeof(string) + sizeof(string)*4 + sizeof(stringstream) + sizeof(int)*3);
        return nullptr;
    }

    int capacidad = 10;
    equipo* lista = new equipo [capacidad];
    sumarMemoriaHeap(sizeof(equipo) * capacidad);
    n = 0;

    string linea;

    while(getline(miArchivo, linea)){
        iteraciones++;
        if(linea.empty()) continue;

        if(n==capacidad){
            capacidad *=2;

            equipo* nuevo = new equipo [capacidad];
            sumarMemoriaHeap(sizeof(equipo) * capacidad);

            for (int i = 0; i < n; i++){
                iteraciones++;
                nuevo [i] = lista [i];
            }

            restarMemoriaHeap(sizeof(equipo) * (capacidad/2));
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

    salirF(sizeof(string) + sizeof(string)*4 + sizeof(stringstream) + sizeof(int)*3);

    return lista;
}