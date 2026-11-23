//
// Created by saria on 23/11/2026.
//

#ifndef PROYECTO_FINAL_URGENCIAS_NODOCAMA_H
#define PROYECTO_FINAL_URGENCIAS_NODOCAMA_H

#include <string>
#include "Paciente.h"

class NodoCama {
private:
    int numeroCama;
    std::string estadoCama;
    Paciente* pacienteActual;
    int turnosRestantesTratamiento;
    NodoCama* prev;
    NodoCama* next;
public:
    NodoCama(int numero);

    int getNumeroCama() const;
    std::string getEstadoCama() const;
    Paciente* getPacienteActual() const;
    int getTurnosRestantes() const;
    NodoCama* getPrev() const;
    NodoCama* getNext() const;
    bool estaVacia() const;
    bool tratamientoTerminado() const;

    void setPrev(NodoCama* prev);
    void setNext(NodoCama* next);

    bool ocupar(Paciente* pacienteActual, int turnos);
    bool tratar();
    bool liberar();
};
#endif //PROYECTO_FINAL_URGENCIAS_NODOCAMA_H
