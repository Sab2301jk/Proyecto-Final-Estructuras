//
// Created by Ivan David Fernandez Salguero on 21/11/26.
//

#include "HistorialHash.h"



HistorialHash::HistorialHash(int numCubetas) {

    for (int i = 0; i < numCubetas; i++) {

        cubetas.push_back(nullptr);
    }
    cantidad = 0;
}
HistorialHash::~HistorialHash() {
    for ( int i = 0; i < cubetas.size(); i++) {
        NodoHash* actual = cubetas[i];

        while (actual!=nullptr) {
            NodoHash* nuevo = actual->next;
            delete actual;
            actual = nuevo;
        }


    }
}


unsigned long HistorialHash::funcionHash(string cedula) const {
    unsigned long h = 0;
    for (int i = 0; i < cedula.size(); i++) {
        h = h * 31 +cedula[i];
    }
    return h % cubetas.size();
}

Paciente* HistorialHash::buscar(string cedula) const {
    NodoHash* actual = cubetas[funcionHash(cedula)];
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
        unsigned long indice = funcionHash(p.getCedula());

        NodoHash* nuevo = new NodoHash(p);

        nuevo->next = cubetas[indice];
        cubetas[indice] = nuevo;

        cantidad++;




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

    for (std::size_t i = 0; i < cubetas.size(); i++) {
        NodoHash* actual = cubetas[i];
        while (actual != nullptr) {
            if (actual->dato.getEstado() == "Perdido") {
                std::cout << "  - " << actual->dato.getNombre()
                        << " (cc " << actual->dato.getCedula() << ") - "
                        << actual->dato.getMedicoAsociado() << std::endl;
                perdidos++;
            }
            actual = actual->next;
        }
    }

    std::cout << "Total de pacientes perdidos: " << perdidos << std::endl;
}


int HistorialHash::totalPacientes() const {
    int total = 0;


    for (int i = 0; i < cubetas.size(); i++) {
        NodoHash* actual = cubetas[i];
        while (actual != nullptr) {
            total++;
            actual = actual->next;
        }

    }
    std::cout << "Total de pacientes "<<total<<std::endl;
    return total;
}
