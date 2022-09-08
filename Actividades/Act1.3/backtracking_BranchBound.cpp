#include <iostream>
#include <vector>
#include <tuple>

/*
 * Carla Oñate Gardella A01653555
 * Octavio Augusto Aleman
 */

std::vector<std::tuple<int, int> > bestSolution;
std::vector<std::vector<std::tuple<int, int> > > solutions;
int backtrackingCount = 0;
int backtrackingTodasSolucionesCount = 0;
int backtrackingPodaCount = 0;
int branchBoundCount = 0;

// Function to print board
void printBoard (std::vector<std::vector<int> > board) {
  for (auto row : board) {
    for (auto col : row) {
      std::cout << " " << col << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

// Print the solutions found - for backtracking
void printSolutionList (std::vector<std::tuple<int, int> > camino) {
  std::cout << "Camino : \n";
  for (auto pos : camino) {
    // print as column x row
    std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")  ";
  }
}

void printSolutions () {
  std::cout << "solutions : \n";
  for (auto solution : solutions) {
    for (auto pos : solution) {
      // print as column x row
      std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")  ";
    }
    std::cout << "\n";
  }
}

void printSolutionAsBoard (std::vector<std::vector<int> > solutionMatrix) {
  auto lastSolution = solutions.back();
  for (auto el : lastSolution) {
    int currentRow = get<0>(el), currentColumn = get<1>(el);
    solutionMatrix[currentRow][currentColumn] = 1;
  }
  printBoard(solutionMatrix);
}

bool isPositionValid (std::vector<std::vector<int> > board, std::vector<std::vector<int> > caminoMatrix, int row, int column) {
  if ((row < board.size() && column < board[0].size()) && (row >= 0 && column >= 0)) { //Within bounds of board and value of pos is valid
    return caminoMatrix[row][column] != 5 && board[row][column] == 1; // If haven't been there and value is 1
  }
  return false;
}

void backtrackingTodasSoluciones (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Revisa si llego a una solucion parcial (una de muchas soluciones posibles)
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions.push_back(camino); // Guarda solucion en lista de soluciones
    return; // Termina este ciclo
  }

  // Encontrar solucion
  if (isPositionValid(board, caminoMatrix, currentRow, currentColumn)) {
    backtrackingTodasSolucionesCount++;
    // Solo recorre si esta opcion es mejor que la mejor opcion actual
    std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
    std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
    std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
    std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
    camino.push_back(position); // Agrega posicion a solucion
    caminoMatrix[currentRow][currentColumn] = 5; // Cambia valor de donde ya pasaste para validacion futura
    // Probar todos caminos en pos actual
    backtrackingTodasSoluciones(camino, board, nextRightPos, caminoMatrix);
    backtrackingTodasSoluciones(camino, board, nextBottomPos, caminoMatrix);
    backtrackingTodasSoluciones(camino, board, nextUpPos, caminoMatrix);
    backtrackingTodasSoluciones(camino, board, nextLeftPos, caminoMatrix);
    // No se encontro solucion
    camino.pop_back(); // elimina candidato que no funciona
    caminoMatrix[currentRow][currentColumn] = 0;
    return;
  }
}


void backtracking (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Revisa si llego a una solucion parcial (una de muchas soluciones posibles)
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions.push_back(camino); // Guarda solucion en lista de soluciones
    return; // Termina este ciclo
  }

  // Encontrar solucion
  if (!isPositionValid(board, caminoMatrix, currentRow, currentColumn) || !solutions.empty()) {
    return; // return if solution has been found - stop searching
  }
  backtrackingCount++;
  // Solo recorre si esta opcion es mejor que la mejor opcion actual
  std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
  std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
  std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
  std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
  camino.push_back(position); // Agrega posicion a solucion
  caminoMatrix[currentRow][currentColumn] = 5; // Cambia valor de donde ya pasaste para validacion futura
  // Probar todos caminos en pos actual
  backtracking(camino, board, nextRightPos, caminoMatrix);
  backtracking(camino, board, nextBottomPos, caminoMatrix);
  backtracking(camino, board, nextUpPos, caminoMatrix);
  backtracking(camino, board, nextLeftPos, caminoMatrix);
  // No se encontro solucion
  camino.pop_back(); // elimina candidato que no funciona
  caminoMatrix[currentRow][currentColumn] = 0;
}

bool backtrackPoda (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  std::tuple<int, int> tempPosition = std::make_tuple(currentRow, currentColumn);

  //Funcion objetivo
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) {
    camino.push_back(position);
    solutions.push_back(camino);
    return true; // Termina de buscar mas soluciones e imprime la primera que encontró
  }

  // Siguiente paso
  if (isPositionValid(board, caminoMatrix, currentRow, currentColumn)) {
    backtrackingPodaCount++;
    std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
    std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
    std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
    std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
    camino.push_back(position);
    caminoMatrix[currentRow][currentColumn] = 5; // Agregar en matriz donde pasaste para validacion isPositionValid2
    // Recorrer todas las opciones hasta encontrar alguna que regrese verdadero
    if (backtrackPoda(camino, board, nextRightPos, caminoMatrix)) return true;
    if (backtrackPoda(camino, board, nextBottomPos, caminoMatrix)) return true;
    if (backtrackPoda(camino, board, nextLeftPos, caminoMatrix)) return true;
    if (backtrackPoda(camino, board, nextUpPos, caminoMatrix)) return true;
    // No se encontraron opciones
    camino.pop_back(); // Quitar el valor que se agrego al camino
    return false;
  }
}

