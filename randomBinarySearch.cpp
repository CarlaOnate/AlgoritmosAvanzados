#include <stdlib.h>
#include <vector>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool regexNumber(string numb) // Time: O(1)
{
    const regex expReg("^[0-9]+$");
    return regex_match(numb, expReg);
}

bool regexFloat(string numb) // Time: O(1)
{
    const regex expReg("^[+-]?([0-9]*[.])?[0-9]+$");
    return regex_match(numb, expReg);
}

void printArray(vector<int> array) {
  for (int el : array) {
    cout << el << " ";
  }
}

int randomBinarySearch (int start, int end, vector<int> array, int value) { // Time: O(logn)
  if (end >= start) {
    srand(time(NULL));
    int middle = (start + rand() % (end - start + 1));

    if (array[middle] == value) {
      return middle;
    }

    if (value < array[middle]) {
      return randomBinarySearch(start, middle - 1, array, value);
    }
    return randomBinarySearch(middle + 1, end, array, value);
  }

  return -1;
}

int main () { // Time: 
  vector<int> array;
  string numberToSearch, sizeArray;

  cout << "Input the number to search: \n";
  cin >> numberToSearch;
  if (!regexNumber(numberToSearch)) {
    cout << "Number to search must be type int\n";
    exit(0);
  }

  int number = stoi(numberToSearch);

  string value;
  cout << "Input array values (1, 2, 3...)\n";
  cin.ignore();
  getline(cin, value);

  value.erase(std::remove(value.begin(), value.end(), ','), value.end());

  stringstream ss(value);
  for (string i; ss >> i;) {
    if (regexNumber(i)) {
      array.push_back(stoi(i));
    } else {
      cout << "Data not valid\n";
      exit(0);
    }
  }

  cout << "Array entered: ";
  printArray(array);
  cout << "\n";

  int result = randomBinarySearch(0, array.size() - 1, array, number);
  if (result < 0) {
    cout << "Value not found in array \n";
  } else {
    cout << "Value at index:  => " << result << "\n";
  }
}