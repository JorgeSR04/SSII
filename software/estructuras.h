#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <string>
#include <vector>

using namespace std;

const int DEFAULT_FC = 0;
const int FACTOR_PRECISION = 1000;

// Enum para los tipos de reglas
enum TipoRegla {AND, OR, NOT};

// Estructura para la regla
struct Regla {
    string id;                  // identificador de la regla
    vector<string> antecedentes; // lista de hip�tesis en la condici�n
    TipoRegla tipoRegla;         // tipo de regla
    string consecuente;          // hip�tesis de conclusi�n
    double factorCerteza;       // factor de certeza
};

// Estructura para los hechos
struct Hecho{
    string id;
    double factorCerteza;
};

#endif // ESTRUCTURAS_H
