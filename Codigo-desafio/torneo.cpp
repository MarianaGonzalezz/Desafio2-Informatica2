#include "torneo.h"
#include "grupo.h"
#include "utils.h"
#include <iostream>

using namespace std;

///constructor
torneo::torneo(){

    grupos = nullptr;
    numGrupos = 0;
    equiposPorGrupo = 0;

    equipos = nullptr;
    numEquipos = 0;

    fases = new eliminatorias [4];
    numFases = 4;
    sumarMemoriaHeap(sizeof(eliminatorias) * 4);

}


///destructor
torneo::~torneo() {
    delete [] grupos;
    restarMemoriaHeap(sizeof(grupo) * numGrupos);

    delete [] fases;
    restarMemoriaHeap(sizeof(eliminatorias) * numFases);
}

void torneo::setEquipos(equipo *lista, int n){
    equipos = lista;
    numEquipos = n;
}

void torneo::crearBombos(equipo** bombos){

    entrarF(sizeof(int)*3 + sizeof(equipo));

    if (numEquipos != 48){
        cout<<"ERROR: se esperan 48 equipos"<<endl;
        return;
    }
    for(int i=0; i < numEquipos -1;i++){
        iteraciones++;

        for(int j = 0; j<numEquipos - i- 1; j++){
            iteraciones++;

            if(equipos[j].getRanking()>equipos[j+1].getRanking()){
                iteraciones++;

                equipo temp = equipos [j];
                equipos[j]= equipos[j+1];
                equipos[j+1] = temp;
            }
        }
    }

    for (int i = 0; i<4; i++){
        bombos[i] = new equipo[12];
        sumarMemoriaHeap(sizeof(equipo) * 12);

    }
    int k = 0;
    for (int i= 0; i<4; i++){
        for(int j = 0; j<12; j++){
            bombos[i][j] = equipos[k++];
        }
    }
    salirF(sizeof(int)*3 + sizeof(equipo));
}

bool torneo::validarGrupo(grupo& g, equipo& e){

    entrarF(sizeof(int) + sizeof(equipo*));

    int uefa = 0;
    equipo* eqs = g.getEquipos();

    for(int i= 0; i<g.getNumEquipos(); i++){
        if(eqs[i].getConfederacion()== e.getConfederacion()){

            if(e.getConfederacion()=="UEFA"){
                uefa++;
                if(uefa>=2) return false;
            } else{
                return false;
            }
        }
    }
    salirF(sizeof(int) + sizeof(equipo*));
    return true;
}



void torneo::crearGrupos(){

    if(numEquipos<4){
        cout<<"No hay suficientes equipos.\n";
        return;
    }

    entrarF(sizeof(int) * 2 + sizeof(equipo*));

    equipo* bombos [4];
    crearBombos(bombos);

    numGrupos = numEquipos / 4;
    if(numEquipos % 4 != 0) numGrupos++;

    grupos = new grupo[numGrupos];

    sumarMemoriaHeap(sizeof(grupo)*numGrupos);

    char letra = 'A';

    for(int i = 0; i<numGrupos;i++){
        grupos[i] = grupo(letra++);
    }

    int* disponibles = new int[4]{12,12,12,12};


    for(int b= 0; b<4;b++){
        iteraciones++;
        for(int g = 0; g<numGrupos;g++){
            iteraciones++;

            bool asignado = false;

            if (disponibles[b] <= 0) break;

            int intentos = 0;

            while(!asignado && intentos < 100){

                if(disponibles[b]<=0) break;

                intentos++;
                iteraciones++;

                int r = rand()%disponibles[b];
                equipo candidato = bombos[b][r];

                if(validarGrupo(grupos[g], candidato)){

                    grupos[g].agregarEquipo(candidato);

                    bombos[b][r] = bombos[b][disponibles[b] -1];
                    disponibles[b]--;

                    asignado = true;
                }
            }
            //if(!asignado){
              //  cout<<"no se pudo asignar al grupo\n";
            //}
        }
    }
    delete[] disponibles;

    for (int i = 0; i<4; i++){
        delete[] bombos [i];
        restarMemoriaHeap(sizeof(equipo) * 12);
    }
    salirF(sizeof(int) * 2 + sizeof(equipo*));
}

void torneo::simularFaseGrupos(){

    entrarF(sizeof(int));

    for (int i = 0; i<numGrupos; i++){
        grupos[i].generarPartidos();
        grupos[i].simularPartidos();
        grupos[i].ordenarTabla();

        grupos[i].mostrarGrupo();
    }
    salirF(sizeof(int));

}

