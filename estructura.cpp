// Inclusión de bibliotecas estándar
#include <iostream> // Biblioteca para operaciones de entrada y salida
#include <vector>   // Biblioteca para usar el contenedor vector
#include <string>   // Biblioteca para usar objetos de tipo string
#include <limits>   // Biblioteca para características de tipos de datos
#include <fstream>  // Biblioteca para operaciones de archivo
#include <algorithm>// Biblioteca para algoritmos estándar
#include <map>      // Biblioteca para usar el contenedor map

// Uso del espacio de nombres estándar para evitar anteponer 'std::'
using namespace std;

// Definición de la estructura Usuario para almacenar información de usuarios
struct Usuario {
    string username; // Nombre de usuario
    string password; // Contraseña del usuario
};

// Definición de la estructura SolicitudEvento para manejar solicitudes de eventos
struct SolicitudEvento {
    string nombre;          // Nombre del evento
    string descripcion;     // Descripción del evento
    string fecha;           // Fecha del evento
    string lugar;           // Lugar del evento
    string hora;            // Hora del evento
    int cantidadPersonas;   // Número de personas esperadas en el evento
    string estado;          // Estado de la solicitud (aprobada, pendiente, etc.)
};

// Definición de la estructura Evento para representar un evento
struct Evento {
    string nombre;          // Nombre del evento
    string descripcion;     // Descripción del evento
    string fecha;           // Fecha del evento
    string lugar;           // Lugar del evento
    string hora;            // Hora del evento
    int cantidadPersonas;   // Número de personas esperadas en el evento
    vector<string> inscritos; // Lista de nombres de usuarios inscritos en el evento
    string estado;          // Estado actual del evento (activo, cancelado, etc.)
};
// Definición de contenedores para almacenar diferentes tipos de datos

vector<SolicitudEvento> solicitudesEventos; // Vector para almacenar solicitudes de eventos
vector<Usuario> usuarios;                   // Vector para almacenar usuarios
vector<Usuario> administradores;            // Vector para almacenar administradores
vector<Evento> eventos;                     // Vector para almacenar eventos
string usuarioActual;                       // Almacena el nombre del usuario actual

// Mapa para asociar un nombre de usuario con un vector de nombres de eventos solicitados
map<string, vector<string>> solicitudesUsuario; 

// Función para obtener eventos por similitud de nombre
vector<Evento*> ObtenerEventosPorSimilitud() {
    vector<Evento*> eventosEncontrados; // Vector para almacenar punteros a eventos encontrados

    cout << "Ingrese parte del nombre del evento a buscar: ";
    string nombreBusqueda;
    cin.ignore(); // Ignora el buffer de entrada para limpiar cualquier entrada previa
    getline(cin, nombreBusqueda); // Obtiene la línea de entrada y la almacena en nombreBusqueda

    // Recorre todos los eventos y busca coincidencias en el nombre
    for (Evento& e : eventos) {
        // Si el nombre del evento contiene la cadena de búsqueda
        if (e.nombre.find(nombreBusqueda) != string::npos) {
            eventosEncontrados.push_back(&e); // Añade el puntero al evento al vector de eventos encontrados
        }
    }

    return eventosEncontrados; // Devuelve el vector de punteros a eventos encontrados
}
// Función para limpiar la pantalla de la consola
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls"); // Si el sistema operativo es Windows, usa el comando 'cls'
    #else
        system("clear"); // En otros sistemas operativos, usa el comando 'clear'
    #endif
}
