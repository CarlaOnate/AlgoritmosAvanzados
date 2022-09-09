//
// Created by Carla Onate on 04/09/22.
//
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>

void printZarr(std::vector<int> z) {
  for (auto el : z) {
    std::cout << " " << el << " ";
  }
  std::cout << "\n\n";
}

void printSth(std::string text) {
  for (auto el : text) std::cout << el;
}

bool zAlgoMultiplePatterns(std::vector<std::string> patterns, std::string text) {
  // Todo: CORREGIR INDICE PARA IMPRIMIRLO
  int matchFound = 0;
  int matchIndex = -1;
  int fileLine = 1;
  std::string patternFound;
  int L = 1; // traverses the z array
  int R = 1; // traverses the string - first index is always 0 since its form same patter concatenated
  int P = 0; // traverses the pattern
  int C = 0; // counts pattern matches

  std::vector<int> zArr(text.size());
  zArr[L] = 0;

  while (L < text.size() && matchFound == 0) { // We only need one match from mcode files
    // if match - move R window and P to check next of the pattern - count in C the number of matches L index remains the same
    if (text[R] == '$') fileLine++; matchIndex = 0;
    for (auto & el : patterns) {
      while (text[R] == el[P] && P < el.size()) { // while pattern matches move right window and count matches
        C++; // Add match
        R++; // Move window
        P++; // Move pattern
      }
      // No match
      if (C == el.size()) {
        matchFound++;
        matchIndex = L;
        patternFound = el;
        break;
      }
      C = 0; P = 0; R = L; // Reset values but dont move left window
    }
    // Print match
    zArr[L] = C;  // Reset values to make new window starting from L, reset counter of matches
    L++; R = L;
  }
  if (matchFound > 0) {
    std::cout << "\t patron => "; printSth(patternFound); std::cout << "\n";
    std::cout << "(true) Se encontro patrón en linea: " << fileLine << ", indice: " << matchIndex << "\n";
  }
  if (matchFound == 0) std::cout << "(false) No se encontraron coincidencias" << "\n";
  return matchFound > 0;
}

std::string readFileToString (std::string filename) {
  std::ifstream file (filename); // this is equivalent to the above
  std::string line;
  std::string result;
  if (file.is_open()) {
    while ( getline (file, line) ) {
      result += '$';
      result += line;
    }
    file.close();
  }
  return result;
}

std::vector<std::string> readFileToVector (std::string filename) {
  std::ifstream file (filename); // this is equivalent to the above
  std::string line;
  std::vector<std::string> result;
  if (file.is_open()) {
    while ( getline (file, line) ) {
      result.push_back(line);
    }
    file.close();
  }
  return result;
}

void searchPatternInFile (std::string stringTransmission, std::string msg) {
  std::vector<std::string> patternCode1 = readFileToVector("../github/Evidencia1/mcode1.txt");
  std::vector<std::string> patternCode2 = readFileToVector("../github/Evidencia1/mcode2.txt");
  std::vector<std::string> patternCode3 = readFileToVector("../github/Evidencia1/mcode3.txt");
  std::tuple<int, int> matchesIndex;
  //Part 1 - find if pattern is in transmission files
  std::cout << "\t" << msg << " -> mcode1\n";
  std::cout << zAlgoMultiplePatterns(patternCode1, stringTransmission) << "\n";
  std::cout << "\t" << msg << " -> mcode2\n";
  std::cout << zAlgoMultiplePatterns(patternCode2, stringTransmission) << "\n";
  std::cout << "\t" << msg << " -> mcode3\n";
  std::cout << zAlgoMultiplePatterns(patternCode3, stringTransmission) << "\n";
}

void printPalindrome(std::string text, int length, int center) {
  int start = center - (length - 2);
  std::cout << "\n";
  for(int i = start; i <= start + (length - 1)*2; i++) {
    if (text[i] == '#') {
      std::cout << " ";
    } else {
      std::cout << text[i];
    }
  }
  std::cout << "\n";
}

std::string makeStringOdd (std::string &text) {
  std::string result;
  result.push_back('#');
  for (char i : text) {
    result.push_back(i);
    result.push_back('#');
  }
  return result;
}

void manacher (std::string text) {
  int sizeArray = text.length();
  std::string oddText = text;
  if (text.length() % 2 == 0) {
    sizeArray = 2 * text.length() + 1;
    oddText = makeStringOdd(text);
  }
  int palindromeLength = 0;
  int palindromeCenter = 0;
  int centro = 0;
  int R = 0;
  std::vector<int> P (sizeArray);

  std::cout << "ODD TEXT => " << oddText << "\n";

  // Un ciclo es centro
  for (int i = 0; i < oddText.length() - 1; i++) {
    if (i < R) { // Centro actual esta dentro del rango del palindromo mas grande encontrado anteriormente
      P[i] = std::min((R - i), (centro*2 - i));
    }

    while (oddText[i - (P[i] - 1)] == oddText[i + (P[i] + 1)]) { // extienden left y right bounds
      P[i]++;
    }

    if (i + P[i] > R) { // Optimizar para recorrer menos pasos - creo
      centro = i;
      R = i + P[i]; // Avanza R a nueva posición encontrada en ciclo anterior
    }

    if (P[i] > palindromeLength) { // sustituir nueva palidromo mas largo
      palindromeCenter = i;
      palindromeLength = P[i];
    }
  }

  std::cout << "palindrome Length =>" << palindromeLength <<"\n";
  std::cout << "palindrome Center =>" << palindromeCenter <<"\n";
  printPalindrome(oddText, palindromeLength, palindromeCenter);
}

void largestPalindrome (std::string text) {
  manacher(text);
}

// DONE: SI LO HACEMOS COMO 1 STRING GIGANTE PONERLE UN CARACTER DE SALTO DE LINEA O SINO BUSCAR PATRON EN CADA LINEA Y NO JUNTAR DESPUES DEL SALTO DE LINEA

int main () {
  //std::vector<std::string> stringTransmission1 = readFileToVector("../github/Evidencia1/transmision1.txt"); // Todo: see how to add absolut path
  //std::vector<std::string> stringTransmission2 = readFileToVector("../github/Evidencia1/transmision2.txt"); // Todo: see how to add absolut path
  std::string stringTransmission1 = readFileToString("../github/Evidencia1/transmision1.txt"); // Todo: see how to add absolut path
  std::string stringTransmission2 = readFileToString("../github/Evidencia1/transmision2.txt"); // Todo: see how to add absolut path
  // Parte 1
  searchPatternInFile(stringTransmission1, "Transmición 1");
  searchPatternInFile(stringTransmission2, "Transmición 2");
  // Parte 2
  //largestPalindrome(stringTransmission1);
  //largestPalindrome(stringTransmission2);

  return 0;
}
