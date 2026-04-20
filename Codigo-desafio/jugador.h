#ifndef JUGADOR_H
#define JUGADOR_H


class jugador{
private:
    char* nombre;
    char* apellido;
    int numeroCamiseta;

    // estadisticas
    int partidosJugados;
    int goles;
    int minutosTotales;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltasAcumuladas;

    // metodos auxiliares
    int longitudCadena(const char* cadena);
    char* copiarCadena(const char* origen);
    void liberarMemoria();

public:

    // constructores y Destructor

    jugador();

    jugador(const char* nom, const char* ap, int num);

    jugador(const jugador& otro);

    ~jugador();

    // operador

    jugador& operator=(const jugador& otro);



    // metodos funcionales

    void actualizarEstadisticas(int golesPartido, int asistenciasPartido,
                                int minutosPartido, int amarillasPartido,
                                int rojasPartido, int faltasPartido);

    void anotaGol();
    void agregarAsistencia();
    void recibirTarjetaAmarilla();
    void recibirTarjetaRoja();
    void agregarFalta();
    void agregarMinutos(int minutos);



    // Getters

    const char* getNombre() const;
    const char* getApellido() const;
    int getnumeroCamiseta() const;
    int getPartidosJugados() const;
    int getGoles() const;
    int getMinutosTotales() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltasAcumuladas() const;

    // Setters

    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setNumeroCamiseta(int num);
    void setGoles(int goles);
    void setAsistencias(int asistencias);
    void setMinutosTotales(int m);
    void setTarjetasAmarillas(int ta);
    void setTarjetasRojas(int tr);
    void setFaltasAcumuladas(int f);

    void mostrar() const;



};

#endif // JUGADOR_H
