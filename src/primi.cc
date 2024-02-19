#include "primi.h"

Point::Point(unsigned int nx, unsigned int ny) {
  _x = nx;
  _y = ny;
}
unsigned int Point::x() {
  return _x;
}

unsigned int Point::y() {
  return _y;
}

void Point::set(unsigned int nx, unsigned int ny) {
  _x = nx;
  _y = ny;
}

Rect::Rect(int nx, int ny, unsigned int nw, unsigned int nh) {
  _x = nx;
  _y = ny;
  _w = nw;
  _h = nh;
}

int Rect::x()
{
  return _x;
}

int Rect::y()
{
  return _y;
}

unsigned int Rect::w()
{
  return _w;
}

unsigned int Rect::h()
{
  return _h;
}

SnakeBlock::SnakeBlock(
                       unsigned int nx,
                       unsigned int ny,
                       Move nm) {
  _x = nx;
  _y = ny;
  _mov = nm;
  _orientation = ORI_VERTICAL;
}

unsigned int SnakeBlock::x() {
  return _x;
}

unsigned int SnakeBlock::y() {
  return _y;
}

Orientation SnakeBlock::orientation() {
  return _orientation;
}

void SnakeBlock::set_orientation(Orientation ori) {
  _orientation = ori;
}

Move SnakeBlock::move() {
  return _mov;
}

bool score_compare(Score *s1, Score *s2) {
  return (s1->score < s2->score);
}

bool Rect::contains(int x, int y) {
  if ((_x <= x ) && (_x + _w >= x) && (_y <= y) && (_y + _h >= y)) {
    return true;
  }
  return false;
}
