// Este programa es la solucion a la evidencia 1 que tiene 3 funcionalidades.
// Encontrar patrones en archivos de texto, encontrar palindromo mas largo en
// archivos de texto y encontrar el substring mas largo entre dos archivos de
// texto Autores: Carla Oñate Gardella              A01653555
//                Octavio Augusto Alemán Esparza    A01660702
// Fecha creado: 04/09/22

#include "util.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

double

    mayorCoincidence[2][3] = {{0, 0, 0}, {0, 0, 0}};
string coincidence = " ";

// Función para imprimir patrones encontrados en parte 1. Recibe la lista de
// patrones encontraods y patrones que se buscaron. No regresa nada ya que la
// impresión se hace dentro de la función.
void printPatterns(
    vector<vector<tuple<string, int, int>>> patternsFound,
    vector<string> patterns) { // O(n*p) -> n de tamaño de patrones a encontrar,
                               // p de patrones encontrados
  for (int i = 0; i < patternsFound.size(); i++) {
    if (patternsFound[i].empty()) {
      cout << "\t| patron => " << patterns[i] << " |\n";
      cout << "\t\t(false) No se encontró patrón "
           << "\n";
    } else {
      cout << "\t| patron => " << patterns[i] << " |\n";
      for (auto pattern : patternsFound[i]) {
        cout << "\t\t(true) Se encontro patrón en linea: " << get<1>(pattern)
             << ", indice: " << get<2>(pattern) << "\n";
      }
    }
  }
}

// Función para encontrar patrones en 1 archivo de transmision - parte 1.
// Regresa un verdadero o false si encontró algun patrón, recibe la lista de
// patrones y el texto en un string separado por $ para identificar cambio de
// linea
bool zAlgoMultiplePatterns(vector<string> patterns,
                           string text) { // O(n*p) -> n del tamaño del string,
                                          // p del numero de patrones a comparar
  int lineIndex = 0;
  int fileLine = 1;
  string patternFound;
  int L = 1; // traverses the z array
  int R = 1; // traverses the string - first index is always 0 since its form
  // same patter concatenated
  int P = 0; // traverses the pattern
  int C = 0; // counts pattern matches

  vector<int> zArr(text.size());
  vector<vector<tuple<string, int, int>>> patternsFound(
      patterns
          .size()); // (pattern, lineInFileOfPattern, indexWherePatternWasFound)
  zArr[L] = 0;

  while (L < text.size()) {
    // if match - move R window and P to check next of the pattern - count in C
    // the number of matches L index remains the same
    if (text[R] == '$') {
      fileLine++;
      lineIndex = 0;
    }

    for (int i = 0; i < patterns.size(); i++) {
      while (text[R] == patterns[i][P] &&
             P < patterns[i].size()) { // while pattern matches move right
        // window and count matches
        C++; // Add match
        R++; // Move window
        P++; // Move pattern
      }
      // No match
      if (C == patterns[i].size()) { // Exact match with current pattern
        tuple<string, int, int> pattern =
            make_tuple(patterns[i], fileLine, lineIndex);
        patternsFound[i].push_back(pattern);
      }
      C = 0;
      P = 0;
      R = L; // Reset values but dont move left window
    }
    zArr[L] = C; // Reset values to make new window starting from L, reset
    // counter of matches
    L++;
    R = L;
    lineIndex++;
  }

  printPatterns(patternsFound, patterns);
  return !patternsFound.empty();
}

// Convierte un archivo de texto a un vector de strings. Recibe el nombre de
// archivo a convertir. retresa la lista de strings
vector<string>
readFileToVector(string filename) { // O(n) -> del numero de lineas del archivo
  ifstream file(filename);          // this is equivalent to the above
  string line;
  vector<string> result;
  if (file.is_open()) {
    while (getline(file, line)) {
      if (line.length() == 0) {
        result.push_back("linea vacía");
      } else {
        result.push_back(line);
      }
    }
    file.close();
  }
  return result;
}

// Genera una tupla que regresa el archivo como un string separado por $ para
// indentificar salto de linea o como una lista de lineas.Recibe el nombre del
// archivo a convertir y regresa la tupla mencionada anteriormente.
tuple<string, vector<string>> readFileToVectorAndString(
    string filename) { // O(n) -> del numero de lineas del archivo
  ifstream file(filename);
  string line;
  string resultingString;
  vector<string> resultingVector;
  if (file.is_open()) {
    while (getline(file, line)) {
      resultingVector.push_back(line);
      resultingString += '$'; // To show end of line
      resultingString += line;
    }
    file.close();
  }
  tuple<string, vector<string>> fileResult =
      make_tuple(resultingString, resultingVector);
  return fileResult;
}

