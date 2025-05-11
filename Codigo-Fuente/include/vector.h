#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <iostream>

// Define's
#define REP 100000 // Número de repeticiones para mediciones

// Declaración de funciones
std::vector<std::string> cargarArchivos(const std::string& dirPath);
void ordenarVector(std::vector<std::string>& vec);
int busquedaSecuencial(const std::vector<std::string>& vec, const std::string& clave);
int busquedaBinaria(const std::vector<std::string>& vec, const std::string& clave);
bool eliminar(std::vector<std::string>& vec, const std::string& clave, bool vectorOrdenado = false);
int insertarOrdenado(std::vector<std::string>& vec, const std::string& valor);
void insertarDesordenado(std::vector<std::string>& vec, const std::string& valor);

#endif // VECTOR_H
