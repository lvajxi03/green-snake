#ifndef __D_TYPES_H__
#define __D_TYPES_H__

#include <windows.h>

#include "dtypes.h"

class Arena;
class Game;

extern HINSTANCE instancja;
extern HWND okno;
extern RECT prostokat;

extern unsigned int f_menu_option;

extern GameBoard game_board;
extern GameState game_state;

extern Arena *arena;
extern Game *game;

#endif /* __D_TYPES_H__ */
