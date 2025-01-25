#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "auxiliares.h"
#include "estructuras.h"
#include "lecturas.h"

using namespace std;


// fichero que guarda el registro de reglas aplicadas y pasos a seguir durante el encaminamiento hacia atrás
ofstream bitacora;
string tabulados;

void escribirRegla(const Regla& R){
    bitacora <<tabulados<< "Regla "  << R.id <<": Si "<<R.antecedentes[0];// Regla activa
    if(R.tipoRegla == TipoRegla::AND){
        bitacora<< " y " << R.antecedentes[1];
    }else if(R.tipoRegla == TipoRegla::OR){
        bitacora<< " o " << R.antecedentes[1];
    }
    bitacora<< " Entonces " << R.consecuente<<endl;
}

// Funciones para dar formato a la salida
void addTab(){
    tabulados += "\t";
}
void quitarTab(){
 if(!tabulados.empty())
    tabulados.erase(tabulados.size() - 1);
}

// Funciones auxiliares


double verificar(string meta, vector<Hecho>& baseHechos, const vector<Regla>& baseConocimientos) {
    double FCResultado = DEFAULT_FC;  // Variable para almacenar el resultado final de certeza
    Hecho HMeta;  // Objeto que almacenará la meta y su factor de certeza

    if (contenida(meta, baseHechos, HMeta)) {  // Si la meta ya está contenida en la base de hechos, devolver el factor de certeza correspondiente
        bitacora <<tabulados<< "Hecho inical: " << HMeta.id << " FC = "<< HMeta.factorCerteza<< endl;
        return HMeta.factorCerteza;
    }

    vector<Regla> CC = equiparar(baseConocimientos, meta);
    int nCC = 0;  // Variable para contar el número de antecedentes que tiene un consecuente necesaria para saber si aplicar el caso 2
    Regla R;
    string RAnterior;
    while (!vacio(CC)) {
        // Contar los antecedentes
        nCC++;
        if(nCC == 2) // Almacenamos la regla anterior para darle formato a la salida
            RAnterior=R.id;
        // Resolver la regla y eliminarla de la lista de antecedentes
        R = resolver(CC);
        escribirRegla(CC.back()); //Escribir la regla en la salida
        eliminar(CC);
        addTab();
        // Extraer nuevas metas de la regla resuelta
        vector<string> NuevasMetas = extraerAntecedentes(R);

        // Verificar la primera nueva meta y obtener su factor de certeza
        double  FCVerificado = verificar(seleccionarMeta(NuevasMetas), baseHechos, baseConocimientos);
        eliminar(NuevasMetas);

        // Si hay más de una nueva meta aplicamos el caso 1
        while (!vacio(NuevasMetas)) {
            string Nmet = seleccionarMeta(NuevasMetas);
            eliminar(NuevasMetas);
            caso1(R, Nmet, FCVerificado, verificar(Nmet, baseHechos, baseConocimientos));
            bitacora <<tabulados<< "Caso 1: FC = " << FCVerificado<< endl;
        }

        // Siempre se aplica el caso 3 al finalizar el procesamiento de metas
        caso3(R, FCVerificado);
        bitacora <<tabulados<< "Caso 3: FC = " << FCVerificado<<endl;

        // Si la meta tiene más de un antecedente, aplicar el caso 2
        quitarTab(); // Dar formato a la salida
        if (nCC > 1) {
            caso2(FCVerificado, FCResultado);
            bitacora <<tabulados<< "Caso 2: entre "<<RAnterior<< " y "<<R.id<<" FC = " << FCResultado<< endl;
            RAnterior +=R.id; // creamos un id para el resultado de aplicar el caso 2, por si lo tenemos que aplicar otra vez
        } else {
            FCResultado = FCVerificado;
        }
    }

    bitacora <<tabulados<<"Hecho: " <<meta <<" FC = " << FCResultado<<" almacenado en la base de hechos"<<endl;
    // Al final, almacenar el resultado en la base de hechos
    HMeta.id = meta;
    HMeta.factorCerteza = FCResultado;
    baseHechos.push_back(HMeta);

    // Retornar el factor de certeza calculado
    return FCResultado;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Error de argumentos, uso correcto: <ficheroBC> <ficheroBH1> [<ficheroBH2> ... <ficheroBHn>]" << endl;
        return 1;
    }

    // Argumento de entrada para la base de conocimientos
    string archivoBC = argv[1];
    
    // Lectura de la base de conocimientos
    vector<Regla> baseConocimientos = leerBC(archivoBC);

    // Procesar cada base de hechos proporcionada como argumento
    for (int i = 2; i < argc; ++i) {
        string archivoBH = argv[i];
        
        string objetivo;
        vector<Hecho> baseHechos;
        leerBH(archivoBH, baseHechos, objetivo);

        // Crear un nombre único para la bitácora de cada base de hechos
        string nombreBitacora = getNombreBitacora(archivoBC, archivoBH);
        bitacora.open(nombreBitacora);

        if (!bitacora.is_open()) {
            cerr << "Error al abrir la bitácora para el archivo: " << archivoBH << endl;
            continue;
        }

        // Escribir datos en la bitácora
        bitacora << "Nombre base de conocimientos: " << archivoBC << endl
                 << "Nombre base de hechos: " << archivoBH << endl
                 << "Con objetivo: " << objetivo << endl << endl;

        // Verificación y cálculo del factor de certeza
        double FCObjetivo = verificar(objetivo, baseHechos, baseConocimientos);
        bitacora << endl << "Conclusión: " << analizarResultado(FCObjetivo, objetivo);
        bitacora.close();
        
        cout << "Procesamiento de " << archivoBH << " completado. Bitácora creada: " << nombreBitacora << endl;
    }

    return 0;
}
