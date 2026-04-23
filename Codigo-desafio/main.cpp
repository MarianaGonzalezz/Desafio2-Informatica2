#include <iostream>
#include "lectura.h"
#include "torneo.h"

using namespace std;

int main()
{
    int n;
    equipo* equipos = cargarEquipos("selecciones_clasificadas_mundial.csv", n);

    torneo t;
    t.setEquipos(equipos, n);
    t.iniciar();
    return 0;
}
