//
// Created by Carla Onate on 23/09/22.
//

#include "graph.h"
using namespace std;

int main () {
  TRIE graph;
  graph.addText("abc");
  graph.addText("huevos");
  graph.addText("hueva");
  graph.addText("abbc");
  graph.addText("acda");
  graph.searchTrie("abbcdadsg");
}

