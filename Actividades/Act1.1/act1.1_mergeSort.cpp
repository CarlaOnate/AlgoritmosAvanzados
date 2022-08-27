#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

/* La implementación del mergeSort -> en esta implementacion no se separa el array literalmente sino que dependiendo de los valores begin y end se puede ir accesando los subarrays. */

void printArray (double lista[], int begin, int end) {
  cout << "El array es =>    ";
  for(int i = begin; i <= end; i++) {
    cout << lista[i] << " ";
  }
  cout << endl;
}

// Juntar todos los subarrays y al hacerlo irlos ordenando de mayor a menor. Recibe indices para identificar el subarray
void merge (double lista[], int begin, int mid, int end) {
  vector<double> mergedArray;
  int leftArrIndex = begin, rightArrIndex = mid + 1, mergedIndex = 0;

  while (leftArrIndex <= mid && rightArrIndex <= end) {
    if (lista[leftArrIndex] > lista[rightArrIndex]) {
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
void mergeSort (double lista[], int begin, int end) {
  if(begin >= end) {
    return;
  }

  int mid = begin + (end - begin) / 2;
  mergeSort(lista, begin, mid);
  mergeSort(lista, mid + 1, end);
  merge(lista, begin, mid, end);
};

// Lee un archivo de texto ordena los valores que recibe del txt
int main () {
  string fileName;
  int listLength, currentListIndex = 0;
  cin >> listLength;
  double lista[listLength - 1];

  while (currentListIndex < listLength) { // O(n) - copiar el archivo de n elementos y agregarlos en una array
    double value;
    cin >> value;
    lista[currentListIndex] = value;
    currentListIndex++;
  }

  int listaSize = sizeof(lista)/sizeof(lista[0]);
  mergeSort(lista, 0, listaSize);
  printArray(lista, 0, listaSize);
  return 0;
};