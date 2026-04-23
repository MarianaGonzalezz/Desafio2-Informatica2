#include "equipo.h"
#include <iostream>
#include <string>


using namespace std;

equipo::equipo()
    :ranking(0), pais(""),federacion(""), confederacion(""),
    golesFavor(0), golesEnContra(0), partidosGanados(0), partidosEmpatados(0),
    partidosPerdidos(0), tarjetasAmarillas(0), tarjetasRojas(0), faltas(0),
    cantidad(0) {
    jugadores = new jugador[26];

}

equipo::equipo(int rank, const string& p, const string& fed, const string& conf,
               int gf, int gc, int pg, int pe, int pp)
    : ranking(rank), pais(p), federacion(fed), confederacion(conf),
    golesFavor(gf), golesEnContra(gc), partidosGanados(pg), partidosEmpatados(pe),
    partidosPerdidos(pp), tarjetasAmarillas(0), tarjetasRojas(0), faltas(0),
    cantidad(0) {
    jugadores = new jugador[26];
}

equipo::equipo(const equipo& otro)
    : ranking(otro.ranking), pais(otro.pais), federacion(otro.federacion),
    confederacion(otro.confederacion), golesFavor(otro.golesFavor),
    golesEnContra(otro.golesEnContra), partidosGanados(otro.partidosGanados),
    partidosEmpatados(otro.partidosEmpatados), partidosPerdidos(otro.partidosPerdidos),
    tarjetasAmarillas(otro.tarjetasAmarillas), tarjetasRojas(otro.tarjetasRojas),
    faltas(otro.faltas), cantidad(otro.cantidad) {

    jugadores = new jugador[26];
    for (int i = 0; i < 26; i++) {
        jugadores[i] = otro.jugadores[i];
    }
}

equipo::~equipo(){
    delete[] jugadores;
}

equipo& equipo::operator=(const equipo& otro) {
    if (this == &otro) return *this;

    ranking = otro.ranking;
    pais = otro.pais;
    federacion = otro.federacion;
    confederacion = otro.confederacion;
    golesFavor = otro.golesFavor;
    golesEnContra = otro.golesEnContra;
    partidosGanados = otro.partidosGanados;
    partidosEmpatados = otro.partidosEmpatados;
    partidosPerdidos = otro.partidosPerdidos;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
    cantidad = otro.cantidad;

    for (int i = 0; i < 26; i++) {
        jugadores[i] = otro.jugadores[i];
    }

    return *this;
}

void equipo::actualizarEstadisticas(int gf, int gc, int amarillas, int rojas,
                                    int faltasPartido, bool ganado, bool empatado, bool perdido) {

    golesFavor+=gf;
    golesEnContra+=gc;
    tarjetasAmarillas+=amarillas;
    tarjetasRojas=rojas;
    faltas+=faltasPartido;

    if(ganado) partidosGanados++;
    if (empatado) partidosEmpatados++;
    if (perdido) partidosPerdidos++;

}

void equipo::repartirGolesHistoricos(){
    for(int i=0;i<26;i++){
        int numero=i+1;
        string nombre= "nombre"+ to_string(numero);
        string apellido = "apellido" + to_string(numero);
        jugadores[cantidad++] = jugador(nombre, apellido, numero);
    }

    int base=golesFavor/26;
    int extra=golesFavor%26;

    for(int i=0; i<26;i++){
        int golesjugador=base;
        if(i<extra) golesjugador++;
        if(golesjugador>0){
            jugadores[i].setGoles(golesjugador);
        }
    }
}


void equipo::mostrar() const {
    cout << "\n========================================\n";
    cout << "PAIS: " << pais << "\n";
    cout << "Federacion: " << federacion << " | Confederacion: " << confederacion << "\n";
    cout << "Ranking: " << ranking << "\n";
    cout << "Goles: " << golesFavor << " a favor - " << golesEnContra << " en contra\n";
    cout << "Tarjetas: " << tarjetasAmarillas << " amarillas - " << tarjetasRojas << " rojas\n";
    cout << "Faltas: " << faltas << "\n";
    cout << "Partidos: G=" << partidosGanados << " E=" << partidosEmpatados
         << " P=" << partidosPerdidos << "\n";
    cout << "Jugadores (" << cantidad << "/26):\n";
    for (int i = 0; i < cantidad; i++) {
        jugadores[i].mostrar();
    }
    cout << "========================================\n";
}



jugador& equipo::getJugador(int idx){
    return jugadores[idx];

}


// getters

int equipo::getRanking() const { return ranking; }
string equipo::getpais() const { return pais; }
string equipo::getFederacion() const { return federacion; }
string equipo::getConfederacion() const { return confederacion; }
int equipo::getGolesAFavor() const { return golesFavor; }
int equipo::getGolesEnContra() const { return golesEnContra; }
int equipo::getPartidosGanados() const { return partidosGanados; }
int equipo::getPartidosEmpatados() const { return partidosEmpatados; }
int equipo::getPartidosPerdidos() const { return partidosPerdidos; }
int equipo::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int equipo::getTarjetasRojas() const { return tarjetasRojas; }
int equipo::getFaltas() const { return faltas; }
int equipo::getCantidad() const { return cantidad; }








