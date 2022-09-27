/*
 * Archivo Auxiliar para la Actividad Integradora 1.
 * Se incluyen las funciones de validación de archivos.
 *        Authors: Carla Onate Gardella              A01653555 
 *                 Octavio Augusto Aleman Esparza    A01660702 
 * Complejidad de : O(n^2)
 * Date: 09.11.2022
 */

#ifndef UTIL_H
#define UTIL_H

#include <filesystem>
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

  if (!mcode1.good()) {
    cout << "ERROR: El archivo mcode1.txt no ha sido encontrado, se encuentra "
            "vacio o esta dañado.\n";
    return false;
  }
  if (!mcode2.good() || (mcode2.peek() == std::ifstream::traits_type::eof())) {
    cout << "ERROR: El archivo mcode2.txt no ha sido encontrado, se encuentra "
            "vacio o esta dañado.\n";
    return false;
  }
  if (!mcode3.good() || (mcode3.peek() == std::ifstream::traits_type::eof())) {
    cout << "ERROR: El archivo mcode3.txt no ha sido encontrado, se encuentra "
            "vacio o esta dañado.\n";
    return false;
  }
  if (!transmision1.good() ||
      (transmision1.peek() == std::ifstream::traits_type::eof())) {
    cout << "ERROR: El archivo transmission1.txt no ha sido encontrado, se "
            "encuentra vacio o esta dañado.\n";
    return false;
  }
  if (!transmision2.good() ||
      (transmision2.peek() == std::ifstream::traits_type::eof())) {
    cout << "ERROR: El archivo transmission2.txt no ha sido encontrado, se "
            "encuentra vacio o esta dañado.\n";
    return false;
  }

  return true;
}

bool validateLine(string currentLine) {
  const regex expReg("^[A-F0-9]*$");

  if (regex_match(currentLine, expReg) == true) {
    return true;
  } else {
    return false;
  }
}

bool validateFileLines() {

  string currentLine;

  while (getline(mcode1, currentLine)) {

    if (validateLine(currentLine) != true) {
      cout << "ERROR: En el archivo mcode1.txt han sido encontrados caracteres "
              "invalidos. \n";
      cout << "ERROR: Los caracteres validos son de A - F y 0 - 9. Y no se "
              "aceptan lineas vacias\n ";
      return false;
    }
  }

  while (getline(mcode2, currentLine)) {

    if (validateLine(currentLine) != true) {
      cout << "ERROR: En el archivo mcode2.txt han sido encontrados caracteres "
              "invalidos. \n";
      cout << "ERROR: Los caracteres validos son de A - F y 0 - 9. Y no se "
              "aceptan lineas vacias\n ";
      return false;
    }
  }

  while (getline(mcode3, currentLine)) {

    if (validateLine(currentLine) != true) {
      cout << "ERROR: En el archivo mcode3.txt han sido encontrados caracteres "
              "invalidos. \n";
      cout << "ERROR: Los caracteres validos son de A - F y 0 - 9. Y no se "
              "aceptan lineas vacias\n ";
      return false;
    }
  }

  while (getline(transmision1, currentLine)) {

    if (validateLine(currentLine) != true) {
      cout << "ERROR: En el archivo transmission1.txt han sido encontrados "
              "caracteres invalidos. \n";
      cout << "ERROR: Los caracteres validos son de A - F y 0 - 9. Y no se "
              "aceptan lineas vacias\n ";
      return false;
    }
  }

  while (getline(transmision2, currentLine)) {

    if (validateLine(currentLine) != true) {
      cout << "ERROR: En el archivo transmission2.txt han sido encontrados "
              "caracteres invalidos. \n";
      cout << "ERROR: Los caracteres validos son de A - F y 0 - 9. Y no se "
              "aceptan lineas vacias\n ";
      return false;
    }
  }

  return true;
}

#endif