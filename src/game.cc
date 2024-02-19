#include <cstdlib>

#include "game.h"
#include "arena.h"
#include "params.h"

Game::Game() {
  _mouse_counter = 0;
  for (int i = 0; i < 6; i++) {
    _menu_rects.push_back(Rect(300, 100*(i+1), 600, 80));
  }
  _menu_rects.push_back(Rect(
                             SCREEN_WIDTH-80,
                             SCREEN_HEIGHT-24,
                             36,
                             20));
  _menu_rects.push_back(Rect(
                             SCREEN_WIDTH-40,
                             SCREEN_HEIGHT-24,
                             36,
                             20));
  for (int i = 0; i < 4; i++) {
    _opt_rects.push_back(Rect(300, 120*(i+1), 600, 80));
  }
  _enabled = false;
  std::srand(std::time(0));
  _board = BOARD_MENU;
  _state = STATE_UNKNOWN;
  _swords_consumed = 0;
  _player = L"new player";
  _collision_counter = 0;
  _counter = 180;
  _lives = 3;
  _score = 0;
  _to_pick = 0;
  _new_mode = MODE_NORMAL;
  _level = NULL;
  snake = NULL;
  _freeze_counter = 0;
  _level_index = 0;
  _menu_pos = 0;
  _lang = conf.lang();
}

Game::~Game() {
}

void Game::notify_pick() {
  _score++;
  _to_pick--;
  arena->media_play_pick();
}

void Game::notify_fireball() {
  _score += 5;
  _to_pick--;
  arena->media_play_diamond();
  if (is_unlimited()) {
    unsigned int f = std::rand() % _level->entry_points.size();
    Point *p = _level->entry_points[f];
    create_sword(p->x(), p->y());
  }
}

void Game::notify_diamond() {
  _score += 5;
  _to_pick--;
  arena->media_play_diamond();
}

void Game::_clear_killers() {
  for (Killer *k: killers) {
    delete k;
  }
  killers.clear();
}

void Game::notify_freeze() {
  arena->media_play_freeze();
  if (!is_frozen()) {
    _clear_killers();
    change_state(STATE_FROZEN);
  } else {
    _freeze_counter = 20;
  }
}

void Game::next_level() {
  if (_level_index < MAX_LEVELS-1) {
    _level_index++;
    if (_level != NULL) {
      delete _level;
    }
    _level = new Level(_level_index);
    _to_pick = _level->points();
    if (snake != NULL) {
      delete snake;
    }
    snake = new Snake(_level);
    if (!is_unlimited()) {
      _counter = 180 + 60 * _level_index;
    } else {
      _counter = 9999;
    }
    create_monsters();
    start_game();
    _state = STATE_INITIALIZED;
  } else {
    stop_game();
    change_board(BOARD_GAMEOVER);
  }
  arena->refresh();
}

void Game::game_initialize() {
  _freeze_counter = 0;
  _level_index = 0;
  _level = new Level(_level_index);
  snake = new Snake(_level);
  _to_pick = _level->points();
  if (!is_unlimited()) {
    _counter = 180 + 60 * _level_index;
  } else {
    _counter = 999;
  }
  _clear_swords();
  _clear_killers();
  _swords_consumed = 0;
  _score = 0;
  _lives = 3;
  create_monsters();
}

void Game::change_state(GameState state) {
  if (_state != state) {
    _state = state;
    switch (_state) {
    case STATE_INITIALIZED:
      game_initialize();
      break;
    case STATE_STARTED:
      start_game();
      break;
    case STATE_PAUSED:
      pause_game();
      break;
    case STATE_COLLIDED:
      stop_game();
      break;
    case STATE_GAMEOVER:
      stop_game();
      break;
    case STATE_FROZEN:
      freeze_game();
      break;
    default:
      break;
    }
  }
  arena->refresh();
}

Monster *Game::create_monster(int x, int y) {
  unsigned char pic = rand() % 7;
  unsigned char speed = 3 + rand() % (3 + 2 * _level_index);
  return new Monster(
                     x,
                     y,
                     MONSTER_WIDTH,
                     MONSTER_HEIGHT,
                     pic,
                     speed);
}

