#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

struct Usuario {
    string username;
    string password;
};

struct SolicitudEvento {
    string nombre;
    string descripcion;
    string fecha;
    string lugar;
    string hora;
    int cantidadPersonas;
    string estado; 

};


struct Evento {
    string nombre;
    string descripcion;
    string fecha;
    string lugar;
    string hora; //  campo para la hora
    int cantidadPersonas; //  campo para la cantidad de personas
    vector<string> inscritos; // Lista de usuarios inscritos en el evento
     string estado;// Nuevo campo para el estado del evento

    
};

vector<SolicitudEvento> solicitudesEventos;
vector<Usuario> usuarios;
vector<Usuario> administradores;
vector<Evento> eventos;
string usuarioActual; // Almacena el nombre del usuario actual
map<string, vector<string>> solicitudesUsuario; 
vector<Evento*> ObtenerEventosPorSimilitud() {
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
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
     }

void mostrarEventos() {
    // Implementación vacía
}

void buscarEventosPorSimilitud() {
    // Implementación vacía
}

void inscribirseEnEvento() {
    // Implementación vacía
}

void verEventosInscritos() {
    // Implementación vacía
}

void enviarSolicitudEvento() {
    // Implementación vacía
}

void verSolicitudesDeEvento() {
    // Implementación vacía
}

bool iniciarSesion(bool esAdmin) {
    return false; // Devuelve false o true según la lógica deseada
}

void menuAdmin() {
    // Implementación vacía
}

void registrarUsuario(bool esAdmin) {
    // Implementación vacía
}


void buscarEventos() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para buscar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
}