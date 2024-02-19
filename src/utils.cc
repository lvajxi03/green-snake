#include "utils.h"

#include <sstream>

Key virtkey(UINT key) {
  switch (key) {
  case VK_LEFT:
    return KEY_LEFT;
    break;
  case VK_RIGHT:
    return KEY_RIGHT;
    break;
  case VK_DOWN:
    return KEY_BOTTOM;
    break;
  case VK_UP:
    return KEY_TOP;
    break;
  case VK_RETURN:
    return KEY_ENTER;
    break;
  case VK_BACK:
    return KEY_BACKSPACE;
    break;
  case VK_ESCAPE:
    return KEY_ESCAPE;
    break;
  case VK_SPACE:
    return KEY_SPACE;
    break;
  case 0x51:
    return KEY_Q;
    break;
  default:
    return KEY_NONE;
    break;
  }
}

std::wstring tzl(const int value, const unsigned int precision) {
  std::wstringstream oss;
  oss << std::setw(precision) << std::setfill(L'0') << value;
  return oss.str();
}

bool DrawBitmap (
                 HDC hDC,
                 int x,
                 int y,
                 int width,
                 int height,
                 HBITMAP hBitmap,
                 DWORD dwROP) {
  bool result = false;
  if (hDC && hBitmap) {
    BITMAP Bitmap;
    HDC hDCBits = CreateCompatibleDC(hDC);
    GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
    SelectObject(hDCBits, hBitmap);
    result = StretchBlt(
                        hDC,
                        x,
                        y,
                        width,
                        height,
                        hDCBits,
                        0,
                        0,
                        Bitmap.bmWidth,
                        Bitmap.bmHeight,
                        dwROP);
    DeleteDC(hDCBits);
  }
  return result;
}

bool DrawBitmapT (
                 HDC hDC,
                 int x,
                 int y,
                 int width,
                 int height,
                 HBITMAP hBitmap,
                 unsigned int tr) {
  bool result = false;
  if (hDC && hBitmap) {
    BITMAP Bitmap;
    HDC hDCBits = CreateCompatibleDC(hDC);
    GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
    SelectObject(hDCBits, hBitmap);
    result = TransparentBlt(
                            hDC,
                            x,
                            y,
                            width,
                            height,
                            hDCBits,
                            0,
                            0,
                            Bitmap.bmWidth,
                            Bitmap.bmHeight,
                            tr);
    DeleteDC(hDCBits);
  }
  return result;
}

Orientation get_orientation(
                            SnakeBlock *prev,
                            SnakeBlock *cur,
                            SnakeBlock *next) {
  if (prev->orientation() == ORI_NE) {
    if (next->move() == MOVE_BOTTOM) {
      cur->set_orientation(ORI_SW);
    } else if (next->move() == MOVE_LEFT) {
      cur->set_orientation(ORI_SW);
    } else if (next->move() == MOVE_RIGHT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_TOP) {
      cur->set_orientation(ORI_VERTICAL);
    }
  } else if (prev->orientation() == ORI_NW) {
    if (next->move() == MOVE_BOTTOM) {
      cur->set_orientation(ORI_SE);
    } else if (next->move() == MOVE_LEFT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_RIGHT) {
      cur->set_orientation(ORI_SE);
    } else if (next->move() == MOVE_TOP) {
      cur->set_orientation(ORI_VERTICAL);
    }
  } else if (prev->orientation() == ORI_SW) {
    if (next->move() == MOVE_BOTTOM) {
      cur->set_orientation(ORI_VERTICAL);
    } else if (next->move() == MOVE_LEFT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_RIGHT) {
      cur->set_orientation(ORI_NE);
    } else if (next->move() == MOVE_TOP) {
      cur->set_orientation(ORI_NE);
    }
  } else if (prev->orientation() == ORI_SE) {
    if (next->move() == MOVE_BOTTOM) {
      cur->set_orientation(ORI_VERTICAL);
    } else if (next->move() == MOVE_LEFT) {
      cur->set_orientation(ORI_NW);
    } else if (next->move() == MOVE_RIGHT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_TOP) {
      cur->set_orientation(ORI_NW);
    }
  } else if (prev->move() == MOVE_RIGHT) {
    if (next->move() == MOVE_RIGHT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_TOP) {
      if (prev->orientation() == ORI_NW) {
        cur->set_orientation(ORI_VERTICAL);
      } else {
        cur->set_orientation(ORI_NW);
      }
    } else if (next->move() == MOVE_BOTTOM) {
      if (prev->orientation() == ORI_SW) {
        cur->set_orientation(ORI_VERTICAL);
      } else {
        cur->set_orientation(ORI_SW);
      }
    }
  } else if (prev->move() == MOVE_LEFT) {
    if (next->move() == MOVE_LEFT) {
      cur->set_orientation(ORI_HORIZONTAL);
    } else if (next->move() == MOVE_TOP) {
      if (prev->orientation() == ORI_NE) {
        cur->set_orientation(ORI_VERTICAL);
      } else {
        cur->set_orientation(ORI_NE);
      }
    } else if (next->move() == MOVE_BOTTOM) {
      if (prev->orientation() == ORI_SE) {
        cur->set_orientation(ORI_VERTICAL);
      } else {
        cur->set_orientation(ORI_SE);
      }
    }
  } else if (prev->move() == MOVE_BOTTOM) {
    if (next->move() == MOVE_BOTTOM) {
      cur->set_orientation(ORI_VERTICAL);
    } else if (next->move() == MOVE_LEFT) {
      if (prev->orientation() == ORI_NW) {
        cur->set_orientation(ORI_HORIZONTAL);
      } else {
        cur->set_orientation(ORI_NW);
      }
    } else if (next->move() == MOVE_RIGHT) {
      if (prev->orientation() == ORI_NE) {
        cur->set_orientation(ORI_HORIZONTAL);
      } else {
        cur->set_orientation(ORI_NE);
      }
    }
  } else if (prev->move() == MOVE_TOP) {
    if (next->move() == MOVE_TOP) {
      cur->set_orientation(ORI_VERTICAL);
    } else if (next->move() == MOVE_RIGHT) {
      if (prev->orientation() == ORI_SE) {
        cur->set_orientation(ORI_HORIZONTAL);
      } else {
        cur->set_orientation(ORI_SE);
      }
    } else if (next->move() == MOVE_LEFT) {
      if (prev->orientation() == ORI_SW) {
        cur->set_orientation(ORI_HORIZONTAL);
      } else {
        cur->set_orientation(ORI_SW);
      }
    }
  }
  return cur->orientation();
}

void replace_str(
                 std::wstring& str,
                 const std::wstring& from,
                 const std::wstring& to) {
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}
