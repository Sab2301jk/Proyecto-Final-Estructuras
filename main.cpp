//
// Created by eddya on 22/11/2026.
//

#include <iostream>
#include <string>
#include "Simulador.h"

using namespace std;

int main() {
  string nombreMedico;
  cout << "=== SIMULADOR DE URGENCIAS ===" << endl;
  cout << "Nombre del medico de turno: ";
  getline(cin, nombreMedico);

  Simulador simulador(nombreMedico, 50);
  bool salir = false;

  while (!salir) {
    if (simulador.jornadaTerminada()) {
      simulador.mostrarReporte();
      cout << "Jornada terminada: use [O] [J] [P] o [S]" << endl;
    } else {
      simulador.mostrarEstado();
    }
    cout << "Acciones: [I][A][D][R][T][X][U][C][E][O][J][P][S]" << endl << "> ";

    string comando;
    getline(cin, comando);
    if (comando.empty()) continue;

    char accion = comando[0];
    if (accion >= 'a' && accion <= 'z') accion = accion - 'a' + 'A';
    bool gastoTurno = false;

    if (accion == 'S') {
      salir = true;
    }
    else if (accion == 'O') {
      cout << "Nombre del nuevo medico: ";
      getline(cin, nombreMedico);
      simulador.cambiarMedico(nombreMedico);
    }
    else if (accion == 'J') {
      cout << "Nombre del medico: ";
      getline(cin, nombreMedico);
      simulador.consultarJornadas(nombreMedico);
    }
    else if (accion == 'P') {
      simulador.resumenPerdidos();
    }
    else if (simulador.jornadaTerminada()) {
      cout << "Jornada terminada." << endl;
    }
    else if (accion == 'I') {
      string cedula, nombre, condicion, textoGravedad;
      int gravedad = 0;
      cout << "Cedula: ";
      getline(cin, cedula);
      cout << "Nombre: ";
      getline(cin, nombre);
      while (gravedad < 1 || gravedad > 5) {
        cout << "Gravedad (1=Critico, 2=Severo, 3=Moderado, 4=Leve, 5=Consulta): ";
        getline(cin, textoGravedad);
        if (textoGravedad.size() == 1) gravedad = textoGravedad[0] - '0';
      }
      cout << "Condicion: ";
      getline(cin, condicion);
      simulador.ingresarPaciente(cedula, nombre, gravedad, condicion);
    }
    else if (accion == 'A') gastoTurno = simulador.retrocederCama();
    else if (accion == 'D') gastoTurno = simulador.avanzarCama();
    else if (accion == 'R') gastoTurno = simulador.pasarPacienteACama();
    else if (accion == 'T') gastoTurno = simulador.tratarPacienteActual();
    else if (accion == 'X') gastoTurno = simulador.darDeAltaEnCama();
    else if (accion == 'U') {
      simulador.verUltimasAltas();
      gastoTurno = true;
    }
    else if (accion == 'C') {
      string cedula;
      cout << "Cedula: ";
      getline(cin, cedula);
      simulador.consultarPaciente(cedula);
      gastoTurno = true;
    }
    else if (accion == 'E') {
      simulador.finalizarJornada();
    }
    else {
      cout << "Accion no valida." << endl;
    }

    if (gastoTurno) simulador.pasarTurno();
  }
  return 0;
}
