//
// Created by Ivan David Fernandez Salguero on 21/11/26.
//

#include "HistorialHash.h"
HistorialHash::HistorialHash(int numCubetas) {
    this->numCubetas = numCubetas;
    primeraCubeta = nullptr;
    NodoCubeta* ultima = nullptr;
    for (int i = 0; i < numCubetas; i++) {
        NodoCubeta* nueva = new NodoCubeta();
        if (primeraCubeta == nullptr) {
            primeraCubeta = nueva;
        } else {
            ultima->siguiente = nueva;
        }
        ultima = nueva;
    }
}
HistorialHash::~HistorialHash() {
    NodoCubeta* cubeta = primeraCubeta;
    while (cubeta != nullptr) {
        NodoHash* actual = cubeta->cabeza;

        while (actual!=nullptr) {
            NodoHash* nuevo = actual->next;
            delete actual;
            actual = nuevo;
        }
        NodoCubeta* siguienteCubeta = cubeta->siguiente;
        delete cubeta;
        cubeta = siguienteCubeta;
    }
}

unsigned long HistorialHash::funcionHash(string cedula) const {
    unsigned long h = 0;
    for (std::size_t i = 0; i < cedula.size(); i++) {
        h = h * 31 +cedula[i];
    }
    return h % numCubetas;
}

NodoCubeta* HistorialHash::obtenerCubeta(unsigned long indice) const {
    NodoCubeta* cubeta = primeraCubeta;
    for (unsigned long i = 0; i < indice; i++) {
        cubeta = cubeta->siguiente;
    }
    return cubeta;
}

Paciente* HistorialHash::buscar(string cedula) const {
    NodoHash* actual = obtenerCubeta(funcionHash(cedula))->cabeza;
    while (actual != nullptr && actual->dato.getCedula() != cedula) {
        actual = actual->next;
    }
    if (actual == nullptr) {
        return nullptr;
    }
    return &(actual->dato);
}

void HistorialHash::guardarOActualizar(Paciente p) {
    Paciente* existe = buscar(p.getCedula());

    if (existe != nullptr) {
        *existe = p;
    }
    else{
        NodoCubeta* cubeta = obtenerCubeta(funcionHash(p.getCedula()));

        NodoHash* nuevo = new NodoHash(p);

        nuevo->next = cubeta->cabeza;
        cubeta->cabeza = nuevo;
    }
}

void HistorialHash::consultarPorCedula(string cedula) const {
        Paciente* p = buscar(cedula);

    if (p == nullptr) {
        std::cout<<"Esta cedula no existe"<<std::endl;
    }
    else {
        std::cout << "Resultado de busqueda en Tabla Hash:" << std::endl;
        std::cout << "  Cedula:    " << p->getCedula() << std::endl;
        std::cout << "  Nombre:    " << p-> getNombre()<< std::endl;
        std::cout << "  Gravedad:  " << p-> getGravedad() << std::endl;
        std::cout << "  Estado:    " << p->getEstado() << std::endl;
        std::cout << "  Atendida por: " <<p->getMedicoAsociado()<< " (turno " << p->getTurnoAlta() << ")" << std::endl;
        std::cout << "  Tiempo de espera: "<< p->getEsperaAcumulada()<< std::endl;
    }
}

void HistorialHash::auditarPerdidos() {
    int perdidos = 0;
    std::cout << "Auditoria de pacientes perdidos:" << std::endl;

    NodoCubeta* cubeta = primeraCubeta;
    while (cubeta != nullptr) {
        NodoHash* actual = cubeta->cabeza;
        while (actual != nullptr) {
            if (actual->dato.getEstado() == "Perdido") {
                std::cout << "  - " << actual->dato.getNombre()
                        << " (cc " << actual->dato.getCedula() << ") - "
                        << actual->dato.getMedicoAsociado() << std::endl;
                perdidos++;
            }
            actual = actual->next;
        }
        cubeta = cubeta->siguiente;
    }

    std::cout << "Total de pacientes perdidos: " << perdidos << std::endl;
}
