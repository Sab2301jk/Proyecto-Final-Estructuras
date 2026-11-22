
#ifndef PROYECTOFINALED_HISTORIALHASH_H
#define PROYECTOFINALED_HISTORIALHASH_H

#include <iostream>
#include <string>
#include <vector>
#include "Paciente.h"

using std::string;

class NodoHash {
public:
    Paciente dato;
    NodoHash* next;

    NodoHash(Paciente p) {
        this->dato = p;
        this->next= nullptr;
    }
};
class HistorialHash {

private:

    std::vector<NodoHash*>  cubetas;

    int cantidad;

    unsigned long funcionHash(string cedula) const;

    public:

    HistorialHash(int numCubetas);
    ~HistorialHash();

    Paciente* buscar(string cedula) const;

    void guardarOActualizar(Paciente p);


    void consultarPorCedula(string cedula) const;

    void auditarPerdidos();

    int totalPacientes() const;

};


#endif //PROYECTOFINALED_HISTORIALHASH_H