// Función que se llaman en main para iniciar la busqueda de patrones en los
// archivos de transmision. Recibe la transmision como un string y un msg a
// imprirmi para indetificar que archivo se esta analizando. No regresa nada ya
// que la impresión se hace dentro de zAlgoMultiplePatterns
void searchPatternInFile(string stringTransmission, string msg) { // O(n*p)
  vector<string> patternCode1 = readFileToVector("mcode1.txt");
  vector<string> patternCode2 = readFileToVector("mcode2.txt");
  vector<string> patternCode3 = readFileToVector("mcode3.txt");
  tuple<int, int> matchesIndex;
  // Part 1 - find if pattern is in transmission files
  cout << "\n" << msg << " -> mcode1 \n\n";
  zAlgoMultiplePatterns(patternCode1, stringTransmission); // O(n*p)
  cout << "\n" << msg << " -> mcode2 \n\n";
  zAlgoMultiplePatterns(patternCode2, stringTransmission);
  cout << "\n" << msg << " -> mcode3 \n\n";
  zAlgoMultiplePatterns(patternCode3, stringTransmission);
}

// Función para conseguir el palindromo encontrado y regresar el resultado.
// Recibe el texto del cual se obtuve el palindromo, el inicio y final de donde
// se encuentra en palindromo. Regresa ua tupla con el palindromo encontrado,
// posicion inicial y final en el archivo.
tuple<string, int, int> getPalindrome(string text, int start,
                                      int end) { // O(n) -> del texto que reciba
  string palindrome;
  for (int i = start; i <= end && i < text.length(); i++) {
    if (text[i] != '#') {
      palindrome += text[i];
    }
  }
  tuple<string, int, int> resultTuple = make_tuple(palindrome, start, end);
  return resultTuple;
}

// Función para generar un string impar el cual se usa en la función de
// manacher. Recibe el texto a modificar y regresa el texto impar modificado con
// # entre los caracteres.
string makeStringOdd(string &text) { // O(n) -> del texto que reciba
  string result;
  for (char i : text) {
    result += '#';
    result += i;
  }
  result += '#';
  return result;
}

