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
	int					getTimeExploding();

	void				setPower(int power);
	void				setRec(MRectangle rec);
	void				setTimeBoomExploding(int timeExploding);
	void				setIndexBoomExploding(int indexExploding);

private:
	MRectangle					b_rec;
	int							b_time_boom_exploding;
	std::string					b_pathTexture[NUM_PATH_TEXTURE_BOOM];
	int							b_index_boom_exploding;
	int							b_power;
};
