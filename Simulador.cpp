//
// Created by eddya on 22/11/2026.
//

#include "Simulador.h"
#include <iostream>

using namespace std;

Simulador::Simulador(string nombreMedico, int topeTurnos) : historial(50) {
  medicoActual = new Medico(nombreMedico);
  medicos.push_back(medicoActual);
  turnoGlobal = 0;
  turnosJornada = 0;
  topeJornada = topeTurnos;
  jornadaActiva = true;
  totalRecibidos = 0;
  totalAltas = 0;
  totalPerdidos = 0;
  sumaMinutosEspera = 0;
}

Medico* Simulador::buscarMedico(string nombreMedico) {
  int totalMedicos = medicos.size();
  for (int i = 0; i < totalMedicos; i++) {
    if (medicos[i]->nombre == nombreMedico) return medicos[i];
  }
  return nullptr;
}

bool Simulador::jornadaTerminada() {
  return jornadaActiva == false;
}

void Simulador::ingresarPaciente(string cedula, string nombre, int gravedad, string condicion) {
  Paciente* nuevoPaciente = new Paciente(cedula, nombre, gravedad, condicion, turnoGlobal);
  nuevoPaciente->setOrdenLlegada(totalRecibidos);
  colaTriage.push(nuevoPaciente);
  totalRecibidos++;
  historial.guardarOActualizar(*nuevoPaciente);
  cout << "Paciente ingresado a triage: " << nombre << " (gravedad " << gravedad << ")" << endl;
}

void Simulador::pasarTurno() {
  turnoGlobal++;
  turnosJornada++;
  medicoActual->sumarTurno();

  priority_queue<Paciente*, vector<Paciente*>, Prioridad> colaNueva;
  while (!colaTriage.empty()) {
    Paciente* pacienteEnEspera = colaTriage.top();
    colaTriage.pop();

    pacienteEnEspera->avanzarEnCola();
    sumaMinutosEspera += 5;

    if (pacienteEnEspera->superoRiesgo()) {
      pacienteEnEspera->marcarPerdido(medicoActual->nombre);
      totalPerdidos++;
      cout << "!! Paciente critico perdido: " << pacienteEnEspera->getNombre() << endl;
    } else {
      colaNueva.push(pacienteEnEspera);
    }
    historial.guardarOActualizar(*pacienteEnEspera);
  }
  colaTriage = colaNueva;

  if (turnosJornada >= topeJornada) finalizarJornada();
}

void Simulador::finalizarJornada() {
  if (!jornadaActiva) return;
  medicoActual->guardarJornada();
  jornadaActiva = false;
  cout << "Jornada cerrada." << endl;
}

void Simulador::cambiarMedico(string nombreNuevoMedico) {
  finalizarJornada();

  medicoActual = buscarMedico(nombreNuevoMedico);
  if (medicoActual == nullptr) {
    medicoActual = new Medico(nombreNuevoMedico);
    medicos.push_back(medicoActual);
  }
  while (corredor.moverIzquierda()) {}
  turnosJornada = 0;
  jornadaActiva = true;
  cout << "Nuevo medico en turno: " << nombreNuevoMedico << endl;
}

bool Simulador::retrocederCama() {
  if (corredor.moverIzquierda()) return true;
  cout << "No hay cama anterior." << endl;
  return false;
}

bool Simulador::avanzarCama() {
  if (corredor.moverDerecha()) return true;
  cout << "No hay cama siguiente." << endl;
  return false;
}

bool Simulador::pasarPacienteACama() {
  NodoCama* camaActual = corredor.getMedicoPosicion();
  if (!camaActual->estaVacia() || colaTriage.empty()) {
    cout << "Se necesita una cama vacia y pacientes en cola." << endl;
    return false;
  }

  Paciente* pacienteRecibido = colaTriage.top();
  colaTriage.pop();
  pacienteRecibido->IniciarTratamiento(medicoActual->nombre);
  camaActual->ocupar(pacienteRecibido, pacienteRecibido->turnosTratamientoRequeridos());

  historial.guardarOActualizar(*pacienteRecibido);
  cout << "Ingreso a cama #" << camaActual->getNumeroCama() << ": " << pacienteRecibido->getNombre() << endl;
  return true;
}

