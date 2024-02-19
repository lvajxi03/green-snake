#ifndef __DTYPES_H__
#define __DTYPES_H__

#include <string>

typedef enum _Key {
  KEY_NONE,
  KEY_LEFT,
  KEY_RIGHT,
  KEY_TOP,
  KEY_BOTTOM,
  KEY_ENTER,
  KEY_ESCAPE,
  KEY_BACKSPACE,
  KEY_SPACE,
  KEY_Q
} Key;

typedef enum _MouseButton {
  BUTTON_NONE,
  BUTTON_LEFT,
  BUTTON_RIGHT,
  BUTTON_MIDDLE,
  BUTTONSCROLL_UP,
  BUTTON_SCROLL_DOWN
} MouseButton;

typedef struct _MouseEvent {
  int x = -1;
  int y = -1;
  MouseButton button = BUTTON_NONE;
} MouseEvent;

typedef enum _Move {
  MOVE_RIGHT,
  MOVE_BOTTOM,
  MOVE_LEFT,
  MOVE_TOP
} Move;

typedef enum _MonsterDirection {
  MD_EAST,
  MD_WEST
} MonsterDirection;

typedef enum _Orientation {
  ORI_NONE = 0,
  ORI_HORIZONTAL = 1,
  ORI_VERTICAL = 2,
  ORI_NW = 3,
  ORI_SW = 4,
  ORI_NE = 5,
  ORI_SE = 6
} Orientation;

typedef enum _GameBoard {
  BOARD_UNKNOWN,
  BOARD_WELCOME,
  BOARD_MENU,
  BOARD_GAME,
  BOARD_OPTIONS,
  BOARD_PAUSE,
  BOARD_HISCORES,
  BOARD_NEWSCORE,
  BOARD_HELP,
  BOARD_ABOUT,
  BOARD_QUIT,
  BOARD_LANGPL, /* fake board */
  BOARD_LANGEN, /* fake board */
  BOARD_GAMEOVER
} GameBoard;

typedef enum _GameState {
  STATE_UNKNOWN,
  STATE_INITIALIZED,
  STATE_STARTED,
  STATE_PAUSED,
  STATE_COLLIDED,
  STATE_FROZEN,
  STATE_GAMEOVER
} GameState;

typedef enum _MenuOption {
  MENU_NEWGAME,
  MENU_OPTIONS,
  MENU_HISCORES,
  MENU_HELP,
  MENU_ABOUT,
  MENU_QUIT
} MenuOption;

#endif /* __DTYPES_H__ */
