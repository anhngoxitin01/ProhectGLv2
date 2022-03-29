#pragma once
#include "GameConfig.h"
#include "MRectangle.h"

class WaterBoom 
{
public:
	WaterBoom();
	WaterBoom(MRectangle rec, std::string pathTexture);
	~WaterBoom();

	std::string		getTexture();
	MRectangle		getRect();

	void			setTexture(std::string pathTexture);
	void			setRect(MRectangle newRec);
	

private:
	std::string		wb_pathTexture;
	MRectangle		wb_rec;

};