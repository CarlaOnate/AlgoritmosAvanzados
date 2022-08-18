#include <iostream>
#include <vector>
using namespace std;

void printArray (int lista[], int begin, int end) {
  cout << "El array es =>    ";
  for(int i = begin; i <= end; i++) {
    cout << lista[i] << " ";
  }
  cout << endl;
}

// Junta dos mitades
void merge (int lista[], int begin, int mid, int end) {
  vector<int> mergedArray;
  int leftArrIndex = begin, rightArrIndex = mid + 1, mergedIndex = 0;

  // cycle both arrays
  while (leftArrIndex <= mid && rightArrIndex <= end) {
    /* if (lista[leftArrIndex] < lista[rightArrIndex]) { */ // menor a mayor
    if (lista[leftArrIndex] > lista[rightArrIndex]) { // mayor a menor
      // el from left list goes first in merged array
      mergedArray.push_back(lista[leftArrIndex]);
      leftArrIndex += 1;
    } else {
      // el from right list goes first in merged array
      mergedArray.push_back(lista[rightArrIndex]);
      rightArrIndex += 1;
    }
    mergedIndex += 1;
  };

  //if values missing to be added to mergedArray add them
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

  //copy merged array into lista
  mergedIndex = 0;
  for(int index = begin; index <= end; index++) {
    lista[index] = mergedArray[mergedIndex];
    mergedIndex += 1;
  };
}

// Separa mitades iguales -> lista se mantiene igual pero lo indices de donde empieza cada sublista van cambiando.
void mergeSort (int lista[], int begin, int end) {
  if(begin >= end) { // list has only 1 element
    return;
  }

  int mid = begin + (end - begin) / 2;
  mergeSort(lista, begin, mid); // separa primera mitad  -> divide en soluciones mas pequeñas
  mergeSort(lista, mid + 1, end); // separa segunda mitad
  merge(lista, begin, mid, end); //junta las dos mitades -> combina el resultado de las soluciones mas pequeñas
};

int main () {
  int lista[6] = { 2, 8 ,16, 1, 21, 13 };
  int listaSize = sizeof(lista)/sizeof(lista[0]);
  mergeSort(lista, 0, listaSize - 1);
  printArray(lista, 0, 5);

  // Para leer de un archivo como en act
  /*   string fileName;
  int listLength, currentListIndex = 0;
  cin >> listLength;
  int lista[listLength - 1];

  while (currentListIndex < listLength) {
    int value;
    cin >> value;
    lista[currentListIndex] = value;
    currentListIndex++;
  }

  printArray(lista, 0, listLength - 1);

  int listaSize = sizeof(lista)/sizeof(lista[0]);
  mergeSort(lista, 0, listaSize);
  printArray(lista, 0, listaSize);
  return 0; */
  return 0;
};