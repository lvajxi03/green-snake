#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>

#include "dtypes.h"
#include "level.h"

#include "globals.h"

class Snake {
public:
  Snake(Level *l);
  ~Snake();
  void append(SnakeBlock *block);
  bool consume();
  bool has_prev(unsigned int x, unsigned int y);
  bool contains(unsigned int x, unsigned int y);
  void move(Move mov);
  void move_left();
  void move_right();
  void move_top();
  void move_bottom();
  std::vector<SnakeBlock *> blocks;
  unsigned int x();
  unsigned int y();
private:
  unsigned int _x;
  unsigned int _y;
  unsigned int _spot_x;
  unsigned int _spot_y;
  Level *_level;
};

#endif /* __SNAKE_H__ */
