#ifndef HASH_TABLE_QP_H
#define HASH_TABLE_QP_H

#include <vector>
#include <string>
#include "IPSummary.h"

// implementacion de una tabla hash usando direccion abierta
// se utiliza una funcion hash para strings
class HashTableQP {
private:
  std::vector<IPSummary> table;
  std::vector<bool> occupied;
  int size;

  // funcion hash que convierte una ip en un indice
  int hashFunction(const std::string& ip) const;

public:
  HashTableQP(int tableSize);

  // inserta un resumen de ip en la tabla hash
  void insert(const IPSummary& summary);
};

#endif
