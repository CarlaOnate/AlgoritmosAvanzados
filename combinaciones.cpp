#include <iostream>
#include <vector>
#include <tuple>
#include <string>

using namespace std;

void printArray(vector<vector<char> > lista) {
  for (vector<char> el : lista) {
    cout << " [ ";
    for (char el2: el) {
      cout << " " << el2 << " ";
    }
    cout << " ] \n";
  }
  cout << "\n";
}

void printArray(vector<char> lista) {
  cout << " [ ";
  for (char el: lista) {
    cout << " " << el << " ";
  }
  cout << " ] ";
  cout << "\n";
}

//Sacado de internet - no entiendo como esto sirve
void combinaciones_nmms (vector<char> lista, vector<char> subset, char comparar, int comparaciones, int size) {
  if (comparaciones >= size) { // termino con ese subset
      cout << "( ";
      for (const auto& item : subset) {
          cout << item << " ";
      }
      cout << ")" << endl;
      return;
  }

  subset.push_back(comparar);
  combinaciones_nmms(lista, subset, lista[comparaciones + 1], comparaciones + 1, size);
  subset.pop_back();
  combinaciones_nmms(lista, subset, lista[comparaciones + 1], comparaciones + 1, size);
}

void getCombination (vector<char> letras, vector<vector<char> > combinaciones, int pivote) { // O(N)
  // https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1126/lectures/07/Slides07.pdf
  // IMPORTANT: Combinations are different from permutation because the order is not important but the uniqueness of each combination within the whole.
  // A B C D
  // B C D
  // C D
  // D
  // vacio

  // termina recursion
  if (pivote == letras.size()) {
    printArray(combinaciones);
    return; // Combinations  already has all the values
  }

  int combSize = combinaciones.size(); // Store size to prevent extra cycles after new combinations are added
  for(int i = 0; i < combSize; i++) { // O(c + 1) - NOT SURE
    vector<char> el = combinaciones[i];
    vector<char> tempVector = el; // store current combination in another vector
    auto it = tempVector.insert(tempVector.begin(), letras[pivote]); // to that combination add the pivot letter to make new combination - A -> AB, ...
    combinaciones.push_back(tempVector); // Push the new combination to the vector to store it
  }

  // IMPORTANT: The previous combinations are not modified during the cycle because a copy of that combination is used to make new combination and the push it.
  // Since you only cycle the current amount of combination, the newer combinations added are not cycled more than 1 time, otherwise the size of the vector would increase
  // and some combinations would be repeated.

  vector<char> tempValue;
  tempValue.push_back(letras[pivote]); // push the pivot as a combination - as if base case
  combinaciones.push_back(tempValue);
  getCombination(letras, combinaciones, pivote + 1); // Get next combination using now next pivot
}

int main () {
  vector<char> letras;
  vector<string> letras2;
  vector<char> opciones;
  vector<vector<char> > subset;
  vector<char> subset2;

  letras.push_back('A');
  letras.push_back('B');
  letras.push_back('C');
  letras.push_back('D');

  combinaciones_nmms(letras, subset2, letras[0], 0, letras.size());
  getCombination(letras, subset, 0);
  return 0;
}