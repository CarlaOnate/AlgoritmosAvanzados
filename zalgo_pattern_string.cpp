//
// Created by Carla Onate on 02/09/22.
//

#include <string>
#include <vector>
#include <iostream>

void printZarr(std::vector<int> z) {
  for (auto el : z) {
    std::cout << " " << el << " ";
  }
  std::cout << "\n\n";
}

void zAlgo(std::string pattern, std::string text) {
  int L = 1; // traverses the z array
  int R = 1; // traverses the string - first index is always 0 since its form same patter concatenated
  int P = 0; // traverses the pattern
  int C = 0; // counts pattern matches

  text = pattern + ':' + text; // it can be used as the vector pattern - to save memory

  std::vector<int> zArr(text.size());
  zArr[L] = 0;
  // concatenate patter with string - in between char that is not in pattern
  // TODO: PODRIA SER RECURSIVO -> WHILE DE AFUERA MAYBE NO NECESARIO
  while (L < text.size()) {
    // if match - move R window and P to check next of the pattern - count in C the number of matches L index remains the same
    while (text[R] == pattern[P] && P < pattern.size()) { // while pattern matches move right window and count matches
      C++; // Add match
      R++; // Move window
      P++; // Move pattern
    }
    // No match
    zArr[L] = C;  // Reset values to make new window starting from L, reset counter of matches
    C = 0; P = 0; L++; R = L;
  }
  printZarr(zArr);
}

int main () {
  zAlgo("jojo", "aslkdfnakjban94235b6i2basdngipuasdgajojojoqwe89ryq9sdnvaojdndbvpiuasdhgp9");


  return 0;
}