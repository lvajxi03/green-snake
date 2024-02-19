#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <windows.h>
#include <vector>
#include <string>

#include "primi.h"

#define MAX_LEVELS 6

extern unsigned int level_1[20][40];
extern unsigned int level_2[20][40];
extern unsigned int level_3[20][40];
extern unsigned int level_4[20][40];
extern unsigned int level_5[20][40];
extern unsigned int level_6[20][40];

extern std::wstring game_titles[6];

class Level {
public:
	Level(unsigned char index);
	unsigned int at(unsigned int x, unsigned int y);
	void clear(unsigned int x, unsigned int y);
	Point *spot();
	std::wstring title();
	std::vector<Point *> entry_points;
	unsigned int points();
	~Level();
private:
	unsigned int level[20][40];
	std::wstring _title;
	Point *_spot;
	unsigned int _points;
};

#endif /* __LEVEL_H__ */
