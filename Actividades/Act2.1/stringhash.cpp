/*
 * hashstring.cpp
 * Programa que recibiendo un archivo de entrada y un numero n (donde 16 >= n <= 64), 
 * regresa una cadena Hexadecimal de tamanio n/4, equivalente al hasheo del archivo dado.
 *        Authors: Carla Onate Gardella              A01653555 
 *                 Octavio Augusto Aleman Esparza    A01660702 
 * Complejidad de : O(n^2)
 * Fecha: 23.09.2022
 */

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

//Funcion que valida si el archivo de entrada se puede abrir y no esta vacio.
//Si el archivo no tiene problemas, se regresa true, d elo contrario, false.
bool validate(string file){

    ifstream archivo(file);

    if(!archivo.good()){ //Si el archivo de entrada no se puede abrir.
        cout<<"ERROR: EL archivo no fue encontrado o se encuentra daniado.\n";
        return false;
    }else if(archivo.peek() == std::ifstream::traits_type::eof()){ //Si el archivo de entrada esta vacio.
        cout<<"ERROR: EL archivo se encuentra vacio.\n";
        return false;
    }else{ //Si no se encontaron problemas con el archivo.
        return true;
    }

}

//Funcion que valida el numero de caracteres dentro del archivo de entrada.
int sizeOfFile(string file){

    ifstream archivo(file); //Se carga el archivo de entrada.

    string currentLine; //Variable que guarda la linea actual del archivo.
    int counter = 0;    //Contador de caracteres dentro del archivo.

    while(getline(archivo, currentLine)){ //Mientras el archivo aun tenga lineas.
        for(int i = 0; i < currentLine.length(); i++){ //Para cada caracter dentro de la linea actual.
            counter += 1; //Suma 1 al contador.
        }
        counter += 1; //Se suma 1 adicional al contador por el salto de linea.
    }

    return counter; //La funcion regresa el numero d ecaracteres dentro del archivo.
}

//Funcion que recibe un numero entero y lo convierte a hexadecimal.
void decToHex(int num){
    
    char hex[10]; //Arreglo de chars que guarda la conversion a hexadecimal.
 
    int i = 0; //Contador que lleva la posicion dentro del arreglo.
    while (num != 0) {// Mientras la avriable temporal no llegue a 0.
        int temp = 0;
 
        temp = num % 16; //Se guarda el resto del mod. dentro d ela variable temporal.
 
        if (temp < 10) { // Si la variable temporal es menor a 0.
            hex[i] = temp + 48; //Guarda en el arreglo el valor ASCII equivalente a temp + 48.
            i++; //Se suma uno al contador.
        }
        else { // Si la avriable temporal es mayor o igual a 10.
            hex[i] = temp + 55; //Guarda en el arreglo el valor ASCII equivalente a temp + 55.
            i++;//Se suma uno al contador.
        }
 
        num = num / 16;
    }
 
                                      //Cada digito del numero hexadecimal ha sido guardado en el arreglo en orden inverso.
    for (int j = i - 1; j >= 0; j--){ //Se imprime el numero hexadecimal.
        cout << hex[j];               //Se imprime el digito actual.
    }
    cout<<" ";
}

