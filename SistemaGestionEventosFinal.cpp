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

    string busqueda; // Almacena el termino de busqueda
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

// Función para revisar y gestionar las solicitudes de eventos
void revisarSolicitudesEventos() {
    // Verifica si hay solicitudes de eventos pendientes
    if (solicitudesEventos.empty()) {
        cout << "No hay solicitudes de eventos pendientes.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la función si no hay solicitudes
    }

    cout << "Revisando solicitudes de eventos...\n";
    // Recorre la lista de solicitudes de eventos
    for (auto& solicitud : solicitudesEventos) {
        // Procesa solo las solicitudes con estado "Pendiente"
        if (solicitud.estado == "Pendiente") {
            // Muestra los detalles de la solicitud pendiente
            cout << "\nSolicitud de Evento:\n";
            cout << "Nombre: " << solicitud.nombre << "\n";
            cout << "Descripcion: " << solicitud.descripcion << "\n";
            cout << "Fecha: " << solicitud.fecha << "\n";
            cout << "Lugar: " << solicitud.lugar << "\n";
            cout << "Hora: " << solicitud.hora << "\n";
            cout << "Cantidad de Personas: " << solicitud.cantidadPersonas << "\n";
            cout << "Estado actual: " << solicitud.estado << "\n";

            // Pide al usuario que acepte o rechace la solicitud
            cout << "Ingrese '0' para salir o:\n";
            cout << "¿Desea aceptar este evento? (s/n): ";
            char respuesta;
            cin >> respuesta;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada

            // Gestiona la respuesta del usuario
            if (respuesta == '0') {
                cout << "Saliendo de la revision de solicitudes.\n";
                return; // Sale de la función completamente
            } else if (respuesta == 's' || respuesta == 'S') {
                // Si se acepta la solicitud, crea un nuevo evento
                Evento nuevoEvento = {
                    solicitud.nombre,
                    solicitud.descripcion,
                    solicitud.fecha,
                    solicitud.lugar,
                    solicitud.hora,
                    solicitud.cantidadPersonas,
                    {}, // Lista de inscritos inicialmente vacía
                    "Activo" // Estado del evento
                };
                eventos.push_back(nuevoEvento); // Agrega el evento a la lista
                solicitud.estado = "Aceptado"; // Actualiza el estado de la solicitud
                cout << "Evento aceptado y agregado a la lista de eventos.\n";
            } else {
                // Si se rechaza la solicitud, actualiza su estado
                solicitud.estado = "Rechazado";
                cout << "Evento rechazado.\n";
            }
            cout << "Presione Enter para continuar...";
            cin.get(); // Espera a que el usuario presione Enter
        }
    }
}
// Función para que los usuarios se inscriban en un evento
void inscribirseEnEvento() {
    // Verifica si hay eventos disponibles
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para inscribirse.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la función si no hay eventos
    }

    int opcion;
    // Presenta opciones para buscar un evento
    cout << "Como desea buscar el evento para inscribirse?\n";
    cout << "1. Listar todos los eventos\n";
    cout << "2. Buscar evento por similitud\n";
    cout << "0. Salir\n"; // Opción para salir
    cout << "Seleccione una opcion o '0' para salir: ";
    cin >> opcion;

    // Si el usuario elige salir, termina la función
    if (opcion == 0) {
        return;
    }

    vector<Evento*> eventosEncontrados; // Vector para almacenar eventos encontrados
    switch (opcion) {
        case 1:
            // Lista todos los eventos disponibles
            for (Evento& e : eventos) {
                eventosEncontrados.push_back(&e);
            }
            break;
        case 2:
            // Busca eventos por similitud
            eventosEncontrados = ObtenerEventosPorSimilitud();
            break;
        default:
            cout << "Opcion no valida.\n";
            return;
    }

    // Verifica si se encontraron eventos
    if (eventosEncontrados.empty()) {
        cout << "No se encontraron eventos.\n";
        return;
    }

    // Presenta los eventos encontrados al usuario
    cout << "Seleccione el numero del evento al que desea inscribirse o '0' para salir:\n";
    for (int i = 0; i < eventosEncontrados.size(); ++i) {
        cout << i + 1 << ". " << eventosEncontrados[i]->nombre << "\n";
    }
    cout << "0. Salir\n";

    int numEvento;
    cin >> numEvento; // Recoge la elección del usuario

    // Gestiona la elección del usuario
    if (numEvento == 0) {
        return; // Sale si el usuario elige '0'
    } else if (numEvento < 1 || numEvento > eventosEncontrados.size()) {
        cout << "Numero de evento no valido.\n";
        return;
    }

    // Obtiene el evento seleccionado
    Evento* eventoSeleccionado = eventosEncontrados[numEvento - 1];
    // Verifica si el usuario ya está inscrito en el evento
    if (find(eventoSeleccionado->inscritos.begin(), eventoSeleccionado->inscritos.end(), usuarioActual) != eventoSeleccionado->inscritos.end()) {
        cout << "Ya estas inscrito en este evento.\n";
    } else {
        // Si no está inscrito, lo añade a la lista de inscritos
        eventoSeleccionado->inscritos.push_back(usuarioActual);
        cout << "Inscripcion exitosa en el evento: " << eventoSeleccionado->nombre << "\n";
        cout << "Total de personas inscritas ahora: " << eventoSeleccionado->inscritos.size() << "\n";
    }

    // Espera a que el usuario presione Enter para continuar
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para mostrar los usuarios inscritos en un evento específico
void mostrarInscritosEnEvento() {
    // Verifica si hay eventos disponibles
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la función si no hay eventos
    }

    // Presenta los eventos disponibles y pide al usuario que seleccione uno
    cout << "Seleccione el numero del evento para ver los inscritos o '0' para salir:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << endl;
    }
    cout << "0. Salir\n";

    int numEvento;
    cin >> numEvento; // Recoge la selección del usuario
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada

    // Gestiona la opción de salida
    if (numEvento == 0) {
        return; // Sale de la función si el usuario elige '0'
    }

    // Valida la elección del usuario
    if (numEvento < 1 || numEvento > eventos.size()) {
        cout << "Numero de evento no valido.\n";
    } else {
        // Muestra los usuarios inscritos en el evento seleccionado
        const Evento& eventoSeleccionado = eventos[numEvento - 1];
        cout << "Personas inscritas en el evento '" << eventoSeleccionado.nombre << "':\n";
        // Verifica si hay usuarios inscritos en el evento
        if (eventoSeleccionado.inscritos.empty()) {
            cout << "No hay personas inscritas en este evento.\n";
        } else {
            // Lista los nombres de los usuarios inscritos
            for (const string& inscrito : eventoSeleccionado.inscritos) {
                cout << "- " << inscrito << endl;
            }
        }
    }

    // Espera a que el usuario presione Enter para continuar
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Funcion para registrar un usuario. Recibe un booleano 'esAdmin' para determinar si el registro es para un administrador.
void registrarUsuario(bool esAdmin) {
    string username, password;

    // Verificacion de contrasena para registrar administradores
    if (esAdmin) {
        string adminPassword;
        cout << "Ingrese la contrasena de administrador o '0' para salir: ";
        cin >> adminPassword;
        // Si el administrador ingresa '0', se sale de la función.
        if (adminPassword == "0") {
            return; // Regresa al menu anterior si el usuario ingresa '0'
        }
        if (adminPassword != "3435") {
            cout << "Contrasena incorrecta. No se puede registrar como administrador.\n";
            cout << "Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }
    }
  // Pedir al usuario que ingrese un nuevo nombre de usuario o '0' para salir.
    cout << "Ingrese su nuevo nombre de usuario o '0' para salir: ";
    cin >> username;
    if (username == "0") {
        return; // Regresa al menu anterior si el usuario ingresa '0'
    }

    // Verificar si el nombre de usuario ya existe
    vector<Usuario>& listaUsuarios = esAdmin ? administradores : usuarios;
    for (const Usuario& u : listaUsuarios) {
        if (u.username == username) {
            cout << "Error: El nombre de usuario ya esta en uso.\n";
            cout << "Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return;
        }
    }
// Pedir al usuario que ingrese una nueva contraseña.
    cout << "Ingrese su nueva contrasena: ";
    cin >> password;

    Usuario nuevoUsuario = {username, password};
    listaUsuarios.push_back(nuevoUsuario);

// Mostrar un mensaje de exito y pedir al usuario que presione Enter para continuar.
    cout << (esAdmin ? "Administrador" : "Usuario") << " registrado con exito.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para crear un evento.
void crearEvento() {
    Evento e;

    // Pedir al usuario ingresar el nombre del evento. '0' para salir.
    cout << "Ingrese el nombre del evento o '0' para salir: ";
    cin.ignore(); // Ignora el último salto de línea que quedó en el buffer de entrada.
    getline(cin, e.nombre); // Obtiene la línea completa como nombre del evento.
    if (e.nombre == "0") {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    // Pedir al usuario ingresar la descripción del evento. '0' para salir.
    cout << "Ingrese la descripcion del evento o '0' para salir: ";
    getline(cin, e.descripcion); // Obtiene la línea completa como descripción del evento.
    if (e.descripcion == "0") {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    // Pedir al usuario ingresar la fecha del evento. '0' para salir.
    cout << "Ingrese la fecha del evento o '0' para salir: ";
    getline(cin, e.fecha); // Obtiene la línea completa como fecha del evento.
    if (e.fecha == "0") {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    // Pedir al usuario ingresar el lugar del evento. '0' para salir.
    cout << "Ingrese el lugar del evento o '0' para salir: ";
    getline(cin, e.lugar); // Obtiene la línea completa como lugar del evento.
    if (e.lugar == "0") {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    // Pedir al usuario ingresar la hora del evento. '0' para salir.
    cout << "Ingrese la hora del evento o '0' para salir: ";
    getline(cin, e.hora); // Obtiene la línea completa como hora del evento.
    if (e.hora == "0") {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    // Pedir al usuario ingresar la cantidad de personas. '0' para salir.
    cout << "Ingrese la cantidad de personas o '0' para salir: ";
    if (!(cin >> e.cantidadPersonas)) { // Intenta leer un valor numérico.
        cin.clear(); // Limpia el estado de error de cin en caso de entrada no numérica.
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el resto de la línea.
        return; // Si la entrada no es numérica, sale de la función.
    }
    if (e.cantidadPersonas == 0) {
        return; // Si el usuario ingresa '0', sale de la función.
    }

    cin.ignore(); // Limpia de entrada después de leer un numero.

    // Añade el evento creado a la lista de eventos.
    eventos.push_back(e);

    // Muestra un mensaje de éxito y espera que el usuario presione Enter para continuar.
    cout << "Evento creado exitosamente. Presione Enter para continuar...";
    cin.get();
}

// Función para eliminar un participante de un evento.
void eliminarParticipante() {
    // Verifica si la lista de eventos esta vacía.
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si no hay eventos.
    }

    mostrarEventos(); // Muestra la lista de eventos disponibles.

    // Pide al usuario elegir un evento.
    cout << "Ingrese el numero del evento del cual desea eliminar un participante o '0' para salir: ";
    int numEvento;
    cin >> numEvento;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia el buffer de entrada.

    // Opción de salida.
    if (numEvento == 0) {
        return; // Sale de la función si el usuario ingresa '0'.
    }

    // Verifica si el numero de evento es válido.
    if (numEvento < 1 || numEvento > eventos.size()) {
        cout << "Numero de evento no valido.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si el numero del evento no es válido.
    }

    // Selecciona el evento elegido por el usuario.
    Evento& eventoSeleccionado = eventos[numEvento - 1];

    // Verifica si hay participantes inscritos en el evento.
    if (eventoSeleccionado.inscritos.empty()) {
        cout << "No hay participantes inscritos en este evento.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si no hay participantes.
    }

    // Muestra los participantes inscritos en el evento.
    cout << "Participantes inscritos en el evento:\n";
    for (int i = 0; i < eventoSeleccionado.inscritos.size(); ++i) {
        cout << i + 1 << ". " << eventoSeleccionado.inscritos[i] << endl;
    }

    // Pide al usuario elegir un participante para eliminar.
    cout << "Ingrese el numero del participante que desea eliminar o '0' para salir: ";
    int numParticipante;
    cin >> numParticipante;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiesa de entrada.

    // Opción de salida.
    if (numParticipante == 0) {
        return; // Sale de la función si el usuario ingresa '0'.
    }

    // Verifica si el número del participante es valido.
    if (numParticipante < 1 || numParticipante > eventoSeleccionado.inscritos.size()) {
        cout << "Numero de participante no valido.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si el número del participante no es válido.
    }

    // Elimina al participante seleccionado de la lista de inscritos.
    eventoSeleccionado.inscritos.erase(eventoSeleccionado.inscritos.begin() + numParticipante - 1);
    cout << "Participante eliminado exitosamente.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para mostrar los eventos disponibles.
void mostrarEventos() {
    // Verifica si la lista de eventos esta vacía.
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n"; // Informa al usuario si no hay eventos.
    } else {
        // Si hay eventos, los recorre y muestra su informacion.
        for (int i = 0; i < eventos.size(); i++) {
            cout << "Evento " << i + 1 << ":\n"; // Muestra el número del evento.
            cout << "Nombre: " << eventos[i].nombre << endl; // Muestra el nombre del evento.
            cout << "Descripcion: " << eventos[i].descripcion << endl; // Muestra la descripción del evento.
            cout << "Fecha: " << eventos[i].fecha << endl; // Muestra la fecha del evento.
            cout << "Lugar: " << eventos[i].lugar << endl; // Muestra el lugar del evento.
            cout << "Hora: " << eventos[i].hora << endl; // Muestra la hora del evento.
            cout << "Cantidad de Personas: " << eventos[i].cantidadPersonas << endl; // Muestra la cantidad de personas permitidas en el evento.
            cout << "Personas Inscritas: " << eventos[i].inscritos.size() << endl; // Muestra el numero actual de personas inscritas.
            cout << endl; // Línea en blanco para separar eventos.
        }
    }
    // Solicita al usuario presionar Enter para continuar.
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora cualquier entrada previa.
    cin.get(); // Espera a que el usuario presione Enter.
}

// Funcion para guardar los eventos en un archivo.
void guardarEventosEnArchivo() {
    // Crea un objeto ofstream para escribir en un archivo.
    ofstream archivo("eventos.txt");

    // Verifica si el archivo se abrio correctamente.
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para escribir.\n"; // Informa al usuario si hay un error al abrir el archivo.
        return; // Sale de la funcion si no se puede abrir el archivo.
    }

    // Recorre la lista de eventos.
    for (const Evento& e : eventos) {
        // Escribe la información del evento en el archivo, separada por líneas.
        archivo << "---------------------------------------------------\n";
        archivo << "Nombre: " << e.nombre << "\n";
        archivo << "Descripcion: " << e.descripcion << "\n";
        archivo << "Fecha: " << e.fecha << "\n";
        archivo << "Lugar: " << e.lugar << "\n";
        archivo << "Hora: " << e.hora << "\n";
        archivo << "Cantidad de Personas: " << e.cantidadPersonas << "\n";
        archivo << "---------------------------------------------------\n";
    }

    // Cierra el archivo después de escribir toda la información.
    archivo.close();

    // Informa al usuario que los eventos han sido guardados y espera una tecla para continuar.
    cout << "Eventos guardados en 'eventos.txt'.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiesa de entrada.
    cin.get(); // Espera que el usuario presione Enter.
}

// Funcion para modificar un evento existente.
void modificarEvento() {
    // Verifica si la lista de eventos esta vacia.
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para modificar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si no hay eventos.
    }

    // Muestra los eventos disponibles para modificar.
    cout << "Eventos disponibles:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << " - " << eventos[i].fecha << "\n";
    }
    cout << "0. Salir sin modificar\n";

    // Pide al usuario elegir un evento para modificar.
    int eleccion;
    cout << "Seleccione el numero del evento que desea modificar o '0' para salir: ";
    cin >> eleccion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Verifica la eleccion del usuario.
    if (eleccion == 0) {
        return; // Sale de la funcion si el usuario elige '0'.
    } else if (eleccion < 1 || eleccion > eventos.size()) {
        cout << "Eleccion no valida.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return; // Sale de la funcion si la eleccion es invalida.
    }

    // Selecciona el evento a modificar.
    Evento& eventoSeleccionado = eventos[eleccion - 1];

    // Muestra las opciones de modificacion.
    cout << "------------------------------------------------\n";
    cout << "Que desea modificar del evento '" << eventoSeleccionado.nombre << "'?\n";
    cout << "* 1. Nombre                                    *\n";
    cout << "* 2. Descripcion                               *\n";
    cout << "* 3. Fecha                                     *\n";
    cout << "* 4. Lugar                                     *\n";
    cout << "* 5. Hora                                      *\n";
    cout << "* 6. Cantidad de Personas                      *\n";
    cout << "------------------------------------------------\n";
    cout << "Ingrese su elección: ";
    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Modifica el evento segun la opcion seleccionada.
    switch (opcion) {
        case 1:
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, eventoSeleccionado.nombre);
            break;
        case 2:
            cout << "Ingrese la nueva descripcion: ";
            getline(cin, eventoSeleccionado.descripcion);
            break;
        case 3:
            cout << "Ingrese la nueva fecha: ";
            getline(cin, eventoSeleccionado.fecha);
            break;
        case 4:
            cout << "Ingrese el nuevo lugar: ";
            getline(cin, eventoSeleccionado.lugar);
            break;
        case 5:
            cout << "Ingrese la nueva hora: ";
            getline(cin, eventoSeleccionado.hora);
            break;
        case 6:
            cout << "Ingrese la nueva cantidad de personas: ";
            cin >> eventoSeleccionado.cantidadPersonas;
            cin.ignore();
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
    }

    // Confirma la modificacion si se eligio una opcion valida.
    if (opcion >= 1 && opcion <= 6) {
        cout << "Evento modificado exitosamente.\n";
    }

    // Espera a que el usuario presione Enter para continuar.
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para mostrar los eventos en los que el usuario actual está inscrito.
void verEventosInscritos() {
    cout << "Eventos en los que estás inscrito:\n";
    bool inscritoEnAlgunEvento = false;

    // Recorre todos los eventos para verificar si el usuario actual está inscrito.
    for (const Evento& e : eventos) {
        // Comprueba si el usuario está inscrito en el evento.
        if (find(e.inscritos.begin(), e.inscritos.end(), usuarioActual) != e.inscritos.end()) {
            // Muestra la información del evento.
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

    // Si el usuario no está inscrito en ningun evento, muestra un mensaje.
    if (!inscritoEnAlgunEvento) {
        cout << "No estas inscrito en ningun evento.\n";
    }

    // Espera a que el usuario presione Enter para continuar.
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Función para eliminar un evento de la lista de eventos disponibles.
void eliminarEvento() {
    // Verifica si hay eventos disponibles para eliminar.
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para eliminar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // Muestra los eventos disponibles para eliminar.
    cout << "Eventos disponibles para eliminar:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << "\n";
    }
    cout << "0. Salir sin eliminar\n";

    // Pide al usuario seleccionar un evento para eliminar.
    cout << "Seleccione el numero del evento que desea eliminar o '0' para salir: ";
    int numeroEventoAEliminar;
    cin >> numeroEventoAEliminar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Verifica la seleccion del usuario.
    if (numeroEventoAEliminar == 0) {
        return; // Sale de la funcion si el usuario elige '0'.
    } else if (numeroEventoAEliminar < 1 || numeroEventoAEliminar > eventos.size()) {
        cout << "Numero de evento no valido.\n";
    } else {
        // Elimina el evento elegido de la lista.
        eventos.erase(eventos.begin() + numeroEventoAEliminar - 1);
        cout << "Evento eliminado exitosamente.\n";
    }

    // Espera a que el usuario presione Enter para continuar.
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Funcion para mostrar el menú de administrador y manejar las opciones seleccionadas.
void menuAdmin() {
    int opcion;
    do {
        limpiarPantalla(); // Limpia la pantalla para mostrar el menú.
        // Muestra las opciones del menu.
        cout << "------------------------------------------------\n";
        cout << "Bienvenido al menu de administrador, " << usuarioActual << "\n";
        cout << "------------------------------------------------\n";
        cout << "* 1. Crear evento                              *\n";
        cout << "* 2. Ver eventos                               *\n";
        cout << "* 3. Modificar evento                          *\n";
        cout << "* 4. Eliminar evento                           *\n";
        cout << "* 5. Guardar eventos en archivo                *\n";
        cout << "* 6. Mostrar personas inscritas en un evento   *\n";
        cout << "* 7. Eliminar participante                     *\n";
        cout << "* 8. Revisar solicitudes de evento             *\n";
        cout << "* 9. buscar Evento                             *\n";
        cout << "* 0. Salir al menu principal                   *\n";
        cout << "------------------------------------------------\n";
        cout << "  Seleccione una opcion: ";
        cin >> opcion; // Recibe la opción del usuario.
        limpiarPantalla(); // Limpia la pantalla tras la selección.

        // Ejecuta la acción correspondiente a la opción seleccionada.
        switch (opcion) {
            case 1:
                crearEvento(); // Crea un nuevo evento.
                break;
            case 2:
                mostrarEventos(); // Muestra los eventos existentes.
                break;
            case 3:
                modificarEvento(); // Modifica un evento existente.
                break;
            case 4:
                eliminarEvento(); // Elimina un evento.
                break;
            case 5:
                guardarEventosEnArchivo(); // Guarda los eventos en un archivo.
                break;
            case 6:
                mostrarInscritosEnEvento(); // Muestra los inscritos en un evento.
                break;
            case 7: 
                eliminarParticipante(); // Elimina un participante de un evento.
                break;
            case 8:
                revisarSolicitudesEventos(); // Revisa solicitudes para eventos.
                break;
            case 9:
                buscarEventosPorSimilitud(); // Busca eventos por similitud.
                break;
            case 0:
                return; // Regresa al menu principal.
            default:
                cout << "Opcion no valida.\n"; // Maneja opciones no validas.
                cout << "Presione Enter para continuar...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
        }
    } while (true); // El menu se ejecuta en un bucle hasta que el usuario decide salir.
}