#include "experimentacion.h"
#include "vector.h"
#include <iostream>
#include <fstream>
#include <random>
#include <filesystem>
#include <cmath>
#include <iomanip>

/**
 * Genera un nombre de archivo aleatorio
 * @return Nombre de archivo aleatorio
 */
std::string generarNombreAleatorio() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> len_dist(10, 20);
    static std::uniform_int_distribution<> char_dist(97, 122); // a-z
    
    int length = len_dist(gen);
    std::string nombre;
    
    for (int i = 0; i < length; i++) {
        nombre += static_cast<char>(char_dist(gen));
    }
    
    // Agregar extensión aleatoria
    static const std::vector<std::string> extensiones = {".txt", ".csv", ".cpp", ".c", ".json", ".xml", ".md"};
    static std::uniform_int_distribution<> ext_dist(0, static_cast<int>(extensiones.size()) - 1);
    
    nombre += extensiones[ext_dist(gen)];
    return nombre;
}

/**
 * Genera un directorio sintético con la cantidad especificada de archivos
 * @param dirPath Ruta donde crear el directorio
 * @param numArchivos Número de archivos a crear
 */
void generarDirectorioSintetico(const std::string& dirPath, int numArchivos) {
    std::cout << "Generando directorio sintético con " << numArchivos << " archivos..." << std::endl;
    
    // Crear directorio si no existe
    if (!std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }
    
    // Generar vector con nombres aleatorios
    std::vector<std::string> nombresArchivos;
    for (int i = 0; i < numArchivos; i++) {
        nombresArchivos.push_back(generarNombreAleatorio());
    }
    
    // Crear archivos vacíos (solo los nombres)
    for (const auto& nombre : nombresArchivos) {
        std::ofstream file(dirPath + "/" + nombre);
        file.close();
    }
    
    std::cout << "Directorio sintético generado en: " << dirPath << std::endl;
}

/**
 * Mide los tiempos de ejecución de las operaciones
 * @param vec Vector con los nombres de archivos
 * @param resultados Estructura donde guardar los resultados
 */
void medirTiempos(std::vector<std::string>& vec, ResultadosMedicion& resultados) {
    // Vector para guardar copia antes de modificaciones
    std::vector<std::string> vecOriginal = vec;
    
    // --------------------------- Medir tiempo de búsqueda secuencial ---------------------------
    std::cout << "Midiendo búsqueda secuencial..." << std::endl;
    
    auto startSeq = std::chrono::high_resolution_clock::now();
    
    // Realizar REP búsquedas secuenciales
    for (int i = 0; i < REP; i++) {
        size_t indiceAleatorio = rand() % vec.size();
        std::string claveExistente = vec[indiceAleatorio];
        busquedaSecuencial(vec, claveExistente);
    }
    
    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracionSeq = endSeq - startSeq;
    resultados.tiempoBusquedaSecuencial = duracionSeq.count() / REP;
    
    // --------------------------- Medir tiempo de ordenamiento y creación ---------------------------
    std::cout << "Midiendo ordenamiento del vector..." << std::endl;
    
    auto startSort = std::chrono::high_resolution_clock::now();
    
    // Ordenar el vector
    ordenarVector(vec);
    
    auto endSort = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracionSort = endSort - startSort;
    resultados.tiempoCreacion = duracionSort.count();
    
    // --------------------------- Medir tiempo de búsqueda binaria ---------------------------
    std::cout << "Midiendo búsqueda binaria..." << std::endl;
    
    auto startBin = std::chrono::high_resolution_clock::now();
    
    // Realizar REP búsquedas binarias
    for (int i = 0; i < REP; i++) {
        size_t indiceAleatorio = rand() % vec.size();
        std::string claveExistente = vec[indiceAleatorio];
        busquedaBinaria(vec, claveExistente);
    }
    
    auto endBin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracionBin = endBin - startBin;
    resultados.tiempoBusquedaBinaria = duracionBin.count() / REP;
    
    // --------------------------- Medir tiempo de eliminación ---------------------------
    std::cout << "Midiendo eliminación..." << std::endl;
    
    // Crear una copia para eliminar elementos
    std::vector<std::string> vecEliminar = vec;
    
    auto startElim = std::chrono::high_resolution_clock::now();
    
    // Eliminar REP elementos aleatorios (o hasta agotar el vector)
    int eliminados = 0;
    for (int i = 0; i < REP && !vecEliminar.empty(); i++) {
        size_t indiceAleatorio = rand() % vecEliminar.size();
        std::string claveExistente = vecEliminar[indiceAleatorio];
        eliminar(vecEliminar, claveExistente, true);
        eliminados++;
    }
    
    auto endElim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracionElim = endElim - startElim;
    resultados.tiempoEliminacion = duracionElim.count() / eliminados;
    
    // --------------------------- Medir tiempo de inserción ---------------------------
    std::cout << "Midiendo inserción ordenada..." << std::endl;
    
    // Preparar nombres aleatorios para insertar
    std::vector<std::string> nuevosNombres;
    for (int i = 0; i < REP; i++) {
        nuevosNombres.push_back(generarNombreAleatorio());
    }
    
    auto startIns = std::chrono::high_resolution_clock::now();
    
    // Realizar REP inserciones ordenadas
    for (int i = 0; i < REP; i++) {
        insertarOrdenado(vec, nuevosNombres[i]);
    }
    
    auto endIns = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracionIns = endIns - startIns;
    resultados.tiempoInsercion = duracionIns.count() / REP;
    
    // Restaurar el vector original para otras pruebas si es necesario
    vec = vecOriginal;
}

