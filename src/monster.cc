#include "monster.h"

Monster::Monster(
                 int nx,
                 int ny,
                 unsigned int nw,
                 unsigned int nh,
                 unsigned char picindex,
                 float speed
                 ) {
  _x = nx;
  _y = ny;
  _w = nw;
  _h = nh;
  _picindex = picindex;
  if (nx > 0) {
    _direction = MD_EAST;
    _real_x = nx * BLOCK_WIDTH + MONSTER_WIDTH + 1;
  } else {
    _direction = MD_WEST;
    _real_x = nx * BLOCK_WIDTH - MONSTER_WIDTH - 1;
  }
  _real_y = ny * BLOCK_HEIGHT;
  _picindex = picindex;
  _speed = speed;
}

float Monster::real_x() {
  return _real_x;
}

float Monster::real_y() {
  return _real_y;
}

unsigned char Monster::index() {
  return _picindex;
}

bool Monster::move() {
  if (_direction == MD_WEST) {
      _real_x += _speed * 0.2;
      if (_real_x >= SCREEN_WIDTH) {
        return false;
      }
  } else {
    _real_x -= _speed * 0.2;
    if (_real_x <= 0) {
      return false;
    }
  }
  return true;
}

unsigned int Monster::w() {
  return _w;
}

unsigned int Monster::h() {
  return _h;
}

int Monster::x() {
  return _x;
}

int Monster::y() {
  return _y;
}

bool Monster::collide(SnakeBlock *b) {
  int x = b->x() * BLOCK_WIDTH;
  int y = b->y() * BLOCK_HEIGHT;
  if (x >= (int)(_real_x + _w)) {
    return false;
  }
  if (_real_x >= x + BLOCK_WIDTH) {
    return false;
  }
  if (y >= (int)(_real_y + _h)) {
    return false;
  }
  if (_real_y >= y + BLOCK_HEIGHT) {
    return false;
  }
  return true;
}
