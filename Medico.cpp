//
// Created by eddya on 22/11/2026.
//

#include "Medico.h"
#include <iostream>

using namespace std;

Medico::Medico(string nombreMedico) {
    nombre = nombreMedico;
    topePila = nullptr;
    turnosActuales = 0;
}

void Medico::sumarTurno() {
    turnosActuales = turnosActuales + 1;
}

void Medico::guardarJornada() {
    jornadas.push_back(turnosActuales);
    turnosActuales = 0;
    topePila = nullptr;
}

void Medico::registrarAlta(Paciente* paciente) {
    NodoPila* nuevoNodo = new NodoPila();
    nuevoNodo->paciente = paciente;
    nuevoNodo->siguiente = topePila;
    topePila = nuevoNodo;
}

void Medico::mostrarUltimosAtendidos() {
    if (topePila == nullptr) {
        cout << "No hay pacientes dados de alta en este turno." << endl;
        return;
    }

    cout << "Ultimos dados de alta (" << nombre << "):" << endl;
    NodoPila* nodoActual = topePila;
    int numero = 1;

    while (nodoActual != nullptr) {
        cout << numero << ". " << nodoActual->paciente->getNombre();
        cout << " - CC: " << nodoActual->paciente->getCedula();
        cout << " - Gravedad: " << nodoActual->paciente->getGravedad() << endl;

        nodoActual = nodoActual->siguiente;
        numero = numero + 1;
    }
}

void Medico::mostrarJornadas() {
    int totalJornadas = jornadas.size();

    cout << "Medico: " << nombre << endl;
    cout << "Jornadas cerradas: " << totalJornadas << endl;

    for (int i = 0; i < totalJornadas; i++) {
        cout << "Jornada " << (i + 1) << ": " << jornadas[i] << " turnos" << endl;
    }

    if (turnosActuales > 0) {
        cout << "Jornada en curso: " << turnosActuales << " turnos" << endl;
    }
}
