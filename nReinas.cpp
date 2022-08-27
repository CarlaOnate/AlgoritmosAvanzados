#include <iostream>
#include <vector>
using namespace std;

vector<int> rowQueens;
vector<int> colQueens;

void printArr(vector<vector<int> > board, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << " " << board[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

bool canQueenStayHere (vector<vector<int> > board, int row, int column, int n) {
  bool queenInRow = false, queenInCol = false, queenInDiagonal = false;
  // Not in the same column or row
  for (int el: rowQueens) {
    if(row == el){
      queenInRow = true;
    }
  };
  for (int el: colQueens) {
    if (column == el) {
      queenInCol = true;
    }
  };
  //Checking diagonals
  //upper left diagonal
/*   for(int i = row; i >= 0; i--) {
    for(int j = column; j >= 0; j--) {
      if (board[i][j] == 6) {
        return queenInDiagonal = true;
      }
    }
  }
  //bottom left diagonal
  for(int i = row; i < n; i++) {
    for(int j = column; j >= 0; j--) {
      if (board[i][j] == 6) {
        return queenInDiagonal = true;
      }
    }
  } */
  return !(queenInDiagonal || queenInCol || queenInRow);
}

void nReinas (vector<vector<int> >& board, int row, int column, int n, int direction) {
  //El numero de reinas es igual a n del tamaño del tablero
  // base case
  if (direction == 0 && row >= n) {
    return; // No more options this way
  } else if (direction == 1 && column >= n) {
    return;
  }

  //finishing case
  if (row == n - 1 && column == n - 1) {
    // finished the board -> finished all posibilities
    return;
  }

  // Check if queen can be set in this position
  bool queenHere = canQueenStayHere(board, row, column, n);

  // if yes -> save position of queen
  if (queenHere) {
    rowQueens.push_back(row);
    colQueens.push_back(column);
    board[row][column] = 6; // solucion parcial del problema, quitar esta solucion de los candidatos
    printArr(board, n);
  }
  nReinas(board, row + 1, column, n, 0);
  nReinas(board, row, column + 1, n, 1);
}

void createMatrix (int n) {
  vector<vector<int> > board(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }
  printArr(board, n);
  nReinas(board, 0, 0, n, 0);
}

int main () {
  int n = 4;
  createMatrix(n);
  return 0;
}