void backtrackingBranchAndBound (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > &caminoMatrix, int currentSteps) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Revisa si llego a una solucion parcial (una de muchas soluciones posibles)
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions.push_back(camino); // Guarda solucion en lista de soluciones
    if (camino.size() <= bestSolution.size() || bestSolution.empty()) {
      bestSolution.swap(camino); // Solucion es igual a mejor reemplaza la solucion mejor anterior
    }
    return; // Termina este ciclo
  }

  // Encontrar solucion
  if (isPositionValid(board, caminoMatrix, currentRow, currentColumn)) {
    if (currentSteps < bestSolution.size() || bestSolution.empty()) {
      branchBoundCount++;      // Solo recorre si esta opcion es mejor que la mejor opcion actual
      std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
      std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
      std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
      std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
      camino.push_back(position); // Agrega posicion a solucion
      caminoMatrix[currentRow][currentColumn] = 5; // Cambia valor de donde ya pasaste para validacion futura
      // Probar todos caminos en pos actual
      backtrackingBranchAndBound(camino, board, nextRightPos, caminoMatrix, currentSteps + 1);
      backtrackingBranchAndBound(camino, board, nextBottomPos, caminoMatrix, currentSteps + 1);
      backtrackingBranchAndBound(camino, board, nextUpPos, caminoMatrix, currentSteps + 1);
      backtrackingBranchAndBound(camino, board, nextLeftPos, caminoMatrix, currentSteps + 1);
      // No se encontro solucion
      camino.pop_back(); // elimina candidato que no funciona
      caminoMatrix[currentRow][currentColumn] = 0;
    }
  }
}

