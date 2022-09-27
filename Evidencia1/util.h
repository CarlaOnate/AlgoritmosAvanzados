/*
 * Actividad 1.1 Implementación de la técnica de programación "divide y
 * vencerás" Program that implements auxiliary functions. util.h Complexity:
 * O(n^2) Authors: Carla Onate Gardella               A01653555 Octavio Augusto
 * Aleman Esparza     A01660702 Date: 08.16.2022
 */

#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

ifstream mcode1("mcode1.txt");
ifstream mcode2("mcode2.txt");
ifstream mcode3("mcode3.txt");
ifstream transmision1("transmission1.txt");
ifstream transmision2("transmission2.txt");

bool validateFiles() {

  bool check = true;
  if (!mcode1.good()) {
    cout << "ERROR: El archivo mcode1.txt no ha sido encontrado o se encuentra "
            "dañado.\n";
    check = false;
  }
  if (!mcode2.good()) {
    cout << "ERROR: El archivo mcode2.txt no ha sido encontrado o se encuentra "
            "dañado.\n";
    check = false;
  }
  if (!mcode3.good()) {
    cout << "ERROR: El archivo mcode3.txt no ha sido encontrado o se encuentra "
            "dañado.\n";
    check = false;
  }
  if (!transmision1.good()) {
    cout << "ERROR: El archivo transmision1.txt no ha sido encontrado o se "
            "encuentra dañado.\n";
    check = false;
  }
  if (!transmision2.good()) {
    cout << "ERROR: El archivo transmision2.txt no ha sido encontrado o se "
            "encuentra dañado.\n";
    check = false;
  }

  return check;
}

bool validateLine(string currentLine) {

  const regex expReg("^[A-F0-9]*$");

  if (regex_match(currentLine, expReg) == true) {
    return true;
  } else {
    return false;
  }
}

bool validateFileLines(){
  
  string currentLine;
  
  while(getline(mcode1, currentLine)){

  if(validateLine(currentLine) != true){
    cout<<"ERROR: En el archivo mcode1.txt han sido encontrados caracteres invalidos. \n";
    cout<<"ERROR: Los caracteres validos son de A - F y 0 - 9. \n";
    return false;
  }
  }
  
  while(getline(mcode2, currentLine)){

  if(validateLine(currentLine) != true){
    cout<<"ERROR: En el archivo mcode2.txt han sido encontrados caracteres invalidos. \n";
    cout<<"ERROR: Los caracteres validos son de A - F y 0 - 9. \n";
    return false;
  }
  }
  
  while(getline(mcode3, currentLine)){

  if(validateLine(currentLine) != true){
    cout<<"ERROR: En el archivo mcode3.txt han sido encontrados caracteres invalidos. \n";
    cout<<"ERROR: Los caracteres validos son de A - F y 0 - 9. \n";
    return false;
  }
  }
  
  while(getline(transmision1, currentLine)){

  if(validateLine(currentLine) != true){
    cout<<"ERROR: En el archivo transmision1.txt han sido encontrados caracteres invalidos. \n";
    cout<<"ERROR: Los caracteres validos son de A - F y 0 - 9. \n";
    return false;
  }
  }
  
    while(getline(transmision2, currentLine)){

    if(validateLine(currentLine) != true){
    cout<<"ERROR: En el archivo transmision2.txt han sido encontrados caracteres invalidos. \n";
    cout<<"ERROR: Los caracteres validos son de A - F y 0 - 9. \n";
    return false;
  }
  }

  return true;
  
  }
    

#endif