//
// Created by saria on 23/11/2026.
//

#ifndef PROYECTO_FINAL_URGENCIAS_CAMACORREDOR_H
#define PROYECTO_FINAL_URGENCIAS_CAMACORREDOR_H

#include "NodoCama.h"

class CamaCorredor {
private:
    NodoCama* primera;
    NodoCama* medicoPosicion;

public:
    CamaCorredor();

    NodoCama* getMedicoPosicion() const;
    bool moverIzquierda();
    bool moverDerecha();
    int contarCamasVacias() const;
    void imprimirSala();
};

#endif //PROYECTO_FINAL_URGENCIAS_CAMACORREDOR_H