void Game::event_tick() {
  bool collided = false;
  SnakeBlock *head = snake->blocks.back();
  for (Killer *k: killers) {
    if (k->collide(head)) {
      if (!is_unlimited() && !is_frozen()) {
        collided = true;
        change_state(STATE_COLLIDED);
        arena->media_play_snake();
        if (_collision_counter == 0) {
          _collision_counter = COLLIDE_COUNTER;
          arena->refresh();
          arena->start_timer(TIMER_COLLISION,
                             TIMER_COLLISION_TIME);
        }
      }
      if (is_unlimited()) {
        if (is_frozen()) {
          int x = k->real_x()/BLOCK_HEIGHT;
          create_sword(
                       x,
                       k->y());
        } else {
          collided = true;
          change_state(STATE_COLLIDED);
          arena->media_play_snake();
          if (_collision_counter == 0) {
            _collision_counter = COLLIDE_COUNTER;
            arena->refresh();
            arena->start_timer(TIMER_COLLISION,
                               TIMER_COLLISION_TIME);
          }
        }
      }
      return;
    }
  }
  std::vector<Sword *>::iterator i;
  for (i = swords.begin(); i != swords.end(); i++) {
    Sword *s = *i;
    if (s->collide(head)) {
      swords.erase(i--);
      _swords_consumed++;
      arena->media_play_eat();
    }
  }
  std::vector<Monster *>::iterator j;
  for (j = monsters.begin(); j != monsters.end(); j++) {
    Monster *m = *j;
    if (m->collide(head)) {
      delete m;
      monsters.erase(j--);
      _score += 2;
      arena->media_play_eat();
      return;
    } else {
      std::vector<SnakeBlock *>::iterator k;
      for (k = snake->blocks.begin(); k!= snake->blocks.end(); k++) {
        SnakeBlock *b = *k;
        if (!collided) {
          if (m->collide(b)) {
            if (!is_unlimited() && !is_frozen()) {
              collided = true;
              change_state(STATE_COLLIDED);
              arena->media_play_snake();
              if (_collision_counter == 0) {
                _collision_counter = COLLIDE_COUNTER;
                arena->refresh();
                arena->start_timer(TIMER_COLLISION,
                                   TIMER_COLLISION_TIME);
              }
            } else {
              // Tutaj jest to dziwne miejsce,
              // gdzie doszlo do kolizji z potworem,
              // tryb gry to unlimited,
              // a ja nie wiem, co dalej
              // i Antoni tez nie.
              // :)
              monsters.erase(j--);
              _score += 2;
              arena->media_play_eat();
            }
          }
        }
      }
    }
    if (!is_frozen() || is_unlimited()) {
      if (!m->move()) {
        monsters.erase(j--);
        create_monster(m->x(), m->y());
        delete m;
      }
    }
  }
  std::vector<Killer *>::iterator l;
  for (l = killers.begin(); l != killers.end(); l++) {
    Killer *k = *l;
    if (!k->move()) {
      killers.erase(l--);
      delete k;
    }
  }
  arena->refresh();
  if (_to_pick == 0) {
    if (_counter > 0) {
      stop_game();
      next_level();
    }
  } else if (_lives == 0) {
    stop_game();
    change_state(STATE_GAMEOVER);
  }
}

bool Game::is_unlimited() {
  return (conf.mode() == MODE_UNLIMITED);
}

void Game::event_freeze() {
  _freeze_counter--;
  if (_freeze_counter == 0) {
    arena->stop_timer(TIMER_FREEZE);
    _state = STATE_STARTED;
    arena->start_timer(TIMER_COUNTER,
                       TIMER_COUNTER_TIME);
  }
}

void Game::update_monsters() {
  if (monsters.size() < (_level->entry_points.size())/2) {
    std::vector<Point *> pick;
    for (Point *p: _level->entry_points) {
      bool iss = false;
      for (Monster *m: monsters) {
        if (((unsigned int)m->x() == p->x()) && ((unsigned int)m->y() == p->y())) {
          iss = true;
        }
      }
      if (!iss) {
        pick.push_back(p);
      }
    }
    unsigned char maxp = pick.size()/2;
    std::random_shuffle(pick.begin(), pick.end());
    for (int n = 0; n < maxp; n++) {
      Point *p = pick[n];
      Monster *m = create_monster(p->x(), p->y());
      monsters.push_back(m);
    }
  }
}

