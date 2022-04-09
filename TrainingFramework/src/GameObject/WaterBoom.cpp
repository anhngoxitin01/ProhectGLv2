#include "WaterBoom.h"
	
WaterBoom::WaterBoom()
{
}

WaterBoom::WaterBoom(MRectangle rec, std::string pathTexture)
{
	wb_rec = rec;
	wb_pathTexture = pathTexture;
}

WaterBoom::~WaterBoom()
{
}

std::string WaterBoom::getTexture()
{
	return wb_pathTexture;
}

MRectangle WaterBoom::getRect()
{
	return wb_rec;
}

void WaterBoom::setTexture(std::string pathTexture)
{
	wb_pathTexture = pathTexture;
}

void WaterBoom::setRect(MRectangle newRec)
{
	wb_rec = newRec;
}
