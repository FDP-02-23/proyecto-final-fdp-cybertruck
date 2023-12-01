#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

struct Usuario {
    string username;
    string password;
};

struct SolicitudEvento {
    string nombre;
    string descripcion;
    string fecha;
    string lugar;
    string hora;
    int cantidadPersonas;
    string estado; 

};


struct Evento {
    string nombre;
    string descripcion;
    string fecha;
    string lugar;
    string hora; //  campo para la hora
    int cantidadPersonas; //  campo para la cantidad de personas
    vector<string> inscritos; // Lista de usuarios inscritos en el evento
     string estado;// Nuevo campo para el estado del evento

    
};