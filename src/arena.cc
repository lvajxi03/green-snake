#include "arena.h"
#include "game.h"

static LPCTSTR MainWndClass = TEXT("ZielonyWaz");

RECT prostokat = {50, 50, 50 + SCREEN_WIDTH, 50 + SCREEN_HEIGHT};
RECT plansza = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

Arena *arena;
Game *game;

// TODO: destroy all HBITMAPs in destructor!

Arena::Arena() {
  _game_frame = CreatePen(PS_SOLID, 10, RGB(136, 0, 0));
  _game_fill = CreateSolidBrush(RGB(151, 0, 0));
  _game_background = CreateSolidBrush(RGB(35, 35, 35));
  _font_medium = CreateFont(
                            FONT_SIZE_MEDIUM,
                            0,
                            0,
                            0,
                            FW_NORMAL,
                            FALSE,
                            FALSE,
                            FALSE,
                            DEFAULT_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH,
                            TEXT(FONT_BASIC));
  if (!_font_medium) {
    _font_medium = CreateFont(
                              FONT_SIZE_MEDIUM,
                              0,
                              0,
                              0,
                              FW_NORMAL,
                              FALSE,
                              FALSE,
                              FALSE,
                              DEFAULT_CHARSET,
                              OUT_DEFAULT_PRECIS,
                              CLIP_DEFAULT_PRECIS,
                              DEFAULT_QUALITY,
                              DEFAULT_PITCH,
                              TEXT(FONT_BACKUP));
  }
  _font_big = CreateFont(
                         FONT_SIZE_LARGE,
                         0,
                         0,
                         0,
                         FW_NORMAL,
                         FALSE,
                         FALSE,
                         FALSE,
                         DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY,
                         DEFAULT_PITCH,
                         TEXT(FONT_BASIC));
  if (!_font_big) {
    _font_big = CreateFont(
                           FONT_SIZE_LARGE,
                           0,
                           0,
                           0,
                           FW_NORMAL,
                           FALSE,
                           FALSE,
                           FALSE,
                           DEFAULT_CHARSET,
                           OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY,
                           DEFAULT_PITCH,
                           TEXT(FONT_BACKUP));
  }
  _font_small = CreateFont(
                         FONT_SIZE_SMALL,
                         0,
                         0,
                         0,
                         FW_NORMAL,
                         FALSE,
                         FALSE,
                         FALSE,
                         DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY,
                         DEFAULT_PITCH,
                         TEXT(FONT_BASIC));
  if (!_font_small) {
    _font_small = CreateFont(
                           FONT_SIZE_SMALL,
                           0,
                           0,
                           0,
                           FW_NORMAL,
                           FALSE,
                           FALSE,
                           FALSE,
                           DEFAULT_CHARSET,
                           OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS,
                           DEFAULT_QUALITY,
                           DEFAULT_PITCH,
                           TEXT(FONT_BACKUP));
  }

  int i = 0;
  _block = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_BLOCK));
  _block_frozen = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_BLOCK_FROZEN));
  _top = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_TOP));
  _square[0] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_SQUARE_1));
  _square[1] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_SQUARE_2));
  _square[2] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_SQUARE_1));
  _square[3] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_SQUARE_1));
  _freeze[0] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_FREEZE_1));
  _freeze[1] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_FREEZE_2));
  _freeze[2] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_FREEZE_3));
  _freeze[3] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_FREEZE_4));
  _diamond[0] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_DIAMOND_1));
  _diamond[1] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_DIAMOND_2));
  _diamond[2] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_DIAMOND_3));
  _diamond[3] = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_DIAMOND_4));
  _cup = LoadBitmap(instancja, MAKEINTRESOURCE(IDB_CUP));
  for (i = 0; i < 4; i++) {
    _fireball[i] = LoadBitmap(
                              instancja,
                              MAKEINTRESOURCE(IDB_FIREBALL_1 + i));
    }
  for (i = 0; i < 7; i++) {
    _creature[i] = LoadBitmap(
                              instancja,
                              MAKEINTRESOURCE(IDB_CREATURE_1 + i));
  }
  for (i = 0; i < 4; i++) {
    _heads_normal[i] = LoadBitmap(
                                  instancja,
                                  MAKEINTRESOURCE(IDB_HEAD_RIGHT + i));
    _heads_frozen[i] = LoadBitmap(
                                  instancja,
                                  MAKEINTRESOURCE(IDB_FRZ_RIGHT + i));
    _heads_inverted[i] = LoadBitmap(
                                    instancja,
                                    MAKEINTRESOURCE(IDB_INV_RIGHT +i));
  }
  for (i = 0; i < 6; i++) {
    _pipes_normal[i] = LoadBitmap(
                                  instancja,
                                  MAKEINTRESOURCE(IDB_SNAKE_HORIZONTAL+i));
    _pipes_frozen[i] = LoadBitmap(
                                  instancja,
                                  MAKEINTRESOURCE(IDB_FRZ_HORIZONTAL+i));
    _pipes_inverted[i] = LoadBitmap(
                                    instancja,
                                    MAKEINTRESOURCE(IDB_INV_HORIZONTAL+i));
  }
  _killers_left[0] = LoadBitmap(instancja,
                               MAKEINTRESOURCE(IDB_KILLER_LEFT));
  _killers_left[1] = LoadBitmap(instancja,
                               MAKEINTRESOURCE(IDB_KILLER_LEFT_B));
  _killers_right[0] = LoadBitmap(instancja,
                               MAKEINTRESOURCE(IDB_KILLER_RIGHT));
  _killers_right[1] = LoadBitmap(instancja,
                               MAKEINTRESOURCE(IDB_KILLER_RIGHT_B));

  _flags[0] = LoadBitmap(instancja,
                        MAKEINTRESOURCE(IDB_FLAG_PL));
  _flags[1] = LoadBitmap(instancja,
                         MAKEINTRESOURCE(IDB_FLAG_EN));

  _swords[0] = LoadBitmap(instancja,
                        MAKEINTRESOURCE(IDB_SWORD_FIRE));
  _swords[1] = LoadBitmap(instancja,
                         MAKEINTRESOURCE(IDB_SWORD_ICE));
}

