#pragma once
#include"GameConfig.h"

class MRectangle
{
public:
	MRectangle();
	MRectangle(int x, int y, int length, int width);
	~MRectangle();

	int isInteract(MRectangle r1, MRectangle r2);

	void setRecXY(int x , int y);
	void setRecLength(int length);
	void setRecWidth(int width);

	int getRecX();
	int getRecY();
	int getRecLength();
	int getRecWidth();

private:
	int r_x;
	int r_y;
	int r_length;
	int r_width;
};