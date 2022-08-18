#include <iostream>
#include <map>
#include <vector>
using namespace std;

int matriz[5][5] = {{1, 1, 1, 1, 1},
                  {1, 1, 0, 0, 1},
                  {1, 1, 1, 1, 1},
                  {0, 1, 0, 1, 0},
                  {1, 1, 0, 1, 1}};
int movements[5][5] = {{0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};
int prevRow, prevCol;

void move(char direction, int& row, int& column) {
  prevRow = row;
  prevCol = column;
  if (direction == 'R') column += 1;
  if (direction == 'L') column -= 1;
  if (direction == 'T') row -= 1;
  if (direction == 'B') row += 1;
  movements[row][column] = 8;
}

map<char, int> getSurroundings (int row, int column) {
  map<char, int> nearMy;

  int leftCellIndex = column - 1 < 0 ? -1 : column - 1;
  int rightCellIndex = column + 1 > 4 ? -1 : column + 1;
  int topCellIndex = row - 1 < 0 ? -1 : row - 1;
  int bottomCellIndex = row + 1 > 4 ? -1 : row + 1;

  bool beenLeft = (leftCellIndex == prevCol) && (row == prevRow);
  bool beenRight = (rightCellIndex == prevCol) && (row == prevRow);
  bool beenTop = (topCellIndex == prevRow) && (column == prevCol);
  bool beenBottom = (bottomCellIndex == prevRow) && (column == prevCol);

  nearMy['L'] = !beenLeft && leftCellIndex > 0 ? matriz[row][leftCellIndex] : -1;
  nearMy['B'] = !beenBottom && bottomCellIndex > 0 ? matriz[bottomCellIndex][column] : -1;
  nearMy['R'] = !beenRight && rightCellIndex > 0 ? matriz[row][rightCellIndex] : -1;
  nearMy['T'] = !beenTop && topCellIndex > 0 ? matriz[topCellIndex][column] : -1;

  return nearMy;
}

void printMatrix(int row, int col) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == row && j == col) {
        cout << 'X' << ' ';
      } else {
        cout << matriz[i][j] << ' ';
      }
    }
    cout << "\n";
  }
}

void printMovements() {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      cout << movements[i][j] << ' ';
    }
    cout << "\n";
  }
}

void printMap(map<char, int> nearMe) {
  cout << "Near my R:  " << nearMe['R'] << "\n";
  cout << "Near my L:  " << nearMe['L'] << "\n";
  cout << "Near my T:  " << nearMe['T'] << "\n";
  cout << "Near my B:  " << nearMe['B'] << "\n";
}

void nextMove(int row, int column) {
  if (row == 4 && column == 4) {
    return;
  }

  printMatrix(row, column);

  map<char, int> nearMe = getSurroundings(row, column);

  bool shouldGoLeft = nearMe['L'] > 0;
  bool shouldGoRight = nearMe['R'] > 0;
  bool shouldGoBottom = nearMe['B'] > 0;
  bool shouldGoTop = nearMe['T'] > 0;

  if (shouldGoRight) { move('R', row, column); }
  else if (shouldGoBottom) { move('B', row, column); }
  else if (shouldGoLeft) { move('L', row, column); }
  else if (shouldGoTop) { move('T', row, column); }
  nextMove(row, column);
}

int main () {
  nextMove(0, 0);
  printMovements();
  return 0;
}

