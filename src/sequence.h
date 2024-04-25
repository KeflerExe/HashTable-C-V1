/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Tablas hash
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 29/03/2023
/// Archivo: sequence.h

#include <vector>
#include <list>

// Clase abstracta que representa una secuencia
template <class Key>
class Sequence {
 public:
  virtual bool Buscar(const Key& k) const = 0;
  virtual bool Insertar(const Key& k) = 0;
  virtual bool EstaLleno() const = 0;
  virtual Key operator[](int posicion) = 0;
};

// Clase List que implementa una secuencia mediante una lista
template <class Key>
class List: public Sequence<Key> {
 public: 
  List() = default;
  ~List() = default;
  bool Buscar(const Key& k) const override;
  bool Insertar(const Key& k) override;
  bool EstaLleno() const override;
  Key operator[](int posicion);
 private:
  std::vector<Key> lista_;
};

template <class Key>
Key List<Key>::operator[](int posicion) {
  return lista_[posicion];
}

// Método que busca un elemento en la secuencia lista
template <class Key>
bool List<Key>::Buscar(const Key& k) const {
  bool encontrado = false;
  for (auto &iterador : lista_) {
    if (iterador == k) {
      encontrado = true;
      break;
    }
  }
  return encontrado;
}

// Método que inserta un elemento en la secuencia lista
template <class Key>
bool List<Key>::Insertar(const Key& k) {
  bool resultado = false;
  if (Buscar(k) == false) {
    lista_.push_back(k);
    resultado = true;
  }
  return resultado;
}

// Método que comprueba si la secuencia lista está llena
template <class Key>
bool List<Key>::EstaLleno() const {
  return false;
}

// Clase Block que implementa una secuencia mediante un bloque
template<class Key>
class Block: public Sequence<Key> {
 public:
  Block();
  Block(int tamanio);
  ~Block();
  bool Buscar(const Key &k) const override;
  bool Insertar(const Key &k) override;
  bool EstaLleno() const override;
  Key operator[](int posicion);
 private:
  int tamaniobloque_;
  int elementosbloque_;
  std::vector<Key> bloque_;
};

template <class Key>
Key Block<Key>::operator[](int posicion) {
  return bloque_[posicion];
}

// Constructor predeterminado de la clase Block
template <class Key>
Block<Key>::Block() : tamaniobloque_(0), elementosbloque_(0) {}

// Constructor de la clase Block
template<class Key>
Block<Key>::Block(int tamanio) : tamaniobloque_(tamanio), elementosbloque_(0) {
  bloque_.resize(tamanio);
}

// Destructor de la clase Block
template<class Key>
Block<Key>::~Block() {}

// Método que busca un elemento en la secuencia bloque
template<class Key>
bool Block<Key>::Buscar(const Key &k) const {
  bool resultado = false;
  for (auto &iterador : bloque_) {
    if (iterador == k) {
      resultado = true;
      break;
    }
  }
  return resultado;
}

// Método que comprueba si la secuencia bloque está llena
template<class Key>
bool Block<Key>::EstaLleno() const {
  bool resultado = false;
  if (elementosbloque_ == tamaniobloque_) {
    resultado = true;
  }
  return resultado;
}

// Método que inserta un elemento en la secuencia bloque
template<class Key>
bool Block<Key>::Insertar(const Key &k) {
  bool resultado = true;
  if (!EstaLleno() && !Buscar(k)){
    bloque_[elementosbloque_] = k;
    elementosbloque_++;
  } else {
    resultado = false;
  }
  return resultado;
}