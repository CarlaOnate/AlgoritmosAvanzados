#include <iostream>
#include <vector>
using namespace std;

vector<int> resultFib;

void fibonacci (int stopNum, int prev, int next) { // SI EL USUARIO DA UN 0 NO PUEDE ESTAR 0 y 1 en el resultado
  int currentNum = prev + next;
  if (prev == 0) {
    resultFib.push_back(0);
    resultFib.push_back(1);
  }
  if (currentNum > stopNum) {
    return;
  }
  resultFib.push_back(currentNum);
  fibonacci(stopNum, next, prev+next);
}

// 0, 1, 1, 2, 3, 5 - suma de los dos anteriores

int main () {
  fibonacci(8, 0, 1);
  for (int i = 0; i < resultFib.size(); i++) {
    cout << " " << resultFib[i] << " ";
  }
  return 0;
}