Arena::~Arena() {
  for (int i = 0; i < 4; i++) {
    DeleteObject(_heads_normal[i]);
    DeleteObject(_heads_frozen[i]);
    DeleteObject(_heads_inverted[i]);
  }
  DeleteObject(_font_big);
  DeleteObject(_font_medium);
  DeleteObject(_font_small);
  DeleteObject(_game_background);
  DeleteObject(_game_frame);
  DeleteObject(_game_fill);
  DeleteObject(_flags[0]);
  DeleteObject(_flags[1]);
  DeleteObject(_cup);
}

void Arena::media_play_consume() {
  PlaySound(
            MAKEINTRESOURCE(IDS_SWOOSH),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::media_play_pick() {
  PlaySound(
            MAKEINTRESOURCE(IDS_PIPE),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::media_play_diamond() {
  PlaySound(
            MAKEINTRESOURCE(IDS_COIN),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::media_play_freeze() {
  PlaySound(
            MAKEINTRESOURCE(IDS_POP),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::media_play_snake() {
  PlaySound(
            MAKEINTRESOURCE(IDS_SNAKE),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::media_play_eat() {
  PlaySound(
            MAKEINTRESOURCE(IDS_STAB),
            instancja,
            SND_ASYNC|SND_RESOURCE);
}

void Arena::paint_game() {
  int x = 0;
  int y = 0;
  PAINTSTRUCT     ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);

  SelectObject(memDC, buffer);
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, _game_background);
  DrawBitmap(memDC, 0, 0, 1200, 100, _top, SRCCOPY);

  for (x = 0; x < 40; x++) {
    for (y = 0; y < 20; y++) {
      switch (game->level()->at(x, y)) {
      case 1:
        {
          DrawBitmap(
                     memDC,
                     x * BLOCK_WIDTH,
                     TOP_OFFSET + y * BLOCK_HEIGHT,
                     BLOCK_WIDTH,
                     BLOCK_HEIGHT,
                     game->is_frozen() ? _block_frozen: _block,
                     SRCCOPY);
        }
        break;
      case 2:
        {
          DrawBitmap(
                     memDC,
                     x * BLOCK_WIDTH,
                     TOP_OFFSET + y * BLOCK_HEIGHT,
                     BLOCK_WIDTH,
                     BLOCK_HEIGHT,
                     _square[game->counter() % 4],
                     SRCCOPY);
        }
        break;
      case 5:
        {
          DrawBitmap(
                     memDC,
                     x * BLOCK_WIDTH,
                     TOP_OFFSET + y * BLOCK_HEIGHT,
                     BLOCK_WIDTH,
                     BLOCK_HEIGHT,
                     _freeze[game->counter() % 4],
                     SRCCOPY);
        }
        break;
      case 6:
        {
          DrawBitmap(
                     memDC,
                     x * BLOCK_WIDTH,
                     TOP_OFFSET + y * BLOCK_HEIGHT,
                     BLOCK_WIDTH,
                     BLOCK_HEIGHT,
                     _diamond[game->counter() % 4],
                     SRCCOPY);
        }
        break;
      case 7:
        {
          DrawBitmap(
                     memDC,
                     x * BLOCK_WIDTH,
                     TOP_OFFSET + y * BLOCK_HEIGHT,
                     BLOCK_WIDTH,
                     BLOCK_HEIGHT,
                     _fireball[game->counter() % 4],
                     SRCCOPY);
        }
        break;
      }
    }
  }
  for (Sword *s: game->swords) {
    DrawBitmapT(
               memDC,
               s->x() * BLOCK_WIDTH,
               TOP_OFFSET_MONSTER + s->y() * BLOCK_HEIGHT,
               BLOCK_WIDTH,
               BLOCK_HEIGHT,
               _swords[0],
               RGB(35, 35, 35));
  }
  if (game->snake) {
    unsigned int sb = game->snake->blocks.size();
    HBITMAP *pipes = _pipes_normal;
    HBITMAP *heads = _heads_normal;
    if (game->is_frozen()) {
      pipes = _pipes_frozen;
      heads = _heads_frozen;
    } else if (game->is_collided()) {
      if (game->collision_counter() %2 == 1) {
        pipes = _pipes_inverted;
        heads = _heads_inverted;
      }
    }
    for (unsigned int sc = 0; sc < sb; sc++) {
      SnakeBlock *current = game->snake->blocks[sc];
      HBITMAP e = pipes[1];
      try {
        SnakeBlock *prev = game->snake->blocks.at(sc-1);
        SnakeBlock *next = game->snake->blocks.at(sc+1);
        e = pipes[get_orientation(prev, current, next)-1];
      } catch (const std::out_of_range& oore) {
        if (sc == 0) {
          e = pipes[1];
        } else if (current->move() == MOVE_BOTTOM) {
          e = heads[1];
        } else if (current->move() == MOVE_TOP) {
          e = heads[3];
        } else if (current->move() == MOVE_RIGHT) {
          e = heads[0];
        } else if (current->move() == MOVE_LEFT) {
          e = heads[2];
        }
      }
      DrawBitmap(
                 memDC,
                 current->x() * BLOCK_WIDTH,
                 current->y() * BLOCK_HEIGHT + TOP_OFFSET,
                 BLOCK_WIDTH,
                 BLOCK_HEIGHT,
                 e,
                 SRCCOPY);
    }
  }

  for (Killer *ki: game->killers) {
    HBITMAP hb;
    if (ki->direction() == MD_EAST
        ) {
      hb = _killers_left[game->counter() %2];
    } else {
      hb = _killers_right[game->counter() %2];
    }
    DrawBitmapT(
               memDC,
               ki->real_x(),
               TOP_OFFSET_MONSTER + ki->real_y(),
               ki->w(),
               ki->h(),
               hb,
               RGB(35, 35, 35));
  }
  std::vector<Monster *>::iterator i;
  if (game->monsters.size() > 0) {
    for (
         i = game->monsters.begin();
         i != game->monsters.end();
         i++) {
      Monster *m = *i;
      if (game->is_frozen()) {
        DrawBitmapT(
                    memDC,
                 m->real_x(),
                    m->real_y() + TOP_OFFSET_MONSTER,
                    m->w(),
                    m->h(),
                    _creature[5],
                    RGB(35, 35, 35));
      } else {
        DrawBitmapT(
                    memDC,
                    m->real_x(),
                    m->real_y() + TOP_OFFSET_MONSTER,
                    m->w(),
                    m->h(),
                    _creature[m->index()],
                    RGB(35, 35, 35));
      }
    }
  }

  SelectObject(memDC, (HGDIOBJ)_font_medium);
  SetBkMode(memDC, TRANSPARENT);
  r = {10, SCREEN_HEIGHT-30, SCREEN_WIDTH-100, SCREEN_HEIGHT};
  SetTextColor(memDC, RGB(184, 184, 184));
  std::wstringstream sstr;
  if (game->lang() == 0) {
    sstr << L"POZIOM #" << game->level_index()+1 << L" ";
    for (unsigned int i = 0; i < game->lives(); i++) {
      sstr << L"❤";
    }
    if (!game->is_unlimited()) {
      sstr << L" CZAS: ";
      sstr << tzl(game->counter(), 3);
    }
    sstr << L" WYNIK: ";
    sstr << tzl(game->score(), 4);
    if (game->is_frozen()) {
      sstr << " ";
      sstr << tzl(game->freeze_counter(), 2);
      if (game->freeze_counter() %2 == 0) {
        sstr << ".";
      }
    }
  } else if (game->lang() == 1) {
    sstr << L"LEVEL #" << game->level_index()+1 << L" ";
    for (unsigned int i = 0; i < game->lives(); i++) {
      sstr << L"❤";
    }
    if (!game->is_unlimited()) {
      sstr << L" TIME: ";
      sstr << tzl(game->counter(), 3);
    }
    sstr << L" SCORE: ";
    sstr << tzl(game->score(), 4);
    if (game->is_frozen()) {
      sstr << " ";
      sstr << tzl(game->freeze_counter(), 2);
      if (game->freeze_counter() %2 == 0) {
        sstr << ".";
      }
    }
  }

  std::wstring wstr = sstr.str();
  DrawText(
           memDC,
           wstr.c_str(),
           -1,
           &r,
           DT_LEFT|DT_VCENTER|DT_SINGLELINE);
  // Swords consumed:
  // TODO
  // Paused:
  SelectObject(memDC, (HGDIOBJ)_font_big);
  if (game->is_paused()) {
    RECT r = {150, 200, 1050, 450};
    FillRect(memDC, &r, _game_fill);
    SelectObject(memDC, _game_frame);
    Rectangle(memDC, 150, 200, 1050, 450);
    SetTextColor(memDC, RGB(136, 0, 0));
    r = {150, 240, 1000, 325};
    if (game->lang() == 0) {
      DrawText(memDC,
               L" GRA WSTRZYMANA",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(memDC,
               L" GAME PAUSED",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
    r = {150, 325, 1050, 420};
    if (game->lang() == 0) {
      DrawText(memDC,
               L"NACISNIJ SPACJE BY KONTYNUOWAC",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(memDC,
               L"PRESS SPACE TO CONTINUE",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  if (game->is_over()) {
    RECT r = {150, 200, 1050, 450};
    FillRect(memDC, &r, _game_fill);
    SelectObject(memDC, _game_frame);
    Rectangle(memDC, 150, 200, 1050, 450);
    SetTextColor(memDC, RGB(136, 0, 0));
    r = {150, 240, 1000, 325};
    if (game->lang() == 0) {
      DrawText(memDC,
               L"KONIEC GRY!",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(memDC,
               L"GAME OVER!",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
    r = {150, 325, 1050, 420};
    if (game->lang() == 0) {
      DrawText(memDC,
               L"NACISNIJ Q ABY ZAKONCZYC",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(memDC,
               L"PRESS Q TO CONTINUE",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  if (game->is_initialized()) {
    RECT r = {150, 200, 1050, 450};
    FillRect(memDC, &r, _game_fill);
    SelectObject(memDC, _game_frame);
    Rectangle(memDC, 150, 200, 1050, 450);
    SetTextColor(memDC, RGB(136, 0, 0));
    r = {150, 240, 1000, 325};
    std::wstringstream sstf;
    if (game->lang() == 0) {
      sstf << L"WITAJ NA POZIOMIE #" << game->level_index()+1;
    } else if (game->lang() == 1) {
      sstf << L"WELCOME TO LEVEL #" << game->level_index()+1;
    }
    DrawText(memDC,
             sstf.str().c_str(),
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    r = {150, 325, 1050, 420};
    if (game->lang() == 0) {
      DrawText(memDC,
               L"NACISNIJ SPACJE BY ROZPOCZAC",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(memDC,
               L"PRESS SPACE TO START",
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  if (game->is_unlimited()) {
    if (game->swords_consumed() > 0) {
      sstr.str(L"");
      sstr << tzl(game->swords_consumed(), 3);
      RECT r = {SCREEN_WIDTH-120,
        SCREEN_HEIGHT-35,
        SCREEN_WIDTH-35,
        SCREEN_HEIGHT};
      SetTextColor(memDC, RGB(184, 184, 184));
      DrawText(memDC,
               sstr.str().c_str(),
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
      DrawBitmapT(
                  memDC,
                  SCREEN_WIDTH-30,
                  SCREEN_HEIGHT-31,
                  BLOCK_WIDTH,
                  BLOCK_HEIGHT,
                  _swords[0],
                  RGB(35, 35, 35));
    }
  }

  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_about() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);

  SelectObject(memDC, buffer);
  SelectObject(memDC, (HGDIOBJ)_font_medium);
  SetBkMode(memDC, TRANSPARENT);
  HBRUSH tlo = CreateSolidBrush(RGB(124, 112, 218));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH tlo2 = CreateSolidBrush(RGB(62, 49, 162));
  r = {50, 50, SCREEN_WIDTH-50, SCREEN_HEIGHT-100};
  FillRect(memDC, &r, tlo2);
  r = {50, 50, SCREEN_WIDTH-50, 100};
  SetTextColor(memDC, RGB(124, 112, 218));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             about_title_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else if (game->lang() == 1) {
    DrawText(
             memDC,
             about_title_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  for (int i = 0; i < 6; i++) {
    r = {50, 140 + i * 70, SCREEN_WIDTH-50, 210 + i * 70};
    if (game->lang() == 0) {
      DrawText(
               memDC,
               about_msg_pl[i],
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(
               memDC,
               about_msg_en[i],
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  SelectObject(memDC, (HGDIOBJ)_font_small);
  SetTextColor(memDC, RGB(62, 49, 162));
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  if (game->lang() == 0) {
    DrawText(
             memDC,
             ctrl_line_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else {
    DrawText(
             memDC,
             ctrl_line_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }

  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_menu() {
  PAINTSTRUCT     ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);

  SelectObject(memDC, buffer);

  HBRUSH tlo = CreateSolidBrush(RGB(35, 35, 35));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH przyciskN = CreateSolidBrush(RGB(151, 151, 151));
  HBRUSH przyciskA = CreateSolidBrush(RGB(15, 68, 128));
  HPEN ramkaN = CreatePen(PS_SOLID, 2, RGB(35, 35, 35));
  HPEN ramkaA = CreatePen(PS_SOLID, 2, RGB(170, 193, 60));
  SelectObject(memDC, (HGDIOBJ)_font_big);
  SetTextColor(memDC, RGB(170, 193, 60));
  SetBkMode(memDC, TRANSPARENT);
  RECT re = {240, 30, 960, 70};
  SetTextColor(memDC, RGB(151, 151, 151));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             menu_title_pl,
             -1,
             &re,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else if (game->lang() == 1) {
    DrawText(
             memDC,
             menu_title_en,
             -1,
             &re,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  for (unsigned int i = 0; i < 6; i++) {
    if (game->menu_pos() == i) {
      SetTextColor(memDC, RGB(170, 193, 60));
      SelectObject(memDC, przyciskA);
      SelectObject(memDC, ramkaA);
    } else {
      SetTextColor(memDC, RGB(35, 35, 35));
      SelectObject(memDC, przyciskN);
      SelectObject(memDC, ramkaN);
    }
    LONG y = 100 * (i+1);
    Rectangle(memDC, 300, y, 900, y+80);
    RECT re = {300, y, 900, y+80};
    if (game->lang() == 0) {
      DrawText(
               memDC,
               menu_options_pl[i],
             -1,
               &re,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(
               memDC,
               menu_options_en[i],
             -1,
               &re,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  DrawBitmapT(
              memDC,
              SCREEN_WIDTH-80,
              SCREEN_HEIGHT-24,
              36,
              20,
              _flags[0],
              RGB(35, 35, 35));
  DrawBitmapT(
              memDC,
              SCREEN_WIDTH-40,
              SCREEN_HEIGHT-24,
              36,
              20,
              _flags[1],
              RGB(35, 35, 35));
  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_options() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);

  SelectObject(memDC, buffer);

  HBRUSH tlo = CreateSolidBrush(RGB(35, 35, 35));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH przyciskN = CreateSolidBrush(RGB(151, 151, 151));
  HBRUSH przyciskA = CreateSolidBrush(RGB(15, 68, 128));
  HPEN ramkaN = CreatePen(PS_SOLID, 2, RGB(35, 35, 35));
  HPEN ramkaA = CreatePen(PS_SOLID, 2, RGB(170, 193, 60));
  SelectObject(memDC, (HGDIOBJ)_font_big);
  SetTextColor(memDC, RGB(170, 193, 60));
  SetBkMode(memDC, TRANSPARENT);
  RECT re = {300, 30, 900, 70};
  SetTextColor(memDC, RGB(151, 151, 151));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             options_title_pl,
             -1,
             &re,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else if (game->lang() == 1) {
    DrawText(
             memDC,
             options_title_en,
             -1,
             &re,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  for (unsigned int i = 0; i < 4; i++) {
    if (game->mode_menu() == i) {
      SetTextColor(memDC, RGB(170, 193, 60));
      SelectObject(memDC, przyciskA);
      SelectObject(memDC, ramkaA);
    } else {
      SetTextColor(memDC, RGB(35, 35, 35));
      SelectObject(memDC, przyciskN);
      SelectObject(memDC, ramkaN);
    }
    LONG y = 120 * (i+1);
    Rectangle(memDC, 300, y, 900, y+80);
    RECT re = {300, y, 900, y+80};
    if (game->lang() == 0) {
      DrawText(
               memDC,
               options_msg_pl[i],
               -1,
               &re,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (game->lang() == 1) {
      DrawText(
               memDC,
               options_msg_en[i],
               -1,
               &re,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  SelectObject(memDC, (HGDIOBJ)_font_small);
  SetTextColor(memDC, RGB(151, 151, 151));
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  if (game->lang() == 0) {
    DrawText(
             memDC,
             ctrl_line_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else {
    DrawText(
             memDC,
             ctrl_line_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_scores() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);

  SelectObject(memDC, buffer);
  SelectObject(memDC, (HGDIOBJ)_font_medium);
  SetBkMode(memDC, TRANSPARENT);
  HBRUSH tlo = CreateSolidBrush(RGB(124, 112, 218));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH tlo2 = CreateSolidBrush(RGB(62, 49, 162));
  r = {50, 50, SCREEN_WIDTH-50, SCREEN_HEIGHT-100};
  FillRect(memDC, &r, tlo2);
  r = {50, 50, SCREEN_WIDTH-50, 100};
  SetTextColor(memDC, RGB(124, 112, 218));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             hiscores_title_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else if (game->lang() == 1) {
    DrawText(
             memDC,
             hiscores_title_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }

  unsigned int si = game->conf.scores.size();
  for (unsigned int i = 0; i < 15; i++) {
    r = {70, 100 + i * 35, SCREEN_WIDTH-50, 150 + i * 35};
    if (i >= si) {
      std::wstring wynik = tzl(i+1, 2) + L".  ----  ---";
      DrawText(
               memDC,
               wynik.c_str(),
               -1,
               &r,
               DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    } else {
      Score *s = game->conf.scores.at(i);
      std::wstring wynik = tzl(i+1, 2) +  \
        + L".  " + \
        tzl(s->score, 4) + \
        L"  "+ s->name.c_str();
      DrawText(
               memDC,
               wynik.c_str(),
               -1,
               &r,
               DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    }
  }
  SelectObject(memDC, (HGDIOBJ)_font_small);
  SetTextColor(memDC, RGB(62, 49, 162));
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  if (game->lang() == 0) {
    DrawText(
             memDC,
             ctrl_line_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else if (game->lang() == 1) {
    DrawText(
             memDC,
             ctrl_line_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_newscore() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);
  SelectObject(memDC, buffer);
  SelectObject(memDC, (HGDIOBJ)_font_medium);
  SetBkMode(memDC, TRANSPARENT);
  HBRUSH tlo = CreateSolidBrush(RGB(124, 112, 218));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH tlo2 = CreateSolidBrush(RGB(62, 49, 162));
  r = {50, 50, SCREEN_WIDTH-50, SCREEN_HEIGHT-100};
  FillRect(memDC, &r, tlo2);
  /* HERE */
  SetTextColor(memDC, RGB(124, 112, 218));
  r = {50, 50, SCREEN_WIDTH-50, 100};
  std::wstring player = game->player() + L"▊";
  std::wstring sc = newscore_msg_pl[2];
  std::wstringstream sstr;
  sstr << game->score();
  replace_str(sc, L"%SCORE%", sstr.str());
  DrawText(
           memDC,
           newscore_title_pl,
           -1,
           &r,
           DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  for (int i = 0; i < 8; i++) {
    r = {100, 110 + i * 50, SCREEN_WIDTH-100, 190 + i * 50};
    if (i == 2) {
      DrawText(
             memDC,
             sc.c_str(),
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else if (i == 7) {
      DrawText(
             memDC,
             player.c_str(),
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else {
      DrawText(
             memDC,
             newscore_msg_pl[i],
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  SetTextColor(memDC, RGB(62, 49, 162));
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  DrawText(
           memDC,
           ctrl_line_ns_pl,
           -1,
           &r,
           DT_CENTER|DT_VCENTER|DT_SINGLELINE);

  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}

void Arena::paint_help() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);
  SelectObject(memDC, buffer);
  SelectObject(memDC, (HGDIOBJ)_font_small);
  SetBkMode(memDC, TRANSPARENT);
  HBRUSH tlo = CreateSolidBrush(RGB(124, 112, 218));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH tlo2 = CreateSolidBrush(RGB(62, 49, 162));
  r = {50, 50, SCREEN_WIDTH-50, SCREEN_HEIGHT-100};
  FillRect(memDC, &r, tlo2);
  r = {50, 50, SCREEN_WIDTH-50, 100};
  SetTextColor(memDC, RGB(124, 112, 218));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             help_title_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else {
    DrawText(
             memDC,
             help_title_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  for (int i = 0; i < 11; i++) {
    r = {100, 110 + i * 45, SCREEN_WIDTH-50, 190 + i * 45};
    if (game->lang() == 0) {
      DrawText(
               memDC,
               help_msg_pl[i],
               -1,
               &r,
               DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    } else {
      DrawText(
               memDC,
               help_msg_en[i],
               -1,
               &r,
               DT_LEFT|DT_VCENTER|DT_SINGLELINE);
    }
  }
  SetTextColor(memDC, RGB(62, 49, 162));
  SelectObject(memDC, (HGDIOBJ)_font_small);
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  if (game->lang() == 0) {
    DrawText(
             memDC,
             ctrl_line_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else {
    DrawText(
             memDC,
             ctrl_line_en,
             -1,
               &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteDC(memDC);
  EndPaint(okno, &ps);
}


LRESULT CALLBACK MainWndProc(
                             HWND hWnd,
                             UINT msg,
                             WPARAM wParam,
                             LPARAM lParam) {
  switch (msg) {
  case WM_TIMER:
    switch(wParam)
      {
      case TIMER_TICK:
        {
          game->event_tick();
        }
        break;
      case TIMER_COUNTER:
        {
          game->event_counter();
        }
        break;
      case TIMER_COLLISION:
        {
          game->event_collision();
        }
        break;
      case TIMER_CONSUME:
        {
          game->event_consume();
        }
        break;
      case TIMER_FREEZE:
        {
          game->event_freeze();
        }
        break;
      default:
        break;
      }
    break;
  case WM_RBUTTONDOWN:
    {
      arena->mouse_pressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), BUTTON_RIGHT);
    }
    break;
  case WM_LBUTTONDOWN:
    {
      arena->mouse_pressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), BUTTON_LEFT);
    }
    break;
    //  case WM_LBUTTONUP:
    //  case WM_MOUSEMOVE:
    //    {
    // arena->mouse_move(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), BUTTON_LEFT);
    //}
    //break;
  case WM_KEYUP:
    {
      arena->keyup(virtkey(wParam));
    }
    break;
  case WM_KEYDOWN:
    {
      arena->keypress(virtkey(wParam));
    }
    break;
  case WM_CHAR:
    {
      if ((wParam >= 32) && (wParam <=126)) {
        unsigned char ch = (unsigned char)wParam;
        arena->processchar(ch);
      }
    }
    break;
  case WM_CREATE:
    {
      arena = new Arena();
      game = new Game();
    }
  case WM_ERASEBKGND:
    return 1;
    break;
  case WM_PAINT:
    {
      game->paint();
      break;
    }
  case WM_DESTROY:
    {
      arena->terminate();
      return 0;
    }
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL RegisterMainWindowClass() {
  WNDCLASSEX wc;
  wc.cbSize = sizeof(wc);
  wc.style = 0;
  wc.lpfnWndProc = &MainWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = instancja;
  wc.hIcon = (HICON)LoadImage(
                              instancja,
                              MAKEINTRESOURCE(IDI_APPICON),
                              IMAGE_ICON,
                              0,
                              0,
                              LR_DEFAULTSIZE | LR_DEFAULTCOLOR | LR_SHARED);
  wc.hCursor = (HCURSOR)LoadImage(
                                  NULL,
                                  IDC_ARROW,
                                  IMAGE_CURSOR,
                                  0,
                                  0,
                                  LR_SHARED);
  wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
  wc.lpszMenuName = 0;
  wc.lpszClassName = MainWndClass;
  wc.hIconSm = (HICON)LoadImage(
                                instancja,
                                MAKEINTRESOURCE(IDI_APPICON),
                                IMAGE_ICON,
                                16,
                                16,
                                LR_DEFAULTCOLOR);

  return (RegisterClassEx(&wc)) ? TRUE : FALSE;
}

HWND CreateMainWindow() {
  AdjustWindowRect(&prostokat, WS_CAPTION | WS_SYSMENU, FALSE);
  HWND hWnd = CreateWindowEx(
                             0,
                             MainWndClass,
                             MainWndClass,
                             WS_CAPTION | WS_SYSMENU,
                             prostokat.left,
                             prostokat.top,
                             prostokat.right-prostokat.left,
                             prostokat.bottom-prostokat.top,
                             NULL,
                             NULL,
                             instancja,
                             NULL);
  return hWnd;
}

void Arena::paint_gameover() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(okno, &ps);
  HDC memDC = CreateCompatibleDC(hdc);
  HBITMAP buffer = CreateCompatibleBitmap(
                                          hdc,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT);
  SelectObject(memDC, buffer);
  SelectObject(memDC, (HGDIOBJ)_font_big);
  SetBkMode(memDC, TRANSPARENT);
  HBRUSH tlo = CreateSolidBrush(RGB(124, 112, 218));
  RECT r = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  FillRect(memDC, &r, tlo);
  HBRUSH tlo2 = CreateSolidBrush(RGB(62, 49, 162));
  r = {50, 50, SCREEN_WIDTH-50, SCREEN_HEIGHT-100};
  FillRect(memDC, &r, tlo2);
  r = {50, 50, SCREEN_WIDTH-50, 100};
  SetTextColor(memDC, RGB(124, 112, 218));
  if (game->lang() == 0) {
    DrawText(
             memDC,
             gameover_title_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else {
    DrawText(
             memDC,
             gameover_title_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  for (int i = 0; i < 3; i++) {
    r = {50, 140 + i * 40, SCREEN_WIDTH-50, 180 + i * 40};
    if (game->lang() == 0) {
      DrawText(
               memDC,
               gameover_msg_pl[i],
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    } else {
      DrawText(
               memDC,
               gameover_msg_en[i],
               -1,
               &r,
               DT_CENTER|DT_VCENTER|DT_SINGLELINE);
    }
  }
  DrawBitmap(
             memDC,
             SCREEN_WIDTH/2 - 100,
             350,
             200,
             250,
             _cup,
             SRCCOPY);
  SelectObject(memDC, (HGDIOBJ)_font_small);
  SetTextColor(memDC, RGB(62, 49, 162));
  r = {50, SCREEN_HEIGHT-100, SCREEN_WIDTH-50, SCREEN_HEIGHT};
  if (game->lang() == 0) {
    DrawText(
             memDC,
             ctrl_line_pl,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  } else {
    DrawText(
             memDC,
             ctrl_line_en,
             -1,
             &r,
             DT_CENTER|DT_VCENTER|DT_SINGLELINE);
  }
  /* HERE */
  BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, memDC, 0, 0, SRCCOPY);
  DeleteObject(buffer);
  DeleteObject(tlo2);
  DeleteObject(tlo);
  DeleteDC(memDC);
  EndPaint(okno, &ps);

}

void Arena::refresh() {
  InvalidateRect(okno, &plansza, TRUE);
}

void Arena::keypress(Key k) {
  game->keypressed(k);
}

void Arena::start_timer(unsigned int timer, unsigned int timeout) {
  SetTimer(
           okno,
           timer,
           timeout,
           (TIMERPROC)NULL);
}

void Arena::stop_timer(unsigned int timer) {
  KillTimer(
            okno,
            timer);
}

void Arena::terminate() {
  game->save();
  delete game;
  delete arena;
  PostQuitMessage(0);
}

void Arena::processchar(unsigned char ch) {
  game->processchar(ch);
}

void Arena::keyup(Key k) {
  game->keyup(k);
}

void Arena::mouse_pressed(int x, int y, MouseButton b) {
  game->mouse_pressed(x, y, b);
}

// void Arena::mouse_center() {
//   POINT pt;
//   pt.x = SCREEN_WIDTH/2;
//   pt.y = SCREEN_HEIGHT/2;
//   ClientToScreen(okno, &pt);
//   SetCursorPos(pt.x, pt.y);
//   game->mouse_setpos(pt.x, pt.y);
// }

void Arena::mouse_released(int x, int y, MouseButton b) {
  game->mouse_released(x, y, b);
}
