#include "torneo.h"
#include <iostream>

using namespace std;

///constructor
torneo::torneo(){
    grupos = new grupo[12];
    numGrupos = 12;

    equipos = nullptr;
    numEquipos = 0;

    fases = new eliminatorias [4];
    numFases = 4;

}


///destructor
torneo::~torneo() {
    delete [] grupos;
    delete [] fases;
}

void torneo::setEquipos(equipo *lista, int n){
    equipos = lista;
    numEquipos = n;
}

void torneo::crearBombos(equipo** bombos){

    for(int i=0; i < numEquipos -1;i++){
        for(int j = 0; j<numEquipos - i- 1; j++){
            if(equipos[j].getRanking()>equipos[j+1].getRanking()){
                equipo temp = equipos [j];
                equipos[j]= equipos[j+1];
                equipos[j+1] = temp;
            }
        }
    }

    for (int i = 0; i<4; i++){
        bombos[i] = new equipo[12];
    }
    int k = 0;
    for (int i= 0; i<4; i++){
        for(int j = 0; j<12; j++){
            bombos[i][j] = equipos[k++];
        }
    }
}

bool torneo::validarGrupo(grupo& g, equipo& e){
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
    return true;
}



void torneo::crearGrupos(){
    equipo* bombos [4];
    crearBombos(bombos);

    char letra = 'A';

    for(int i = 0; i<12;i++){
        grupos[i] = grupo(letra++);
    }

    for(int b= 0; b<4;b++){

        int disponibles = 12;
        for(int g = 0; g<12;g++){
            bool asignado = false;

            while(!asignado){
                int r = rand()%disponibles;
                equipo candidato = bombos[b][r];

                if(validoGrupo(grupos[g], candidato)){
                    grupos[g].agregarEquipo(candidato);

                    bombos[b][r] = bombos[b][disponibles -1];
                    disponibles--;

                    asignado = true;
                }
            }
        }
    }
}

void torneo::simularFaseGrupos(){

    for (int i = 0; i<numGrupos; i++){
        grupos[i].generarPartidos();
        grupos[i].simularPartidos();
        grupos[i].calcularTabla();
        grupos[i].ordenarTabla();

        grupos[i].mostrarGrupo();
    }

}

equipo* torneo::obtenerMejoresTerceros(){

    equipo* terceros = new equipo [12];

    for (int i = 0; i<12;i++){
        equipo* tabla = grupos[i].obtenerClasificados();
        terceros[i] = tabla[2];

        delete[] tabla;
    }
    for (int i = 0; i<11;i++){
        for(int j = 0; j<11-i;j++){
            if(terceros[j].getPuntos()<terceros[j+1].getPuntos()){
                swap(terceros[j],terceros[j+1]);
            }
        }
    }
    /// top 8
    equipo* mejores = new equipo[8];
    for (int i = 0; i<8;i++){
        mejores[i] = terceros[i];
    }
    return mejores;
}

void torneo::prepararEliminatorias(){

    equipo* clasificados = new equipo[32];
    int aux = 0;

    // 1° y 2°
    for(int i =0; i<12;i++){
        equipo* tabla = grupos[i].obtenerClasificados();

        clasificados[aux++] = tabla[0];
        clasificados[aux++] = tabla[1];

        delete [] tabla;
    }

    equipo* mejores = obtenerMejoresTerceros();

    for (int i = 0; i<8; i++){
        clasificados[aux++] = mejores[i];
    }

    delete[] mejores;

    fases[0] = eliminatorias("R16");
    fases[0].setEquipos(clasificados, 32);
    fases[0].crearCruces();
}

void torneo::simularEliminatorias(){

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
}


void torneo::mostrarEstadisticas(){

    cout<<"\n=== ESTADISTICAS DEL TORNEO ===\n";

    //Campeon
    equipo* ganador = fases[3].obtenerGanadores();
    cout << "CAMPEON: "<<ganador[0].getNombre()<<endl;

    //Subcampeon
    equipo* finalistas = fases [3].getEquipos();
    cout<<"SUBCAMPEON: "<<finalistas[1].getNombre()<<endl;

    //Equipo con mas goles
    int maxGoles = -1;
    string mejorEquipo;

    for(int i = 0;i<numEquipos; i++){
        if(equipos[i].getGF()> maxGoles){
            maxGoles = equipos[i].getGF();
            mejorEquipo = equipos[i].getNombre();
        }
    }
    cout<<"EQUIPO CON MAS GOLES: "<<mejorEquipo<<" ("<<maxGoles<<": goles\n";
    cout<<"================================\n";
}

void torneo::iniciar(){

    cout<<"=== INICIO DEL TORNEO ===\n";

    crearGrupos();
    simularFaseGrupos();

    prepararEliminatorias();
    simularEliminatorias();

    cout<<"=== FIN DEL TORNEO ===";
}