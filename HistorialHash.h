//
// Created by Ivan David Fernandez Salguero on 21/11/26.
//

#ifndef PROYECTO_FINAL_URGENCIAS_HISTORIALHASH_H
#define PROYECTO_FINAL_URGENCIAS_HISTORIALHASH_H

#include <iostream>
#include <string>
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

// Cada cubeta es un nodo de una lista enlazada que guarda el inicio de su cadena de colisiones
class NodoCubeta {
public:
    NodoHash* cabeza;
    NodoCubeta* siguiente;

    NodoCubeta() {
        this->cabeza = nullptr;
        this->siguiente = nullptr;
    }
};

class HistorialHash {
private:
    NodoCubeta* primeraCubeta;
    int numCubetas;

    unsigned long funcionHash(string cedula) const;
    NodoCubeta* obtenerCubeta(unsigned long indice) const;

public:
    HistorialHash(int numCubetas);
    ~HistorialHash();

    Paciente* buscar(string cedula) const;

    void guardarOActualizar(Paciente p);

    void consultarPorCedula(string cedula) const;

    void auditarPerdidos();
};
#endif //PROYECTO_FINAL_URGENCIAS_HISTORIALHASH_H
