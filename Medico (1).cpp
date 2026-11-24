//
// Created by eddya on 22/11/2026.
//

#include "Medico.h"
#include <iostream>

using namespace std;

Medico::Medico(string nombreMedico) {
    nombre = nombreMedico;
    topePila = nullptr;
    primeraJornada = nullptr;
    ultimaJornada = nullptr;
    totalJornadas = 0;
    turnosActuales = 0;
}

void Medico::sumarTurno() {
    turnosActuales = turnosActuales + 1;
}

void Medico::guardarJornada() {
    NodoJornada* nuevaJornada = new NodoJornada();
    nuevaJornada->turnos = turnosActuales;
    nuevaJornada->siguiente = nullptr;
    if (primeraJornada == nullptr) {
        primeraJornada = nuevaJornada;
    } else {
        ultimaJornada->siguiente = nuevaJornada;
    }
    ultimaJornada = nuevaJornada;
    totalJornadas = totalJornadas + 1;
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
        cout << " - Cédula: " << nodoActual->paciente->getCedula();
        cout << " - Gravedad: " << nodoActual->paciente->getGravedad() << endl;

        nodoActual = nodoActual->siguiente;
        numero = numero + 1;
    }
}

void Medico::mostrarJornadas() {
    cout << "Medico: " << nombre << endl;
    cout << "Jornadas cerradas: " << totalJornadas << endl;

    NodoJornada* jornadaActual = primeraJornada;
    int numero = 1;
    while (jornadaActual != nullptr) {
        cout << "Jornada " << numero << ": " << jornadaActual->turnos << " turnos" << endl;
        jornadaActual = jornadaActual->siguiente;
        numero = numero + 1;
    }

    if (turnosActuales > 0) {
        cout << "Jornada en curso: " << turnosActuales << " turnos" << endl;
    }
}
