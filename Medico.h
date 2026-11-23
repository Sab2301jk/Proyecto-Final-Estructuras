//
// Created by eddya on 22/11/2026.
//

#ifndef PROYECTO_FINAL_URGENCIAS_MEDICO_H
#define PROYECTO_FINAL_URGENCIAS_MEDICO_H

#include <string>
#include "Paciente.h"

using namespace std;

struct NodoPila {
    Paciente* paciente;
    NodoPila* siguiente;
};

struct NodoJornada {
    int turnos;
    NodoJornada* siguiente;
};

class Medico {
private:
    NodoPila* topePila;
    NodoJornada* primeraJornada;
    NodoJornada* ultimaJornada;
    int totalJornadas;
    int turnosActuales;

public:
    string nombre;

    Medico(string nombreMedico);

    void sumarTurno();
    void guardarJornada();
    void registrarAlta(Paciente* paciente);
    void mostrarUltimosAtendidos();
    void mostrarJornadas();
};

#endif //PROYECTO_FINAL_URGENCIAS_MEDICO_H
