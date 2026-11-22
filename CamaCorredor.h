#ifndef CAMACORREDOR_H
#define CAMACORREDOR_H

#include "NodoCama.h"

class CamaCorredor {
private:
    NodoCama* primera;      //primera cama o la cabeza de la lista
    NodoCama* medicoPosicion;

public:
    CamaCorredor();

    NodoCama *getMedicoPosicion();

    NodoCama* getMedicoPosicion() const;
    bool moverIzquierda();
    bool moverDerecha();
    int contarCamasVacias() const;
    void imprimirSala();

};


#endif //CAMACORREDOR_H