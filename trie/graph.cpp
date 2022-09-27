//
// Created by Carla Onate on 27/09/22.
//

#include "graph.h"

void Graph::addEdge(string prevNode, string toNode) {
  if (graph.find(prevNode) != graph.end()) { // If prev node exists
    graph[prevNode].insert(toNode); // Link current Node with next Node
  } else {
    graph[prevNode] = set<string>();
    graph[prevNode].insert(toNode);
  }
}

void Graph::createGraph(string text) {
  for (int i  = 1; i < text.length(); i++) {
    string currentSubstring = text.substr(0, i); // H
    string nextSubstring = text.substr(0, i+1); // HU
    addEdge(currentSubstring, nextSubstring); // H -> [HU], HU -> []
  }
}

void Graph::printGraph() {
  for (const auto & it : graph) {
    cout << it.first << " : [  ";
    for (auto el : it.second){
      cout << el << "  ";
    }
    cout << "  ]\n";
  }
}
