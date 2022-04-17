#pragma once
#include"GameConfig.h"

class MRectangle
{
public:
	MRectangle();
	MRectangle(float x, float y, int height, int width);
	~MRectangle();

	int isInteract(MRectangle anotherRec);
	int caculDistanceToAnotherRecWithDirection(MRectangle anotherRec, int direction);

	void setRecXY(float x , float y);
	void setRecHeight(int height);
	void setRecWidth(int width);

	float getRecX();
	float getRecY();
	int getRecHeight();
	int getRecWidth();

	void toString();

private:
	float r_x;
	float r_y;
	int r_height;
	int r_width;
};