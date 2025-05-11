#include "vector.h"

/**
 * Carga archivos de un directorio en un vector
 * @param dirPath Ruta del directorio a cargar
 * @return Vector con las rutas de los archivos
 */
std::vector<std::string> cargarArchivos(const std::string& dirPath) {
    std::vector<std::string> archivos;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                archivos.push_back(entry.path().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error al cargar archivos: " << e.what() << std::endl;
    }
    return archivos;
}

/**
 * Ordena un vector de strings lexicográficamente
 * @param vec Vector a ordenar
 */
void ordenarVector(std::vector<std::string>& vec) {
    std::sort(vec.begin(), vec.end());
}

/**
 * Realiza una búsqueda secuencial en el vector
 * @param vec Vector donde buscar
 * @param clave Elemento a buscar
 * @return Índice donde se encuentra el elemento o -1 si no existe
 */
int busquedaSecuencial(const std::vector<std::string>& vec, const std::string& clave) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == clave) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/**
 * Realiza una búsqueda binaria en el vector (requiere vector ordenado)
 * @param vec Vector ordenado donde buscar
 * @param clave Elemento a buscar
 * @return Índice donde se encuentra el elemento o -1 si no existe
 */
int busquedaBinaria(const std::vector<std::string>& vec, const std::string& clave) {
    int izq = 0;
    int der = static_cast<int>(vec.size()) - 1;
    
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        
        if (vec[medio] == clave) {
            return medio;
        }
        else if (vec[medio] < clave) {
            izq = medio + 1;
        }
        else {
            der = medio - 1;
        }
    }
    
    return -1;
}

/**
 * Elimina un elemento del vector
 * @param vec Vector del cual eliminar
 * @param clave Elemento a eliminar
 * @param vectorOrdenado Indica si el vector está ordenado para usar búsqueda binaria
 * @return true si se eliminó, false si no se encontró
 */
bool eliminar(std::vector<std::string>& vec, const std::string& clave, bool vectorOrdenado) {
    int idx;
    
    // Buscar el elemento usando el algoritmo apropiado
    if (vectorOrdenado) {
        idx = busquedaBinaria(vec, clave);
    } else {
        idx = busquedaSecuencial(vec, clave);
    }
    
    // Si no se encontró, retornar false
    if (idx == -1) {
        return false;
    }
    
    // Eliminar el elemento usando vector.erase()
    vec.erase(vec.begin() + idx);
    return true;
}

/**
 * Inserta un elemento en un vector ordenado manteniendo el orden
 * @param vec Vector ordenado donde insertar
 * @param valor Elemento a insertar
 * @return Posición donde se insertó el elemento
 */
int insertarOrdenado(std::vector<std::string>& vec, const std::string& valor) {
    // Buscar posición de inserción
    int izq = 0;
    int der = static_cast<int>(vec.size()) - 1;
    int pos = 0;
    
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        
        if (vec[medio] < valor) {
            izq = medio + 1;
            pos = izq;
        } else {
            der = medio - 1;
            pos = medio;
        }
    }
    
    // Insertar en la posición encontrada
    vec.insert(vec.begin() + pos, valor);
    return pos;
}

/**
 * Inserta un elemento al final de un vector desordenado
 * @param vec Vector donde insertar
 * @param valor Elemento a insertar
 */
void insertarDesordenado(std::vector<std::string>& vec, const std::string& valor) {
    vec.push_back(valor);
}