//Funcion que controla el Hasheo del archivo de entrada.
//Recibe como parametros un numero n y el nombre del archivo.
void hashString(int n, string file){

    if(validate(file) == true){ //Si no se encontraron problemas con el archivo.

        int m = sizeOfFile(file); //Variable m equivalente al numero de caracteres dentro del archivo.

        int matrix[(m / n) + 1][n]; //Matriz con numero de columnas igual a n, y filas igual a m/n + 1.
        int tempAdd[n]; //Arreglo que guarda la suma de todos los caracteres dentro de una misma columna.
        int accum[n / 4]; //Arreglo que sumariza los valores de cada 4 columnas con un total de n/4 posiciones.

        for(int i = 0; i < (m / n) + 1; i++){ //Ciclo que rellena la matriz con 0's.
            for(int j = 0; j < n; j++){
                matrix[i][j] = 0;
            }
        }
        cout<<"\n";

        ifstream archivo(file); //Se carga el archivo de entrada.
        string currentLine; //Variable que guarda la linea actual del archivo.
        getline(archivo, currentLine); //Se carga a la avriable la primera linea del archivo.

        int lineSize = currentLine.length(); //Variable que lleva el control del tamanio de la linea actual.
        int key = 0; //Llave que lleva el control de la posicion dentro de una linea determinada.

        for(int i = 0; i < n; i++){ //Se rellena el arreglo con 0's.
            tempAdd[i] = 0;
        }

        for(int i = 0; i < n / 4; i++){//Se rellena el arreglo con 0's.
            accum[i] = 0;
        }

        for(int i = 0; i < (m / n) + 1; i++){ //Ciclo que rellena la matriz con los valores ASCII correpondientes a cada caracter en el archivo de entrada.
            for(int j = 0; j < n; j++){
                if(lineSize > key && lineSize != 0){ //Si el tamanio d ela linea es mayor a la llave y no es igual a 0.
                    matrix[i][j] = int(currentLine[key]); //En la posicion actual de la matriz se agrega el valor ASCII del caracter actual dentro de la linea actual.
                    key += 1; //Se agrega 1 a la llave.
                    tempAdd[j] += matrix[i][j]; //En el arreglo que sumariza las columnas, se va sumando el valor ASCII actual recien aniadido.
                }else if(lineSize == key && getline(archivo, currentLine)){ //Si el tamanio de la linea es igual al valor de la llave.
                    key = 0; //Se reinicia el valor de la llave.
                    lineSize = currentLine.length(); //Se vuelve a calcular el tamanio de la linea.
                    matrix[i][j] = 10; //Se agrega el valor ASCII correspondiente al salto de linea.
                    tempAdd[j] += matrix[i][j];//En el arreglo que sumariza las columnas, se va sumando el valor ASCII actual recien aniadido.
                }else{ //Si ya no hay caracteres que aniadir, se rellena elr esto d ela matriz con el valor de n.
                    matrix[i][j] = n;
                    tempAdd[j] += matrix[i][j];
                }
            }
        }

        accum[0] += tempAdd[0]; //Al acumulador final se suma en la primera posicional el primer valor acumulado de columnas en el arreglo.
        key = 0;

        for(int i = 1; i < n; i++){ //Ciclo que rellena el acumulador final con la suma de las columnas, cada 4 posiciones.
            accum[key] += tempAdd[i];

            if((i + 1) % 4 == 0){ //Si el valor de i + 1 actual es multiplo de 4.
                key += 1; //Se cambia d eposicion en el acumulador.
            }
        }

        cout<<"Resultado: ";
        for(int i = 0; i < n / 4; i++){ //Se imprime el resultado, llamando a la funciond e conversion hexadecimal.
            decToHex(accum[i]);
        }
        cout<<"\n";

    }

    cout<<"\nPrograma Terminado.\n";

}

//Funcion que inicializa el programa.
void init(){

    string fileName; //Nombre del archivo.
    int hashSize = 0; //Valor n d eentrada.

    cout<<"\nBienvenido al programa de Hash String.\n";
    cout<<"Ingresa un nombre de archivo: ";
    cin>> fileName;;
    cout<<"Ingresa un tamanio: ";
    cin>> hashSize;

    if(hashSize % 4 != 0){ //Si el valor ingresado no es multiplo de 4.
        cout<<"ERROR: Tamanio invalido. Tamanio debe ser multiplo de 4.";
    }else if(hashSize < 16 || hashSize > 64){ //Si el valor ingresao e smultiplo de 4, pero es menor a 16 o mayor a 64.
        cout<<"ERROR: Tamanio debe ser mayor o igual a 16 y menor o igual a 64.";
    }else{ //Si el numero ingresado es adecuado.
        hashString(hashSize, fileName);
    }
}

int main(){
    init();
    return 0;
}