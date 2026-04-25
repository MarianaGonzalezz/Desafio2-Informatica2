#include <iostream>
#include "utils.h"
#include "torneo.h"

using namespace std;

int main()
{
    int n;
    equipo* equipos = cargarEquipos("selecciones_clasificadas_mundial.csv", n);

    torneo t;
    t.setEquipos(equipos, n);

    resetearMedidor();
    t.crearGrupos();
    mostrarMedidor();

    resetearMedidor();
    t.simularFaseGrupos();
    mostrarMedidor();

    resetearMedidor();
    t.prepararEliminatorias();
    mostrarMedidor();

    resetearMedidor();
    t.simularEliminatorias();
    mostrarMedidor();

    guardarHistorialEquipos(equipos, n);

    delete [] equipos;
    restarMemoriaHeap(sizeof(equipo) * n);

    return 0;
}
