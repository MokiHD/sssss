#ifndef EXPERIMENTACION_H
#define EXPERIMENTACION_H

#include <vector>
#include <string>
#include <chrono>

// Define's
enum class TamanoDirectorio {
    PEQUENO = 200000,    // 200,000 archivos
    MEDIANO = 1000000,   // 1,000,000 archivos
    GRANDE = 10000000    // 10,000,000 archivos
};

// Estructura para almacenar resultados
struct ResultadosMedicion {
    double tiempoCreacion;
    double tiempoBusquedaSecuencial;
    double tiempoBusquedaBinaria;
    double tiempoEliminacion;
    double tiempoInsercion;
};

// Declaración de funciones
void generarDirectorioSintetico(const std::string& dirPath, int numArchivos);
void ejecutarExperimentos(TamanoDirectorio tamano);
void medirTiempos(std::vector<std::string>& vec, ResultadosMedicion& resultados);
void mostrarResultados(const ResultadosMedicion& resultados, TamanoDirectorio tamano);

#endif // EXPERIMENTACION_H
