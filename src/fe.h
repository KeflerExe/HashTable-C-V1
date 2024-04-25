/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Tablas hash
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 29/03/2023
/// Archivo: fe.h

// Clase abstracta que representa una función de exploración
template<class Key>
class FuncionExploracion {
 public:
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

// Clase que implementa una función de exploración lineal
template<class Key>
class feLineal: public FuncionExploracion<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const {
    return i;
  }
};

// Clase que implementa una función de exploración cuadrática
template<class Key>
class feCuadratica : public FuncionExploracion<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const {
    return i * i;
  }
};

// Clase que implementa una función de exploración redispersión
template<class Key>
class feRedispersion : public FuncionExploracion<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const {
    srand(k);
    for (int iterador = 0; iterador < i; iterador++) {
      rand();
    }
    return rand();
  }
};

// Clase que implementa una función de exploración doble dispersión
template<class Key>
class feDobleDispersion : public FuncionExploracion<Key> {
 public:
    feDobleDispersion(FuncionDispersion<Key> *funcion1) : fd1_(funcion1) {}
    unsigned operator()(const Key &k, unsigned i) const {
      unsigned funcion_disp1 = (*fd1_)(k);
      return funcion_disp1 * i;
    }
 private:
  FuncionDispersion<Key> *fd1_;
};