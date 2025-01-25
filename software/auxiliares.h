#ifndef FUNCIONES_AUXILIARES_H
#define FUNCIONES_AUXILIARES_H

#include <vector>
#include <string>
#include "estructuras.h"

bool vacio(const vector<Regla>& CC);
bool vacio(const vector<string>& NuevasMetas);
Regla resolver(const vector<Regla>& CC);
void eliminar(vector<Regla>& CC);
void eliminar(vector<string> &NuevasMetas);
vector<string> extraerAntecedentes(const Regla& R);
string seleccionarMeta(const vector<string>& NuevasMetas);
bool contenida(const string& meta, const vector<Hecho>& baseHechos, Hecho& HMeta);
vector<Regla> equiparar(const vector<Regla>& baseConocimientos, const string& Meta);
void caso1(const Regla& R,const string& Nmet, double& FClocal, double FCVerificado);
void caso2(const double FCVerificado, double& FCResultado);
void caso3(const Regla& R, double& FClocal);
string analizarResultado(double FC, const string& objetivo);

#endif // FUNCIONES_AUXILIARES_H
