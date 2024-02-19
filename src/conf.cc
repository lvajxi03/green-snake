#include "conf.h"

#include <algorithm>

static LPCWSTR _akey = L"Software\\printf.pl\\ZielonyWaz";

Configuration::Configuration() {
  _lang = 0;
  _min_score = 0;
  _mode = 0;
  long _modef = 0;
  HKEY key;
  DWORD atype;
  DWORD asize;
  if (RegOpenKeyEx(
                   HKEY_CURRENT_USER,
                   _akey,
                   0,
                   KEY_QUERY_VALUE,
                   &key) == ERROR_SUCCESS) {
    asize = 4;
    atype = REG_DWORD;
    long err = RegQueryValueEx(
                               key,
                               L"game-mode",
                               NULL,
                               &atype,
                               (LPBYTE)&_modef,
                               &asize);
    if (err == ERROR_SUCCESS) {
      _mode = (unsigned char)_modef;
      _mode = _mode < 0 ? 0 : _mode;
      _mode = _mode > 3 ? 3 : _mode;
    }
    long langf = 0;
    err = RegQueryValueEx(
                               key,
                               L"lang",
                               NULL,
                               &atype,
                               (LPBYTE)&langf,
                               &asize);
    if (err == ERROR_SUCCESS) {
      _lang = (unsigned char)langf;
      _lang = _lang < 0 ? 0 : _lang;
      _lang = _lang > 1 ? 1 : _lang;
    }
    long srs = 0;
    err = RegQueryValueEx(
                          key,
                          L"scores-size",
                          NULL,
                          &atype,
                          (LPBYTE)&srs,
                          &asize);
    if (err == ERROR_SUCCESS) {
      for (long i = 0; i < srs; i++) {
        TCHAR buffer[100];
        DWORD bsize = sizeof(buffer);
        std::wstringstream sstr;
        sstr << L"name-";
        sstr << i;
        err = RegQueryValueEx(
                              key,
                              sstr.str().c_str(),
                              0,
                              NULL,
                        (BYTE *)buffer,
                              &bsize);
        if (err == ERROR_SUCCESS) {
          sstr.str(L"");
          sstr << L"score-";
          sstr << i;
          long score = 0;
          long err = RegQueryValueEx(
                                     key,
                                     sstr.str().c_str(),
                                     NULL,
                                     &atype,
                                     (LPBYTE)&score,
                                     &asize);
          if (err == ERROR_SUCCESS) {
            append_score(buffer, score);
          }
        }
      }
    }
  }
  RegCloseKey(key);
}

Configuration::~Configuration() {
  for (Score *s: scores) {
    delete s;
  }
  scores.clear();
}

unsigned int Configuration::min_score() {
  return _min_score;
}

void Configuration::save() {
  HKEY key;
  DWORD asize = 4;
  LONG retval = RegCreateKeyEx(
                               HKEY_CURRENT_USER,
                               _akey,
                               0,
                               NULL,
                               REG_OPTION_NON_VOLATILE,
                               KEY_WRITE,
                               NULL,
                               &key,
                               NULL);
  if (retval == ERROR_SUCCESS) {
    unsigned long m = scores.size();
    unsigned long n = (unsigned long)_mode;
    unsigned long o = (unsigned long)_lang;
    RegSetValueEx(
                  key,
                  L"game-mode",
                  0,
                  REG_DWORD,
                  (const BYTE*)&n,
                  asize);
    RegSetValueEx(
                  key,
                  L"lang",
                  0,
                  REG_DWORD,
                  (const BYTE*)&o,
                  asize);
    RegSetValueEx(
                  key,
                  L"scores-size",
                  0,
                  REG_DWORD,
                  (const BYTE*)&m,
                  asize);
    for (unsigned char i = 0; i < m; i++) {
      Score *s = scores.at(i);
      if (s != NULL) {
        std::wstringstream sstr;
        sstr << L"name-";
        sstr << i;
        const wchar_t *f = s->name.c_str();
        RegSetValueEx(
                      key,
                      sstr.str().c_str(),
                      0,
                      REG_SZ,
                      (LPBYTE)f,
                      (s->name.size()+1) * (sizeof(wchar_t)));
        sstr.str(L"");
        sstr << L"score-";
        sstr << i;
        RegSetValueEx(
                      key,
                      sstr.str().c_str(),
                      0,
                      REG_DWORD,
                      (const BYTE*)&s->score,
                      sizeof(s->score));

      }
    }
  }
  RegCloseKey(key);
}

void Configuration::append_score(
                                 const std::wstring&  name,
                                 unsigned int score) {
  if (score > _min_score) {
    Score *s = new Score();
    s->name = name.c_str();
    s->score = score;
    scores.push_back(s);
    _recalc_scores();
  }
}

void Configuration::_recalc_scores() {
  std::sort(scores.begin(), scores.end(), score_compare);
  std::reverse(scores.begin(), scores.end());
  if (scores.size() > 15) {
    scores.resize(15);
  }
  if (scores.size() == 15) {
    Score *s = scores.back();
    _min_score = s->score;
  } else {
    _min_score = 0;
  }

}

unsigned char Configuration::mode() {
  return _mode;
}


unsigned char Configuration::lang() {
  return _lang;
}

void Configuration::set_mode(unsigned char mode) {
  _mode = mode;
}

void Configuration::set_lang(unsigned char lang) {
  _lang = lang;
}
