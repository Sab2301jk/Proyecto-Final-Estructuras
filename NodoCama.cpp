
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
std::string NodoCama::getEstadoCama() {
    return this->estadoCama;
}

Paciente* NodoCama::getPacienteActual() {
    return this->pacienteActual;
}

int NodoCama::getTurnosRestantes() {
    return turnosRestantesTratamiento;
}

NodoCama* NodoCama::getPrev() {
    return this->prev;
}

NodoCama* NodoCama::getNext() {
    return this->next;
}

bool NodoCama::estaVacia() {
    if (this->estadoCama == "Vacia") {
        return true;
    }else {
        return false;
    }
}
bool NodoCama::tratamientoTerminado() {
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
    if (!this->estaVacia() || paciente == nullptr || turnos <=0) {   //si la cama no esta vacia o no hay paciente no se puede ocupar
        return false;                                                // tampoco los turnos deben ser menores que 0
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