//
// Created by Carla Onate on 03/10/22.
//


#include "graph.h"



void djikstra () {
  char currentNode;

}

int main () {
  Graph graph(5);
  graph.addEdge('A', 'B', 5);
  graph.addEdge('A', 'C', 7);
  graph.addEdge('B', 'E', 8);
  graph.addEdge('C', 'D', 10);
  graph.addEdge('D', 'E', 2);
  graph.printGraph();
}
