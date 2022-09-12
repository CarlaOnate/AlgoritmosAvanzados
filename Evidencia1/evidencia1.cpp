//
// Created by Carla Onate on 04/09/22.
//
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>

void printPatterns(std::vector<std::vector<std::tuple<std::string, int, int>>> patternsFound, std::vector<std::string> patterns) {
  for (int i = 0; i < patternsFound.size(); i++) {
    if (patternsFound[i].empty()) {
      std::cout << "\t| patron => " << patterns[i] << " |\n";
      std::cout << "\t\t(false) No se encontró patrón " << "\n";
    }
    for (auto pattern : patternsFound[i]) {
      std::cout << "\t| patron => " << std::get<0>(pattern) << " |\n";
      std::cout << "\t\t(true) Se encontro patrón en linea: " << std::get<1>(pattern) << ", indice: " << std::get<2>(pattern) << "\n";
    }
  }
}

bool zAlgoMultiplePatterns(std::vector<std::string> patterns, std::string text) {
  int lineIndex = 0;
  int fileLine = 1;
  std::string patternFound;
  int L = 1; // traverses the z array
  int R = 1; // traverses the string - first index is always 0 since its form same patter concatenated
  int P = 0; // traverses the pattern
  int C = 0; // counts pattern matches

  std::vector<int> zArr(text.size());
  std::vector<std::vector<std::tuple<std::string, int, int>>> patternsFound(patterns.size()); // (pattern, lineInFileOfPattern, indexWherePatternWasFound)
  zArr[L] = 0;

  while (L < text.size()) {
    // if match - move R window and P to check next of the pattern - count in C the number of matches L index remains the same
    if (text[R] == '$') {
      fileLine++;
      lineIndex = 0;
    }

    for (int i = 0; i < patterns.size(); i++) {
      while (text[R] == patterns[i][P] && P < patterns[i].size()) { // while pattern matches move right window and count matches
        C++; // Add match
        R++; // Move window
        P++; // Move pattern
      }
      // No match
      if (C == patterns[i].size()) { // Exact match with current pattern
        std::tuple<std::string, int, int> pattern = std::make_tuple(patterns[i], fileLine, lineIndex);
        patternsFound[i].push_back(pattern);
      }
      C = 0; P = 0; R = L; // Reset values but dont move left window
    }
    zArr[L] = C;  // Reset values to make new window starting from L, reset counter of matches
    L++; R = L;
    lineIndex++;
  }

  printPatterns(patternsFound, patterns);
  return !patternsFound.empty();
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

std::tuple<std::string, std::vector<std::string> > readFileToVectorAndString (std::string filename) {
  std::ifstream file (filename);
  std::string line;
  std::string resultingString;
  std::vector<std::string> resultingVector;
  if (file.is_open()) {
    while ( getline (file, line) ) {
      resultingVector.push_back(line);
      resultingString += '$'; // To show end of line
      resultingString += line;
    }
    file.close();
  }
  std::tuple<std::string, std::vector<std::string> > fileResult = std::make_tuple(resultingString, resultingVector);
  return fileResult;
}

void searchPatternInFile (std::string stringTransmission, std::string msg) {
  std::vector<std::string> patternCode1 = readFileToVector("../github/Evidencia1/mcode1.txt");
  std::vector<std::string> patternCode2 = readFileToVector("../github/Evidencia1/mcode2.txt");
  std::vector<std::string> patternCode3 = readFileToVector("../github/Evidencia1/mcode3.txt");
  std::tuple<int, int> matchesIndex;
  //Part 1 - find if pattern is in transmission files
  std::cout << "\n" << msg << " -> mcode1 \n\n";
  zAlgoMultiplePatterns(patternCode1, stringTransmission);
  std::cout << "\n" << msg << " -> mcode2 \n\n";
  zAlgoMultiplePatterns(patternCode2, stringTransmission);
  std::cout << "\n" << msg << " -> mcode3 \n\n";
  zAlgoMultiplePatterns(patternCode3, stringTransmission);
}

std::tuple<std::string, int, int> getPalindrome(std::string text, int start, int end) {
  std::string palindrome;
  for(int i = start; i <= end && i < text.length(); i++) {
    if (text[i] != '#') {
      palindrome += text[i];
    }
  }
  std::tuple<std::string, int, int> resultTuple = std::make_tuple(palindrome, start, end);
  return resultTuple;
}

std::string makeStringOdd (std::string &text) {
  std::string result;
  for (char i : text) {
    result += '#';
    result += i;
  }
  result += '#';
  return result;
}

std::tuple<std::string, int, int> manacher (std::string text) {
  std::string oddText = makeStringOdd(text);
  int R = 0; // stores right of lps
  int C = 0; // store center of longest palindromic seq
  int maxLen = 0; // longest palindrome seq length
  int palindromeCenter = 0;
  std::vector<int> p (oddText.length());

  for (int i = 0; i < oddText.length(); i++) {
    int mirror = (2 * C - i);

    if (i > R) { // Optimize steps
      p[i] = std::min(R - i, p[mirror]);
    }

    while (oddText[i + (1 + p[i])] == oddText[i - (p[i] + 1)]) {
      // Since always is odd sum + 1 to step over #
      p[i]++;
    }

    if (p[i] > maxLen) { // biggest palindrome found, replace values
      maxLen = p[i];
      palindromeCenter = i;
    }

    if (i + p[i] > R) { // current palindrome goes over boundary
      C = i;
      R = i + p[i];
    }
  }

  int start = (palindromeCenter - maxLen)/2 < 0 ? 0 : (palindromeCenter - maxLen)/2;
  int end = (start + maxLen - 1) > text.length() ? text.length() : (start + maxLen - 1);
  return getPalindrome(text, start, end);
}

void largestPalindrome (std::vector<std::string> texts, std::string msg) {
  std::tuple<std::string, int, int> bestPalindrome;
  int lineInFile = 0;
  int palindromeFile = 0;

  for (auto text : texts) {
    lineInFile++;
    std::tuple<std::string, int, int> palindromeFound = manacher(text);
    if (std::get<0>(palindromeFound).length() > std::get<0>(bestPalindrome).length()) {
      bestPalindrome = palindromeFound;
      palindromeFile = lineInFile;
    }
  }

  std::cout << msg << "\n";
  std::cout << "\t Palindromo mas largo encontrado: " << std::get<0>(bestPalindrome) << "\n";
  std::cout << "\t Linea: " << palindromeFile << "  -   indice inicial:" << std::get<1>(bestPalindrome) << "  -   indice final: " << std::get<2>(bestPalindrome) << "\n";
}

// DONE: SI LO HACEMOS COMO 1 STRING GIGANTE PONERLE UN CARACTER DE SALTO DE LINEA O SINO BUSCAR PATRON EN CADA LINEA Y NO JUNTAR DESPUES DEL SALTO DE LINEA
// TODO: VALIDACIONES QUE TEXTO SEA DE 0 A 9 Y DE A a F. -> no se que mas validaciones
// TODO: REMOVE COMMENTS

int main () {
  std::tuple<std::string, std::vector<std::string> > transmission1 = readFileToVectorAndString("../github/Evidencia1/transmision1.txt"); // Todo: see how to add absolut path
  std::tuple<std::string, std::vector<std::string> > transmission2 = readFileToVectorAndString("../github/Evidencia1/transmision2.txt"); // Todo: see how to add absolut path
  std::cout << "\nParte 1\n";
  // Parte 1 - casi casi falta indice correcto
  searchPatternInFile(std::get<0>(transmission1), "Transmición 1");
  searchPatternInFile(std::get<0>(transmission2), "Transmición 2");
  std::cout << "\nParte 2\n";
  // Parte 2
  largestPalindrome(std::get<1>(transmission1), "Transmición 1");
  largestPalindrome(std::get<1>(transmission2), "Transmición 2");

  return 0;
}
