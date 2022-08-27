/*
 * Actividad 1.2 Implementación de la técnica de programación "Programación dinámica" y "algoritmos avaros"
 * Program that returns the smallest amount of coins for returning change, given a price and paid amount.
 * monedas.h
 * Complexity: O(n^2)
 * Authors:
 *          Carla Onate Gardella               A01653555
 *          Octavio Augusto Aleman Esparza     A01660702
 *          Date: 08.26.2022
 */

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void printResult (int denomination[], int currencies[], int cash, int sizeDenomination, int totalCoins) {
  for (int i = 0; i < sizeDenomination; i++) {
    if (currencies[i] > 0) {
        cout<<"Coin: "<<denomination[i]<<" -> x"<<currencies[i]<<endl;
    }
  }
  cout << "Total Coins: " << totalCoins << endl;
  if (cash > 0) {
    cout << "El problema no fue resuelto ya que no se pudo regresar la cantidad deseada" << "\n";
  }
}

//Function that returns the least amount of coins in which change can be returned.
//Receives as input parameters: remaining change, list of denominations, list of used coins, amount of accumulated coins and size of the lists.
void changeDynamic (int cash, int denomination[], int currencies[], int totalCoins, int sizeDenomination) {
  //Cycle comparing the remaining change with the denominations. It always seeks to return the largest coin (or bill).
  //If the remaining change is greater than the current currency, that currency is returned and the cycle is broken.
  //Calling the function again restarts the cycle and the largest possible coin can be returned again.
  for (int i = 0; i < sizeDenomination; i++) {
    if (cash >= denomination[i]) {
      currencies[i] += 1;
      totalCoins += 1;
      cash -= denomination[i];
      break;
    }
  }

  //If the remaining change is greater than 0, the function is called again.
  //If the remaining change equals 0, the used currencies are printed and the function ends.
  if (cash > 0) {
    changeDynamic(cash, denomination, currencies, totalCoins, sizeDenomination);
  } else {
    cout << "\n\n --  DYNAMIC --  " << "\n";
    printResult(denomination, currencies, cash, sizeDenomination, totalCoins);
  }
}

void changeGreedy (int cash, int denomination[], int currencies[], int sizeDenomination) { // O(N)
  int denominationIndex = 0, totalCoins = 0;

  while (cash >= 0 && denominationIndex < sizeDenomination) { //Repeat until no more candidates
    int currDenom = denomination[denominationIndex];

    if (currDenom <= cash) { //First denomination that solves the subproblem in a greedy way
      int amountOfDenomination = floor(cash / currDenom); // how much coins from that denomination can we have -> if decimal number floor it
      currencies[denominationIndex] = amountOfDenomination; // Store the amount of coins for that denomination
      cash -= (amountOfDenomination * currDenom); // Remove subproblem from candidate
      totalCoins += amountOfDenomination;
    }
    denominationIndex++;
  }

  cout << "\n\n --  GREEDY --  " << "\n";
  printResult(denomination, currencies, cash, sizeDenomination, totalCoins);
}

int main(){
  int denominationLength, price, paidWith, cash, currentListIndex = 0;

  cin >> denominationLength;
  int denomination[denominationLength];

  int currencies[denominationLength];
  fill_n (currencies, denominationLength, 0); // initialize currencies array to 0

  while (currentListIndex < denominationLength) { // Fill denomination array with values (coins (or bills) to give money back)
    int value;
    cin >> value;
    denomination[currentListIndex] = value;
    currentListIndex++;
  }
  sort(denomination, denomination + denominationLength); // ordered in ascending order
  reverse(denomination, denomination + denominationLength); // reverse array so that its in descending order

  cin >> price;
  cin >> paidWith;
  cash = paidWith - price;

  // IMPORTANT: Denomination array must be sorted in descending order for this to work
  cout << "Price: "  << price << "; Paid: " << paidWith << "; Change: " << cash << endl;

  changeDynamic(cash, denomination, currencies, 0, denominationLength); // O(n^2)
  changeGreedy(cash, denomination, currencies, denominationLength); // O(n)

  return 0;
}