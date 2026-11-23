//
// Created by Ivan David Fernandez Salguero on 21/11/26.
//

#ifndef PROYECTO_FINAL_URGENCIAS_PACIENTE_H
#define PROYECTO_FINAL_URGENCIAS_PACIENTE_H
#include <string>
using std::string;

class Paciente {
private:
    string cedula;
    string nombre;
    int gravedad;
    string condicion;
    int turnoLlegada;
    int turnoAlta;
    int esperaAcumulada;
    int contadorRiesgo;
    string estado;
    string medicoAsociado;
    int ordenLlegada;

public:
    Paciente();
    Paciente(string cedula, string nombre, int gravedad, string condicion, int turnoLlegada);

    string getCedula() const;
    string getNombre() const;
    string getCondicion() const;
    string getEstado() const;
    string getMedicoAsociado() const;

    int getGravedad() const;
    int getTurnoLlegada() const;
    int getTurnoAlta() const;
    int getEsperaAcumulada() const;
    int getContadorRiesgo() const;
    int getOrdenLlegada() const;
    int turnosTratamientoRequeridos() const;

    void setOrdenLlegada(int orden);

    bool esCritico() const;
    bool superoRiesgo() const;

    void avanzarEnCola();
    void IniciarTratamiento(string medico);
    void darAlta(int turno);
    void marcarPerdido(string medico);
};
#endif //PROYECTO_FINAL_URGENCIAS_PACIENTE_H
