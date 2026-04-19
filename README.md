# SSII — Sistema Basado en Reglas con Factor de Certeza (Encadenamiento hacia atrás)

Proyecto de **Sistemas Inteligentes II (SSII)**: implementación de un **Sistema Basado en Reglas (SBR)** que realiza **inferencias mediante encaminamiento/encadenamiento hacia atrás** y calcula un **Factor de Certeza (FC)** para una meta (objetivo).

> Nota personal: en esta práctica obtuve un **9,5**.

---

## ¿Qué hay en este repositorio?

El repo incluye:

- **Código fuente C++** del motor de inferencia y sus utilidades (carpeta `software/`).
- **Ejecutable** ya compilado (`software/programa.exe`) para lanzar pruebas rápidamente (entorno Windows).
- **Ficheros de ejemplo** de *Base de Conocimientos* y *Base de Hechos* (`ficheros/`).
- **Ejecuciones/bitácoras** de ejemplo (archivos `Ejecucion-*.txt` en `ficheros/`).
- Documentación de la práctica (`Practica2-*.pdf/.docx`) y manuales (`Manual de uso.*`).
- Script de ayuda para ejecutar varios casos (`CrearEjecuciones.bat`).

---

## Descripción del sistema

Este sistema sigue el paradigma clásico de un **Sistema Basado en Reglas**:

- **Base de Conocimientos (BC)**: conjunto de reglas de la forma “Si antecedentes ⇒ entonces consecuente”, cada una con su **factor de certeza**.
- **Base de Hechos (BH)**: conjunto de hechos iniciales con su **FC** y una **meta/objetivo** que se quiere demostrar o refutar (con certeza).
- **Motor de inferencia**: aplica reglas para intentar justificar la meta, **generando sub-metas** (antecedentes) y calculando el **FC final**.
- **Bitácora de ejecución**: se genera un fichero por ejecución con el rastro de reglas aplicadas, casos utilizados y conclusiones.

La lógica principal está implementada siguiendo **encadenamiento hacia atrás** (backward chaining):

1. Si la **meta** ya existe en la BH, se devuelve su FC.
2. Si no, se buscan reglas cuyo **consecuente** coincide con la meta.
3. Cada regla genera **nuevas metas** (sus antecedentes) que se verifican recursivamente.
4. Se combinan los FC usando los distintos **casos de inferencia** y se almacena el resultado como nuevo hecho.

---

## Estructura del proyecto

### `software/` (núcleo del sistema)

- `SBR-FC.cpp`
  - **Programa principal** y lógica del motor de inferencia.
  - Gestión de bitácoras y verificación recursiva de metas.
- `auxiliares.h / auxiliares.cpp`
  - Funciones auxiliares para:
    - comprobar si un hecho está en la base de hechos,
    - equiparar reglas candidatas,
    - extraer antecedentes,
    - aplicar los casos de inferencia y combinar factores de certeza,
    - analizar el resultado final para construir la conclusión.
- `estructuras.h`
  - Definición de estructuras de datos (por ejemplo `Regla`, `Hecho`) y enumeraciones (p. ej. tipo de regla `AND/OR/NOT`) además de constantes relacionadas con FC.
- `lecturas.h / lecturas.cpp`
  - Lectura de archivos de entrada:
    - `leerBC(...)`: carga reglas desde la base de conocimientos.
    - `leerBH(...)`: carga hechos iniciales y objetivo desde la base de hechos.
    - `getNombreBitacora(...)`: genera el nombre del fichero de bitácora a partir de BC y BH.
- `programa.exe`
  - Ejecutable listo para usar (Windows).
- `Manual de uso.pdf` / `README.txt`
  - Guía rápida y descripción de módulos.

### `ficheros/` (datos de entrada/salida)

- Bases de conocimientos de ejemplo: `BC-2.txt`, `BC-3.txt`, `BC-A.txt`, ...
- Bases de hechos de ejemplo: `BH-21.txt`, `BH-22.txt`, `BH-3.txt`, `BH-A.txt`, ...
- Ejecuciones/bitácoras ya generadas: `Ejecucion-BC-*-BH-*.txt`

---

## Cómo ejecutar

### Opción A — Ejecutar el `.exe` (recomendado si estás en Windows)

El programa espera, como mínimo:

- 1º argumento: fichero BC
- 2º argumento: fichero BH
- (opcional) más BH adicionales

**Uso:**

```bash
software\programa.exe <ficheroBC> <ficheroBH1> [<ficheroBH2> ... <ficheroBHn>]
```

**Ejemplos (usando ficheros de este repo):**

```bash
software\programa.exe ficheros\BC-2.txt ficheros\BH-21.txt
software\programa.exe ficheros\BC-2.txt ficheros\BH-22.txt
software\programa.exe ficheros\BC-3.txt ficheros\BH-3.txt
software\programa.exe ficheros\BC-A.txt ficheros\BH-A.txt
```

Al terminar, se crea una **bitácora** por cada BH procesada (con un nombre derivado de BC/BH).

### Opción B — Script de ejecuciones

En la raíz del repo existe `CrearEjecuciones.bat`, que lanza varias ejecuciones de ejemplo de forma automática (Windows).

---

## ¿Qué genera el sistema? (bitácoras)

Por cada ejecución se genera un fichero de salida donde se registra:

- La BC y BH utilizadas
- La **meta/objetivo**
- Las **reglas aplicadas**
- El cálculo progresivo del FC por cada caso
- La conclusión final en lenguaje natural

En `ficheros/` hay varias bitácoras ya incluidas (`Ejecucion-*.txt`) para comparar resultados.

---

## Compilación (si quieres recompilar el programa)

> El repo ya incluye `programa.exe`, pero si quieres compilar desde código fuente:

Con **g++** (MinGW en Windows, o Linux):

```bash
g++ -std=c++17 -O2 -o programa software/SBR-FC.cpp software/auxiliares.cpp software/lecturas.cpp
```

Luego ejecútalo apuntando a tus ficheros BC/BH.

---

## Detalles de implementación (resumen)

- El núcleo es una función recursiva de verificación (ver `software/SBR-FC.cpp`) que:
  - comprueba si la meta ya está en BH,
  - selecciona reglas cuyo consecuente coincide con la meta,
  - resuelve antecedentes como nuevas metas,
  - aplica combinaciones de FC (casos 1/2/3),
  - almacena la meta inferida con su FC en la BH.
- Se cuida especialmente la **trazabilidad** mediante tabulación y escritura de cada paso en la bitácora.

---

## Documentación adicional

- `Practica2-informe.pdf` / `Practica2-Cuestiones.pdf`: informe y cuestiones de la práctica.
- `Manual de uso.pdf`: guía de uso y ejemplos.

---

## Autor

- **JorgeSR04**

---

## Licencia

Este repositorio se entrega con fines académicos (SSII). Si necesitas una licencia concreta (MIT, GPL, etc.), dímelo y la añadimos.
