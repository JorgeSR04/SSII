1. auxiliares
Incluye funciones auxiliares que se utilizan para manipular las reglas, metas y hechos durante el proceso de 
inferencia. Esto abarca la verificación de la presencia de un hecho en la base de hechos, la extracción de
 antecedentes de las reglas y la aplicación de diferentes casos de inferencia.

2. estructuras
Define las estructuras de datos fundamentales:

Regla: Representa una regla de inferencia que incluye antecedentes, consecuente, tipo de regla y factor de 
certeza.
Hecho: Representa un hecho con su identificador y factor de certeza. También incluye un enum para los tipos
de reglas (AND, OR, NOT) y constantes relacionadas con el factor de certeza.

3. lecturas
Ofrece funciones para leer los archivos de entrada:
leerBC: Lee la base de conocimientos (archivo de reglas).
leerBH: Lee la base de hechos (archivo de hechos).

getNombreBitacora: Genera el nombre de la bitácora a partir de los nombres de los archivos de entrada.

4. SBR_FC
Contiene la lógica principal del programa. Se encarga de leer los archivos de entrada (base de conocimientos 
y base de hechos), realizar la inferencia utilizando el enfoque de encaminamiento hacia atrás y generar 
bitácoras de ejecución que registran las reglas aplicadas y los resultados.