#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::~Rectangle()
{
}

int Rectangle::isInteract(Rectangle r1, Rectangle r2)
{

	int l1_x		= r1.r_x - r1.r_length / 2;		//	left_top_r1_x	
	int l1_y		= r1.r_y - r1.r_width / 2;		//	left_top_r1_y
	int r1_x		= r1.r_x + r1.r_length / 2;		//	right_bottom_r1_x
	int r2_y		= r1.r_y + r1.r_width / 2;		//	right_bottom_r1_y

	int l2_x		= r2.r_x - r2.r_length / 2;			//	left_top_r2_x
	int l2_y		= r2.r_y - r2.r_width / 2;			//	left_top_r2_y
	int r2_x		= r2.r_x + r2.r_length / 2;		//	right_bottom_r2_x
	int r2_y		= r2.r_y + r2.r_width / 2;		//	right_bottom_r2_y

	if (l1_x == r1.r_x || l1_y == r1.r_y || l2_x == r2.r_x || l2_y == r2.r_y)
	{
		//this case is the line not the rectangle
		return REC_IS_LINE;
	}
	else if (r1.r_x == r2.r_x && r1.r_y == r2.r_y && r1.r_width == r2.r_width && r1.r_length == r2.r_length)
	{
		return REC_OVER_LAP;
	}
	else if (l1_x >= r2_x || l2_x >= r1_x || l1_y <= r2_y || l2_y <= r1_x)
	{
		return REC_NOT_ABOVE;
	}
	else
		return REC_ABOVE;
}

void Rectangle::initRec(int x, int y, int length, int width)
{
	r_x = x;
	r_y = y;
	r_length = length;
	r_width = width;
}

void Rectangle::setRecX(int x)
{
	r_x = x;
}

void Rectangle::setRecY(int y)
{
	r_y = y;
}

void Rectangle::setRecLength(int length)
{
	r_length = length;
}

void Rectangle::setRecWidth(int width)
{
	r_width = width;
}
