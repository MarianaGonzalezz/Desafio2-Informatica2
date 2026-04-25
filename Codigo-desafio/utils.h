#ifndef UTILS_H
#define UTILS_H

#include "equipo.h"
#include <string>

using namespace std;

//Medidor iteraciones
extern unsigned long long iteraciones;

//Medidor memoria
extern unsigned long long memoriaHeap;
extern unsigned long long memoriaStack;


void resetearMedidor();
void mostrarMedidor();

void sumarMemoriaHeap(unsigned long long bytes);
void restarMemoriaHeap(unsigned long long bytes);

void entrarF(unsigned long long bytes);
void salirF(unsigned long long bytes);

//Lectura
equipo* cargarEquipos(string archivo, int &n);
//Escritura
void guardarHistorialEquipos(equipo* equipos, int n);

#endif // UTILS_H
