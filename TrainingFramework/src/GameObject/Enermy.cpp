#include "Enermy.h"

Enermy::Enermy(): e_status(STATUS_LIVE), e_speed(ENERMY_BASE_SPEED), e_direction(ENERMY_MOVE_DOWN)
{
	//NOT GOOD SOLUTION
	e_path_texture = "enermy_animation.tga";
	//increase the id enermy system
	e_id = Globals::enermy_Id++;
}

Enermy::Enermy(float location_x, float location_y,int width , int height,  int enermy_size_x, int enermy_size_y, int direction, int level) : e_status(STATUS_LIVE)
{
	setEnermyDirection(direction);
	e_location_x = location_x;
	e_location_y = location_y;
	e_rec = MRectangle(e_location_x, e_location_y, width, height);
	e_size_x = enermy_size_x;
	e_size_y = enermy_size_y;

	//update time enermy moving
	switch (level)
	{
	case MAP_LEVEL_1:
		e_speed = ENERMY_BASE_SPEED;
		break;
	case MAP_LEVEL_2:
		e_speed = ENERMY_BASE_SPEED + 0.2f;
		break;
	case MAP_LEVEL_3:
		e_speed = ENERMY_BASE_SPEED + 0.2f;
		break;
	default:
		break;
	}

	e_path_texture = "enermy_animation.tga";
	//increase the id enermy system
	e_id = Globals::enermy_Id++;
}

Enermy::~Enermy() 
{
}

void Enermy::setEnermyDirection(int direction)
{
	e_direction = direction;
}

void Enermy::setEnermyLocation(float x, float y)
{
	e_location_x = x;
	e_location_y = y;
	e_rec.setRecXY(x, y);
}

void Enermy::setEnermyLocation(float x, float y, int width, int height)
{
	e_location_x = x;
	e_location_y = y;
	e_rec = MRectangle(e_location_x, e_location_y, width, height);
}

void Enermy::setStatus(int status)
{
	e_status = status;
}

void Enermy::setSpeed(int speed)
{
	e_speed = speed;
}

MRectangle Enermy::getRect()
{
	return e_rec;
}

int Enermy::getDirection()
{
	return e_direction;
}

float Enermy::getSpeed()
{
	return e_speed;
}

int Enermy::getStatus()
{
	return e_status;
}

void Enermy::show()
{
	printf("Enermy: rec:%d, %d || location:%d, %d || direction: %d || status: %d || speed: %d \n"
		, e_rec.getRecX()
		, e_rec.getRecY()
		, e_location_x
		, e_location_y
		, e_direction
		, e_status);
}

int Enermy::getEnermyId()
{
	return e_id;
}

std::string Enermy::getPathTexture()
{
	return e_path_texture;
}

float Enermy::getLocationX()
{
	return e_location_x;
}

float Enermy::getLocationY()
{
	return e_location_y;
}

int Enermy::getSizeX()
{
	return e_size_x;
}

int Enermy::getSizeY()
{
	return e_size_y;
}

