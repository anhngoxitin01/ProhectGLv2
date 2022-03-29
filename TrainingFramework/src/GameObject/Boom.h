#pragma once
#include"MRectangle.h"
#include<GameConfig.h>
#include<string>
#include<list>

class Boom {
public:
	Boom();
	~Boom();

	std::string			getPathTexture(int index);
	MRectangle			getRect();
	int					getPower();
	int					getIndexBoomExploding();

private:
	MRectangle					b_rec;
	int							b_time_boom_exploding;
	std::string					b_pathTexture[NUM_PATH_TEXTURE_BOOM];
	int							b_index_boom_exploding;
	int							b_power;
};
