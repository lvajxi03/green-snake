#ifndef __GAME_H__
#define __GAME_H__

#include "dtypes.h"
#include "globals.h"
#include "primi.h"
#include "monster.h"
#include "killer.h"
#include "sword.h"
#include "snake.h"
#include "conf.h"

#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

class Arena;

class Game {
public:
  Game();
  ~Game();
  /* Flags */
  bool is_frozen();
  bool is_initialized();
  bool is_started();
  bool is_unlimited();
  bool is_over();
  bool is_paused();
  bool is_collided();

  /* Events */
  void event_tick();
  void event_counter();
  void event_collision();
  void event_consume();
  void event_freeze();
  void event_help();

  Monster *create_monster(int x, int y);

  void change_board();
  void change_board(GameBoard gb);
  void change_state(GameState state);
  void create_killer();
  void create_monsters();
  void create_sword(int nx, int ny);
  void freeze_game();
  void game_initialize();
  void get_msg();
  void keypressed(Key k);
  void keypressed_about(Key k);
  void keypressed_game(Key k);
  void keypressed_gameover(Key k);
  void keypressed_help(Key k);
  void keypressed_hiscores(Key k);
  void keypressed_menu(Key k);
  void keypressed_newhiscore(Key k);
  void keypressed_options(Key k);

  void keyup(Key k);
  void keyup_about(Key k);
  void keyup_game(Key k);
  void keyup_gameover(Key k);
  void keyup_help(Key k);
  void keyup_hiscores(Key k);
  void keyup_menu(Key k);
  void keyup_newhiscore(Key k);
  void keyup_options(Key k);
  void mouse_pressed(int x, int y, MouseButton b);
  void mouse_pressed_about(int x, int y, MouseButton b);
  void mouse_pressed_menu(int x, int y, MouseButton b);
  void mouse_pressed_game(int x, int y, MouseButton b);
  void mouse_pressed_help(int x, int y, MouseButton b);
  void mouse_pressed_options(int x, int y, MouseButton b);
  void mouse_pressed_hiscores(int x, int y, MouseButton b);
  void mouse_released(int x, int y, MouseButton b);
  void mouse_released_about(int x, int y, MouseButton b);
  void mouse_released_menu(int x, int y, MouseButton b);
  void mouse_released_game(int x, int y, MouseButton b);
  void mouse_released_help(int x, int y, MouseButton b);
  void mouse_released_options(int x, int y, MouseButton b);
  void mouse_released_hiscores(int x, int y, MouseButton b);
  void move_back();
  void move_bottom();
  void move_left();
  void move_right();
  void move_top();
  void next_level();
  void notify_diamond();
  void notify_fireball();
  void notify_freeze();
  void notify_pick();
  void paint();
  void pause_game();
  void processchar(unsigned char ch);
  void run_game();
  void start_game();
  void stop_game();
  void update_monsters();

  std::vector<Monster *> monsters;
  std::vector<Sword *> swords;

  /* Certain getters */
  GameBoard board();
  unsigned char mode();
  unsigned char mode_menu();
  unsigned char menu_pos();
  unsigned int counter();
  std::wstring player();
  Level *level();
  Snake *snake;
  unsigned int score();
  unsigned int freeze_counter();
  unsigned int lives();
  unsigned int level_index();
  std::vector<Killer *> killers;
  unsigned int collision_counter();
  unsigned char lang();

  void mouse_setpos(int x, int y);
  void save();
  Configuration conf;
  unsigned int swords_consumed();

private:
  void _clear_killers();
  void _clear_swords();
  int _pos_x;
  int _pos_y;

  std::vector<Rect> _menu_rects;
  std::vector<Rect> _opt_rects;

  GameState _state;
  GameBoard _board;
  Level *_level;
  unsigned int _score;
  unsigned int _swords_consumed;
  unsigned int _level_index;
  std::wstring _player;
  unsigned int _counter;
  unsigned int _freeze_counter;
  unsigned int _lives;
  unsigned int _to_pick;
  unsigned int _collision_counter;
  unsigned char _menu_pos;
  unsigned char _new_mode;
  bool _enabled;
  unsigned char _lang;
  unsigned long _mouse_counter;

};

#endif /* __GAME_H__ */