void Game::create_killer() {
  if (killers.size() == 0) {
    unsigned char speed = 0;
    if (is_unlimited()) {
      speed = 5 + _level_index;
    } else {
      speed = 3 + rand() % (3 + 2 * _level_index);
    }
    int n = rand() % _level->entry_points.size();
    Point *p = _level->entry_points[n];
    Killer *k = new Killer(
                           p->x(),
                           p->y(),
                           MONSTER_WIDTH,
                           MONSTER_HEIGHT,
                           speed);
    killers.push_back(k);
  }
}

void Game::event_counter() {
  _counter--;
  if (_counter % 10 == 0) {
    update_monsters();
  }
  if (_counter % 24 == 0) {
    create_killer();
  }
  if (!is_unlimited()) {
    if (_counter == 0) {
      stop_game();
      change_state(STATE_GAMEOVER);
    }
  } else {
    if (_counter < 0) {
      _counter = 999;
    }
  }
}

void Game::paint() {
  switch(_board) {
  case BOARD_MENU:
    arena->paint_menu();
    break;
  case BOARD_GAME:
    arena->paint_game();
    break;
  case BOARD_OPTIONS:
    arena->paint_options();
    break;
  case BOARD_HISCORES:
    arena->paint_scores();
    break;
  case BOARD_NEWSCORE:
    arena->paint_newscore();
  case BOARD_HELP:
    arena->paint_help();
    break;
  case BOARD_ABOUT:
    arena->paint_about();
    break;
  case BOARD_GAMEOVER:
    arena->paint_gameover();
    break;
  default:
    break;
  }
}

void Game::create_monsters() {
  if (_level != NULL) {
    monsters.clear();
    std::vector<Point *>::iterator i;
    if (_level->entry_points.size() > 0) {
      for (
           i = _level->entry_points.begin();
           i != _level->entry_points.end();
           ++i) {
        Point *p = *i;
        monsters.push_back(
                            create_monster(
                                           p->x(),
                                           p->y()));
      }
    }
  }
}

void Game::event_consume() {
  if (!snake->consume()) {
    arena->stop_timer(TIMER_CONSUME);
    create_monsters();
    if (!is_unlimited()) {
      if (_lives > 0) {
        _lives--;
      }
      if (_lives == 0) {
        change_state(STATE_GAMEOVER);
      } else {
        run_game();
      }
    } else {
      run_game();
    }
  } else {
    arena->media_play_consume();
    arena->refresh();
  }
}

void Game::create_sword(int nx, int ny) {
  Sword *s = new Sword(nx, ny);
  swords.push_back(s);
}

void Game::event_collision() {
  if (_collision_counter > 0) {
    _collision_counter--;
    arena->refresh();
  } else {
    arena->stop_timer(TIMER_COLLISION);
    arena->start_timer(TIMER_CONSUME,
                       TIMER_CONSUME_TIME);
  }
}

void Game::start_game() {
  _freeze_counter = 0;
}

void Game::run_game() {
  _state = STATE_STARTED;
  _clear_killers();
  arena->start_timer(
                     TIMER_TICK,
                     TIMER_TICK_TIME);
  arena->start_timer(
                     TIMER_COUNTER,
                     TIMER_COUNTER_TIME);
}

void Game::pause_game() {
  arena->stop_timer(TIMER_TICK);
  arena->stop_timer(TIMER_COUNTER);
  arena->refresh();
}

void Game::stop_game() {
  _clear_killers();
  for (int i = 0; i < 5; i++) {
    arena->stop_timer(TIMER_TICK+i);
  }
}

void Game::freeze_game() {
  _freeze_counter = 20;
  arena->stop_timer(TIMER_COUNTER);
  arena->start_timer(TIMER_FREEZE,
                     TIMER_FREEZE_TIME);
}

void Game::move_right() {
  snake->move_right();
}

void Game::move_left() {
  snake->move_left();
}

void Game::move_top() {
  snake->move_top();
}

void Game::move_bottom() {
  snake->move_bottom();
}

void Game::move_back() {
  arena->media_play_consume();
  snake->consume();
}

