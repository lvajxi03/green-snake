#ifndef __SWORD_H__
#define __SWORD_H__

#include "primi.h"

class Sword {
public:
  Sword(
        unsigned int nx,
        unsigned int ny);
  bool collide(SnakeBlock *b);
  unsigned int x();
  unsigned int y();
private:
  unsigned int _x;
  unsigned int _y;
};

#endif /* __SWORD_H__ */
