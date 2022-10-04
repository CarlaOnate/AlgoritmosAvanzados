//
// Created by Carla Onate on 04/10/22.
//

#include <map>
#include <list>
#include <iostream>

using namespace std;

// Grafo no dirigido
class Node {
  public:
  char value;
  int cost;
  bool visited = false;

  Node(char, int);
};

Node::Node(char val, int cost) {
  this->value = val;
  this->cost = cost;
}

class Graph {
  public:
  int totalEdges = 0;
  map<char, list<Node*>> adjList;

  Graph(int);
  void addEdge(char, char, int);
  void printGraph();
};

Graph::Graph(int numberEdges) {
  this->totalEdges = numberEdges;
}

void Graph::addEdge(char from, char to, int cost) {
  Node* toNode = new Node(to, cost);
  Node* fromNode = new Node(from, cost);
  this->adjList[from].push_back(toNode);
  this->adjList[to].push_back(fromNode);
}

void Graph::printGraph() {
  for (auto el : this->adjList) {
    cout << el.first << ": ";
    for (auto node : el.second) {
      cout << " " << node->value << " (" << node->cost <<  ")";
    }
    cout << "\n";
  }
}
