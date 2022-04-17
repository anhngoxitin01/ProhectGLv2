#include "MRectangle.h"

MRectangle::MRectangle()
{
}

MRectangle::MRectangle(int x, int y, int height, int width)
{
	r_x = x;
	r_y = y;
	r_height = height;
	r_width = width;
}

MRectangle::~MRectangle()
{
}

int MRectangle::isInteract(MRectangle anotherRec)
{
	//printf("ThisRec : %d , %d , %d , %d|| anotherRec: %d ,%d , %d , %d\n", r_x, r_y,r_height , r_width , anotherRec.getRecX(), anotherRec.getRecY() , anotherRec.getRecWidth() , anotherRec.getRecHeight());

	int l1_x		= r_x - r_height / 2;		//	left_top_r1_x	
	int l1_y		= r_y - r_width / 2;		//	left_top_r1_y
	int r1_x		= r_x + r_height / 2;		//	right_bottom_r1_x
	int r1_y		= r_y + r_width / 2;		//	right_bottom_r1_y

	int l2_x		= anotherRec.r_x - anotherRec.r_height / 2;		//	left_top_r2_x
	int l2_y		= anotherRec.r_y - anotherRec.r_width / 2;		//	left_top_r2_y
	int r2_x		= anotherRec.r_x + anotherRec.r_height / 2;		//	right_bottom_r2_x
	int r2_y		= anotherRec.r_y + anotherRec.r_width / 2;		//	right_bottom_r2_y

	

	if (l1_x == r_x || l1_y == r_y || l2_x == anotherRec.r_x || l2_y == anotherRec.r_y)
	{
		//this case is the line not the rectangle
		return REC_IS_LINE;
	}
	else if (r_x == anotherRec.r_x && r_y == anotherRec.r_y && r_width == anotherRec.r_width && r_height == anotherRec.r_height)
	{
		return REC_OVER_LAP;
	}
	else if((r_x + r_width/2) <= (anotherRec.getRecX() - anotherRec.getRecWidth()/2) 
				|| (anotherRec.r_x + anotherRec.getRecWidth()/2) <= (r_x - r_width/2)
				|| (r_y + r_height/2) <= (anotherRec.getRecY() - anotherRec.getRecHeight()/2) 
				|| (anotherRec.getRecY() + anotherRec.getRecHeight()/2) <= (r_y - r_height/2))
	{
		return REC_NOT_ABOVE;
	}
	else
	{
		//printf("ThisRec : %d , %d , %d , %d|| anotherRec: %d ,%d , %d , %d\n", r_x, r_y,r_height , r_width , anotherRec.getRecX(), anotherRec.getRecY() , anotherRec.getRecWidth() , anotherRec.getRecHeight());
		return REC_ABOVE;
	}
		
}
/*
* WARNING : this func is not true with rectangles just true with squares
* PLEASE CAREFULLY WHEN USING
* the direction of another rec to this rec
*/ 
int MRectangle::caculDistanceToAnotherRecWithDirection(MRectangle anotherRec, int direction)
{
	switch (direction)
	{
	case ON_THE_TOP_REC: // so sanh voi hcn o tren
		//printf(" on the top Rec %d - %d = %d \n", (r_y - r_width / 2), (anotherRec.r_y + anotherRec.r_width / 2), (r_y - r_width / 2) - (anotherRec.r_y + anotherRec.r_width / 2));
		return (r_y - r_height / 2) - (anotherRec.r_y + anotherRec.r_height / 2);
		break;
	case ON_THE_LEFT_REC: // so sanh voi hcn o ben trai
		//printf(" on the top Rec %d - %d = %d \n", (r_x - r_height / 2), (anotherRec.r_x + anotherRec.r_height / 2), (r_x - r_height / 2) - (anotherRec.r_x + anotherRec.r_height / 2));
		return (r_x - r_width / 2) - (anotherRec.r_x + anotherRec.r_width / 2);
		break;
	case ON_THE_RIGHT_REC: // so sanh voi hcn o ben phai
		//printf(" on the right Rec %d - %d = %d \n", (anotherRec.r_x - anotherRec.r_height / 2), (r_x + r_height / 2), (anotherRec.r_x - anotherRec.r_height / 2) - (r_x + r_height / 2));
		return (anotherRec.r_x - anotherRec.r_width / 2) - (r_x + r_width / 2);
		break;
	case ON_THE_BOTTOM_REC: // so sanh voi hcn o duoi
		//printf(" on the bottom Rec %d - %d = %d \n", (anotherRec.r_y - anotherRec.r_width / 2), (r_y + r_width / 2), (anotherRec.r_y - anotherRec.r_width / 2) - (r_y + r_width / 2));
		return (anotherRec.r_y - anotherRec.r_height / 2) - (r_y + r_height / 2);
		break;
	default:
		break;
	}
	return 0;
}

void MRectangle::setRecXY(int x, int y)
{
	r_x = x;
	r_y = y;
}

void MRectangle::setRecHeight(int height)
{
	r_height = height;
}

void MRectangle::setRecWidth(int width)
{
	r_width = width;
}

int MRectangle::getRecX()
{
	return r_x;
}

int MRectangle::getRecY()
{
	return r_y;
}

int MRectangle::getRecHeight()
{
	return r_height;
}

int MRectangle::getRecWidth()
{
	return r_width;
}

void MRectangle::toString()
{
	printf("The rec: x= %d , y= %d , width = %d , height = %d\n", r_x, r_y, r_width, r_height);
}
