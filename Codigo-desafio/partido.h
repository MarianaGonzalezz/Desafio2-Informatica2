#ifndef PARTIDO_H
#define PARTIDO_H


#include <string>

using namespace std;

class equipo;
class participacion;

class partido{
private:
    string fecha;
    string hora;
    string sede;
    int arbitros[3];
    participacion* participacion1;
    participacion* participacion2;
    bool prorroga;

    // Metodos privados

    double calcularGolesEsperados(equipo* eqA, equipo* eqB) const;
    double calcularPosesion(int r1, int r2) const;
    void seleccionarConvocados(int indices1[11], int indices2[11]) const;


public:
    partido();
    partido(const string& fecha, const string& hora, const string& sede, int arb[3]);
    ~partido();

    void crearParticipaciones(equipo* eq1, equipo* eq2);
    void simular();
    void actualizarHistoricos();
    void mostrarResultado() const;
    void mostrarGoleadores() const;

    equipo* getGanador() const;
    participacion* getParticipacion1() const;
    participacion* getParticipacion2() const;
    bool getProrroga() const;

};

#endif // PARTIDO_H
