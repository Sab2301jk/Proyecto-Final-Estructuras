//
// Created by eddya on 22/11/2026.
//

#ifndef PROYECTO_FINAL_URGENCIAS_SIMULADOR_H
#define PROYECTO_FINAL_URGENCIAS_SIMULADOR_H

#include <queue>
#include <string>
#include <vector>
#include "Paciente.h"
#include "NodoCama.h"
#include "Medico.h"
#include "CamaCorredor.h"
#include "HistorialHash.h"

using namespace std;

struct Prioridad {
    bool operator()(Paciente* pacienteA, Paciente* pacienteB) const {
        if (pacienteA->getGravedad() != pacienteB->getGravedad()) {
            return pacienteA->getGravedad() > pacienteB->getGravedad();
        }
        return pacienteA->getOrdenLlegada() > pacienteB->getOrdenLlegada();
    }
};

class Simulador {
private:
    vector<Medico*> medicos;
    Medico* medicoActual;
    CamaCorredor corredor;
    HistorialHash historial;
    priority_queue<Paciente*, vector<Paciente*>, Prioridad> colaTriage;
    int turnoGlobal;
    int turnosJornada;
    int topeJornada;
    bool jornadaActiva;
    int totalRecibidos;
    int totalAltas;
    int totalPerdidos;
    double sumaMinutosEspera;
    Medico* buscarMedico(string nombreMedico);

public:
    Simulador(string nombreMedico, int topeTurnos);

    void ingresarPaciente(string cedula, string nombre, int gravedad, string condicion);
    void pasarTurno();
    void finalizarJornada();
    void cambiarMedico(string nombreNuevoMedico);

    bool retrocederCama();
    bool avanzarCama();
    bool pasarPacienteACama();
    bool tratarPacienteActual();
    bool darDeAltaEnCama();
    void verUltimasAltas();
    void consultarPaciente(string cedula);
    void mostrarEstado();
    void mostrarReporte();
    void consultarJornadas(string nombreMedico);
    void resumenPerdidos();
    bool jornadaTerminada();
};

#endif //PROYECTO_FINAL_URGENCIAS_SIMULADOR_H
