#ifndef __UTILS_H__
#define __UTILS_H__

#include "dtypes.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <windows.h>
#include "primi.h"
#include "monster.h"

Key virtkey(UINT key);

std::wstring tzl(
                 const int value,
                 const unsigned int precision);

bool DrawBitmap(
                HDC hDC,
                int x,
                int y,
                int width,
                int height,
                HBITMAP hBitmap,
                DWORD dwROP);

bool DrawBitmapT(
                HDC hDC,
                int x,
                int y,
                int width,
                int height,
                HBITMAP hBitmap,
                unsigned int tr);

Orientation get_orientation(
                            SnakeBlock *prev,
                            SnakeBlock *cur,
                            SnakeBlock *next);

void replace_str(
                 std::wstring& str,
                 const std::wstring& from,
                 const std::wstring& to);

#endif /* __UTILS_H__ */
