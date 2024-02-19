/* Primitive types definition */

#ifndef __PRIMI_H__
#define __PRIMI_H__

#include <windows.h>

#include "dtypes.h"
#include "params.h"

class Point
{
public:
  Point(unsigned int nx, unsigned int ny);
  unsigned int x();
  unsigned int y();
  void set(unsigned int nx, unsigned int ny);
private:
  unsigned int _x;
  unsigned int _y;
};

class Rect {
public:
  Rect(int nx, int ny, unsigned int nw, unsigned int nh);
  int x();
  int y();
  unsigned int w();
  unsigned int h();
  bool contains(int x, int y);
private:
  int _x;
  int _y;
  unsigned int _w;
  unsigned int _h;
};

class SnakeBlock {
public:
  SnakeBlock(unsigned int nx, unsigned int ny, Move nm);
  unsigned int x();
  unsigned int y();
  Orientation orientation();
  void set_orientation(Orientation ori);
  Move move();
private:
  unsigned int _x;
  unsigned int _y;
  Orientation _orientation;
  Move _mov;
};

typedef struct _Score {
  std::wstring name;
  unsigned int score;
} Score;

bool score_compare(Score *s1, Score *s2);
#endif /* __PRIMI_H__ */