void Game::change_board(GameBoard gb) {
  if (_board != gb) {
    _enabled = false;
    _board = gb;
    switch(gb) {
    case BOARD_GAME:
      change_state(STATE_INITIALIZED);
      break;
    case BOARD_NEWSCORE:
      _enabled = false;
      break;
    default:
      stop_game();
      break;
    }
    arena->refresh();
  }
}

void Game::keypressed_menu(Key k) {
}

bool Game::is_started() {
  return (_state == STATE_STARTED);
}

bool Game::is_paused() {
  return (_state == STATE_PAUSED);
}

bool Game::is_initialized() {
  return (_state == STATE_INITIALIZED);
}

bool Game::is_frozen() {
  return (_state == STATE_FROZEN);
}

void Game::keypressed_newhiscore(Key k) {
}

void Game::get_msg() {
}

void Game::keypressed_game(Key k) {
  switch (k) {
  case KEY_LEFT:
    {
      if (is_started() || is_frozen()) {
        move_left();
      }
    }
    break;
  case KEY_RIGHT:
    {
      if (is_started() || is_frozen()) {
        move_right();
      }
    }
    break;
  case KEY_TOP:
    {
      if (is_started() || is_frozen()) {
        move_top();
      }
    }
    break;
  case KEY_BOTTOM:
    {
      if (is_started() || is_frozen()) {
        move_bottom();
      }
    }
    break;
  case KEY_BACKSPACE:
    {
      if (is_started() || is_frozen()) {
        move_back();
      }
    }
    break;
  default:
    break;
  }
}

void Game::keypressed_options(Key k) {
  // All keyboard handling in keyip_options
}

void Game::keypressed_gameover(Key k) {
  // All keyboard handling in keyup_gameover
}

void Game::keypressed_about(Key k){
  // All keyboard handling in keyup_about
}

void Game::keypressed(Key k) {
  switch(_board) {
  case BOARD_MENU:
    keypressed_menu(k);
    break;
  case BOARD_ABOUT:
    keypressed_about(k);
    break;
  case BOARD_HELP:
    keypressed_help(k);
    break;
  case BOARD_HISCORES:
    keypressed_hiscores(k);
    break;
  case BOARD_NEWSCORE:
    keypressed_newhiscore(k);
    break;
  case BOARD_OPTIONS:
    keypressed_options(k);
    break;
  case BOARD_GAMEOVER:
    keypressed_gameover(k);
    break;
  case BOARD_GAME:
    keypressed_game(k);
    break;
  default:
    break;
  }
}

void Game::mouse_pressed(int x, int y, MouseButton b) {
  switch (_board) {
  case BOARD_GAME:
    mouse_pressed_game(x, y, b);
    break;
  case BOARD_OPTIONS:
    mouse_pressed_options(x, y, b);
    break;
  case BOARD_HELP:
    mouse_pressed_help(x, y, b);
    break;
  case BOARD_ABOUT:
    mouse_pressed_about(x, y, b);
    break;
  case BOARD_MENU:
    mouse_pressed_menu(x, y, b);
    break;
  case BOARD_HISCORES:
    mouse_pressed_hiscores(x, y, b);
    break;
  default:
    break;
  }
}

void Game::mouse_pressed_options(int x, int y, MouseButton b) {
  std::vector<Rect>::iterator i;
  unsigned char found = -1;
  unsigned char cnt = 0;
  for (i = _opt_rects.begin(); i != _opt_rects.end(); i++) {
    Rect r = *i;
    if (r.contains(x, y)) {
      found = cnt;
    }
    cnt++;
  }
  if (found >= 0) {
    conf.set_mode(found);
  }
  change_board(BOARD_MENU);
}

void Game::mouse_pressed_game(int x, int y, MouseButton b) {
  if (is_started() || is_frozen()) {
    switch (b) {
    case BUTTON_RIGHT:
      move_back();
      break;
    case BUTTON_LEFT:
      if ((_state == STATE_STARTED) || (_state == STATE_FROZEN)) {
        y = (y - TOP_OFFSET)/BLOCK_HEIGHT;
        x = x/BLOCK_WIDTH;
        if (x < snake->x()) {
          move_left();
        } else if (x > snake->x()) {
          move_right();
        }
        if (y < snake->y()) {
          move_top();
        } else if (y > snake->y()) {
          move_bottom();
        }
      }
      break;
    default:
      break;
    }
  } else if (is_initialized() || is_paused()) {
    change_state(STATE_STARTED);
    run_game();
  }
}