// Función principal de la parte 2 donde se encuentra el palindromo mas grande
// de un texto. Recibe la un texto que es una linea de un archivo de transmision
// y regresa una tupla con el palindromo encontrado.
tuple<string, int, int>
manacher(string text) { // O(n) -> del string que reciba como parametro
  string oddText = makeStringOdd(text);
  int R = 0;      // stores right of lps
  int C = 0;      // store center of longest palindromic seq
  int maxLen = 0; // longest palindrome seq length
  int palindromeCenter = 0;
  vector<int> p(oddText.length());

  for (int i = 0; i < oddText.length(); i++) {
    int mirror = (2 * C - i);

    if (i > R) { // Optimize steps
      p[i] = min(R - i, p[mirror]);
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

  int start =
      (palindromeCenter - maxLen) / 2 < 0 ? 0 : (palindromeCenter - maxLen) / 2;
  int end = (start + maxLen - 1) > text.length() ? text.length()
                                                 : (start + maxLen - 1);
  return getPalindrome(text, start, end);
}

// Funcion que se llama desde main para iniciar la parte 2. Recibe la lista de
// lineas del archivo de tranmision y un msg a imprimir para identificar que
// archivo se esta analizando. Cicla la lista de lineas del archivo y va
// revisando el palindromo resultante para despues imprimir solo el mejor
// encontrado. No regresa nada ya que se imprime dentro de la función.
void largestPalindrome(vector<string> texts,
                       string msg) { // O(n*m) -> numero de lineas del archivo *
                                     // tamaño de string a revisar
  tuple<string, int, int> bestPalindrome;
  int lineInFile = 0;
  int palindromeFile = 0;

  for (auto text : texts) { // O(n)
    lineInFile++;
    tuple<string, int, int> palindromeFound =
        manacher(text); // O(m) -> m siendo el tamaño del string a revisar
    if (get<0>(palindromeFound).length() > get<0>(bestPalindrome).length()) {
      bestPalindrome = palindromeFound;
      palindromeFile = lineInFile;
    }
  }

  cout << msg << "\n";
  cout << "\t Palindromo mas largo encontrado: " << get<0>(bestPalindrome)
       << "\n";
  cout << "\t Linea: " << palindromeFile
       << "  -   indice inicial:" << get<1>(bestPalindrome)
       << "  -   indice final: " << get<2>(bestPalindrome) << "\n";
}

/*********************************TERCERA
 * PARTE****************************************/
// Funcion que hace uso del algoritmo de longest common substring para encontrar
// la coincidencia más larga entre los archivos de transmision1.txt y
// transmision2.txt . Recibe como parametros una linea de cada archivo para
// compararlas entre sí, además del número de dichas lineas.
void findCommon(string line, string line1, int lineNumber2, int lineNumber1) {

  int n = line.length();  // Se declara la variable n del tamaño de la primera
                          // linea recibida.
  int m = line1.length(); // Se declara la variable m del tamaño de la segunda
                          // linea recibida.

  int matrix[n + 1][m + 1]; // Se declara una matriz de tamaño (n + 1) * (m + 1)
                            // Esta matriz contendra posteriormente las
                            // coincidencias entre los strings a comparar.

  for (int i = 0; i <= n;
       i++) { // Se igualan a 0 todas las pocisiones dentro de la matriz.
    for (int j = 0; j <= m; j++) {
      matrix[i][j] = 0;
    }
  }

  int mayor =
      mayorCoincidence[0][0]; // Se declara la variable mayor, la cual lleva el
                              // registro de la coincidencia mas larga. Se
                              // asigna el valor 0 a la variable mayor.

  for (int i = 1; i <= n;
       i++) { // Dos ciclos for anidados se encargan de hacer la comparacion
              // caracter por caracter del primer string, con los caracteres del
              // segundo.
    for (int j = 1; j <= m; j++) {
      if (line[i - 1] ==
          line1[j - 1]) { // Si los caracteres comparados son iguales.
        matrix[i][j] =
            matrix[i - 1][j - 1] + 1; // registra en la casilla actual el valor
                                      // de la casilla en diagonal anterior + 1.

        if (matrix[i][j] > mayor) { // Si el valor de la casilla actual es mayor
                                    // al valor mas grande guardado.
          mayor = matrix[i][j]; // Registra el valor de la casilla actual como
                                // el neuvo valor mayor.

          // Para el primer string:
          mayorCoincidence[0][0] = mayor; // Registra el mayor valor.
          mayorCoincidence[0][1] =
              lineNumber1; // Registra el numero de linea (Del primer archivo).
          mayorCoincidence[0][2] =
              i; // Registra la posición final en el primer string.

          // Para el segundo string:
          mayorCoincidence[1][0] = mayor; // Registra el mayor valor.
          mayorCoincidence[1][1] =
              lineNumber2; // Registra el numero de linea (Del segundo archivo).
          mayorCoincidence[1][2] =
              j; // Registra la posicion final en el segundo string.

          coincidence = line.substr(
              i - mayor,
              mayor); // Registra en un nuevo string la region coincidente.
        }
      }
    }
  }
}

// Funcion que invoca dos archivos de entrada, transmision1.txt y
// transmision2.txt Mediante dos for anidados, toma una linea del primer archivo
// y la comparar con todas las lineas del segundo archivo, al invocar a la
// funcion findCommon() Si se encuentra alguna coincidencia, se registra en una
// matriz.
void findLongestCS(vector<string> file1, vector<string> file2) {
  int lineNumber =
      0; // Numero de linea en el archivo 1.                 // Numero de
  for (int i = 0; i < file1.size(); i++) {
    int lineNumber1 = 0;
    // Para las lineas del archivo 1
    for (int j = 0; j < file2.size(); j++) { // Para la slineas del archivo 2
      findCommon(file1[i], file2[j], lineNumber1,
                 lineNumber); // Invoca a la funcion findCommon.
      lineNumber1 += 1;       // Se añade 1 al contador de linea.
    }
    lineNumber += 1; // Se añade 1 al contador de linea.
  }

  if (mayorCoincidence[0][0] > 1) { // Si existen coincidencias mayores a 1
                                    // caracter, se imprimen los resultados
    cout << "La coincidencia más larga es: " << coincidence << "\n";
    cout << "Fue encontrada en: \n";
    cout << "transmision1.txt: -> Linea: " << mayorCoincidence[0][1] + 1;
    cout << "; Pos. Inicial: "
         << mayorCoincidence[0][2] - mayorCoincidence[0][0];
    cout << "; Pos. Final:   " << mayorCoincidence[0][2] - 1 << ". \n";
    cout << "transmision2.txt: -> Linea: " << mayorCoincidence[1][1] + 1;
    cout << "; Pos. Inicial: "
         << mayorCoincidence[1][2] - mayorCoincidence[1][0];
    cout << "; Pos. Final:   " << mayorCoincidence[1][2] - 1 << ". \n";
    cout << "Tamanio: " << mayorCoincidence[0][0] << "\n";
  } else {
    cout << "No existen coincidencias o estas no son mayores a 1 caracter.\n";
  }
}

// Función principal donde se llaman la parte 1, 2 y 3 en orden para ser
// mostradas en consola. Regresa un 0 al terminar indicando que ya se termino el
// programa.
int main() {

  if (validateFiles() == true && validateFileLines() == true) {
    std::tuple<std::string, std::vector<std::string>> transmission1 =
        readFileToVectorAndString("transmission1.txt");
    std::tuple<std::string, std::vector<std::string>> transmission2 =
        readFileToVectorAndString("transmission2.txt");
    std::cout << "\nParte 1\n";
    // Parte 1 - casi casi falta indice correcto
    searchPatternInFile(std::get<0>(transmission1), "Transmición 1");
    searchPatternInFile(std::get<0>(transmission2), "Transmición 2");
    std::cout << "\nParte 2\n";
    // Parte 2
    largestPalindrome(std::get<1>(transmission1), "Transmición 1");
    largestPalindrome(std::get<1>(transmission2), "Transmición 2");
    cout << "\nParte 3\n";
    // Parte 3
    findLongestCS(get<1>(transmission1), get<1>(transmission2));
  } else {
    cout << "Programa Terminado." << endl;
  }
}