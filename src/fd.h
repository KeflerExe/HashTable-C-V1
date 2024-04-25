/// Universidad de La Laguna
/// Escuela Superior de Ingeniería y Tecnología
/// Grado en Ingeniería Informática
/// Asignatura: AyEDA
/// Curso: 2º
/// Práctica 2: Tablas hash
/// Autor: Joel Oscar Martín Gutiérrez
/// Correo: alu0101473840@ull.es
/// Fecha: 29/03/2023
/// Archivo: fd.h

// Clase abstracta que representa una función de dispersión
template<class Key>
class FuncionDispersion {
 public:
  virtual unsigned operator()(const Key& k) const = 0;
};

// Clase que implementa una función de dispersión modular
template<class Key>
class fdModulo: public FuncionDispersion<Key> {
 public:
  fdModulo(const unsigned n): tableSize(n){}
  unsigned operator()(const Key& k) const {
    return k % tableSize;
  }
 private:
  unsigned tableSize;
};

// Clase que implementa una función de dispersión por suma de dígitos
template<class Key>
class fdSuma: public FuncionDispersion<Key> {
 public:
  fdSuma(const unsigned n): tableSize(n){}
  unsigned operator()(const Key& k) const {
    long suma = 0; 
    long valor = k;
    while (valor > 0) {
      int digito = valor % 10;
      suma = suma + digito;
      valor = valor / 10;
    }
    return (suma % tableSize);
  }
 private:
  unsigned tableSize;
};

// Clase que implementa una función de dispersión pseudoaleatoria
template<class Key>
class fdPseudoAleatorio: public FuncionDispersion<Key> {
 public:
  fdPseudoAleatorio(const unsigned n): tableSize(n){}
  unsigned operator()(const Key& k) const {
    srand(k);
    return rand() % tableSize;
  }
 private:
  unsigned tableSize;
};