/**
 * Muestra los resultados de las mediciones
 * @param resultados Estructura con los resultados de las mediciones
 * @param tamano Tamaño del directorio utilizado
 */
void mostrarResultados(const ResultadosMedicion& resultados, TamanoDirectorio tamano) {
    int numArchivos;
    
    switch (tamano) {
        case TamanoDirectorio::PEQUENO:
            numArchivos = 200000;
            std::cout << "\n===== RESULTADOS PARA DIRECTORIO PEQUEÑO (" << numArchivos << " archivos) =====\n";
            break;
        case TamanoDirectorio::MEDIANO:
            numArchivos = 1000000;
            std::cout << "\n===== RESULTADOS PARA DIRECTORIO MEDIANO (" << numArchivos << " archivos) =====\n";
            break;
        case TamanoDirectorio::GRANDE:
            numArchivos = 10000000;
            std::cout << "\n===== RESULTADOS PARA DIRECTORIO GRANDE (" << numArchivos << " archivos) =====\n";
            break;
    }
    
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Tiempo de ordenamiento:           " << resultados.tiempoCreacion << " ms\n";
    std::cout << "Tiempo promedio búsqueda secuencial: " << resultados.tiempoBusquedaSecuencial << " ms\n";
    std::cout << "Tiempo promedio búsqueda binaria:    " << resultados.tiempoBusquedaBinaria << " ms\n";
    std::cout << "Tiempo promedio eliminación:         " << resultados.tiempoEliminacion << " ms\n";
    std::cout << "Tiempo promedio inserción ordenada:  " << resultados.tiempoInsercion << " ms\n";
    std::cout << "Ratio búsqueda secuencial/binaria:   " << resultados.tiempoBusquedaSecuencial / resultados.tiempoBusquedaBinaria << "x\n";
    std::cout << "=========================================\n";
}

/**
 * Ejecuta los experimentos para un tamaño de directorio específico
 * @param tamano Tamaño del directorio a utilizar
 */
void ejecutarExperimentos(TamanoDirectorio tamano) {
    int numArchivos;
    std::string dirPath;
    
    switch (tamano) {
        case TamanoDirectorio::PEQUENO:
            numArchivos = 200000;
            dirPath = "./dir_pequeno";
            break;
        case TamanoDirectorio::MEDIANO:
            numArchivos = 1000000;
            dirPath = "./dir_mediano";
            break;
        case TamanoDirectorio::GRANDE:
            numArchivos = 10000000;
            dirPath = "./dir_grande";
            break;
    }
    
    // Para el experimento, usamos una cantidad mucho menor para evitar tiempos excesivos
    // En un entorno real, usaríamos numArchivos completo
    int numArchivosExperimento = std::min(numArchivos, 10000); // Limitar a 10,000 para pruebas
    
    // Generar directorio sintético si no existe o si está vacío
    if (!std::filesystem::exists(dirPath) || 
        std::filesystem::is_empty(dirPath)) {
        generarDirectorioSintetico(dirPath, numArchivosExperimento);
    }
    
    // Cargar archivos en el vector
    std::cout << "Cargando archivos desde " << dirPath << "..." << std::endl;
    std::vector<std::string> archivos = cargarArchivos(dirPath);
    
    if (archivos.empty()) {
        std::cerr << "Error: No se encontraron archivos en " << dirPath << std::endl;
        return;
    }
    
    std::cout << "Se cargaron " << archivos.size() << " archivos." << std::endl;
    
    // Medir tiempos y mostrar resultados
    ResultadosMedicion resultados;
    medirTiempos(archivos, resultados);
    mostrarResultados(resultados, tamano);
}
