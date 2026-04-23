#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;


class jugador{
private:
    string nombre;
    string apellido;
    int numeroCamiseta;

    // estadisticas
    int partidosJugados;
    int goles;
    int minutosTotales;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltasAcumuladas;



public:

    // constructores y Destructor

    jugador();

    jugador(string nom, string ap, int num);

    jugador(const jugador& otro);

    ~jugador();

    // operador

    jugador& operator=(const jugador& otro);



    // metodos funcionales

    void actualizarEstadisticas(int golesPartido, int asistenciasPartido,
                                int minutosPartido, int amarillasPartido,
                                int rojasPartido, int faltasPartido);



    // Getters

    string getNombre() const;
    string getApellido() const;
    int getnumeroCamiseta() const;
    int getPartidosJugados() const;
    int getGoles() const;
    int getMinutosTotales() const;
    int getAsistencias() const;
    int getAmarillas() const;
    int getRojas() const;
    int getFaltasAcumuladas() const;

    // Setters

    void setNombre(string nom);
    void setApellido(string ap);
    void setNumeroCamiseta(int num);
    void setPartidosJugados(int pj);
    void setGoles(int goles);
    void setAsistencias(int asistencias);
    void setMinutosTotales(int m);
    void setAmarillas(int ta);
    void setRojas(int tr);
    void setFaltasAcumuladas(int f);

    void mostrar() const;



};

#endif // JUGADOR_H
