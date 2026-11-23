//
// Created by saria on 23/11/2026.
//

#include "NodoCama.h"

NodoCama::NodoCama(int numero) {
    this->numeroCama = numero;
    this->estadoCama = "Vacia";
    this->pacienteActual = nullptr;
    this->turnosRestantesTratamiento = 0;
    this->prev = nullptr;
    this->next = nullptr;
}
int NodoCama::getNumeroCama() const {
    return this->numeroCama;
}
std::string NodoCama::getEstadoCama() const {
    return this->estadoCama;
}

Paciente* NodoCama::getPacienteActual() const {
    return this->pacienteActual;
}

int NodoCama::getTurnosRestantes() const {
    return this->turnosRestantesTratamiento;
}

NodoCama* NodoCama::getPrev() const {
    return this->prev;
}

NodoCama* NodoCama::getNext() const {
    return this->next;
}

bool NodoCama::estaVacia() const {
    if (this->estadoCama == "Vacia") {
        return true;
    }else {
        return false;
    }
}
bool NodoCama::tratamientoTerminado() const {
    if (this->estadoCama == "Ocupada" && this->turnosRestantesTratamiento == 0) {
        return true;
    }else {
        return false;
    }
}
void NodoCama::setPrev(NodoCama* prev) {
    this->prev = prev;
}
void NodoCama::setNext(NodoCama* next) {
    this->next = next;
}
bool NodoCama::ocupar(Paciente* paciente, int turnos) {
    if (!this->estaVacia() || paciente == nullptr) {
        return false;
    }
    this->pacienteActual = paciente;
    this->turnosRestantesTratamiento = turnos;
    this->estadoCama = "Ocupada";
    return true;
}
bool NodoCama::tratar() {
    if (this->estadoCama != "Ocupada" || this->turnosRestantesTratamiento == 0) {
        return false;
    }
    this->turnosRestantesTratamiento--;
    return true;
}
bool NodoCama::liberar() {
    if (this->estadoCama != "Ocupada") {
        return false;
    }
    this->pacienteActual = nullptr;
    this->turnosRestantesTratamiento = 0;
    this->estadoCama = "Vacia";
    return true;
}