bool Simulador::tratarPacienteActual() {
  NodoCama* camaActual = corredor.getMedicoPosicion();
  if (!camaActual->tratar()) {
    cout << "No hay tratamiento pendiente en esta cama." << endl;
    return false;
  }

  cout << "Turnos de tratamiento pendientes: " << camaActual->getTurnosRestantes() << endl;
  return true;
}

bool Simulador::darDeAltaEnCama() {
  NodoCama* camaActual = corredor.getMedicoPosicion();
  if (!camaActual->tratamientoTerminado()) {
    cout << "No se puede dar de alta: cama vacia o tratamiento incompleto." << endl;
    return false;
  }

  Paciente* pacienteAlta = camaActual->getPacienteActual();
  pacienteAlta->darAlta(turnoGlobal);

  medicoActual->registrarAlta(pacienteAlta);
  historial.guardarOActualizar(*pacienteAlta);
  totalAltas++;

  camaActual->liberar();
  cout << "Paciente dado de alta: " << pacienteAlta->getNombre() << endl;
  return true;
}

void Simulador::verUltimasAltas() {
  medicoActual->mostrarUltimosAtendidos();
}

void Simulador::consultarPaciente(string cedula) {
  historial.consultarPorCedula(cedula);
}

void Simulador::mostrarEstado() {
  cout << endl << "Dr. " << medicoActual->nombre << " | Turno: " << turnosJornada + 1 << "/" << topeJornada
       << " | Pacientes en cola: " << colaTriage.size() << endl;
  corredor.imprimirSala();

  NodoCama* camaActual = corredor.getMedicoPosicion();
  cout << "Cama actual: #" << camaActual->getNumeroCama();
  if (camaActual->estaVacia()) {
    cout << " (Vacia)";
  } else {
    Paciente* pacienteEnCama = camaActual->getPacienteActual();
    cout << " - " << pacienteEnCama->getNombre() << " (gravedad " << pacienteEnCama->getGravedad()
         << "), turnos pendientes: " << camaActual->getTurnosRestantes();
  }
  cout << endl;

  vector<int> cantidad(6, 0);
  int mayorRiesgo = 0;
  priority_queue<Paciente*, vector<Paciente*>, Prioridad> copiaCola = colaTriage;
  while (!copiaCola.empty()) {
    Paciente* pacienteEnEspera = copiaCola.top();
    copiaCola.pop();
    cantidad[pacienteEnEspera->getGravedad()]++;
    if (pacienteEnEspera->getContadorRiesgo() > mayorRiesgo) mayorRiesgo = pacienteEnEspera->getContadorRiesgo();
  }

  cout << "Cola por gravedad -> ";
  for (int gravedad = 1; gravedad <= 5; gravedad++) {
    cout << "G" << gravedad << ": " << cantidad[gravedad] << "  ";
  }
  cout << endl;
  if (mayorRiesgo >= 3) cout << "ALERTA: paciente critico en riesgo (" << mayorRiesgo << "/6)" << endl;
}

void Simulador::mostrarReporte() {
  double promedioEspera = 0;
  if (totalRecibidos > 0) promedioEspera = sumaMinutosEspera / totalRecibidos;

  cout << endl << "Reporte - Dr. " << medicoActual->nombre << endl;
  cout << "Pacientes recibidos: " << totalRecibidos << endl;
  cout << "Pacientes dados de alta: " << totalAltas << endl;
  cout << "Pacientes perdidos: " << totalPerdidos << endl;
  cout << "Tiempo promedio de espera: " << promedioEspera << " min" << endl;
  cout << "Camas desocupadas: " << corredor.contarCamasVacias() << endl;
  cout << "Cantidad de medicos: " << medicos.size() << endl;
  cout << "Turnos usados: " << turnosJornada << "/" << topeJornada << endl;
}

void Simulador::consultarJornadas(string nombreMedico) {
  Medico* medicoBuscado = buscarMedico(nombreMedico);
  if (medicoBuscado == nullptr) cout << "No existe ese medico." << endl;
  else medicoBuscado->mostrarJornadas();
}

void Simulador::resumenPerdidos() {
  historial.auditarPerdidos();
}
