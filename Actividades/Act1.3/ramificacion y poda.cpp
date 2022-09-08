/*
 * Actividad 1.3 Implementación de la técnica de programación "backtracking" y "ramificación y poda"
 * ramificacionypoda.cpp
 * Complexity: O(n^2)
 * Authors:
 *          Carla Onate Gardella               A01653555
 *          Octavio Augusto Aleman Esparza     A01660702
 *          Date: 09.02.2022 
 */

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> currentPath;

template <typename T>
void printMatrix(vector<vector<T>> matriz){
    cout<<"\n";
    for(int i = 0; i < matriz.size(); i++){
        for(int j = 0; j < matriz[0].size(); j++){
            cout<<matriz[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void printResult(int n, int m, vector<vector<int>> result){
    int aux[20][20];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            aux[i][j] = 0;
        }
    }

    int size = result.size();

    for(int i = 0; i < size; i++){
        aux[(result[result.size() - 1][0])][result[result.size() - 1][1]] = 1;
        result.pop_back();
    }

    aux[n - 1][m - 1] = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout<<aux[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void moveThroughMaze(int posX, int posY, int n, int m, vector<vector<int>> matriz, vector<vector<int>> visitado, int counter){

    if((!(posX == n - 1)) || (!(posY == m - 1))){
        if((posX < n - 1) && (matriz[posY][posX + 1] == 1) && (visitado[posY][posX + 1] == 0) && (visitado[posY][posX] == 0)){
            visitado[posY][posX] = 1;
            currentPath.push_back({posY, posX});
            moveThroughMaze(posX + 1, posY, n, m, matriz, visitado, counter + 1);
        }else if((posY < m - 1) && (matriz[posY + 1][posX] == 1) && (visitado[posY + 1][posX] == 0) && (visitado[posY + 1][posX] == 0)){
            visitado[posY][posX] = 1;
            currentPath.push_back({posY, posX});
            moveThroughMaze(posX, posY + 1, n, m, matriz, visitado, counter + 1); 
        }else{
            if((!(posX == n - 1)) || (!(posY == m - 1))){
                visitado[posY][posX] = 1;
                int size = currentPath.size();
                vector<int> aux = {currentPath[size - 1][1], currentPath[size - 1][0]};
                currentPath.pop_back();
                moveThroughMaze(aux[0], aux[1], n, m, matriz, visitado, counter + 1);
            }else{
                cout<<"The finish point could not be reached"<<endl;
            }
        }

    }else if(posX == n - 1 && posY == m - 1){
        cout<<"El final ha sido alcanzado - ramificación y poda:"<<endl;
        printResult(n, m, currentPath);
        cout<<"Resultado obtenido en: "<<counter<<" movimientos."<<endl;
    }

}


int main(){

    vector<vector<int>> matrix;
    vector<vector<int>> visited;
    int auxiliar, n, m;
    bool tracker = true;

    cout << "FILAS: "; cin >> m;
    cout << "\nCOLUMNAS: "; cin >> n;
    cout << "\nIntroduzca tablero:" << endl;
    for(int i=0; i<m; i++){ 

        vector<int> rows;
        vector<int> rows1;

        for(int j=0; j<n; j++){

            cin >> auxiliar;
            if(!(auxiliar == 1 || auxiliar == 0) || cin.fail()) tracker = false;
            rows.push_back(auxiliar);
            rows1.push_back(0);
            }

        matrix.push_back(rows);
        visited.push_back(rows1);
    }

    //cout<<"Matriz de inicio: "<<endl;
    //printMatrix(matrix);
    //cout<<"\n";
    moveThroughMaze(0, 0, n, n, matrix, visited, 0);

    return 0;
}