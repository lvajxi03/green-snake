#include "loc.h"

LPCTSTR menu_title_pl = L"*** ZIELONY WAZ ***";
LPCTSTR menu_title_en = L"*** THE GREEN SNAKE ***";

LPCTSTR about_title_pl = L"*** O PROGRAMIE ***";
LPCTSTR about_title_en = L"*** ABOUT ***";

LPCTSTR ctrl_line_pl = L"(uzyj klawisza ESC lub Q aby opuscic ten ekran)";
LPCTSTR ctrl_line_en = L"(use ESC or Q key to leave this screen)";

LPCTSTR options_title_pl = L"*** OPCJE GRY ***";
LPCTSTR options_title_en = L"*** GAME OPTIONS ***";

LPCTSTR gameover_title_pl = L"*** KONIEC GRY! ***";
LPCTSTR gameover_title_en = L"*** GAME OVER! ***";

const wchar_t * menu_options_pl[6] = {
  L"NOWA GRA",
  L"OPCJE",
  L"TABELA REKORDOW",
  L"POMOC",
  L"O PROGRAMIE",
  L"KONIEC"
};
const wchar_t *menu_options_en[6] = {
  L"NEW GAME",
  L"OPTIONS",
  L"HIGH SCORES",
  L"HELP",
  L"ABOUT",
  L"QUIT"
};

const wchar_t *about_msg_pl[6] = {
  L"POMYSL WZIETY Z ORYGINALNEJ",
  L"*OIL\'S WELL*",
  L"(C) THOMAS J. MITCHELL, 1983",
  L"",
  L"NAPISANA JAKO CWICZENIE W Win32API",
  L"(Marcin Bielewicz, 2020)"
};

const wchar_t *about_msg_en[6] = {
  L"WORKING TRIBUTE TO ORIGINAL",
  L"*OIL\'S WELL*",
  L"BY THOMAS J. MITCHELL, 1993",
  L"",
  L"WRITTEN TO PRACTISE Win32API",
  L"(Marcin Bielewicz, 2020)"
};

const wchar_t *options_msg_pl[4] = {
  L"TRYB LATWY",
  L"TRYB NORMALNY",
  L"TRYB TRUDNY",
  L"BRAK LIMITU CZASU"
};

const wchar_t *options_msg_en[4] = {
  L"EASY MODE",
  L"NORMAL MODE",
  L"HARDCORE MODE",
  L"NO TIME LIMIT"
};

LPCTSTR help_title_pl = L"*** POMOC ***";
LPCTSTR help_title_en = L"*** HELP ***";

const wchar_t *help_msg_pl[11] = {
  L"* UZYJ KLAWISZY STRZALEK DO KONTROLI WEZA",
  L"* ORAZ BACKSPACE DO POWROTU",
  L"",
  L"* ZOLTE KWADRATY SA WARTE 1 PUNKT",
  L"* DIAMENTY I  MONETY SA WARTE 5 PUNKTOW",
  L"* NIEBIESKIE KULKI ZAMRAZAJA RUCH NA 20 SEKUND",
  L"",
  L"* POTWORY NIE MOGA DOTKNAC CIALA WEZA",
  L"* DUCH NIE MOZE DOTKNAC JEGO GLOWY",
  L"",
  L"  POWODZENIA! BEDZIE CI POTRZEBNE!"
};

const wchar_t *help_msg_en[11] = {
  L"* USE ARROW KEYS TO CONTROL THE SNAKE",
  L"* AND BACKSPACE FOR IMMEDIATE RETURN",
  L"",
  L"* YELLOW SQUARES ARE WORTH 1 POINT",
  L"* DIAMONDS AND COINS ARE WORTH 5 POINTS",
  L"* BLUE PILLS SLOW MONSTERS FOR 20 SECONDS",
  L"",
  L"* MONSTER SHOULD NOT HIT SNAKE BODY",
  L"* A GHOST SHOULD NOT HIT ITS HEAD",
  L"",
  L"  GOOD LUCK! YOU WILL NEED IT!"
};

LPCTSTR hiscores_title_pl = L"*** TABELA REKORDOW ***";
LPCTSTR hiscores_title_en = L"*** HIGH SCORES ***";

LPCTSTR ctrl_line_ns_pl = L"(uzyj liter, cyfr, klawisza Enter lub Esc)";
LPCTSTR ctrl_line_ns_en = L"(use letters, digits, Enter or Esc keys)";

LPCTSTR newscore_title_pl = L"*** NOWY REKORD ***";
LPCTSTR newscore_title_en = L"*** NEW HISCORE ***";

const wchar_t *newscore_msg_pl[8] = {
  L"GRATULACJE!",
  L"",
  L"TWOJ WYNIK (%SCORE%) ZOSTANIE UMIESZCZONY",
  L"NA TABLICY REKORDOW!",
  L"",
  L"WPROWADZ SWOJE IMIE:",
  L"",
  L"%PLAYER%▊"
};

const wchar_t *newscore_msg_en[8] = {
  L"CONGRATULATIONS!",
  L"YOUR SCORE (%SCORE%) WILL NOW BE PRESENT",
  L"ON THE SCORE TABLE!",
  L"",
  L"PLEASE ENTER YOUR NAME:",
  L"",
  L"%PLAYER%▊"
};

const wchar_t *gameover_msg_pl[3] = {
  L"GRATULACJE!",
  L"",
  L"GRA UKONCZONA!"
};

const wchar_t *gameover_msg_en[3] = {
  L"CONGRATULATIONS!",
  L"",
  L"YOU HAVE JUST COMPLETED THIS GAME!"
};
