//
// Created by Carla Onate on 04/09/22.
//
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void printZarr(std::vector<int> z) {
  for (auto el : z) {
    std::cout << " " << el << " ";
  }
  std::cout << "\n\n";
}

std::vector<int> zAlgo(std::string pattern, std::string text) {
  int matchFound = 0;
  int L = 1; // traverses the z array
  int R = 1; // traverses the string - first index is always 0 since its form same patter concatenated
  int P = 0; // traverses the pattern
  int C = 0; // counts pattern matches

  text = pattern + ':' + text; // it can be used as the vector pattern - to save memory

  std::vector<int> zArr(text.size());
  zArr[L] = 0;
  // concatenate patter with string - in between char that is not in pattern

  while (L < text.size()) {
    // if match - move R window and P to check next of the pattern - count in C the number of matches L index remains the same
    while (text[R] == pattern[P] && P < pattern.size()) { // while pattern matches move right window and count matches
      C++; // Add match
      R++; // Move window
      P++; // Move pattern
    }
    // No match
    // Print match
    if (C == pattern.size()) matchFound++;
    zArr[L] = C;  // Reset values to make new window starting from L, reset counter of matches
    C = 0; P = 0; L++; R = L;
  }
  if (matchFound > 0) std::cout << "(true) Se encontro patrón en indice: " << L << "\n";
  if (matchFound == 0) std::cout << "(false) No se encontraron coincidencias" << "\n";
  return zArr;
}

std::string readFile (std::string filename) {
  std::ifstream file (filename); // this is equivalent to the above
  std::string line;
  std::string result;
  if (file.is_open()) {
    while ( getline (file, line) ) {
      result += '#';
      result += line;
    }
    file.close();
  }
  return result;
}

void searchPatternInFile () {
  std::string stringTransmission1 = readFile("../github/Evidencia1/transmision1.txt"); // Todo: see how to add absolut path
  std::string stringTransmission2 = readFile("../github/Evidencia1/transmision2.txt"); // Todo: see how to add absolut path
  std::string patternCode1 = readFile("../github/Evidencia1/mcode1.txt");
  std::string patternCode2 = readFile("../github/Evidencia1/mcode2.txt");
  std::string patternCode3 = readFile("../github/Evidencia1/mcode3.txt");
  //Part 1 - find if pattern is in transmission files
  std::vector<int> matchesTrans1Code1 = zAlgo(patternCode1, stringTransmission1);
  std::vector<int> matchesTrans1Code2 = zAlgo(patternCode2, stringTransmission1);
  std::vector<int> matchesTrans1Code3 = zAlgo(patternCode3, stringTransmission1);
  std::vector<int> matchesTrans2Code1 = zAlgo(patternCode1, stringTransmission2);
  std::vector<int> matchesTrans2Code2 = zAlgo(patternCode2, stringTransmission2);
  std::vector<int> matchesTrans2Code3 = zAlgo(patternCode3, stringTransmission2);
}

// DONE: SI LO HACEMOS COMO 1 STRING GIGANTE PONERLE UN CARACTER DE SALTO DE LINEA O SINO BUSCAR PATRON EN CADA LINEA Y NO JUNTAR DESPUES DEL SALTO DE LINEA

int main () {
  // Parte 1
  searchPatternInFile();
  // Parte 2

  return 0;
}
