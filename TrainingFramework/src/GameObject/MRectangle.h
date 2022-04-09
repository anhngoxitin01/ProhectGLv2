#pragma once
#include"GameConfig.h"

class MRectangle
{
public:
	MRectangle();
	MRectangle(int x, int y, int length, int width);
	~MRectangle();

	int isInteract(MRectangle anotherRec);
	int caculDistanceToAnotherRecWithDirection(MRectangle anotherRec, int direction);

	void setRecXY(int x , int y);
	void setRecLength(int length);
	void setRecWidth(int width);

	int getRecX();
	int getRecY();
	int getRecLength();
	int getRecWidth();

	void toString();

private:
	int r_x;
	int r_y;
	int r_length;
	int r_width;
};