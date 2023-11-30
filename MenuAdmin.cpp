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

// Declaraciones de funciones
bool iniciarSesion(bool esAdmin);
void registrarUsuario(bool esAdmin);
void menuAdmin();
void menuUsuario();
void crearEvento();
void mostrarEventos();
void modificarEvento(Evento& e);
void buscarEventosPorSimilitud();
void eliminarEvento(int index);
void inscribirseEnEvento();
void verificarMisEventos();
void enviarSolicitudEvento();
void verSolicitudesDeEvento();

// Funcion para limpiar la pantalla de la consola 
void limpiarPantalla() {
    system("cls");
}

// Funcion para crear un nuevo evento y agregarlo al vector 'eventos'.
void crearEvento() {
    Evento e; // Se crea una instancia de la estructura 'Evento' para almacenar la informacion del nuevo evento.
    cout << "Ingrese el nombre del evento o '0' para salir: ";
    cin.ignore(); 
    getline(cin, e.nombre); // Se lee la línea de entrada (nombre del evento) y se almacena en 'e.nombre'.
    if (e.nombre == "0") { // Si el nombre ingresado es "0", se cancela la creación del evento.
        return;
    }
    cout << "Ingrese la descripcion del evento o '0' para salir: ";
    getline(cin, e.descripcion); // Se lee la descripcion del evento y se almacena en 'e.descripcion'.
    if (e.descripcion == "0") { // Si la descripcion ingresada es "0", se cancela la creación del evento.
        return;
    }
    cout << "Ingrese la fecha del evento o '0' para salir: ";
    getline(cin, e.fecha); // Se lee la fecha del evento y se almacena en 'e.fecha'.
    if (e.fecha == "0") { // Si la fecha ingresada es "0", se cancela la creacion del evento.
        return;
    }
    cout << "Ingrese el lugar del evento o '0' para salir: ";
    getline(cin, e.lugar); // Se lee el lugar del evento y se almacena en 'e.lugar'.
    if (e.lugar == "0") { // Si el lugar ingresado es "0", se cancela la creación del evento.
        return;
    }
    cout << "Ingrese la hora del evento o '0' para salir: ";
    getline(cin, e.hora); // Se lee la hora del evento y se almacena en 'e.hora'.
    if (e.hora == "0") { // Si la hora ingresada es "0", se cancela la creación del evento.
        return;
    }
    cout << "Ingrese la cantidad de personas o '0' para salir: ";
    if (!(cin >> e.cantidadPersonas)) { // Se verifica si la entrada es un numero valido.
        cin.clear(); // Se limpia el estado de error de cin.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Se ignora la entrada incorrecta.
        return;
    }
    if (e.cantidadPersonas == 0) { // Si la cantidad de personas es 0, se cancela la creacion del evento.
        return;
    }
    cin.ignore(); // Se ignora el salto de linea pendiente en el búfer de entrada.
    eventos.push_back(e); // Se agrega el evento al vector 'eventos'.
    cout << "Evento creado exitosamente. Presione Enter para continuar...";
    cin.get(); // Espera a que se presione Enter antes de continuar.
}

void mostrarEventos();

// Función para eliminar un participante de un evento.
void eliminarParticipante() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    mostrarEventos(); // Mostrar eventos disponibles.
    cout << "Ingrese el numero del evento del cual desea eliminar un participante o '0' para salir: ";
    int numEvento;
    cin >> numEvento;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (numEvento == 0) {
        return;
    }
    if (numEvento < 1 || numEvento > eventos.size()) {
        cout << "numero de evento no valido.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    Evento& eventoSeleccionado = eventos[numEvento - 1];
    if (eventoSeleccionado.inscritos.empty()) {
        cout << "No hay participantes inscritos en este evento.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    cout << "Participantes inscritos en el evento:\n";
    for (int i = 0; i < eventoSeleccionado.inscritos.size(); ++i) {
        cout << i + 1 << ". " << eventoSeleccionado.inscritos[i] << endl;
    }
    cout << "Ingrese el numero del participante que desea eliminar o '0' para salir: ";
    int numParticipante;
    cin >> numParticipante;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (numParticipante == 0) {
        return;
    }
    if (numParticipante < 1 || numParticipante > eventoSeleccionado.inscritos.size()) {
        cout << "Numero de participante no valido.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    eventoSeleccionado.inscritos.erase(eventoSeleccionado.inscritos.begin() + numParticipante - 1);
    cout << "Participante eliminado exitosamente.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}