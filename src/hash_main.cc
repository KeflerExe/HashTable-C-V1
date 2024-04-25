/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Tablas hash
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 29/03/2023
/// Archivo: hash_main.cc

#include <iostream>
#include <fstream>

#include "hash.h"

typedef long key;

// Función encargada de crear la función de exploración a utilizar
void CreaFuncionDispersion(unsigned tamanio_tabla, FuncionDispersion<key> *&funcion_dispersion) {
  std::cout << "Elija la función de dispersión a utilizar:" << std::endl;
  std::cout << "[1] Módulo" << std::endl;
  std::cout << "[2] Basada en suma" << std::endl;
  std::cout << "[3] Pseudoaleatoria" << std::endl;
  int funcion_escogida{0};
  std::cin >> funcion_escogida;
  switch (funcion_escogida) {
    case 1 : {
      funcion_dispersion = new fdModulo<key>(tamanio_tabla);
      break;
    }
    case 2 : {
      funcion_dispersion = new fdSuma<key>(tamanio_tabla);
      break;
    }
    case 3 : {
      funcion_dispersion = new fdPseudoAleatorio<key>(tamanio_tabla);   
      break;
    }    
    default: {
      std::cout << "Opción seleccionada no válida. Finalizando programa..." << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
}

// Función encargada de crear la tabla hash a utilizar y preguntar por la técnica de dispersión a utilizar
void CreaTablaHash(unsigned tamanio_tabla, FuncionDispersion<key> *funcion_dispersion, HashTable<key> *&tabla_hash) {
  std::cout << "Elija la técnica de dispersión a utilizar:" << std::endl;
  std::cout << "[1] Abierta" << std::endl;
  std::cout << "[2] Cerrada" << std::endl;
  int tecnica_escogida{0};
  std::cin >> tecnica_escogida;
  switch (tecnica_escogida) {
    case 1: {
      tabla_hash = new HashTable<key>(tamanio_tabla, funcion_dispersion);
      break;
    }
    case 2: {
      std::cout << "Introduzca el tamaño del bloque:";
      int tamanio_bloque{0};
      std::cin >> tamanio_bloque;
      FuncionExploracion<key> *funcion_exploracion;
      std::cout << "Elija la función de exploración a usar:" << std::endl;
      std::cout << "[1] Lineal" << std::endl; 
      std::cout << "[2] Cuadrática" << std::endl;
      std::cout << "[3] Doble dispersión" << std::endl;
      std::cout << "[4] Redispersión" << std::endl;
      int exploracion_escogida{0};
      std::cin >> exploracion_escogida;
      switch (exploracion_escogida) {
        case 1: {
          funcion_exploracion = new feLineal<key>();
          break;
        }
        case 2: {
          funcion_exploracion = new feCuadratica<key>();
          break;
        }
        case 3: {
          funcion_exploracion = new feDobleDispersion<key>(funcion_dispersion);
          break;
        }
        case 4: {
          funcion_exploracion = new feRedispersion<key>();
          break;
        }
        default: {
          std::cout << "Opción seleccionada no válida. Finalizando programa..." << std::endl;
          exit(EXIT_SUCCESS);
        }
      }
      tabla_hash = new HashTable<key>(tamanio_tabla, funcion_dispersion, funcion_exploracion, tamanio_bloque);
      break;
    }
    default: {
      std::cout << "Opción seleccionada no válida. Finalizando programa..." << std::endl;
      exit(EXIT_SUCCESS);
    }
  }
}

int main() {
  unsigned tamanio_tabla{0};
  HashTable<key> *tabla_hash;
  FuncionDispersion<key>* funcion_dispersion;
  std::cout << "Introduzca el tamaño de la tabla : ";
  std::cin >> tamanio_tabla;
  CreaFuncionDispersion(tamanio_tabla, funcion_dispersion);
  CreaTablaHash(tamanio_tabla, funcion_dispersion, tabla_hash);
  while (true) {
    std::cout << "Elija una opción:" << std::endl;
    std::cout << "[1] Insertar" << std::endl;
    std::cout << "[2] Buscar" << std::endl;
    std::cout << "[3] Finalizar programa" << std::endl;
    std::cout << "[4] Mostrar tabla" << std::endl;
    int opcion_escogida{0};
    std::cin >> opcion_escogida;
    switch (opcion_escogida) {
      case 1: {
        std::cout << "Introduzca el elemento a insertar:";
        key elemento{0};
        std::cin >> elemento;
        tabla_hash->Insertar(elemento);
        break;
      }
      case 2: {
        std::cout << "Introduzca el elemento a buscar:";
        key elemento{0};
        std::cin >> elemento;
        if (tabla_hash->Buscar(elemento)) {
          std::cout << "El elemento se encuentra en la tabla." << std::endl;
          std::cout << "Posición:" << tabla_hash->DevuelvePosicionValor(elemento) << std::endl;
        } else {
          std::cout << "El elemento no se encuentra en la tabla." << std::endl;
        }
        break;
      }
      case 3: {
        std::cout << "Finalizando programa..." << std::endl;
        exit(EXIT_SUCCESS);
      }
      case 4: {
        key key_obtenida{0};
        std::vector<key> valores_tabla = tabla_hash->ExtraeValoresAVector();
        for (int iterador = 0; iterador < valores_tabla.size(); ++iterador) {
         std::cout << "Valor: " << valores_tabla[iterador] << "Posición: " << tabla_hash->DevuelvePosicionValor(valores_tabla[iterador]) << std::endl;
        }
      }
      default: {
        std::cout << "Opción seleccionada no válida. Finalizando programa..." << std::endl;
        exit(EXIT_SUCCESS);
      }
    }
  }
  return 0;
}