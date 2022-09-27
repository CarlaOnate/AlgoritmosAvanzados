//
// Created by Carla Onate on 23/09/22.
//

#include "graph.h"
using namespace std;

int main () {
  Graph graph;
  graph.createGraph("abc");
  graph.createGraph("abcdef");
  graph.createGraph("abb");
  graph.createGraph("mochon");
  graph.createGraph("mochito");
  graph.createGraph("moshon");
  graph.printGraph();
}