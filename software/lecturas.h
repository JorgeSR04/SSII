#ifndef LECTURAS_H
#define LECTURAS_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>
#include "estructuras.h"

vector<Regla> leerBC(const string& nombreFichero);

void leerBH(const string& BH, vector<Hecho> &hechos, string &objetivo);

string getNombreBitacora(string BC, string BH);


#endif // LECTURAS_H
