#include "jugador.h"
#include <iostream>
#include <cstring>

using namespace std;

jugador::jugador()
    : nombre("Sin nombre"), apellido("Sin apellido"), numeroCamiseta(0),
    partidosJugados(0), goles(0), minutosTotales(0),
    asistencias(0), tarjetasAmarillas(0), tarjetasRojas(0), faltasAcumuladas(0) {}


jugador::jugador(string nom, string ap, int num)
    : nombre(nom), apellido(ap), numeroCamiseta(num),
    partidosJugados(0), goles(0), minutosTotales(0),
    asistencias(0), tarjetasAmarillas(0), tarjetasRojas(0),
    faltasAcumuladas(0) {}


jugador::jugador(const jugador& otro)
    : nombre(otro.nombre), apellido(otro.apellido), numeroCamiseta(otro.numeroCamiseta),
    partidosJugados(otro.partidosJugados), goles(otro.goles),
    minutosTotales(otro.minutosTotales), asistencias(otro.asistencias),
    tarjetasAmarillas(otro.tarjetasAmarillas), tarjetasRojas(otro.tarjetasRojas),
    faltasAcumuladas(otro.faltasAcumuladas) {}


jugador::~jugador(){}


jugador& jugador::operator=(const jugador& otro){
    if (this != &otro){
        nombre = otro.nombre;
        apellido = otro.apellido;
        numeroCamiseta = otro.numeroCamiseta;
        partidosJugados = otro.partidosJugados;
        goles = otro.goles;
        minutosTotales = otro.minutosTotales;
        asistencias = otro.asistencias;
        tarjetasAmarillas = otro.tarjetasAmarillas;
        tarjetasRojas = otro.tarjetasRojas;
        faltasAcumuladas = otro.faltasAcumuladas;
    }

    return *this;
}

void jugador::actualizarEstadisticas(int golesPartido, int asistenciasPartido,
                                     int minutosPartido, int amarillasPartido,
                                     int rojasPartido, int faltasPartido){

    partidosJugados++;
    goles+=golesPartido;
    asistencias+=asistenciasPartido;
    minutosTotales+=minutosPartido;
    tarjetasAmarillas+=amarillasPartido;
    tarjetasRojas+=rojasPartido;
    faltasAcumuladas+=faltasPartido;

}

// Getters

string jugador::getNombre() const { return nombre; }
string jugador::getApellido() const { return apellido; }
int jugador::getnumeroCamiseta() const { return numeroCamiseta; }
int jugador::getPartidosJugados() const { return partidosJugados; }
int jugador::getGoles() const { return goles; }
int jugador::getMinutosTotales() const { return minutosTotales; }
int jugador::getAsistencias() const { return asistencias; }
int jugador::getAmarillas() const { return tarjetasAmarillas; }
int jugador::getRojas() const { return tarjetasRojas; }
int jugador::getFaltasAcumuladas() const { return faltasAcumuladas; }

// Setters

void jugador::setNombre(string nom){
    nombre=nom;
}

void jugador::setApellido(string ap){
    apellido=ap;
}

void jugador::setNumeroCamiseta(int num){
    numeroCamiseta=num;
}

void jugador::setPartidosJugados(int pj){
    partidosJugados=pj;
}

void jugador::setGoles(int g){
    goles=g;
}

void jugador::setMinutosTotales(int m){
    minutosTotales=m;
}

void jugador::setAsistencias(int a){
    asistencias=a;
}

void jugador::setAmarillas(int ta){
    tarjetasAmarillas=ta;
}

void jugador::setRojas(int tr){
    tarjetasRojas=tr;
}

void jugador::setFaltasAcumuladas(int f){
    faltasAcumuladas=f;
}


void jugador::mostrar() const{
    cout << "Jugador: " << nombre << " " << apellido
         << " (#" << numeroCamiseta << ")\n";
    cout << "  Partidos: " << partidosJugados << " | Goles: " << goles
         << " | Asistencias: " << asistencias << "\n";
    cout << "  Minutos: " << minutosTotales << " | Amarillas: " << tarjetasAmarillas
         << " | Rojas: " << tarjetasRojas << " | Faltas: " << faltasAcumuladas << "\n";
}






