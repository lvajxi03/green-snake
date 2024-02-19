#ifndef __ARENA_H__
#define __ARENA_H__

#include <windows.h>
#include <windowsx.h>
#include <wingdi.h>

#include <vector>
#include <map>

#include "conf.h"
#include "dtypes.h"
#include "globals.h"
#include "level.h"
#include "loc.h"
#include "params.h"
#include "res.h"
#include "utils.h"
#include "utils.h"

#include "monster.h"


LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL RegisterMainWindowClass(void);
HWND CreateMainWindow(void);

class Game;

class Arena {
public:
  Arena();
  ~Arena();
  void paint_menu();
  void paint_game();
  void paint_options();
  void paint_scores();
  void paint_newscore();
  void paint_help();
  void paint_about();
  void paint_gameover();

  void keypress(Key k);
  void keyup(Key k);

  void mouse_pressed(int x, int y, MouseButton b);
  void mouse_released(int x, int y, MouseButton b);
  void media_play_consume();
  void media_play_pick();
  void media_play_diamond();
  void media_play_freeze();
  void media_play_snake();
  void media_play_eat();

  void refresh();
  void terminate();

  void mouse_center();
  void mouse_move(int x, int y);

  void start_timer(unsigned int timer, unsigned int timeout);
  void stop_timer(unsigned int timer);

  void processchar(unsigned char ch);

private:
  std::vector<Rect *>_menu_regions;
  std::vector<Rect *>_menu_options;
  std::map<std::string, unsigned int> _sounds;
  std::map<std::string, unsigned int> _timers;
  std::vector<unsigned int> _creatures;
  std::vector<unsigned int> _freezes;
  std::vector<unsigned int> _diamonds;
  std::vector<unsigned int> _squares;
  std::vector<unsigned int> _fireballs;

  HBITMAP _top;
  HBITMAP _block;
  HBITMAP _block_frozen;
  HBITMAP _square[4];
  HBITMAP _freeze[4];
  HBITMAP _diamond[4];
  HBITMAP _fireball[4];
  HBITMAP _creature[7];
  HBITMAP _snake[2];
  HBITMAP _flags[2];
  HBITMAP _pipes_normal[6];
  HBITMAP _pipes_frozen[6];
  HBITMAP _pipes_inverted[6];
  HBITMAP _heads_normal[4];
  HBITMAP _heads_frozen[4];
  HBITMAP _heads_inverted[4];
  HBITMAP _killers_left[2];
  HBITMAP _killers_right[2];
  HBITMAP _cup;
  HBITMAP _swords[2];
  HFONT _font_big;
  HFONT _font_medium;
  HFONT _font_small;
  HPEN _game_frame;
  HBRUSH _game_fill;
  HBRUSH _game_background;
};

#endif /* __ARENA_H__ */
