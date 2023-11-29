// verEventosInscritos.h

#ifndef VER_EVENTOS_INSCRITOS_H //condicion de preprocesador que verifica si INSCRIBIRSE_EN_EVENTO_H no ha sido definido anteriormente
#define VER_EVENTOS_INSCRITOS_H //Si INSCRIBIRSE_EN_EVENTO_H no esta definido, esta línea lo define
#include <iostream>
#include <vector>
#include <algorithm>
#include "estructuras.h"  

using namespace std;

// La funcion verEventosInscritos muestra todos los eventos en los que esta inscrito el usuario actual.
// Recorre la lista de eventos y verifica si el usuario actual está inscrito en cada uno de ellos.
// Muestra detalles del evento si el usuario esta inscrito.
void verEventosInscritos(const vector<Evento>& eventos, const string& usuarioActual) {
    cout << "Eventos en los que estas inscrito:\n";
    bool inscritoEnAlgunEvento = false;

    // Recorremos cada evento para verificar si el usuario actual esta inscrito
    for (const Evento& e : eventos) {
        if (find(e.inscritos.begin(), e.inscritos.end(), usuarioActual) != e.inscritos.end()) {
            cout << "Nombre: " << e.nombre << "\n";
            cout << "Descripcion: " << e.descripcion << "\n";
            cout << "Fecha: " << e.fecha << "\n";
            cout << "Lugar: " << e.lugar << "\n";
            cout << "Hora: " << e.hora << "\n";
            cout << "Cantidad de Personas: " << e.cantidadPersonas << "\n";
            cout << "-----------------------\n";
            inscritoEnAlgunEvento = true;
        }
    }

    // Si el usuario no esta inscrito en ningun evento, mostramos un mensaje
    if (!inscritoEnAlgunEvento) {
        cout << "No estas inscrito en ningun evento.\n";
    }

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

#endif // VER_EVENTOS_INSCRITOS_H