equipo* torneo::obtenerMejoresTerceros(){

    entrarF(sizeof(int)*2 + sizeof(equipo*));

    equipo* terceros = new equipo [12];
    sumarMemoriaHeap(sizeof(equipo) * 12);


    for (int i = 0; i<12;i++){
        iteraciones++;

        equipo* tabla = grupos[i].obtenerClasificados();
        terceros[i] = tabla[2];


        delete[] tabla;
        restarMemoriaHeap(sizeof(equipo) * 3);

    }
    for (int i = 0; i<11;i++){
        iteraciones++;
        for(int j = 0; j<11-i;j++){
            iteraciones++;
            if(terceros[j].getPuntos()<terceros[j+1].getPuntos()){
                swap(terceros[j],terceros[j+1]);
            }
        }
    }
    /// top 8
    equipo* mejores = new equipo[8];
    sumarMemoriaHeap(sizeof(equipo) * 8);

    for (int i = 0; i<8;i++){
        iteraciones++;
        mejores[i] = terceros[i];
    }

    delete[] terceros;
    restarMemoriaHeap(sizeof(equipo) * 12);

    salirF(sizeof(int)*2 + sizeof(equipo*));
    return mejores;
}

void torneo::prepararEliminatorias(){

    entrarF(sizeof(int) + sizeof(equipo*));

    equipo* clasificados = new equipo[32];
    sumarMemoriaHeap(sizeof(equipo) * 32);

    int aux = 0;

    // 1° y 2°
    for(int i =0; i<numGrupos;i++){
        iteraciones++;
        equipo* tabla = grupos[i].obtenerClasificados();

        clasificados[aux++] = tabla[0];
        clasificados[aux++] = tabla[1];

        delete [] tabla;
        restarMemoriaHeap(sizeof(equipo) * 3);
    }

    equipo* mejores = obtenerMejoresTerceros();

    for (int i = 0; i<8; i++){
        iteraciones++;
        clasificados[aux++] = mejores[i];
    }

    delete[] mejores;
    restarMemoriaHeap(sizeof(equipo) * 8);

    fases[0] = eliminatorias("\n=== R16 ===\n");
    fases[0].setEquipos(clasificados, 32);
    fases[0].crearCruces();

    salirF(sizeof(int) + sizeof(equipo*));
}

void torneo::simularEliminatorias(){

    entrarF(sizeof(int));

    //R16
    fases[0].simularFase();

    //QF
    fases[1] = eliminatorias("\n=== QF ===\n");
    fases[0].generarSiguienteFase(fases[1]);
    fases[1].simularFase();

    //SF
    fases[2] = eliminatorias("\n=== SF ===\n");
    fases[1].generarSiguienteFase(fases[2]);
    fases[2].simularFase();

    //Final
    fases[3] = eliminatorias ("\n=== FINAL ===\n");
    fases[2].generarSiguienteFase(fases[3]);
    fases[3].simularFase();

    salirF(sizeof(int));
}


void torneo::mostrarEstadisticas(){

    entrarF(sizeof(int) + sizeof(equipo*) + sizeof(string));

    cout<<"\n=== ESTADISTICAS DEL TORNEO ===\n";

    //Campeon
    equipo* ganador = fases[3].obtenerGanadores();
    cout << "CAMPEON: "<<ganador[0].getpais()<<endl;

    delete[] ganador;
    restarMemoriaHeap(sizeof(equipo) * fases[3].getNumPartidos());

    //Subcampeon
    equipo* finalistas = fases [3].getEquipos();
    cout<<"SUBCAMPEON: "<<finalistas[1].getpais()<<endl;

    //Equipo con mas goles
    int maxGoles = -1;
    string mejorEquipo;

    for(int i = 0;i<numEquipos; i++){
        iteraciones++;
        if(equipos[i].getGolesAFavor()> maxGoles){
            iteraciones++;
            maxGoles = equipos[i].getGolesAFavor();
            mejorEquipo = equipos[i].getpais();
        }
    }
    cout<<"EQUIPO CON MAS GOLES: "<<mejorEquipo<<" ("<<maxGoles<<": goles\n";
    cout<<"================================\n";

    salirF(sizeof(int) + sizeof(equipo*) + sizeof(string));
}

void torneo::iniciar(){

    cout<<"\n========================== Crear Grupos ==========================\n";
    resetearMedidor();
    crearGrupos();
    mostrarMedidor();

    cout<<"\n========================== Simular Fase Grupos ==========================\n";
    resetearMedidor();
    simularFaseGrupos();
    mostrarMedidor();

    cout<<"\n========================== Preparar Eliminatorias ==========================\n";
    resetearMedidor();
    prepararEliminatorias();
    mostrarMedidor();

    cout<<"\n========================== Simular Eliminatorias ==========================\n";
    resetearMedidor();
    simularEliminatorias();
    mostrarMedidor();

}