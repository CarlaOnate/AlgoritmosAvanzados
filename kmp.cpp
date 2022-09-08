//
// Created by Carla Onate on 01/09/22.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>

std::vector<int> lpsVector;

void printVector () {
  for (auto el : lpsVector) {
    std::cout << " " << el << " ";
  }
}

void lpsTable(std::string pattern) {
  std::vector<int> tempLps(pattern.size(), 0);
  int length = 0;
  int i = 1;
  while (i < length) {
    if (pattern[i] == pattern[length]) {
      length++;
      lpsVector[i] = length;
    } else {
      if (length != 0) {
        length = tempLps[length - 1];
      } else {
        tempLps[i] = 0;
        i++;
      }
    }
  }
  lpsVector = tempLps;
}

void kmp () {
//  LPS ← ComputeLPS(Pattern) {build LPS table function}
//  i ← 0
//  j ← 0
//  n ← string length
//  m ← pattern length
//  while i < n do
//    if pattern[j] = string[i] then  {if the characters are a match}
//  i ← i + 1
//  j ← j + 1
//  if j = m then  {j pointer has reached end of pattern}
//  return i - j {index of the match}
//  j ← LPS[j - 1]
//
//  else if i<n && pattern[j] != string[i] then {no match}
//  if j > 0
//  j ← LPS[j - 1]
//  else
//  i ← i + 1
//  return -1 {no match}
}

int main () {
  std::string pattern = "mochon";
  lpsTable(pattern);
  printVector();
  return 0;
}