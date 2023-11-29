// Función para iniciar sesión como administrador o usuario
bool iniciarSesion(bool esAdmin) {
    string username, password;

    // Pedir al usuario su nombre de usuario y contraseña
    cout << "Ingrese su nombre de usuario o '0' para regresar: ";
    cin >> username;

    // Opción para regresar al menú anterior
    if (username == "0") {
        return false;
    }

    cout << "Ingrese su contraseña: ";
    cin >> password;

    // Seleccionar la lista de usuarios o administradores según el tipo de inicio de sesión
    vector<Usuario>& listaUsuarios = esAdmin ? administradores : usuarios;

    // Verificar si el usuario y contraseña coinciden con algún registro
    for (const Usuario& u : listaUsuarios) {
        if (u.username == username && u.password == password) {
            usuarioActual = username;
            cout << "Inicio de sesión exitoso. Presione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            return true;
        }
    }

    // Si no se encuentra el usuario o la contraseña es incorrecta, mostrar un mensaje de error
    cout << "Error: Usuario no registrado o usuario/contraseña incorrectos.\n";
    cout << "Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return false;
}
