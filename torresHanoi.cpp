#include <iostream>
#include <vector>
using namespace std;

// 3 steps
// n-1 from "from" to "aux"
// n from "from" to "destination"
// n-1 from "aux" to "destination"
// LA PRIMERA LLAMADA RECURSIVA LO QUE QUIERE DECIR ES QUE PASES TODOS LOS DISCOS ARRIBA DEL MAS GRANDE A LA TORRE AUXILIAR
// DESPUES YA PUEDES MOVER LA ULTIMA PIEZA AL LUGAR FINAL
// SEGUNDA LLAMADA QUIERE DECIR QUE PASES TODOS LOS DISCOS QUE ESTABAN ARRIBA DEL MAS GRANDE DE LA TORRE AUXILIAR AL DESTINATION OSEA ARRIBA DEL MAS GRANDE.
//esto se va haciendo recursivamente por lo que cada llamada represetna lo mismo pero para diferente numero de discos.

// Tienes n numero de discos -> cuando llegas al disco 1 o mas pequeño lo pasas al lugar de destino
// if last disc switch to tower from to tower to
void hanoi (int disc, char from, char to, char aux) {
  if (disc == 1) {
    return;
  }
  hanoi(disc - 1, from, aux, to);
  // move from to dest
  hanoi(disc - 1, aux, to, from);
}


int main () {
  hanoi(3, 'A', 'B', 'C');
  return 0;
}
