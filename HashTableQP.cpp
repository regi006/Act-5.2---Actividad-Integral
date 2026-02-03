#include "HashTableQP.h"

// constructor de la tabla hash
HashTableQP::HashTableQP(int tableSize) {
  size = tableSize;
  table.resize(size);
  occupied.resize(size, false);
  collisions = 0;
}

//funcion hash
// complejidad O(n) donde n es el tamaño de la cadena ip
// implementado de: https://www.geeksforgeeks.org/string-hashing-using-polynomial-rolling-hash-function/
int HashTableQP::hashFunction(const std::string& ip) const {
  unsigned long hash = 0;
  for (char c : ip) {
    hash = hash * 31 + c;
  }
  return hash % size;
}

// inserta usando direccion abierta
// complejidad O(1) promedio, O(n) en el peor de los casos
// implementado de: https://www.geeksforgeeks.org/open-addressing-collision-handling-technique-in-hashing/
void HashTableQP::insert(const IPSummary& summary) {
  int index = hashFunction(summary.ip);
  int i = 0;

  // cada intento adicional cuenta como una colision
  while (occupied[(index + i * i) % size]) {
    collisions++;
    i++;
  }

  int finalIndex = (index + i * i) % size;
  table[finalIndex] = summary;
  occupied[finalIndex] = true;
}

// regresa el total de colisiones generadas
int HashTableQP::getCollisions() const {
  return collisions;
}
