#include "killer.h"

Killer::Killer(
               int nx,
               int ny,
               unsigned int nw,
               unsigned int nh,
               unsigned char speed) {
  _x = nx;
  _y = ny;
  _w = nw;
  _h = nh;
  _speed = speed;
  _direction = nx > 0 ? MD_EAST : MD_WEST;
  _real_x = nx * BLOCK_WIDTH,
  _real_y = ny * BLOCK_HEIGHT;
}

MonsterDirection Killer::direction() {
  return _direction;
}

int Killer::x() {
  return _x;
}

int Killer::y() {
  return _y;
}

unsigned int Killer::w() {
  return _w;
}

unsigned int Killer::h() {
  return _h;
}

unsigned char Killer::speed() {
  return _speed;
}

bool Killer::move() {
  if (_direction == MD_WEST) {
      _real_x += _speed;
      if (_real_x >= SCREEN_WIDTH) {
        return false;
      }
  } else {
    _real_x -= _speed;
    if (_real_x <= 0) {
      return false;
    }
  }
  return true;
}

bool Killer::collide(SnakeBlock *b) {
  int x = b->x() * BLOCK_WIDTH;
  int y = b->y() * BLOCK_HEIGHT;
  if (x > _real_x + _w) {
    return false;
  }
    if (_real_x >= x + BLOCK_WIDTH) {
    return false;
  }
    if (y >= _real_y + _h) {
    return false;
  }
    if (_real_y >= y + BLOCK_HEIGHT) {
    return false;
  }
  return true;
}

int Killer::real_x() {
  return _real_x;
}

int Killer::real_y() {
  return _real_y;
}
