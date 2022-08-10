#include <iostream>
using namespace std;

void printArray (int lista[], int n) {
  cout << "El array es => \n";
  for(int i = 0; i < n; i++) {
    cout << lista[i] << " ";
  }
  cout << endl;
}

void selectionSort (int lista[], int n) {
  int min = 0, prevListValue;

  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (lista[j] < lista[min]) {
        min = j;
      }
    }
    prevListValue = lista[i];
    lista[i] = lista[min];
    lista[min] = prevListValue;
  }

  printArray(lista, n);
}

int main () {
  int list[] = { 2, 5, 1, 3 };
  selectionSort(list, 4);

  return 0;
}