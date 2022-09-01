// Ojetivo: Encontrar la solucion a un laberinto usando backtracking y el metodo de poda

#include <iostream>
#include <vector>
#include <tuple>

std::vector<std::tuple<int, int> > bestSolution2;
std::vector<std::vector<std::tuple<int, int> > > solutions2;

/*
 * RESUMEN QUE YA ME CONFINDÍ
 * Backtracking: Tiene que regresar todas las posibles soluciones al probelma
 * Branch and bound: Tiene que regresar la solucion mas optima, pero ignorando caminos que sabes que no dan la respuesta mas optima.
 */

// Function to print intial board
void printBoard2 (std::vector<std::vector<int> > board) {
  for (auto row : board) {
    for (auto col : row) {
      std::cout << " " << col << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

// Function used for debbugging - leaving it there if needed
void printBoard2 (std::vector<std::vector<int> > board, std::tuple<int, int> position) {
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

// Print the solutions2 found - for backtracking
void printSolutionList2 (std::vector<std::tuple<int, int> > camino) {
  std::cout << "Camino : \n";
  for (auto pos : camino) {
    // print as column x row
    std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")  ";
  }
}

// Print all the solutions2 found - for branchBound
void printSolutionList2 () {
  std::cout << "solutions2 : \n";
  for (auto solution : solutions2) {
    for (auto pos : solution) {
      // print as column x row
      std::cout << "(" << get<0>(pos) << ", " << get<1>(pos) << ")  ";
    }
    std::cout << "\n";
  }
}

bool isPositionValid2 (std::vector<std::vector<int> > board, std::vector<std::vector<int> > caminoMatrix, int row, int column) {
  if ((row < board.size() && column < board[0].size()) && (row >= 0 && column >= 0)) { //Within bounds of board and value of pos is valid
    return caminoMatrix[row][column] != 5 && board[row][column] == 1; // If haven't been there and value is 1
  }
  return false;
}

bool backtrack (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
    int currentRow = get<0>(position), currentColumn = get<1>(position);
    std::tuple<int, int> tempPosition = std::make_tuple(currentRow, currentColumn);
    //Funcion objetivo
    if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) {
      camino.push_back(position);
      printSolutionList2(camino);
      return true; // Termina de buscar mas soluciones e imprime la primera que encontró
    }

    // Siguiente paso
    if (isPositionValid2(board, caminoMatrix, currentRow, currentColumn)) {
      std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
      std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
      std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
      std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
      camino.push_back(position);
      caminoMatrix[currentRow][currentColumn] = 5; // Agregar en matriz donde pasaste para validacion isPositionValid2
      // Recorrer todas las opciones hasta encontrar alguna que regrese verdadero
      if (backtrack(camino, board, nextRightPos, caminoMatrix)) return true;
      if (backtrack(camino, board, nextBottomPos, caminoMatrix)) return true;
      if (backtrack(camino, board, nextLeftPos, caminoMatrix)) return true;
      if (backtrack(camino, board, nextUpPos, caminoMatrix)) return true;
      // No se encontraron opciones
      camino.pop_back(); // Quitar el valor que se agrego al camino
      caminoMatrix[currentRow][currentColumn] = 0; // Regresar el valor de la matriz a default
      return false;
    }

    return false;
};

// Esta funciona hace igual backtracking pero de toads las solciones posibles a los laberintos - esto no es poda
void branchBound (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Revisa si llego a una solucion parcial (una de muchas soluciones posibles)
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions2.push_back(camino); // Guarda solucion en lista de soluciones
    if (camino.size() <= bestSolution2.size() || bestSolution2.empty()) {
      bestSolution2.swap(camino); // Solucion es igual a mejor reemplaza la solucion mejor anterior
    }
    return; // Termina este ciclo
  }

  // Encontrar solucion
  if (isPositionValid2(board, caminoMatrix, currentRow, currentColumn)){
    std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
    std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
    std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
    std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
    camino.push_back(position); // Agrega posicion a solucion
    caminoMatrix[currentRow][currentColumn] = 5; // Cambia valor de donde ya pasaste para validacion futura
    // Probar todos caminos en pos actual
    branchBound(camino, board, nextRightPos, caminoMatrix);
    branchBound(camino, board, nextBottomPos, caminoMatrix);
    branchBound(camino, board, nextUpPos, caminoMatrix);
    branchBound(camino, board, nextLeftPos, caminoMatrix);
    // No se encontro solucion
    camino.pop_back(); // Se hace poda -> elimina candidato que no funciona
    caminoMatrix[currentRow][currentColumn] = 0;
  }
  // If nothing valid then do nothing
}

// todo: Tal vez esto no es backtracking y es otra cosa rara
bool noSoyBacktracking (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  std::tuple<int, int> tempPosition = std::make_tuple(currentRow, currentColumn);
  //Funcion objetivo
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) {
    camino.push_back(position);
    printSolutionList2(camino);
    return true; // Termina de buscar mas soluciones e imprime la primera que encontró
  }

  // Siguiente paso
  if (isPositionValid2(board, caminoMatrix, currentRow, currentColumn)) {
    std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
    std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
    std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
    std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
    camino.push_back(position);
    caminoMatrix[currentRow][currentColumn] = 5; // Agregar en matriz donde pasaste para validacion isPositionValid
    // Recorrer todas las opciones hasta encontrar alguna que regrese verdadero
    if (noSoyBacktracking(camino, board, nextRightPos, caminoMatrix)) return true;
    if (noSoyBacktracking(camino, board, nextBottomPos, caminoMatrix)) return true;
    if (noSoyBacktracking(camino, board, nextLeftPos, caminoMatrix)) return true;
    if (noSoyBacktracking(camino, board, nextUpPos, caminoMatrix)) return true;
    // No se encontraron opciones
    camino.pop_back(); // Quitar el valor que se agrego al camino
    caminoMatrix[currentRow][currentColumn] = 0; // Regresar el valor de la matriz a default
    return false;
  }

  return false;
};

/*
 * podaaaaa
 * USAR EL MISMO QUE REVISA VARIAS SOLUCIONES PERO SI LOS PASOS ACTUALES QUE ESTAS TOMANDO SON MAYORES A LA OPCION OPTIMA SO FAR ENTONCES NO SIGAS ESE CAMINO
 *
 */
void backtrackPoda (std::vector<std::tuple<int, int> > camino, std::vector<std::vector<int> > board, std::tuple<int, int> position, std::vector<std::vector<int> > caminoMatrix, int currentSteps) {
  int currentRow = get<0>(position), currentColumn = get<1>(position);
  // Revisa si llego a una solucion parcial (una de muchas soluciones posibles)
  if (currentRow == board.size() - 1 && currentColumn == board[0].size() - 1) { // función objetivo - determina si ya llego al punto deseado del tablero
    camino.push_back(position); // Registra ultima posicion en solucion
    solutions2.push_back(camino); // Guarda solucion en lista de soluciones
    if (camino.size() <= bestSolution2.size() || bestSolution2.empty()) {
      bestSolution2.swap(camino); // Solucion es igual a mejor reemplaza la solucion mejor anterior
    }
    return; // Termina este ciclo
  }

  // Encontrar solucion
  if (isPositionValid2(board, caminoMatrix, currentRow, currentColumn)) {
    if (currentSteps < bestSolution2.size()) {
      // Solo recorre si esta opcion es mejor que la mejor opcion actual
      std::tuple<int, int> nextRightPos = std::make_tuple(currentRow, currentColumn + 1);
      std::tuple<int, int> nextBottomPos = std::make_tuple(currentRow + 1, currentColumn);
      std::tuple<int, int> nextLeftPos = std::make_tuple(currentRow, currentColumn - 1);
      std::tuple<int, int> nextUpPos = std::make_tuple(currentRow - 1, currentColumn);
      camino.push_back(position); // Agrega posicion a solucion
      caminoMatrix[currentRow][currentColumn] = 5; // Cambia valor de donde ya pasaste para validacion futura
      // Probar todos caminos en pos actual
      backtrackPoda(camino, board, nextRightPos, caminoMatrix, currentSteps);
      backtrackPoda(camino, board, nextBottomPos, caminoMatrix, currentSteps);
      backtrackPoda(camino, board, nextUpPos, caminoMatrix, currentSteps);
      backtrackPoda(camino, board, nextLeftPos, caminoMatrix, currentSteps);
      // No se encontro solucion
      camino.pop_back(); // Se hace poda -> elimina candidato que no funciona
      caminoMatrix[currentRow][currentColumn] = 0;
    }
  }
}

int main2 () {
  //Tablero de 4x4
  std::vector<std::tuple<int, int> > camino;
  std::vector<std::vector<int>> caminoMatrix = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
  std::vector<std::vector<int>> tablero;
  std::vector<int> fila;
  fila.push_back(1);fila.push_back(1);fila.push_back(1);fila.push_back(1); fila.push_back(1);
  tablero.push_back(fila);
  fila.clear();
  fila.push_back(0);fila.push_back(0);fila.push_back(0);fila.push_back(1); fila.push_back(1);
  tablero.push_back(fila);
  fila.clear();
  fila.push_back(1);fila.push_back(1);fila.push_back(1);fila.push_back(1); fila.push_back(0);
  tablero.push_back(fila);
  fila.clear();
  fila.push_back(0);fila.push_back(1);fila.push_back(0);fila.push_back(0); fila.push_back(1);
  tablero.push_back(fila);
  fila.clear();
  fila.push_back(0);fila.push_back(1);fila.push_back(1);fila.push_back(1); fila.push_back(1);
  tablero.push_back(fila);
  fila.clear();

  //TODO: Missing validation
    // - Starting point must be a 1 and end point must be 1
    // - Data given must be numbers

  std::cout << "Initial tablero \n";
  printBoard2(tablero);
  std::tuple<int, int> initialPos = std::make_tuple(0, 0);

  if(backtrack(camino, tablero, initialPos, caminoMatrix)){
    std::cout << "SOLUCION\n\n\n";
  } else {
    std::cout << "NO  SOLUCION\n\n\n";
  }

  //Branch and bound

  std::vector<std::tuple<int, int>> mejorSolucion;
  // branchBound(camino, tablero, initialPos, caminoMatrix);
  backtrackPoda(camino, tablero, initialPos, caminoMatrix, 0);
  /* if (!solutions2.empty()) {
    printSolutionList2();
    std::cout << "\t Mejo solucion => \n";
    printSolutionList2(bestSolution2);
  } else {
    std::cout << "\t NO SE ENCONTRO SOLUCION \n";
  } */

  return 0;
}