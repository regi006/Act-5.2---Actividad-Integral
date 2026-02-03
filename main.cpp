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
#include <limits>

#include "DirectedGraph.h"
#include "HashTableQP.h"
#include "IPSummary.h"

// elimina el puerto de una ip (ej. 192.168.1.1:8080 -> 192.168.1.1)
// complejidad O(n) donde n es la longitud de la cadena
std::string removePort(const std::string& ipPort) {
  size_t pos = ipPort.find(':');
  if (pos == std::string::npos) {
    return ipPort;
  }
  return ipPort.substr(0, pos);
}

int main() {
  // se crea el grafo dirigido usando lista de adyacencia
  DirectedGraph graph;

  // se abre el archivo de la bitacora
  std::ifstream file("bitacoraGrafos.txt");
  if (!file.is_open()) {
    std::cerr << "error al abrir el archivo bitacoraGrafos.txt\n";
    return 1;
  }

  // el archivo comienza con un entero n (numero de ips)
  int n;
  file >> n;

  // se leen y descartan las n ips del archivo
  // complejidad O(n)
  std::string ip;
  for (int i = 0; i < n; i++) {
    file >> ip;
  }

  // variables para leer las incidencias
  std::string month, time;
  int day, weight;
  std::string srcIPPort, dstIPPort;

  // se leen las incidencias del archivo
  // complejidad O(m) donde m es el numero de incidencias
  while (file >> month >> day >> time >> srcIPPort >> dstIPPort >> weight) {
    std::string srcIP = removePort(srcIPPort);
    std::string dstIP = removePort(dstIPPort);

    // se agrega la arista dirigida al grafo
    graph.addEdge(srcIP, dstIP);

    // se ignora el resto de la linea (razon de la incidencia)
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  file.close();

  // se crea la tabla hash para almacenar el resumen de cada ip
  HashTableQP hashTable(101);

  const auto& outDegrees = graph.getOutDegrees();
  const auto& inDegrees  = graph.getInDegrees();

  // se recorre el conjunto de ips para generar su resumen
  // complejidad O(n)
  for (const auto& pair : outDegrees) {
    IPSummary summary;
    summary.ip = pair.first;
    summary.outDegree = pair.second;
    summary.inDegree = inDegrees.count(pair.first) ? inDegrees.at(pair.first) : 0;

    // se inserta el resumen en la tabla hash
    hashTable.insert(summary);
  }

  std::cout << "tabla hash creada correctamente a partir del grafo dirigido\n";
  std::cout << "total de colisiones generadas: " << hashTable.getCollisions() << std::endl;




  return 0;
}
