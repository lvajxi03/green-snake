#ifndef __KILLER_H__
#define __KILLER_H__

#include "primi.h"

class Killer {
public:
  Killer(
         int nx,
         int ny,
         unsigned int nw,
         unsigned int nh,
         unsigned char speed);
  int x();
  int y();
  unsigned int w();
  unsigned int h();
  unsigned char speed();
  bool move();
  bool collide(SnakeBlock *b);
  int real_x();
  int real_y();
  MonsterDirection direction();
 private:
  int _x;
  int _y;
  int _real_x;
  int _real_y;
  unsigned int _w;
  unsigned int _h;
  unsigned char _speed;
  MonsterDirection _direction;
};

#endif /* __KILLER_H__ */
