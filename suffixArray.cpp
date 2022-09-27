//
// Created by Carla Onate on 20/09/22.
//
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

void printArr(vector<pair<int, string>> array) {
  cout << "tabla sufijos" << "\n";
  for (auto par : array) {
    cout << "(" << par.first << " " << par.second << ")  ";
  }
  cout << "\n";
}

bool sortByPair(const pair<int, string>& a, const pair<int, string>& b){
  return (a.second < b.second);
}

void suffixArray (string text) {
// separate each suffix in vector
  vector<pair<int, string>> suffixes;
  vector<pair<int, string>> orderedSuffix;
  string tempText = text;
  for (int i = 0; i < text.length(); i++) {
    suffixes.push_back(make_pair(i, tempText));
    tempText.erase(tempText.begin());
  }
  printArr(suffixes);
  orderedSuffix = suffixes;
  sort(orderedSuffix.begin(), orderedSuffix.end(), sortByPair);
  printArr(orderedSuffix);
}

int main () {
  string text;
  cout << "Ingrese texto: " << "\n";
  std::getline(std::cin,text);
  cout << "Texto ingresado => " << text << "\n";
  suffixArray(text);
}