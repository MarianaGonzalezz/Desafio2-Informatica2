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
    cout<<"\n*********** MEDICION ***********\n";
    cout<<"ITERACIONES: "<< iteraciones<<endl;
    cout<<"MEMORIA TOTAL (bytes): "<< (memoriaHeap + memoriaStack)<<endl;
    cout<<"- Heap: "<<memoriaHeap<<endl;
    cout<<"- Stack: "<<memoriaStack<<endl;
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

        equipos[i].repartirGolesHistoricos();
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

    getline(miArchivo, linea); // título
    getline(miArchivo, linea);

    while(getline(miArchivo, linea)){
        iteraciones++;

        if(linea.empty()) continue;

        if (linea.find(';') == string::npos) continue;

        if(n==capacidad){

            int capacidadAnterior = capacidad;
            capacidad *=2;

            equipo* nuevo = new equipo [capacidad];
            sumarMemoriaHeap(sizeof(equipo) * capacidad);

            for (int i = 0; i < n; i++){
                iteraciones++;
                nuevo [i] = lista [i];
            }

            delete [] lista;
            restarMemoriaHeap(sizeof(equipo) * (capacidadAnterior));

            lista = nuevo;
        }

        stringstream ss (linea);

        string rankingStr, pais, dt, fed, conf;
        string gfStr,gcStr, pgStr,peStr,ppStr;

        getline(ss,rankingStr, ';');
        getline(ss,pais, ';');
        getline(ss,dt, ';');
        getline(ss, fed, ';');
        getline(ss,conf, ';');
        getline(ss,gfStr, ';');
        getline(ss,gcStr, ';');
        getline(ss, pgStr, ';');
        getline(ss, peStr, ';');
        getline(ss, ppStr, ';');

        try {
        int ranking = stoi(rankingStr);
        int gf = stoi(gfStr);
        int gc = stoi(gcStr);

        //cout << rankingStr << " | "<< pais << " | "<< dt << " | "<< fed << " | "<< conf << " | "<< gfStr << " | "<< gcStr << endl;

        lista[n] = equipo(ranking, pais, fed, conf, gf, gc,
            0, // partidos ganados
            0, // empatados
            0  // perdidos
            );

        lista[n].actualizarEstadisticas(gf, gc, 0, 0, 0, false, false, false);

        n++;
    } catch (exception& e) {
    cout << "ERROR en linea: " << linea << endl;
    cout << "rankingStr: [" << rankingStr << "]\n";
    cout << "gfStr: [" << gfStr << "]\n";
    cout << "gcStr: [" << gcStr << "]\n";
        }

    }

    miArchivo.close();

    salirF(sizeof(string) + sizeof(string)*4 + sizeof(stringstream) + sizeof(int)*3);

    return lista;
}