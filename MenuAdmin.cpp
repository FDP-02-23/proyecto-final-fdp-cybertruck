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

// Funcion para eliminar un participante de un evento.
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

// Funcion para mostrar la informacion de los eventos disponibles.
void mostrarEventos() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n";
    } else {
        for (int i = 0; i < eventos.size(); i++) {
            cout << "Evento " << i + 1 << ":\n";
            cout << "Nombre: " << eventos[i].nombre << endl;
            cout << "Descripcion: " << eventos[i].descripcion << endl;
            cout << "Fecha: " << eventos[i].fecha << endl;
            cout << "Lugar: " << eventos[i].lugar << endl;
            cout << "Hora: " << eventos[i].hora << endl;
            cout << "Cantidad de Personas: " << eventos[i].cantidadPersonas << endl;
            cout << "Personas Inscritas: " << eventos[i].inscritos.size() << endl;
            cout << endl;
        }
    }
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Funcion para guardar la informacion de los eventos en un archivo de texto.
void guardarEventosEnArchivo() {
    // Abrir un archivo llamado 'eventos.txt' para escritura.
    ofstream archivo("eventos.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo para escribir.\n";
        return;
    } 
    // Iterar a traves de los eventos y escribir su informacion en el archivo.
    for (const Evento& e : eventos) {
        archivo << "---------------------------------------------------\n";
        archivo << "Nombre: " << e.nombre << "\n";
        archivo << "Descripcion: " << e.descripcion << "               \n";
        archivo << "Fecha: " << e.fecha << "                          \n";
        archivo << "Lugar: " << e.lugar << "                          \n";
        archivo << "Hora: " << e.hora << "                            \n";
        archivo << "Cantidad de Personas: " << e.cantidadPersonas << "\n";
        archivo << "---------------------------------------------------\n";
    }
    // Cerrar el archivo después de escribir los datos.
    archivo.close();
    cout << "Eventos guardados en 'eventos.txt'.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void modificarEvento() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para modificar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
    cout << "Eventos disponibles:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << " - " << eventos[i].fecha << "\n";
    }
    cout << "0. Salir sin modificar\n";
    int eleccion;
    cout << "Seleccione el numero del evento que desea modificar o '0' para salir: ";
    cin >> eleccion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (eleccion == 0) {
        return;
    } else if (eleccion < 1 || eleccion > eventos.size()) {
        cout << "Eleccion no valida.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

     // Mostrar las opciones de modificación disponibles.
    Evento& eventoSeleccionado = eventos[eleccion - 1];
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
    switch (opcion) {   // Realizar la modificacion segun la eleccion del usuario
        case 1: 
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, eventoSeleccionado.nombre);
            break;
        case 2:
            cout << "Ingrese la nueva descripción: ";
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
    if (opcion >= 1 && opcion <= 6) {
        cout << "Evento modificado exitosamente.\n";
    }
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}



