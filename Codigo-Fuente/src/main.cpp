#include "experimentacion.h"
#include "vector.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    // Inicializar semilla para generación de números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    std::cout << "==================================================" << std::endl;
    std::cout << "SIMULACIÓN DE SISTEMA DE ARCHIVOS CON VECTORES" << std::endl;
    std::cout << "==================================================" << std::endl;
    
    int opcion = 0;
    
    do {
        std::cout << "MENU PRINCIPAL:" << std::endl;
        std::cout << "1. Ejecutar experimento con directorio pequeño (200,000 archivos)" << std::endl;
        std::cout << "2. Ejecutar experimento con directorio mediano (1,000,000 archivos)" << std::endl;
        std::cout << "3. Ejecutar experimento con directorio grande (10,000,000 archivos)" << std::endl;
        std::cout << "4. Ejecutar todos los experimentos" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingrese su opción: ";
        std::cin >> opcion;
        
        switch (opcion) {
            case 1:
                ejecutarExperimentos(TamanoDirectorio::PEQUENO);
                break;
            case 2:
                ejecutarExperimentos(TamanoDirectorio::MEDIANO);
                break;
            case 3:
                ejecutarExperimentos(TamanoDirectorio::GRANDE);
                break;
            case 4:
                std::cout << "\nEjecutando experimentos para todos los tamaños de directorio...\n" << std::endl;
                ejecutarExperimentos(TamanoDirectorio::PEQUENO);
                ejecutarExperimentos(TamanoDirectorio::MEDIANO);
                ejecutarExperimentos(TamanoDirectorio::GRANDE);
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }
    } while (opcion != 0);
    
    return 0;
}
