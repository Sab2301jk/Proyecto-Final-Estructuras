//
// Created by Ivan David Fernandez Salguero on 21/11/26.
//

#include "Paciente.h"



Paciente::Paciente() {

    this->cedula = "";
    this->nombre = "";
    this->gravedad = 5;
    this->condicion = "";
    this->turnoLlegada = 0;
    this->turnoAlta = -1;
    this->esperaAcumulada = 0;
    this->contadorRiesgo = 0;
    this->estado = "En cola";
    this->medicoAsociado = "Sin asignar";
}


Paciente::Paciente(string cedula, string nombre, int gravedad, string condicion, int turnoLlegada) {
    this->cedula = cedula;
    this->nombre = nombre;
    this->gravedad = gravedad;
    this->condicion = condicion;
    this->turnoLlegada = turnoLlegada;
    this->turnoAlta = -1;
    this->esperaAcumulada = 0;
    this->contadorRiesgo = 0;
    this->estado = "En cola";
    this->medicoAsociado = "Sin asignar";
}

string Paciente::getCedula() const {
    return this->cedula;
}
string Paciente::getNombre() const {
    return this->nombre;
}
string Paciente::getCondicion() const {
    return this->condicion;
}
string Paciente::getEstado() const {
    return this->estado;
}
string Paciente::getMedicoAsociado() const {
    return this->medicoAsociado;
}

int Paciente::getGravedad() const {
    return this->gravedad;
}
int Paciente::getTurnoLlegada() const {
    return this->turnoLlegada;
}
int Paciente::getTurnoAlta() const {
    return this->turnoAlta;
}
int Paciente::getEsperaAcumulada() const {
    return this->esperaAcumulada;
}
int Paciente::getContadorRiesgo() const {
    return this->contadorRiesgo;
}
int Paciente::turnosTratamientoRequeridos() const {
    return 6-gravedad;
}


bool Paciente::esCritico() const {
    if (gravedad == 1) {
        return true;
    }else {
        return false;
    }
}
bool Paciente::superoRiesgo() const {
    return this->esCritico() && this-> contadorRiesgo > 6;

}

void Paciente::avanzarEnCola() {
    esperaAcumulada = esperaAcumulada + 5;
    if (esCritico()) {
        contadorRiesgo++;
    }
}
void Paciente::IniciarTratamiento(string medico) {
    estado = "En tratamiento";
    medicoAsociado = medico;
}
void Paciente::darAlta(int turno) {

    estado = "Alta";
    turnoAlta = turno;
}
void Paciente::marcarPerdido(string medico) {
    estado = "Perdido";
    medicoAsociado = medico;
}
