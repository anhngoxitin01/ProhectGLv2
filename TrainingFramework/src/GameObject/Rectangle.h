#pragma once
#include"GameConfig.h"

class Rectangle
{
public:
	Rectangle();
	~Rectangle();

	int isInteract(Rectangle r1, Rectangle r2);
	
	void initRec(int x, int y, int length, int width);
	void setRecX(int x);
	void setRecY(int y);
	void setRecLength(int length);
	void setRecWidth(int width);

private:
	int r_x;
	int r_y;
	int r_length;
	int r_width;
};