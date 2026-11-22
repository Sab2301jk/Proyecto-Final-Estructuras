#ifndef NODOCAMA_H
#define NODOCAMA_H
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
    std::string getEstadoCama();
    Paciente* getPacienteActual();
    int getTurnosRestantes();
    NodoCama* getPrev();
    NodoCama* getNext();
    bool estaVacia();
    bool tratamientoTerminado();

    void setPrev(NodoCama* prev);
    void setNext(NodoCama* next);

    bool ocupar(Paciente* pacienteActual, int turnos);
    bool tratar();
    bool liberar();
};


#endif //NODOCAMA_H