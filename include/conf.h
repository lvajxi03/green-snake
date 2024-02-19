#ifndef __CONF_H__
#define __CONF_H__

#include <windows.h>

#include <string>
#include <vector>
#include <sstream>

#include "dtypes.h"
#include "globals.h"
#include "primi.h"

class Configuration {
public:
  Configuration();
  ~Configuration();
  unsigned int min_score();
  unsigned char mode();
  unsigned char lang();
  void set_mode(unsigned char mode);
  void set_lang(unsigned char lang);
  void save();
  void append_score(const std::wstring& name, unsigned int score);
  std::vector<Score *> scores;
private:
  void _recalc_scores();
  unsigned char _mode;
  unsigned char _lang;
  unsigned int _min_score;
};

#endif /* __CONF_H__ */
