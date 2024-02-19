#include "sword.h"

Sword::Sword(unsigned int nx, unsigned int ny) {
  _x = nx;
  _y = ny;
}

unsigned int Sword::x() {
  return _x;
}

unsigned int Sword::y() {
  return _y;
}

bool Sword::collide(SnakeBlock *b) {
  return ((_x == b->x()) && (_y == b->y()));;
}
