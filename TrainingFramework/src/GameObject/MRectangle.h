#pragma once
#include"GameConfig.h"

class MRectangle
{
public:
	MRectangle();
	MRectangle(int x, int y, int height, int width);
	~MRectangle();

	int isInteract(MRectangle anotherRec);
	int caculDistanceToAnotherRecWithDirection(MRectangle anotherRec, int direction);

	void setRecXY(int x , int y);
	void setRecHeight(int height);
	void setRecWidth(int width);

	int getRecX();
	int getRecY();
	int getRecHeight();
	int getRecWidth();

	void toString();

private:
	int r_x;
	int r_y;
	int r_height;
	int r_width;
};