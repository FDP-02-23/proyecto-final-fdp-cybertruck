
#include <iostream>
#include <vector>
#include <string>
#include "estructuras.h" 

using namespace std;

// Función para limpiar la pantalla, compatible con Windows y Unix/Linux
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para obtener eventos por similitud de nombre
vector<Evento*> ObtenerEventosPorSimilitud(vector<Evento>& eventos) {
    vector<Evento*> eventosEncontrados;
    cout << "Ingrese parte del nombre del evento a buscar: ";
    string nombreBusqueda;
    cin.ignore();
    getline(cin, nombreBusqueda);

    for (Evento& e : eventos) {
        if (e.nombre.find(nombreBusqueda) != string::npos) {
            eventosEncontrados.push_back(&e);
        }
    }

    return eventosEncontrados;
}
