#include "auxiliares.h"
#include <cmath> // Max() y Min()


bool vacio(const vector<Regla>& CC) {
    return CC.empty();
}

bool vacio(const vector<string>& NuevasMetas) {
    return NuevasMetas.empty();
}

Regla resolver(const vector<Regla>& CC) {
    return CC.back();
}

void eliminar(vector<Regla>& CC) {
    CC.pop_back();
}

void eliminar(vector<string> &NuevasMetas){
    NuevasMetas.pop_back();
}


vector<string> extraerAntecedentes(const Regla& R) {
    return R.antecedentes;
}

string seleccionarMeta(const vector<string>& NuevasMetas) {
    return NuevasMetas.back();
}

// Verificar si un hecho está contenido en la base de hechos
bool contenida(const string& meta, const vector<Hecho>& baseHechos, Hecho& HMeta) {
    for ( auto& hecho : baseHechos) {
        if (hecho.id == meta) {
            HMeta = hecho;
            return true;
        }
    }
    return false;
}

// Equiparar reglas con la meta
vector<Regla> equiparar(const vector<Regla>& baseConocimientos, const string& Meta) {
    vector<Regla> CC;
    for (const auto& regla : baseConocimientos) {
        if (regla.consecuente == Meta) {
            CC.push_back(regla);
        }
    }
    return CC;
}
void caso1(const Regla& R,const string& Nmet, double& FClocal, double FCVerificado){
    if (R.tipoRegla == AND) {
        FClocal = min(FClocal, FCVerificado);
    } else if (R.tipoRegla == OR) {
        FClocal = max(FClocal, FCVerificado);
    }
}
void caso2(const double FCVerificado, double& FCResultado){

    if (FCResultado >= 0 && FCVerificado >= 0) {
        FCResultado = round((FCResultado + FCVerificado * (1 - FCResultado)) * FACTOR_PRECISION) / FACTOR_PRECISION;
    } else if (FCResultado <= 0 && FCVerificado <= 0) {
        FCResultado = round((FCResultado + FCVerificado * (1 + FCResultado)) * FACTOR_PRECISION) / FACTOR_PRECISION;
    } else {
        double denominador = 1 - min(abs(FCResultado), abs(FCVerificado));
        if(denominador == 0){ // Comprobamos que el denominador no sea 0
            FCResultado = 0;
            return;
        }
        FCResultado = round(((FCResultado + FCVerificado) / denominador) * FACTOR_PRECISION) / FACTOR_PRECISION;
    }
}
void caso3(const Regla& R, double& FClocal){
    FClocal = round(R.factorCerteza * max(0.0, FClocal) * FACTOR_PRECISION) / FACTOR_PRECISION;
}

string analizarResultado(double FC, const string& objetivo) {
    string resultado;

    if (FC >= 0.9 && FC <= 1) {
        resultado = "Hay casi total seguridad de que el hecho " + objetivo + " sea cierto";
    }
    if (FC >= 0.75 && FC < 0.9) {
        resultado = "Hay una alta probabilidad de que el hecho " + objetivo + " sea cierto";
    }
    else if (FC >= 0.5 && FC < 0.75) {
        resultado = "Es probable que el hecho " + objetivo + " sea cierto";
    }
    else if (FC >= 0.25 && FC < 0.5) {
        resultado = "Es poco probable que el hecho " + objetivo + " sea cierto";
    }
    else if (FC >= 0.0 && FC < 0.25) {
        resultado = "Es muy poco probable que el hecho " + objetivo + " sea cierto";
    }
    else if (FC == 0) {
        resultado = "Indeterminado, no se tiene certeza sobre el hecho " + objetivo;
    }
    else if (FC > -0.25 && FC < 0) {
       resultado = "Es muy poco probable que el hecho " + objetivo + " no suceda";
    }
    else if (FC > -0.5 && FC < 0) {
        resultado = "Es poco probable que el hecho " + objetivo + " no suceda";
    }
    else if (FC <= -0.75 && FC > -0.9) {
        resultado = "Es probable que el hecho " + objetivo + " no suceda";
    }
    else if (FC <= -0.9 && FC > -1) {
         resultado = "Hay casi total seguridad de que el hecho " + objetivo + " no suceda";
    }
    else {
        resultado = "Valor fuera del rango esperado";
    }

   return resultado;
}
