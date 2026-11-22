#include "CamaCorredor.h"
#include "Paciente.h"
#include <iostream>
using namespace std;

CamaCorredor::CamaCorredor() {
    primera = new NodoCama(1);
    NodoCama* prev = primera;
    for (int numero = 1; numero <= 10; numero++) {
        NodoCama* nueva = new NodoCama(numero);
        prev->setNext(nueva);
        nueva->setPrev(prev);
        prev = nueva;
    }
    medicoPosicion = primera;


}

NodoCama* CamaCorredor::getMedicoPosicion() const {
    return medicoPosicion;
}

bool CamaCorredor::moverIzquierda() {
    if (medicoPosicion->getPrev() == nullptr) {
        return false;
    }
    medicoPosicion = medicoPosicion->getPrev();
    return true;
}

bool CamaCorredor::moverDerecha() {
    if (medicoPosicion->getNext()== nullptr) {
        return false;
    }
    medicoPosicion = medicoPosicion->getNext();
    return true;
}

int CamaCorredor::contarCamasVacias() const {
    int vacias = 0;
    NodoCama* camaAux = primera;
    while (camaAux != nullptr) {
        if (camaAux->estaVacia()) vacias++;
        camaAux = camaAux->getNext();
    }
    return vacias;
}

void CamaCorredor::imprimirSala() {
    NodoCama* camaAux = primera;
    int posicion = 0;
    int posicionMedico = 0;
    while (camaAux != nullptr) {
        if (camaAux == medicoPosicion) {
            posicionMedico = posicion;
        }
        cout << "[#";
        if (camaAux->getNumeroCama() < 10) {
            cout << " ";
        }
        cout << camaAux->getNumeroCama() << ":";
        if (camaAux->estaVacia()) {
            cout << "V ";
        }else {
            cout << "P" << camaAux->getPacienteActual()->getGravedad();
            cout << "]";
        }
        if (camaAux->getNext() != nullptr) {
            cout << "=";
        }
        camaAux = camaAux->getNext();
        posicion++;
    }
    cout << endl;

    for (int i = 0; i < posicionMedico * 9 + 3; i++) {
        cout << " ";
    }
    cout << "M\n";
};

