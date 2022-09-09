//
// Created by Carla Onate on 06/09/22.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

// ciclo de i 1 a t length suma de 1 en 1
// guardas el mirror que es 2*C -i
// si i es menor que R ->
// mientras tanto derecha e izq coincidan
// se va guardando el contador en la matriz de longitudes
// si i + P[i] > R -> que el centro mas el numero de espejo es mayor a R ?? NO SE QUE PEDO CON ESTO
//    el contador es igual a i
//    el R va a ser i mas P[i]

string makeStringOdd (string &text) {
  string result;
  result.push_back('#');
  for (char i : text) {
    result.push_back(i);
    result.push_back('#');
  }
  return result;
}

void printPalindrome(string text, int length, int center) {
  int start = center - (length - 2);
  cout << "\n";
  for(int i = start; i <= start + (length - 1)*2; i++) {
    if (text[i] == '#') {
      cout << " ";
    } else {
      cout << text[i];
    }
  }
  cout << "\n";
}

void printP(vector<int> P) {
  for (auto el : P) {
    cout << el << " ";
  }
  cout << "\n";
}

void manacher (string text) {
  int sizeArray = text.length();
  string oddText = makeStringOdd(text);;
  /*if (text.length() % 2 == 0) {
    sizeArray = 2 * text.length() + 1;
    oddText = makeStringOdd(text);
  } */
  int palindromeLength = 0;
  int palindromeCenter = 0;
  int centro = 0;
  int R = 0;
  vector<int> P (sizeArray);

  cout << "ODD TEXT => " << oddText << "\n";
  // #a#b#b#a#
  // Un ciclo es centro
  for (int i = 0; i < oddText.length() - 1; i++) {
    if (i < R) { // Centro actual esta dentro del rango del palindromo mas grande encontrado anteriormente
      P[i] = min((R - i), (centro*2 - i));
    }

    while (oddText[i - (P[i] - 1)] == oddText[i + (P[i] + 1)]) { // extienden left y right bounds
      P[i]++;
    }

    if (i + P[i] > R) { // Optimizar para recorrer menos pasos - creo
      centro = i;
      R = i + P[i]; // Avanza R a nueva posición encontrada en ciclo anterior
    }

    if (P[i] > palindromeLength) { // sustituir nueva palidromo mas largo
      palindromeCenter = i;
      palindromeLength = P[i];
    }
  }

  cout << "palindrome Length =>" << palindromeLength <<"\n";
  cout << "palindrome Center =>" << palindromeCenter <<"\n";
  printP(P);
  printPalindrome(oddText, palindromeLength, palindromeCenter);
}

void copiaInternet (string text) {
  int N = text.length();
  if(N == 0)
    return;
  N = 2*N + 1; //Position count
  int L[N]; //LPS Length Array
  L[0] = 0;
  L[1] = 1;
  int C = 1; //centerPosition
  int R = 2; //centerRightPosition
  int i = 0; //currentRightPosition
  int iMirror; //currentLeftPosition
  int maxLPSLength = 0;
  int maxLPSCenterPosition = 0;
  int start = -1;
  int end = -1;
  int diff = -1;

  for (i = 2; i < N; i++)
  {
    //get currentLeftPosition iMirror for currentRightPosition i
    iMirror = 2*C-i;
    L[i] = 0;
    diff = R - i;
    //If currentRightPosition i is within centerRightPosition R
    if(diff > 0)
      L[i] = min(L[iMirror], diff);

    //Attempt to expand palindrome centered at currentRightPosition i
    //Here for odd positions, we compare characters and
    //if match then increment LPS Length by ONE
    //If even position, we just increment LPS by ONE without
    //any character comparison
    while ( ((i + L[i]) < N && (i - L[i]) > 0) &&
            ( ((i + L[i] + 1) % 2 == 0) ||
              (text[(i + L[i] + 1)/2] == text[(i - L[i] - 1)/2] )))
    {
      L[i]++;
    }

    if(L[i] > maxLPSLength) // Track maxLPSLength
    {
      maxLPSLength = L[i];
      maxLPSCenterPosition = i;
    }

    //If palindrome centered at currentRightPosition i
    //expand beyond centerRightPosition R,
    //adjust centerPosition C based on expanded palindrome.
    if (i + L[i] > R)
    {
      C = i;
      R = i + L[i];
    }
    //Uncomment it to print LPS Length array
    //printf("%d ", L[i]);
  }
  //printf("\n");
  start = (maxLPSCenterPosition - maxLPSLength)/2;
  end = start + maxLPSLength - 1;
  for(i=start; i<=end; i++)
    printf("%c", text[i]);
  printf("\n");
}

int main () {
  manacher("jabbajkjhgf");
  copiaInternet("jabbajkjhgf");
}
