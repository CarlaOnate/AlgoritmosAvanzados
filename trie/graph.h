//
// Created by Carla Onate on 27/09/22.
//

#ifndef ALGORITMOS_AVANZADOS_GRAPH_H
#define ALGORITMOS_AVANZADOS_GRAPH_H

#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;

class Graph {
  private:
    char firstNode;
    map<string, set<string> > graph;

  public:
    void addEdge(string, string);
    void createGraph(string);
    void printGraph();
};

#endif //ALGORITMOS_AVANZADOS_GRAPH_H