int main () {
  std::vector<std::tuple<int, int> > currentRoute; // Store the positions of the solution
  std::vector<std::vector<int>> board; // Board given by user
  int N = 0;
  int M = 0;
  int start = 0;
  std::vector<std::vector<int> > prevStepsBacktracking; //Matrix of 0s to check if algo has been there before
  std::vector<std::vector<int> > prevStepsBranchBound; //Matrix of 0s to check if algo has been there before
  std::vector<std::vector<int> > prevStepsIntentoPoda; //Matrix of 0s to check if algo has been there before
  std::vector<std::vector<int> > prevStepsBackTodasSoluciones; //Matrix of 0s to check if algo has been there before
  std::vector<std::vector<int> > solutionMatrix; //Matrix of 0s to show result

  //Matriz de n x m

  while (start == 0) {
    std::cout << "\t Valores: 1 = Camino, 0 = Pared \n";
    std::cout << "Largo de la matriz: ";
    std::cin >> N;
    std::cout << "Ancho de la matriz: ";
    std::cin >> M;

    std::vector<std::vector<int> > prevStepsTempMatrix(M, std::vector<int>(N,0)); //Matrix of 0s to check if algo has been there before

    // Creacion y validacion de valores de matriz a usar
    for (int j = 0; j < M; j++) {
      std::cout << "Fila " << j + 1 << "\n";
      std::vector<int> row;
      for (int i = 0; i < N; i++) {
        int tempValue;
        std::cin >> tempValue;
        if (!std::cin.good() || tempValue < 0 || tempValue > 1) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Dato ingresado tiene que ser un numero 0 o 1\n\n";
          i--;
        } else {
          row.push_back(tempValue); // fill row
        }
      }
      board.push_back(row);
      row.clear(); // reset row
      std::cout << "Progreso tablero => \n";
      printBoard(board);
    }

    //Board validations
    if (board[0][0] != 0 && board[M - 1][N - 1] != 0) {
      std::cout << "Tablero final: \n";
      printBoard(board);
      std::cout << "Es correcto el tablero?? => Si : 1, No : 0      ";
      std::cin >> start;
      prevStepsBacktracking = prevStepsTempMatrix; // Swap values with global 0s matrix
      prevStepsBranchBound = prevStepsTempMatrix;
      prevStepsIntentoPoda = prevStepsTempMatrix;
      prevStepsBackTodasSoluciones = prevStepsTempMatrix;
      solutionMatrix = prevStepsTempMatrix;
    } else {
      std::cout << "Coordenada inicial o final no tiene un valor de 1 \n\n";
      board.clear();
      start = 0;
    }
  }

  std::cout << "Initial Board \n";
  printBoard(board);
  std::tuple<int, int> initialPos = std::make_tuple(0, 0);

  std::cout << "\t BACKTRACKING 1 SOLUCION \n\n\n";
  backtracking(currentRoute, board, initialPos, prevStepsBacktracking);
  if (solutions.empty()) {
    std::cout << "\t No se encontró solución con backtracking \n\n";
  } else {
//    printSolutions();
    std::cout << "Solución backtracking \n\n\n";
    printSolutionAsBoard(solutionMatrix);
  }

  std::cout << "\t PODA - este fue un intento de poda pero no funciono \n\n\n";
  solutions.clear();
  backtrackPoda(currentRoute, board, initialPos, prevStepsIntentoPoda);
  if (solutions.empty()) {
    std::cout << "\t No se encontró solución con poda \n\n";
  } else {
//    printSolutions();
    std::cout << "Solución poda\n\n\n";
    printSolutionAsBoard(solutionMatrix);
  }

  std::cout << "\t BRANCH AND BOUND - esta hace una poda del tablero tomando como condicion la mejor ruta\n \t como backtracking se detiene en primera solucion este toma mas pasos ya que busca varias soluciones. \n\n\n";
  solutions.clear();
  backtrackingBranchAndBound(currentRoute, board, initialPos, prevStepsBranchBound, 0);
  if (solutions.empty()) {
    std::cout << "\t No se encontró solución con branch and bound \n\n";
  } else {
//    printSolutions();
//    printSolutionList(bestSolution);
    std::cout << "Solución branch and bound\n\n\n";
    printSolutionAsBoard(solutionMatrix);
  }

  std::cout << "\t Conteo llamadas backtracking:" << backtrackingCount << "\n";
  std::cout << "\t Conteo llamadas branch and bound:" << branchBoundCount << "\n";
  std::cout << "\t Conteo llamadas poda:" << backtrackingPodaCount << "\n\n\n";

  std::cout << "\t BACKTRACKING TODAS SOLUCIONES \n\n\n";
  solutions.clear();
  backtrackingTodasSoluciones(currentRoute, board, initialPos, prevStepsBackTodasSoluciones);
  if (solutions.empty()) {
    std::cout << "\t No se encontró solución con backtracking todas soluciones \n\n";
  } else {
//    printSolutions();
    std::cout << "Solución backtracking todas soluciones \n\n\n";
    printSolutionAsBoard(solutionMatrix);
  }

  std::cout << "\t Conteo llamadas backtracking todas soluciones:" << backtrackingTodasSolucionesCount << "\n";

  return 0;
}


