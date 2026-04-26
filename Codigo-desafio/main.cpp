#include <iostream>
#include "utils.h"
#include "torneo.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    int n;
    equipo* equipos = cargarEquipos("selecciones_clasificadas_mundial.csv", n);
    //cout<<"equipos cargados: "<<n<<endl;

    if(n != 48){
        cout<<"ERROR: se esperan 48 equipos. Se cargaron: "<<n<<endl;
        return 0;
    }

    torneo t;
    t.setEquipos(equipos, n);

    t.iniciar();

    cout<<"\n========================== Guardar Historial ==========================\n";
    resetearMedidor();
    guardarHistorialEquipos(equipos, n);
    mostrarMedidor();

    delete [] equipos;
    restarMemoriaHeap(sizeof(equipo) * n);

    return 0;
}
