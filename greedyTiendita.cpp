#include <iostream>
#include <vector>
using namespace std;

// funcion de seleccion, factibilidad y listado de candidatos y seleccionados

vector<int> selected;
int selectedTime;

void printArr (vector<int> lista) {
  for(int i = 0; i < lista.size(); i++) { // O n
    cout << " " << lista[i] << " ";
  }
  cout << "\n";
}

int getTotalTime (vector<int> list) {
  int totalTime = 0, clientsTime = 0;

  // selected[0] + (selected[0] + selected[1]) + (selected[0] + selected[1] + selected[2]);
  for (int i = 0; i < list.size(); i++) {
    for (int j = 0; j <= i; j++) {
      clientsTime += list[j];
    }
    totalTime += clientsTime;
    clientsTime = 0;
  }

  return totalTime;
}

void optimalSolution(vector<int>& tempSelected) {
  int tempSelectedTime = getTotalTime(tempSelected);
  selectedTime = getTotalTime(selected);

  if (tempSelectedTime < selectedTime || selectedTime == 0) {
    tempSelected.swap(selected);
  }

  tempSelected.erase(tempSelected.begin(), tempSelected.end());
}

void selectCandidate (int candidateIndex, vector<int>& candidates, vector<int>& tempSelected) {
  tempSelected.push_back(candidates[candidateIndex]);
}

void greedy (vector<int> clientes) {
  vector<int> tempSelected;

  // No da todas las combinaciones

  for(int i = 0; i < clientes.size(); i++) {
    selectCandidate(i, clientes, tempSelected);
    for(int j = 0; j < clientes.size(); j++) {
      if (j != i) {
        selectCandidate(j, clientes, tempSelected);
      }
    }
    printArr(tempSelected);
    optimalSolution(tempSelected);
  }
}

void permutation (vector<int> lista) { // O(n)
  int iteraciones, combinaciones = 1;
  for (int i = 1; i <= lista.size(); i++) { // O(n)
    combinaciones *= i;
  }

  iteraciones = combinaciones/lista.size();
  cout << "combinaciones totales=> " << combinaciones << " iteracion por pivote => " << combinaciones/lista.size() << "\n";

  for(int i = 0; i < lista.size(); i++) { // O(n*n-1) => // O(n^2)
    int loopNumber, movingIndex = 1;
    if (i != 0) {
      vector<int>::iterator it = lista.begin();
      // swap i el to be the first el in list -> move other elements to the right
      int newPivot = lista[i];
      lista.erase(lista.begin() + i);
      lista.insert(it, newPivot);
    }

    // nueva combinación
    while (loopNumber <= iteraciones + 1) { // O(n-1) - se tiene 1 pivote y se corren las combinaciones de n-1 valores

      cout << "Moving index => " << movingIndex << "   " << lista[movingIndex] << "\n";

      if (loopNumber == iteraciones + 1) {
        /* int temp = lista[movingIndex]; */
        // No es combinacion - hacer swap
      } else {
        // else -> hacer el swap revisando el moving index
        if (movingIndex == lista.size() - 1) {
          movingIndex = 1;
        }
        // swap movingIndex, al lugar derecho movingIndex + 1
        // nueva combinación
      }
      movingIndex += 1;
      loopNumber += 1;
    }
  }
}

int main () {
  vector<int> vect1;
  vect1.push_back(6);
  vect1.push_back(12);
  vect1.push_back(4);
  permutation(vect1);
  return 0;
}
