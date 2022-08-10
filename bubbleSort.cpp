#include <iostream>
using namespace std;

void printArray (int lista[], int n) {
  cout << "El array es => \n";
  for(int i = 0; i < n; i++) {
    cout << lista[i] << " ";
  }
  cout << endl;
}

void bubbleSort (int lista[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if(lista[j] > lista[j+1]){
        int prev = lista[j+1];
        lista[j+1] = lista[j];
        lista[j] = prev;
      }
    }
  }

  printArray(lista, n);
}

int main () {
  int arr[] = { 7, 6, 3, 1 };
  bubbleSort(arr, 4);
  return 0;
}