void Game::mouse_pressed_help(int x, int y, MouseButton b) {
  change_board(BOARD_MENU);
}

void Game::mouse_pressed_about(int x, int y, MouseButton b) {
  change_board(BOARD_MENU);
}

void Game::mouse_pressed_menu(int x, int y, MouseButton b) {
  std::vector<Rect>::iterator i;
  unsigned char found = -1;
  unsigned char cnt = 0;
  for (i = _menu_rects.begin(); i != _menu_rects.end(); i++) {
    Rect r = *i;
    if (r.contains(x, y)) {
      found = cnt;
    }
    cnt++;
  }
  switch(found) {
  case 0:
    change_board(BOARD_GAME);
    break;
  case 1:
    change_board(BOARD_OPTIONS);
    break;
  case 2:
    change_board(BOARD_HISCORES);
    break;
  case 3:
    change_board(BOARD_HELP);
    break;
  case 4:
    change_board(BOARD_ABOUT);
    break;
  case 5:
    conf.save();
    arena->terminate();
    break;
  case 6:
    _lang = 0;
    conf.set_lang(0);
    arena->refresh();
    break;
  case 7:
    _lang = 1;
    conf.set_lang(1);
    arena->refresh();
    break;
  default:
    break;
  }
}

void Game::mouse_pressed_hiscores(int x, int y, MouseButton b) {
  change_board(BOARD_MENU);
}

void Game::keypressed_help(Key k) {
  // All keyboard handling in keyup_help
}

void Game::keypressed_hiscores(Key k) {
  // All keyboard handling in keyup_hiscores
}

/* Certain getters */

GameBoard Game::board() {
  return _board;
}

unsigned char Game::mode() {
  return conf.mode();
}

unsigned char Game::mode_menu() {
  return _new_mode;
}

unsigned int Game::counter() {
  return _counter;
}

Level *Game::level() {
  return _level;
}

void Game::_clear_swords() {
  for (Sword *s: swords) {
    delete s;
  }
  swords.clear();
}

bool Game::is_over() {
  return (_state == STATE_GAMEOVER);
}

unsigned int Game::score() {
  return _score;
}

unsigned int Game::freeze_counter() {
  return _freeze_counter;
}

unsigned int Game::lives() {
  return _lives;
}

unsigned int Game::level_index() {
  return _level_index;
}

unsigned int Game::collision_counter() {
  return _collision_counter;
}

bool Game::is_collided() {
  return (_state == STATE_COLLIDED);
}

unsigned char Game::menu_pos() {
  return _menu_pos;
}

void Game::save() {
  conf.save();
}

std::wstring Game::player() {
  return _player;
}

void Game::processchar(unsigned char ch) {
  switch (_board) {
  case BOARD_NEWSCORE:
    if (_enabled) {
      if (_player.size() < 20) {
        _player += ch;
        arena->refresh();
      }
    }
    break;
  default:
    break;
  }
}

void Game::keyup(Key k) {
  _enabled = true;
  switch(_board) {
  case BOARD_MENU:
    keyup_menu(k);
    break;
  case BOARD_ABOUT:
    keyup_about(k);
    break;
  case BOARD_HELP:
    keyup_help(k);
    break;
  case BOARD_HISCORES:
    keyup_hiscores(k);
    break;
  case BOARD_NEWSCORE:
    keyup_newhiscore(k);
    break;
  case BOARD_OPTIONS:
    keyup_options(k);
    break;
  case BOARD_GAMEOVER:
    keyup_gameover(k);
    break;
  case BOARD_GAME:
    keyup_game(k);
    break;
  default:
    break;
  }

}

unsigned char Game::lang() {
  return _lang;
}

void Game::mouse_released(int x, int y, MouseButton b) {
}

void Game::mouse_released_about(int x, int y, MouseButton b) {
}

void Game::mouse_released_menu(int x, int y, MouseButton b) {
}