// Funcion para modificar un evento existente.
void mostrarInscritosEnEvento() {
    // Verificar si hay eventos disponibles
    if (eventos.empty()) {
        cout << "No hay eventos disponibles.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    // Mostrar la lista de eventos disponibles.
    cout << "Seleccione el numero del evento para ver los inscritos o '0' para salir:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << endl;
    }
    cout << "0. Salir\n";

    int numEvento;
    cin >> numEvento;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Opción de salida
    if (numEvento == 0) {
        return;
    }

    // Validar la eleccion del evento
    if (numEvento < 1 || numEvento > eventos.size()) {
        cout << "Número de evento no válido.\n";
    } else {
        // Mostrar los inscritos en el evento seleccionado
        const Evento& eventoSeleccionado = eventos[numEvento - 1];
        cout << "Personas inscritas en el evento '" << eventoSeleccionado.nombre << "':\n";
        if (eventoSeleccionado.inscritos.empty()) {
            cout << "No hay personas inscritas en este evento.\n";
        } else {
            for (const string& inscrito : eventoSeleccionado.inscritos) {
                cout << "- " << inscrito << endl;
            }
        }
    }

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Funcion para buscar eventos por similitud en nombre, lugar o fecha.
void buscarEventosPorSimilitud() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para buscar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }
   // Mostrar opciones de busqueda.
    cout << "Buscar evento por:\n";
    cout << "1. Nombre\n";
    cout << "2. Lugar\n";
    cout << "3. Fecha\n";
    cout << "Seleccione una opcion: ";
    int opcion;
    cin >> opcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string busqueda;
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
            cout << "Opcion no valida.\n";
            return;
    }
    getline(cin, busqueda);

    bool encontrado = false;
    for (const Evento& e : eventos) {
        bool coincide = false;
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
// Mostrar informacion del evento encontrado.
        if (coincide) {
            cout << "* Evento encontrado:  *\n";
            cout << "* Nombre:  *" << e.nombre << "\n";
            cout << "* Descripcion: *" << e.descripcion << "\n";
            cout << "* Fecha:  *" << e.fecha << "\n";
            cout << "* Lugar:  *" << e.lugar << "\n";
            cout << "* Hora:  *" << e.hora << "\n";
            cout << "* Cantidad de Personas:  *" << e.cantidadPersonas << "\n";
            cout << "------------------------------\n";
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron eventos con esos criterios.\n";
    }

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


// Funcion para revisar y gestionar las solicitudes de eventos pendientes.
void revisarSolicitudesEventos() {
    if (solicitudesEventos.empty()) {
        cout << "No hay solicitudes de eventos pendientes.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    cout << "Revisando solicitudes de eventos...\n";
    for (auto& solicitud : solicitudesEventos) {
        if (solicitud.estado == "Pendiente") {
            cout << "\nSolicitud de Evento:\n";
            // Mostrar los detalles de la solicitud pendiente
            cout << "Nombre: " << solicitud.nombre << "\n";
            cout << "Descripcion: " << solicitud.descripcion << "\n";
            cout << "Fecha: " << solicitud.fecha << "\n";
            cout << "Lugar: " << solicitud.lugar << "\n";
            cout << "Hora: " << solicitud.hora << "\n";
            cout << "Cantidad de Personas: " << solicitud.cantidadPersonas << "\n";
            cout << "Estado actual: " << solicitud.estado << "\n";

            cout << "Ingrese '0' para salir o:\n";
            cout << "¿Desea aceptar este evento? (s/n): ";
            char respuesta;
            cin >> respuesta;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia la entrada

            if (respuesta == '0') {
                cout << "Saliendo de la revision de solicitudes.\n";
                return; // Sale de la funcion completamente
            } else if (respuesta == 's' || respuesta == 'S') {
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
                eventos.push_back(nuevoEvento); // Agregar el evento a la lista de eventos
                solicitud.estado = "Aceptado"; // Actualizar el estado de la solicitud
                cout << "Evento aceptado y agregado a la lista de eventos.\n";
            } else {
                solicitud.estado = "Rechazado"; // Actualizar el estado de la solicitud
                cout << "Evento rechazado.\n";
            }
            cout << "Presione Enter para continuar...";
            cin.get(); // Espera a que el usuario presione Enter
        }
    }
}



// Funcion para mostrar los eventos en los que el usuario actual esta inscrito.
void verEventosInscritos() {
    cout << "Eventos en los que estas inscrito:\n";
    bool inscritoEnAlgunEvento = false;
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
    if (!inscritoEnAlgunEvento) {
        cout << "No estas inscrito en ningun evento.\n";
    }
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Funcion para eliminar un evento de la lista de eventos
void eliminarEvento() {
    if (eventos.empty()) {
        cout << "No hay eventos disponibles para eliminar.\n";
        cout << "Presione Enter para continuar...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    cout << "Eventos disponibles para eliminar:\n";
    for (int i = 0; i < eventos.size(); i++) {
        cout << i + 1 << ". " << eventos[i].nombre << "\n";
    }
    cout << "0. Salir sin eliminar\n";

    cout << "Seleccione el numero del evento que desea eliminar o '0' para salir: ";
    int numeroEventoAEliminar;
    cin >> numeroEventoAEliminar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (numeroEventoAEliminar == 0) {
        return; // Salir si el usuario elige '0'
    } else if (numeroEventoAEliminar < 1 || numeroEventoAEliminar > eventos.size()) {
        cout << "Numero de evento no valido.\n";
    } else {
        // Restar 1 porque en C++ comienzan en 0.
        eventos.erase(eventos.begin() + numeroEventoAEliminar - 1);
        cout << "Evento eliminado exitosamente.\n";
    }

    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}