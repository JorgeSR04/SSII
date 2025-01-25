#include "lecturas.h"

vector<Regla> leerBC(const string& nombreFichero)
{
    vector<Regla> reglas;
    ifstream archivo(nombreFichero);

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreFichero << endl;
        return reglas;
    }

    int numeroReglas;
    archivo >> numeroReglas;

    string linea;
    getline(archivo,linea); // linea vacia

    while(getline(archivo,linea))
    {
        if(linea != "")
        {
            istringstream lineaRegla(linea);
            Regla regla;
            // en un principio partimos de la base de que hay un solo antecedente hasta que nos cruzemos una disyunción/conjunción
            regla.tipoRegla = TipoRegla::NOT;


            getline(lineaRegla, regla.id, ':');

            string h;
            // por cada espacio que se encuentre hasta entonces, ve si es un antecedente, un enlace o debe omitirlo
            while(getline(lineaRegla >> ws, h, ' ') && h != "Entonces")
            {
                if(h != "Si" && h != "o" && h != "y")
                {
                    regla.antecedentes.push_back(h);
                }else
                {
                    if(h == "o")
                    {
                        regla.tipoRegla = TipoRegla::OR;
                    }else if(h == "y")
                    {
                        regla.tipoRegla = TipoRegla::AND;
                    }
                }
            }
            getline(lineaRegla, regla.consecuente, ',');
            lineaRegla.ignore(4);
            lineaRegla >> regla.factorCerteza;
            reglas.push_back(regla);
        }

    }
    return reglas;
}


void leerBH(const string& BH, vector<Hecho> &hechos, string &objetivo)
{
    ifstream archivoBH(BH);

    int numeroHechos;
    archivoBH >> numeroHechos;

    string linea;
    getline(archivoBH,linea);
    while(numeroHechos)
    {
        getline(archivoBH,linea);
        istringstream lineaHecho(linea);
        Hecho hecho;
        string certeza;
        getline(lineaHecho,hecho.id,',');
        lineaHecho.ignore(4);
        getline(lineaHecho,certeza,'\n');
        hecho.factorCerteza = stod(certeza);
        hechos.push_back(hecho);
        numeroHechos--;
    }
    getline(archivoBH,linea);
    archivoBH >> objetivo;

}

string getNombreBitacora(string BC, string BH)
{
   // Obtener nombres de los archivos sin la ruta
    regex patron(R"([^\\/]+$)"), exp(R"((.*?)(\.[^\.]+)?)");
    smatch coincidenciaBC, coincidenciaBH, match1, match2;
    regex_search(BC, coincidenciaBC, patron);
    regex_search(BH, coincidenciaBH, patron);
    string fileNameBC = coincidenciaBC[0].str();
    string fileNameBH = coincidenciaBH[0].str();
    regex_match(fileNameBC, match1, exp);
    regex_match(fileNameBH, match2, exp);
    // Generar nombre de la bitácora
    return "Ejecucion-" + match1[1].str() + "-" +  match2[1].str() + ".txt";
}
