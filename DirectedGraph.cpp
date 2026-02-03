#include "DirectedGraph.h"

// agrega una arista dirigida from -> to
// complejidad O(1) promedio usando unordered_map
void DirectedGraph::addEdge(const std::string& from, const std::string& to) {
  adjList[from].push_back(to);
  outDegree[from]++;
  inDegree[to]++;

  //asegura que ambas ips existan aunque tengan grado 0
  if (!inDegree.count(from)) inDegree[from] = 0;
  if (!outDegree.count(to)) outDegree[to] = 0;
}

const std::unordered_map<std::string, int>& DirectedGraph::getOutDegrees() const {
  return outDegree;
}

const std::unordered_map<std::string, int>& DirectedGraph::getInDegrees() const {
  return inDegree;
}
