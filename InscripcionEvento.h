// inscribirseEnEvento.h

#ifndef INSCRIBIRSE_EN_EVENTO_H
#define INSCRIBIRSE_EN_EVENTO_H

#include <iostream>
#include <vector>
#include "estructuras.h"  

using namespace std;

// La función inscribirseEnEvento permite a un usuario inscribirse en un evento.
// Los eventos pueden ser buscados por similitud o listados todos.
// El usuario elige un evento para inscribirse.
// La funcion modifica la lista de inscritos del evento seleccionado.
void inscribirseEnEvento(vector<Evento>& eventos, const string& usuarioActual) {
    if (eventos.empty()) {
        // Si no hay eventos, informamos al usuario y salimos de la funcion.
        cout << "No hay eventos disponibles para inscribirse.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    int opcion;
    cout << "¿Cómo desea buscar el evento para inscribirse?\n";
    cout << "1. Listar todos los eventos\n";
    cout << "2. Buscar evento por similitud\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion o '0' para salir: ";
    cin >> opcion;

    // Si el usuario elige salir, terminamos la funcion.
    if (opcion == 0) {
        return;
    }

    vector<Evento*> eventosEncontrados;
    switch (opcion) {
        case 1:
            // Listamos todos los eventos disponibles.
            for (Evento& e : eventos) {
                eventosEncontrados.push_back(&e);
            }
            break;
        case 2:
            // Buscamos eventos por similitud de nombre.
            eventosEncontrados = ObtenerEventosPorSimilitud(eventos);
            break;
        default:
            cout << "Opcion no valida.\n";
            return;
    }

    if (eventosEncontrados.empty()) {
        cout << "No se encontraron eventos.\n";
        return;
    }

    cout << "Seleccione el numero del evento al que desea inscribirse o '0' para salir:\n";
    for (int i = 0; i < eventosEncontrados.size(); ++i) {
        cout << i + 1 << ". " << eventosEncontrados[i]->nombre << "\n";
    }
    cout << "0. Salir\n";

    int numEvento;
    cin >> numEvento;

    if (numEvento == 0) {
        return;
    } else if (numEvento < 1 || numEvento > eventosEncontrados.size()) {
        cout << "Numero de evento no valido.\n";
        return;
    }

    Evento* eventoSeleccionado = eventosEncontrados[numEvento - 1];
    // Verificamos si el usuario ya está inscrito en el evento.
    if (find(eventoSeleccionado->inscritos.begin(), eventoSeleccionado->inscritos.end(), usuarioActual) != eventoSeleccionado->inscritos.end()) {
        cout << "Ya estas inscrito en este evento.\n";
    } else {
        // Si no está inscrito, lo añadimos a la lista de inscritos.
        eventoSeleccionado->inscritos.push_back(usuarioActual);
        cout << "Inscripcion exitosa en el evento: " << eventoSeleccionado->nombre << "\n";
    }

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

#endif // INSCRIBIRSE_EN_EVENTO_H
