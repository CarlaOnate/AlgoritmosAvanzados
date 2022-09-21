//
// Created by Carla Onate on 20/09/22.
//
#include <string>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

void printArr(vector<pair<int, string>> array) {
  cout << "tabla sufijos" << "\n";
  for (auto par : array) {
    cout << par.second << "  ";
  }
  cout << "\n";
}

void printArr(vector<string> array) {
  cout << "sufijos ordenados" << "\n";
  for (auto el : array) {
    cout << el << "  ";
  }
  cout << "\n";
}

void suffixArray (string text) {
// separate each suffix in vector
  vector<pair<int, string>> suffixes;
  vector<string> orderedSuffix;
  string tempText = text;
  for (int i = 0; i < text.length(); i++) {
    suffixes.push_back(make_pair(i, tempText));
    orderedSuffix.push_back(tempText);
    cout << tempText << "\n";
    tempText.erase(tempText.begin());
  }
  printArr(suffixes);
  sort(orderedSuffix.begin(), orderedSuffix.end());
  printArr(orderedSuffix);
}

int main () {
  string text;
  cout << "Ingrese texto: " << "\n";
  std::getline(std::cin,text);
  cout << "Texto ingresado => " << text << "\n";
  suffixArray(text);
}