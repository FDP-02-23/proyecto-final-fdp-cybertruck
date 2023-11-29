// menuUsuario.h

#ifndef MENU_USUARIO_H //condicion de preprocesador que verifica si INSCRIBIRSE_EN_EVENTO_H no ha sido definido anteriormente
#define MENU_USUARIO_H //Si INSCRIBIRSE_EN_EVENTO_H no esta definido, esta línea lo define

#include <iostream>
#include "estructuras.h"  // Asumiendo que las estructuras están en este archivo

using namespace std;

// La funcion menuUsuario proporciona la interfaz de menu para los usuarios regulares.
// Permite al usuario realizar varias acciones como ver eventos, inscribirse en eventos,
// enviar solicitudes de eventos, y ver sus eventos inscritos.
void menuUsuario(vector<Evento>& eventos, string& usuarioActual) {
    int opcion;
    do {
        // Presenta opciones del menu
        cout << "--------------------------------------------------\n";
        cout << " Bienvenido al menu de usuario, " << usuarioActual << "\n";
        cout << "--------------------------------------------------\n";
        cout << "* 1. Ver eventos                                 *\n";
        cout << "* 2. Buscar evento por similitud                 *\n";
        cout << "* 3. Inscribirse en un evento                    *\n";
        cout << "* 4. Ver eventos inscritos                       *\n";
        cout << "* 5. Enviar solicitud de evento                  *\n";
        cout << "* 6. Ver solicitudes de evento                   *\n";      
        cout << "* 0. Salir al menu principal                     *\n";
        cout << "--------------------------------------------------\n";
        cout << " Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                mostrarEventos(eventos);
                break;
            case 2:
                buscarEventosPorSimilitud(eventos);
                break;
            case 3:
                inscribirseEnEvento(eventos, usuarioActual);
                break;
            case 4:
                verEventosInscritos(eventos, usuarioActual);
                break;
            case 5:
                enviarSolicitudEvento();
                break;
            case 6:
                verSolicitudesDeEvento();
                break;
            case 0:
                return; // Regresa al menu principal
            default:
                cout << "Opcion no valida.\n";
                cout << "Presione Enter para continuar...";
                cin.get();
        }
    } while (true);
}

#endif // MENU_USUARIO_H