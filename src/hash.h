/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Tablas hash
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 29/03/2023
/// Archivo: hash.h

#include <stdlib.h>

#include "fd.h"
#include "fe.h"
#include "sequence.h"

// Clase HashTable que implementa una tabla hash con una función de dispersión y una función de exploración
template<class Key>
class HashTable {
 public:
  HashTable(unsigned tamaniotabla, FuncionDispersion<Key>* fd, FuncionExploracion<Key>* fe = nullptr, unsigned tamaniobloque = 0);
  ~HashTable() = default;
  bool Buscar(const Key& k);
  bool Insertar(const Key& k);
  int DevuelvePosicionValor(const Key& k);
  std::vector<Key> ExtraeValoresAVector() const;
 private:
  unsigned tamaniotabla_;
  Sequence<Key> **tabla_;
  FuncionDispersion<Key>* fd_;
  unsigned tamaniobloque_;
  FuncionExploracion<Key>* fe_;
};

// Constructor de la clase HashTable
template<class Key>
HashTable<Key>::HashTable(unsigned tamaniotabla, FuncionDispersion<Key>* fd, FuncionExploracion<Key>* fe, unsigned tamaniobloque) {
  tamaniotabla_ = tamaniotabla;
  tamaniobloque_ = tamaniobloque;
  fe_ = fe;
  fd_ = fd;
  tabla_ = new Sequence<Key>*[tamaniotabla_];
  for (int iterador = 0; iterador < tamaniotabla_; iterador++) {
    if (tamaniobloque_ > 0) {
      tabla_[iterador] = new Block<Key>(tamaniobloque_);
    } else {
      tabla_[iterador] = new List<Key>();
    }
  }
}

// Método que inserta un elemento en la tabla hash
template<class Key> 
bool HashTable<Key>::Insertar(const Key& k) {
  unsigned posicion = (*fd_)(k);
  if (tabla_[posicion]->EstaLleno()) {
    int iterador = 0;
    while (iterador < tamaniobloque_ && tabla_[posicion]->EstaLleno()) {
      posicion = (*fe_)(k, posicion);
      iterador++;
    }
  }
  return tabla_[posicion]->Insertar(k);
}

// Método que busca un elemento en la tabla hash
template <class Key>  
bool HashTable<Key>::Buscar(const Key& k) {
  unsigned posicion = (*fd_)(k);
  bool encontrado = false;
  if (tabla_[posicion]->Buscar(k)) {
    encontrado = true;
  } else {
    if (tamaniobloque_ > 0) {
      int iterador = 0;
      while (iterador < tamaniobloque_ && !encontrado) {
        posicion = (*fe_)(k, posicion);
        encontrado = tabla_[posicion]->Buscar(k);
        iterador++;
      }
    }
  }
  return encontrado;
}

template <class Key>
int HashTable<Key>::DevuelvePosicionValor(const Key& k) {
  unsigned posicion = (*fd_)(k);
  bool encontrado = false;
  unsigned posicion_encontrado{0};
  if (tabla_[posicion]->Buscar(k)) {
    encontrado = true;
    posicion_encontrado = posicion;
  } else {
    if (tamaniobloque_ > 0) {
      int iterador = 0;
      while (iterador < tamaniobloque_ && !encontrado) {
        posicion = (*fe_)(k, posicion);
        posicion_encontrado = posicion;
        encontrado = tabla_[posicion]->Buscar(k);
        iterador++;
      }
    }
  }
  if (!encontrado) {
    return 0;
  } else {
    return posicion_encontrado;
  }
}

template <class Key>
std::vector<Key> HashTable<Key>::ExtraeValoresAVector() const {
  std::vector<Key> valores_extraidos;
  for (int iterador = 0; iterador < tamaniotabla_; ++iterador) {
    if (tamaniobloque_ > 0) {
      for (int iterador2 = 0; iterador2 < tamaniobloque_; ++iterador2) {
        if (tabla_[iterador][iterador2][0] != 0) {
          valores_extraidos.push_back(tabla_[iterador][iterador2][0]);
        }        
      }
    } 
  }
  return valores_extraidos;
}
