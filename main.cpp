/*
 * Act 5.2 - Actividad Integral sobre el uso de códigos hash
 *
 * equipo:
 * - Ana Regina Rodriguez Múzquiz | A01286913
 * - Javier Barron Vargas | A00842507
 * - Alfonso Jose Morales Mallozzi | A00841550
 *
 * compilación:
 * g++ -std=c++17 -Wall -Wextra -O3 main.cpp DirectedGraph.cpp HashTableQP.cpp -o main
 *
 * ejecución:
 * ./main
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "DirectedGraph.h"
#include "HashTableQP.h"
#include "IPSummary.h"

int main() {
  // se crea el grafo dirigido
  DirectedGraph graph;

  // se abre el archivo de la bitacora
  std::ifstream file("bitacoraGrafos.txt");
  if (!file.is_open()) {
    std::cerr << "error al abrir el archivo bitacoraGrafos.txt\n";
    return 1;
  }

  // se leen las lineas del archivo
  // complejidad O(n) donde n es el numero de lineas
  std::string line;
  while (getline(file, line)) {
    std::stringstream ss(line);
    std::string fromIP, toIP;

    // se asume que las ips ya vienen separadas
    ss >> fromIP >> toIP;
    graph.addEdge(fromIP, toIP);
  }

  file.close();

  // se crea la tabla hash para almacenar el resumen de las ips
  HashTableQP hashTable(101);

  const auto& outDegrees = graph.getOutDegrees();
  const auto& inDegrees  = graph.getInDegrees();

  // se recorre el conjunto de ips para generar el resumen
  // complejidad O(n)
  for (const auto& pair : outDegrees) {
    IPSummary summary;
    summary.ip = pair.first;
    summary.outDegree = pair.second;
    summary.inDegree = inDegrees.count(pair.first) ? inDegrees.at(pair.first) : 0;

    hashTable.insert(summary);
  }

  std::cout << "tabla hash creada correctamente con el resumen de las ips\n";

  // nota para el equipo:
  // aqui se puede continuar con la consulta de una ip y el ordenamiento descendente

  return 0;
}

