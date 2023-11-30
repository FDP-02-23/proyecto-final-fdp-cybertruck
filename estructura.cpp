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
// Función para buscar eventos por similitud según diferentes criterios
void buscarEventosPorSimilitud() {
    // Verifica si la lista de eventos está vacía
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para buscar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Si está vacía, sale de la función
    }

    // Presenta opciones de búsqueda al usuario
    cout << "Buscar evento por:\n";
    cout << "1. Nombre\n";
    cout << "2. Lugar\n";
    cout << "3. Fecha\n";
    cout << "Seleccione una opcion: ";
    int opcion;
    cin >> opcion; // Recoge la opción seleccionada por el usuario
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada

    string busqueda; // Almacena el término de búsqueda
    // Muestra mensajes basados en la opción seleccionada y recoge el término de búsqueda
    switch (opcion) {
        case 1:
            cout << "Ingrese parte del nombre del evento a buscar: ";
            break;
        case 2:
            cout << "Ingrese parte del lugar del evento a buscar: ";
            break;
        case 3:
            cout << "Ingrese parte de la fecha del evento a buscar: ";
            break;
        default:
            cout << "Opcion no valida.\n"; // Manejo de opción inválida
            return;
    }
    getline(cin, busqueda); // Obtiene el término de búsqueda del usuario

    bool encontrado = false; // Bandera para indicar si se encontraron coincidencias
    // Recorre todos los eventos buscando coincidencias con el término de búsqueda
    for (const Evento& e : eventos) {
        bool coincide = false; // Bandera para coincidencias individuales
        // Busca coincidencias según la opción seleccionada
        switch (opcion) {
            case 1:
                coincide = e.nombre.find(busqueda) != string::npos;
                break;
            case 2:
                coincide = e.lugar.find(busqueda) != string::npos;
                break;
            case 3:
                coincide = e.fecha.find(busqueda) != string::npos;
                break;
        }

        // Si se encuentra una coincidencia, muestra los detalles del evento
        if (coincide) {
            cout << "* Evento encontrado:  *\n";
            cout << "* Nombre:  *" << e.nombre << "\n";
            cout << "* Descripcion: *" << e.descripcion << "\n";
            cout << "* Fecha:  *" << e.fecha << "\n";
            cout << "* Lugar:  *" << e.lugar << "\n";
            cout << "* Hora:  *" << e.hora << "\n";
            cout << "* Cantidad de Personas:  *" << e.cantidadPersonas << "\n";
            cout << "------------------------------\n";
            encontrado = true; // Actualiza la bandera a verdadero
        }
    }

    // Si no se encontraron coincidencias, muestra un mensaje
    if (!encontrado) {
        cout << "No se encontraron eventos con esos criterios.\n";
    }

    // Espera a que el usuario presione Enter para continuar
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
// Función para visualizar todas las solicitudes de eventos
void verSolicitudesDeEvento() {
    // Verifica si hay solicitudes de eventos para mostrar
    if (solicitudesEventos.empty()) {
        cout << "No hay solicitudes de eventos para mostrar.\n"; // Mensaje si la lista está vacía
    } else {
        // Si hay solicitudes, muestra cada una de ellas
        cout << "Listado de todas las solicitudes de eventos:\n";
        for (const auto& solicitud : solicitudesEventos) {
            // Mostrar los detalles de cada solicitud de evento
            cout << "\nSolicitud de Evento:\n";
            cout << "Nombre: " << solicitud.nombre << "\n";
            cout << "Descripcion: " << solicitud.descripcion << "\n";
            cout << "Fecha: " << solicitud.fecha << "\n";
            cout << "Lugar: " << solicitud.lugar << "\n";
            cout << "Hora: " << solicitud.hora << "\n";
            cout << "Cantidad de Personas: " << solicitud.cantidadPersonas << "\n";
            cout << "Estado: " << solicitud.estado << "\n";
        }
    }

    // Espera que el usuario presione Enter para continuar
    cout << "\nPresione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada
    cin.get(); // Espera a que el usuario presione Enter
}
// Función para enviar una solicitud de creación de un nuevo evento
void enviarSolicitudEvento() {
    SolicitudEvento solicitud; // Crear una nueva instancia de SolicitudEvento

    // Limpiar el buffer de entrada para evitar tomar entradas previas
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese el nombre del evento o '0' para salir: ";
    getline(cin, solicitud.nombre); // Obtener el nombre del evento

    // Si el usuario ingresa '0', sale de la función
    if (solicitud.nombre == "0") {
        return;
    }

    // Verificar que se haya ingresado un nombre para el evento
    if (solicitud.nombre.empty()) {
        cout << "No se puede crear una solicitud sin un nombre de evento.\n";
    } else {
        // Si se ingresó un nombre, continúa pidiendo el resto de la información
        cout << "Ingrese la descripcion del evento: ";
        getline(cin, solicitud.descripcion); // Obtener la descripción del evento

        cout << "Ingrese la fecha del evento (formato YYYY-MM-DD): ";
        getline(cin, solicitud.fecha); // Obtener la fecha del evento

        cout << "Ingrese el lugar del evento: ";
        getline(cin, solicitud.lugar); // Obtener el lugar del evento

        cout << "Ingrese la hora del evento (formato HH:MM): ";
        getline(cin, solicitud.hora); // Obtener la hora del evento

        cout << "Ingrese la cantidad de personas esperadas: ";
        // Obtener la cantidad de personas y verificar si la entrada es válida
        if (!(cin >> solicitud.cantidadPersonas)) {
            cin.clear(); // Limpia el estado de error de cin
            cout << "Entrada invalida para la cantidad de personas.\n";
        } else {
            // Si la entrada es válida, establece el estado y añade la solicitud
            solicitud.estado = "Pendiente"; // Establecer el estado de la solicitud a "Pendiente"
            solicitudesEventos.push_back(solicitud); // Añadir la solicitud a la lista
            cout << "Solicitud de evento enviada para revision.\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    }

    // Espera que el usuario presione Enter para continuar
    cout << "Presione Enter para continuar...";
    cin.get();
}