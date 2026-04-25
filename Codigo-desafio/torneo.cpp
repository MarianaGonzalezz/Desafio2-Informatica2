#include "torneo.h"
#include <iostream>

using namespace std;

///constructor
torneo::torneo(){
    grupos = new grupo[12];
    numGrupos = 12;
    sumarMemoriaHeap(sizeof(grupo) * 12);

    equipos = nullptr;
    numEquipos = 0;

    fases = new eliminatorias [4];
    numFases = 4;
    sumarMemoriaHeap(sizeof(eliminatorias) * 4);

}


///destructor
torneo::~torneo() {
    delete [] grupos;
    memoria -= sizeof(grupo) * numGrupos;
    delete [] fases;
    memoria -= sizeof(eliminatorias) * numFases;
}

void torneo::setEquipos(equipo *lista, int n){
    equipos = lista;
    numEquipos = n;
}

void torneo::crearBombos(equipo** bombos){

    entrarF(sizeof(int)*3 + sizeof(equipo));

    for(int i=0; i < numEquipos -1;i++){
        iteraciones++;

        for(int j = 0; j<numEquipos - i- 1; j++){
            iteraciones++;

            if(equipos[j].getRanking()>equipos[j+1].getRanking()){
                iteraciones++;

                equipo temp = equipos [j];
                memoria += sizeof(equipo);
                equipos[j]= equipos[j+1];
                equipos[j+1] = temp;
            }
        }
    }

    for (int i = 0; i<4; i++){
        bombos[i] = new equipo[12];
        memoria += sizeof(equipo) * 12;

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

    entrarF(sizeof(char) + sizeof(int)*3 + sizeof(equipo*));

    equipo* bombos [4];
    crearBombos(bombos);

    char letra = 'A';

    for(int i = 0; i<12;i++){
        grupos[i] = grupo(letra++);
    }

    for(int b= 0; b<4;b++){
        iteraciones++;

        int disponibles = 12;
        for(int g = 0; g<12;g++){
            iteraciones++;

            bool asignado = false;

            while(!asignado){
                iteraciones++;

                int r = rand()%disponibles;
                equipo candidato = bombos[b][r];

                if(validarGrupo(grupos[g], candidato)){
                    grupos[g].agregarEquipo(candidato);

                    bombos[b][r] = bombos[b][disponibles -1];
                    disponibles--;

                    asignado = true;
                }
            }
        }
    }
    for (int i = 0; i<4; i++){
        delete[] bombos [i];
        memoria -= sizeof(equipo) * 12;
    }
    salirF(sizeof(char) + sizeof(int)*3 + sizeof(equipo*));
}

void torneo::simularFaseGrupos(){

    entrarF(sizeof(int));

    for (int i = 0; i<numGrupos; i++){
        grupos[i].generarPartidos();
        grupos[i].simularPartidos();
        grupos[i].calcularTabla();
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
    for(int i =0; i<12;i++){
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

    fases[0] = eliminatorias("R16");
    fases[0].setEquipos(clasificados, 32);
    fases[0].crearCruces();

    salirF(sizeof(int) + sizeof(equipo*));
}

void torneo::simularEliminatorias(){

    entrarF(sizeof(int));

    //R16
    fases[0].simularFase();

    //QF
    fases[1] = eliminatorias("QF");
    fases[0].generarSiguienteFase(fases[1]);
    fases[1].simularFase();

    //SF
    fases[2] = eliminatorias("SF");
    fases[1].generarSiguienteFase(fases[2]);
    fases[2].simularFase();

    //Final
    fases[3] = eliminatorias ("FINAL");
    fases[2].generarSiguienteFase(fases[3]);
    fases[3].simularFase();

    salirF(sizeof(int));
}


void torneo::mostrarEstadisticas(){

    entrarF(sizeof(int) + sizeof(equipo*) + sizeof(string));

    cout<<"\n=== ESTADISTICAS DEL TORNEO ===\n";

    //Campeon
    equipo* ganador = fases[3].obtenerGanadores();
    cout << "CAMPEON: "<<ganador[0].getNombre()<<endl;

    delete[] ganador;
    restarMemoriaHeap(sizeof(equipo) * fases[3].getNumPartidos());

    //Subcampeon
    equipo* finalistas = fases [3].getEquipos();
    cout<<"SUBCAMPEON: "<<finalistas[1].getNombre()<<endl;

    //Equipo con mas goles
    int maxGoles = -1;
    string mejorEquipo;

    for(int i = 0;i<numEquipos; i++){
        iteraciones++;
        if(equipos[i].getGF()> maxGoles){
            iteraciones++;
            maxGoles = equipos[i].getGF();
            mejorEquipo = equipos[i].getNombre();
        }
    }
    cout<<"EQUIPO CON MAS GOLES: "<<mejorEquipo<<" ("<<maxGoles<<": goles\n";
    cout<<"================================\n";

    salirF(sizeof(int) + sizeof(equipo*) + sizeof(string));
}

void torneo::iniciar(){

    cout<<"=== INICIO DEL TORNEO ===\n";

    crearGrupos();
    simularFaseGrupos();

    prepararEliminatorias();
    simularEliminatorias();

    cout<<"=== FIN DEL TORNEO ===";
}