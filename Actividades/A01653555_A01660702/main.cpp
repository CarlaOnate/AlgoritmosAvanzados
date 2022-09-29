/*
 * El siguiente programa calcula los sufijos de una palabra y los imprime de manera ordenada.
 */
// Octavio Augusto Aleman A01660702
// Carla Oñate Gardella A01653555
// Versión 20 de C++
// Complejidad: O(n^2)
//

#include <utility>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Funcion para imprimr las listas de sufijo
void printArr(vector<pair<int, string>> array) {
  for (auto par : array) {
    cout << "(" << par.first << " " << par.second << ")  ";
  }
  cout << "\n";
}

// Juntar todos los subarrays y al hacerlo irlos ordenando de mayor a menor. Recibe indices para identificar el subarray
// Recibo la lista de pares de sufijos separados anteriormente en mergeSort
void merge (vector<pair<int, string>> &lista, int begin, int mid, int end) {
  vector<pair<int, string>>  mergedArray;
  int leftArrIndex = begin, rightArrIndex = mid + 1, mergedIndex = 0;

  while (leftArrIndex <= mid && rightArrIndex <= end) {
    // if (lista[leftArrIndex].second > lista[rightArrIndex].second) {
    if (lista[leftArrIndex].second.compare(lista[rightArrIndex].second) < 0) {
      mergedArray.push_back(lista[leftArrIndex]);
      leftArrIndex += 1;
    } else {
      mergedArray.push_back(lista[rightArrIndex]);
      rightArrIndex += 1;
    }
    mergedIndex += 1;
  };

  while (leftArrIndex <= mid) {
    mergedArray.push_back(lista[leftArrIndex]);
    leftArrIndex += 1;
    mergedIndex += 1;
  }
  while(rightArrIndex <= end) {
    mergedArray.push_back(lista[rightArrIndex]);
    rightArrIndex += 1;
    mergedIndex += 1;
  }

  mergedIndex = 0;
  for(int index = begin; index <= end; index++) {
    lista[index] = mergedArray[mergedIndex];
    mergedIndex += 1;
  };
}

// Separa la lista completa en mitades haciendo llamadas recursivas con diferentes valores para begin y end
// Recibe la lista de pares con los sufijos obtenidos
void mergeSort (vector<pair<int, string>> &lista, int begin, int end) {
  if (begin >= end) {
    return;
  }
  int mid = begin + (end - begin) / 2;
  mergeSort(lista, begin, mid);
  mergeSort(lista, mid + 1, end);
  merge(lista, begin, mid, end);
};

void suffixArray (string text) { // O(n * nlogn) => O (n^2 * nlogn) => O(n^2)
  // separate each suffix in vector
  vector<pair<int, string>> suffixes;
  vector<pair<int, string>> orderedSuffix;
  string tempText = text;
  for (int i = 0; i < text.length(); i++) { // O(n)
    suffixes.push_back(make_pair(i, tempText));
    tempText.erase(tempText.begin());
  }
  cout << "Tabla sufijos\n";
  printArr(suffixes);
  // Ordenar el sufijo
  mergeSort(suffixes, 0, suffixes.size() - 1); // O(n logn)
  cout << "Tabla sufijos ordenados\n";
  printArr(suffixes);
}

int main () {
  string text;
  cout << "Ingrese texto: " << "\n";
  std::getline(std::cin,text);
  if (text.empty()) {
    cout << "No se aceptan cadenas vacias\n";
    return 0;
  }
  cout << "Texto ingresado => " << text << "\n";
  suffixArray(text);
}