void Game::mouse_released_game(int x, int y, MouseButton b) {
}

void Game::mouse_released_help(int x, int y, MouseButton b) {
}

void Game::mouse_released_options(int x, int y, MouseButton b) {
}

void Game::mouse_released_hiscores(int x, int y, MouseButton b) {
}

void Game::keyup_about(Key k) {
  switch (k) {
  case KEY_Q:
  case KEY_ESCAPE:
    change_board(BOARD_MENU);
    break;
  default:
    break;
  }
}

void Game::keyup_game(Key k) {
  switch(k) {
  case KEY_ESCAPE:
    {
      if (is_started()) {
        change_state(STATE_PAUSED);
      }
    }
    break;
  case KEY_Q:
  {
    stop_game();
    if (is_over()) {
      if (_score > conf.min_score()) {
        change_board(BOARD_NEWSCORE);
      } else {
        change_board(BOARD_MENU);
      }
    } else {
      change_board(BOARD_MENU);
    }
  }
  break;
  case KEY_SPACE:
  {
    if (is_initialized() || is_paused()) {
      change_state(STATE_STARTED);
      run_game();
    }
  }
  break;
  default:
    break;
  }
}

void Game::keyup_gameover(Key k) {
  switch (k) {
  case KEY_Q:
  case KEY_ESCAPE:
    if (_score > conf.min_score()) {
      change_board(BOARD_NEWSCORE);
    } else {
        change_board(BOARD_MENU);
    }
    break;
  default:
    break;
  }
}

void Game::keyup_help(Key k) {
  switch (k) {
  case KEY_Q:
  case KEY_ESCAPE:
    change_board(BOARD_MENU);
    break;
  default:
    break;
  }
}

void Game::keyup_hiscores(Key k) {
  switch (k) {
  case KEY_Q:
  case KEY_ESCAPE:
    change_board(BOARD_MENU);
    break;
  default:
    break;
  }
}

void Game::keyup_menu(Key k) {
  switch(k) {
  case KEY_BOTTOM:
    {
      if (_menu_pos < 5) {
        _menu_pos++;
        arena->media_play_pick();
        arena->refresh();
      }
    }
    break;
  case KEY_TOP: {
    if (_menu_pos > 0) {
      _menu_pos--;
      arena->media_play_pick();
      arena->refresh();
    }
  }
    break;
  case KEY_ENTER: {
    arena->media_play_eat();
    switch (_menu_pos) {
    case 0:
      change_board(BOARD_GAME);
      break;
    case 1:
      _new_mode = conf.mode();
      change_board(BOARD_OPTIONS);
      break;
    case 2:
      change_board(BOARD_HISCORES);
      break;
    case 3:
      change_board(BOARD_HELP);
      break;
    case 4:
      change_board(BOARD_ABOUT);
      break;
    case 5:
      arena->terminate();
    }
  }
    break;
  case KEY_Q:
    {
      arena->terminate();
    }
    break;
  default:
    break;
  }
}

void Game::keyup_newhiscore(Key k) {
  switch (k) {
  case KEY_ESCAPE:
    change_board(BOARD_MENU);
    break;
  case KEY_BACKSPACE:
    if (_player.size() > 0) {
      _player.pop_back();
      arena->refresh();
    }
    break;
  case KEY_ENTER:
    conf.append_score(_player.c_str(), _score);
    change_board(BOARD_HISCORES);
    break;
  default:
    break;
  }
}

void Game::keyup_options(Key k) {
  switch (k) {
  case KEY_TOP:
    if (_new_mode > 0) {
      _new_mode--;
      arena->media_play_pick();
      arena->refresh();
    }
    break;
  case KEY_BOTTOM:
    if (_new_mode < 3) {
      _new_mode++;
      arena->media_play_pick();
      arena->refresh();
    }
    break;
  case KEY_ENTER:
    {
      arena->media_play_freeze();
      conf.set_mode(_new_mode);
      change_board(BOARD_MENU);
    }
    break;
  case KEY_Q:
  case KEY_ESCAPE:
    change_board(BOARD_MENU);
    break;
  default:
    break;
  }
}

unsigned int Game::swords_consumed() {
  return _swords_consumed;
}

