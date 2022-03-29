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

int Boom::getTimeExploding()
{
	return b_time_boom_exploding;
}

void Boom::setPower(int power)
{
	b_power = power;
}

void Boom::setRec(MRectangle rec)
{
	b_rec = rec;
}

void Boom::setTimeBoomExploding(int timeExploding)
{
	b_time_boom_exploding = timeExploding;
}

void Boom::setIndexBoomExploding(int indexExploding)
{
	b_index_boom_exploding = indexExploding;
}

MRectangle Boom::calculateLocationGenerate(MRectangle playerRec)
{
	//create new Rec for boom
	MRectangle newBoomRec;
	//add value width , lenght
	newBoomRec.setRecWidth(Globals::item_size);
	newBoomRec.setRecLength(Globals::item_size);

	//get the index xy in map where player is standing
	int indexX = playerRec.getRecX() / Globals::item_size;
	int indexY = playerRec.getRecY() / Globals::item_size;

	//get the location xy in map where player is standing
	newBoomRec.setRecXY(
		indexX * Globals::item_size + Globals::item_size / 2
		, indexY * Globals::item_size + Globals::item_size / 2);

	return newBoomRec;
}
