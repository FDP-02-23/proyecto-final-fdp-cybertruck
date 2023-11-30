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
// Declaraciones de funciones adicionales para el manejo de usuarios, eventos y administradores

bool iniciarSesion(bool esAdmin); // Función para iniciar sesión, diferenciando entre admin y usuario normal

void registrarUsuario(bool esAdmin); // Función para registrar un nuevo usuario o administrador

void menuAdmin(); // Función para mostrar el menú de opciones para administradores

void menuUsuario(); // Función para mostrar el menú de opciones para usuarios

void crearEvento(); // Función para crear un nuevo evento

void mostrarEventos(); // Función para mostrar todos los eventos disponibles

void modificarEvento(Evento& e); // Función para modificar un evento existente

void buscarEventosPorSimilitud(); // Función para buscar eventos por similitud en el nombre

void eliminarEvento(int index); // Función para eliminar un evento por su índice

void inscribirseEnEvento(); // Función para que un usuario se inscriba en un evento

void verificarMisEventos(); // Función para que un usuario verifique los eventos en los que está inscrito

void enviarSolicitudEvento(); // Función para enviar una solicitud para un nuevo evento

void verSolicitudesDeEvento(); // Función para ver las solicitudes de eventos (probablemente para administradores)

// Función para iniciar sesión, ya sea como administrador o como usuario regular
bool iniciarSesion(bool esAdmin) {
    string username, password;
    // Solicita el nombre de usuario
    cout << "Ingrese su nombre de usuario o '0' para regresar: ";
    cin >> username;

    // Si el usuario ingresa '0', termina la función y regresa al menú anterior
    if (username == "0") {
        return false; 
    }

    // Solicita la contraseña
    cout << "Ingrese su contrasena: ";
    cin >> password;

    // Elige entre la lista de administradores o usuarios según el tipo de inicio de sesión
    vector<Usuario>& listaUsuarios = esAdmin ? administradores : usuarios;

    // Recorre la lista de usuarios para encontrar una coincidencia
    for (const Usuario& u : listaUsuarios) {
        // Si encuentra una coincidencia en nombre de usuario y contraseña
        if (u.username == username && u.password == password) {
            usuarioActual = username; // Establece el usuario actual
            cout << "Inicio de sesion exitoso. Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
            cin.get(); // Espera que el usuario presione Enter
            return true; // Retorna verdadero, indicando un inicio de sesión exitoso
        }
    }

    // Si no se encuentra ninguna coincidencia, muestra un mensaje de error
    cout << "Error: Usuario no registrado o usuario/contrasena incorrectos.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea
    cin.get(); // Espera que el usuario presione Enter
    return false; // Retorna falso, indicando que el inicio de sesión falló
}