// Ojetivo: Encontrar la solucion a un laberinto usando backtracking y el metodo de poda

#include <iostream>
#include <vector>
#include <tuple>

void printBoard (std::vector<std::vector<int> > board) {
  for (auto row : board) {
    for (auto col : row) {
      std::cout << " " << col << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void printSolutionList (std::vector<std::tuple<int, int> > camino) {
  std::cout << "Camino : \n";
  for (auto pos : camino) {
    // print as column x row
    std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ") \n";
  }
}

bool isPositionValid (std::vector<std::vector<int> > board, int row, int column) {
  return row < board.size() && column < board[0].size() && board[row][column] == 1; //Still row inside board and next row value equals 1
}

bool backtrack (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position) {
    int currentRow = get<0>(position), currentColumn = get<1>(position);
    std::tuple<int, int> tempPosition = std::make_tuple(currentRow, currentColumn);
    //Funcion obejtivo
    if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) {
      camino.push_back(position);
      printSolutionList(camino);
      return true;
    }

    // If sig posicion derecha es valida ir - same con abajo
    if (isPositionValid(board, currentRow + 1, currentColumn)) {
      camino.push_back(position);
      get<0>(position) = currentRow + 1;
      if (backtrack(camino, board, position)) {
        return true;
      }
      camino.pop_back();
    }

    if (isPositionValid(board, currentRow, currentColumn)) {
      camino.push_back(position);
      get<0>(position) = currentRow;
      get<1>(position) = currentColumn + 1;
      if (backtrack(camino, board, position)) {
        return true;
      }
      camino.pop_back();
    }

    return false;
};

int main () {
  //Tablero de 4x4
  std::vector<std::tuple<int, int> > camino;
  std::vector<std::vector<int>> board;
  std::vector<int> row;
  row.push_back(1);row.push_back(1);row.push_back(1);row.push_back(1);
  board.push_back(row);
  row.clear();
  row.push_back(0);row.push_back(1);row.push_back(0);row.push_back(1);
  board.push_back(row);
  row.clear();
  row.push_back(1);row.push_back(1);row.push_back(1);row.push_back(0);
  board.push_back(row);
  row.clear();
  row.push_back(1);row.push_back(0);row.push_back(1);row.push_back(1);
  board.push_back(row);
  row.clear();

  std::cout << "Initial Board \n";
  printBoard(board);
  std::tuple<int, int> initialPos = std::make_tuple(0, 0);
  camino.push_back(initialPos);
//  backtrack(camino, board, initialPos);
  if(backtrack(camino, board, initialPos)){
    std::cout << "SOLUCION\n\n\n";
  } else {
    std::cout << "NO  SOLUCION\n\n\n";
  }
  return 0;
}