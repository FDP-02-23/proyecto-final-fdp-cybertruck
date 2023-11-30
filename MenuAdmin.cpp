#include <iostream>  // Biblioteca estándar de entrada y salida, que permite la lectura y escritura en la consola.
#include <string>    // Biblioteca para trabajar con cadenas de texto (strings).
#include <vector>    // Biblioteca para trabajar con vectores, que son arreglos dinámicos.
#include <fstream>   // Biblioteca para trabajar con archivos (lectura y escritura).
#include <algorithm> // Biblioteca que proporciona funciones para trabajar con algoritmos, como ordenar elementos.
#include <limits>    // Biblioteca que proporciona constantes y límites de tipos de datos.
using namespace std;

// Definición de la estructura 'Evento' que representa un evento existente
struct Evento {
    string nombre; // Nombre del evento
    string descripcion; // Descripción del evento
    string fecha; // Fecha del evento
    string lugar; // Lugar del evento
    string hora; //  campo para la hora
    int cantidadPersonas; //  campo para la cantidad de personas
    vector<string> inscritos; // Lista de usuarios inscritos en el evento
     string estado;// Nuevo campo para el estado del evento   
};

// Definicion de la estructura 'SolicitudEvento' que representa una solicitud de evento pendiente
struct SolicitudEvento {
    string nombre; // Nombre de la solicitud de evento
    string descripcion; // Descripcion de la solicitud de evento
    string fecha; // Fecha propuesta para el evento
    string lugar; // Lugar propuesto para el evento
    string hora; // Hora propuesta para el evento
    int cantidadPersonas; // Cantidad de personas esperadas en el evento
    string estado; // Estado de la solicitud de evento (por ejemplo, 'pendiente' o 'aprobada')
};

vector<SolicitudEvento> solicitudesEventos; // Lista de solicitudes de eventos pendientes
vector<Evento> eventos; // Lista de eventos existentes
string usuarioActual = "Admin"; // Usuario actual (inicializado como 'Admin')
