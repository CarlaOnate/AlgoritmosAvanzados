#include <iostream>
using namespace std;

void printArray (int lista[], int n) {
  cout << "El array es => \n";
  for(int i = 0; i < n; i++) {
    cout << lista[i] << " ";
  }
  cout << endl;
}

void insertionSort (int lista[], int size) {
  for (int i = 0; i < size; i++) {
    int j = i - 1;
    while(j >= 0 && lista[i] < lista[j]) {
      cout << "swapped =>  " << lista[i] << " por " << lista[j] << endl;
      int prevListValue = lista[i];
      lista[i] = lista[j];
      lista[j] = prevListValue;
      printArray(lista, size);
      j--;
    }

/*     for (int j = i; j >= 0; j--) {
      cout << "pivote =>  " << lista[i] << "  <  " << lista[j] << endl;
      if (lista[j] > lista[i]) {
        cout << "swapped =>  " << lista[i] << " por " << lista[j] << endl;
        int prevListValue = lista[i];
        lista[i] = lista[j];
        lista[j] = prevListValue;
        printArray(lista, size);
      }
    } */
  }

  printArray(lista, size);
}

int main () {
  int list[] = { 8, 7, 6, 5, 4, 1 };
  insertionSort(list, 6);
  return 0;
}