#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Estructura para almacenar la información de los usuarios.
struct Usuario {
    string username; // Nombre de usuario
    string password; // Contraseña
};

// Estructura para gestionar las solicitudes de eventos.
struct SolicitudEvento {
    string nombre;           // Nombre del evento
    string descripcion;      // Descripción del evento
    string fecha;            // Fecha del evento
    string lugar;            // Lugar del evento
    string hora;             // Hora del evento
    int cantidadPersonas;    // Cantidad de personas esperadas
    string estado;           // Estado de la solicitud (Pendiente, Aceptado, etc.)
};

// Estructura para representar los eventos dentro del sistema.
struct Evento {
    string nombre;               // Nombre del evento
    string descripcion;          // Descripción del evento
    string fecha;                // Fecha del evento
    string lugar;                // Lugar del evento
    string hora;                 // Hora del evento
    int cantidadPersonas;        // Cantidad de personas esperadas
    vector<string> inscritos;    // Lista de usuarios inscritos en el evento
    string estado;               // Estado del evento (Activo, Finalizado, etc.)
};

// Variables globales

// Lista para almacenar las solicitudes de eventos.
vector<SolicitudEvento> solicitudesEventos;

// Lista de usuarios registrados en el sistema.
vector<Usuario> usuarios;

// Lista de administradores del sistema.
vector<Usuario> administradores;

// Lista de eventos disponibles o creados en el sistema.
vector<Evento> eventos;

// Usuario actualmente activo en el sistema.
string usuarioActual;

// Mapa para asociar a cada usuario con sus solicitudes.
map<string, vector<string>> solicitudesUsuario;

int main() {
    
    return 0;
}
