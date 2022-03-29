#include "Boom.h"

Boom::Boom() : b_power(1) , b_index_boom_exploding(0) , b_time_boom_exploding(0)
{
	b_pathTexture[0] = "boom1.tga";
	b_pathTexture[2] = "boom2.tga";
	b_pathTexture[3] = "boom3.tga";
	b_pathTexture[4] = "boom4.tga";
	b_pathTexture[5] = "boom5.tga";
	b_pathTexture[6] = "boom6.tga";
	b_pathTexture[7] = "boom7.tga";
}

Boom::~Boom()
{
}

std::string Boom::getPathTexture(int index)
{
	return b_pathTexture[index];
}

MRectangle Boom::getRect()
{
	return b_rec;
}

int Boom::getPower()
{
	return b_power;
}

int Boom::getIndexBoomExploding()
{
	return b_index_boom_exploding;
}
