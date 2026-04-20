#include "jugador.h"
#include <iostream>
#include <cstring>

using namespace std;


int jugador::longitudCadena(const char*cadena){
    int longitud=0;
    while(cadena[longitud] != '\0'){
        longitud++;
    }
    return longitud;
}


char* jugador::copiarCadena(const char* origen){
    if(origen==nullptr) return nullptr;

    int longitud=longitudCadena(origen);
    char*copia= new char[longitud+1];

    for(int i=0; i<longitud; i++){
        copia[i]= origen[i];
    }
    copia[longitud]= '\0';

    return copia;

}

void jugador::liberarMemoria(){
    delete[] nombre;
    delete[] apellido;
}



