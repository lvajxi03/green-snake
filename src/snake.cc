#include "snake.h"

#include "game.h"


Snake::Snake(Level *l) {
  _level = l;
  Point *p = _level->spot();
  append(new SnakeBlock(
                        p->x(),
                        p->y(),
                        MOVE_BOTTOM));
  append(new SnakeBlock(
                        p->x(),
                        p->y()+1,
                        MOVE_BOTTOM));
  _spot_x = p->x();
  _spot_y = p->y();
  _x = _spot_x;
  _y = _spot_y+1;
}


Snake::~Snake() {
  for (SnakeBlock *b: blocks) {
    delete b;
  }
  blocks.clear();
}

void Snake::append(SnakeBlock *block) {
  blocks.push_back(block);
}

bool Snake::consume() {
  if (blocks.size() > 2) {
    blocks.pop_back();
    SnakeBlock *b = blocks.back();
    _x = b->x();
    _y = b->y();
    return true;
  }
  return false;
}


bool Snake::has_prev(unsigned int x, unsigned int y) {
  if (blocks.size() >= 2) {
    SnakeBlock *b = blocks[blocks.size()-2];
    if ((b->x() == x) && (b->y() == y)) {
      return true;
    }
  }
  return false;
}

bool Snake::contains(unsigned int x, unsigned int y) {
  for (SnakeBlock *b: blocks) {
    if ((b->x() == x) && (b->y() == y)) {
      return true;
    }
  }
  return false;
}

void Snake::move(Move mov) {
  int next_x = 0;
  int next_y = 0;
  switch (mov) {
  case MOVE_RIGHT:
    {
      next_x = _x+1;
      next_y = _y;
    }
    break;
  case MOVE_BOTTOM:
    {
      next_x = _x;
      next_y = _y+1;
    }
    break;
  case MOVE_LEFT:
    {
      next_x = _x-1;
      next_y = _y;
    }
    break;
  case MOVE_TOP:
    {
      next_x = _x;
      next_y = _y-1;
    }
    break;
  }
  if (next_x < 0) {
    return;
  }
  if (next_x > 39) {
    return;
  }
  if (next_y < 0) {
    return;
  }
  if (next_y > 19) {
    return;
  }
  unsigned int h = _level->at(next_x, next_y);
  if (has_prev(next_x, next_y)) {
    consume();
  } else if (contains(next_x, next_y)) {
    return;
  } else if (h != 1) {
    _x = next_x;
    _y = next_y;
    switch(h) {
    case 2: // '.'
      {
        _level->clear(_x, _y);
        game->notify_pick();
      }
      break;
    case 7: // v
      {
        _level->clear(_x, _y);
        game->notify_fireball();
      }
      break;
    case 6: // %
      {
        _level->clear(_x, _y);
        game->notify_diamond();
      }
      break;
    case 5: // *
      {
        _level->clear(_x, _y);
        game->notify_freeze();
      }
      break;
    }
    SnakeBlock *b = new SnakeBlock(_x, _y, mov);
    blocks.push_back(b);
  }
}

void Snake::move_left() {
  move(MOVE_LEFT);
}

void Snake::move_right() {
  move(MOVE_RIGHT);
}

void Snake::move_top() {
  move(MOVE_TOP);
}

void Snake::move_bottom() {
  move(MOVE_BOTTOM);
}

unsigned int Snake::x() {
  return _x;
}

unsigned int Snake::y() {
  return _y;
}
