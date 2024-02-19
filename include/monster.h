#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "dtypes.h"
#include "params.h"
#include "primi.h"

class Monster {
public:
  Monster(
          int nx,
          int ny,
          unsigned int nw,
          unsigned int nh,
          unsigned char picindex,
          float speed);
  float real_x();
  float real_y();
  int x();
  int y();
  unsigned int w();
  unsigned int h();
  unsigned char index();
  bool move();
  bool collide(SnakeBlock *b);
private:
  unsigned char _picindex;
  MonsterDirection _direction;
  float _real_x;
  float _real_y;
  int _x;
  int _y;
  unsigned int _w;
  unsigned int _h;
  float _speed;
};

#endif /* __MONSTER_H__ */
