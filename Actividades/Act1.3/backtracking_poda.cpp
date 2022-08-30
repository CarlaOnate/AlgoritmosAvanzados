// Ojetivo: Encontrar la solucion a un laberinto usando backtracking y el metodo de poda

#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int, int> > bestSolution;
std::vector<std::vector<std::tuple<int, int> > > solutions;

void printBoard (std::vector<std::vector<int> > board) {
  for (auto row : board) {
    for (auto col : row) {
      std::cout << " " << col << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

void printBoard (std::vector<std::vector<int> > board, std::tuple<int, int> position) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Add current position in board
  int prevValue = board[currentRow][currentColumn];
  board[currentRow][currentColumn] = 9;
  for (auto row : board) {
    for (auto col : row) {
      std::cout << " " << col << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
  // Return pos to default
  board[currentRow][currentColumn] = prevValue;
}

void printSolutionList (std::vector<std::tuple<int, int> > camino) {
  std::cout << "Camino : \n";
  for (auto pos : camino) {
    // print as column x row
    std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ") \n";
  }
}

void printSolutionList () {
  std::cout << "Camino : \n";
  for (auto solution : solutions) {
    for (auto pos : solution) {
      // print as column x row
      std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")  ";
    }
    std::cout << "\n";
  }
}

bool isPositionValid (std::vector<std::vector<int> > board, int row, int column) {
  return row < board.size() && column < board[0].size() && board[row][column] == 1; //Still row inside board and next row value equals 1
}

bool backtrack (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position) {
  // TODO: Agregar que INTENTE A LA IZQ Y ARRIBA
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

    if (isPositionValid(board, currentRow, currentColumn + 1)) {
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

void branchBound (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Llego solucion??
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions.push_back(camino);
    if (camino.size() <= bestSolution.size() || bestSolution.empty()) { // Camino igual o mas corto se toma como mejor camino
      bestSolution.swap(camino);
      std::cout << "\t Mejo solucion => \n";
      printSolutionList(bestSolution);
    }
    return;
  }

  // Encontrar solucion
  if (isPositionValid(board, currentRow, currentColumn)){
    std::tuple<int, int> tempPosition = std::make_tuple(currentRow, currentColumn);
    std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
    std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
    std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
    std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
    camino.push_back(tempPosition);
    branchBound(camino, board, nextRightPos);
    branchBound(camino, board, nextBottomPos);
    camino.pop_back(); // Se hace poda -> elimina candidato que no funciona
  }

  // If nothing valid then do nothing
}

int main () {
  //Tablero de 4x4
  std::vector<std::tuple<int, int> > camino;
  std::vector<std::tuple<int, int> > camino2;
  std::vector<std::vector<int>> board;
  std::vector<int> row;
  row.push_back(1);row.push_back(1);row.push_back(1);row.push_back(1); row.push_back(1);
  board.push_back(row);
  row.clear();
  row.push_back(0);row.push_back(1);row.push_back(0);row.push_back(1); row.push_back(1);
  board.push_back(row);
  row.clear();
  row.push_back(1);row.push_back(1);row.push_back(1);row.push_back(0); row.push_back(1);
  board.push_back(row);
  row.clear();
  row.push_back(1);row.push_back(0);row.push_back(1);row.push_back(1); row.push_back(1);
  board.push_back(row);
  row.clear();

  //Missing validation
    // - Starting point must be a 1
    // - Data given must be numbers

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

  //Branch and boud
  std::vector<std::tuple<int, int>> mejorSolucion;
  branchBound(camino2, board, initialPos);
  printSolutionList();
  return 0;
}