#include "Enermy.h"

Enermy::Enermy(): e_status(STATUS_LIVE), e_speed(ENERMY_BASE_SPEED), e_direction(ENERMY_MOVE_DOWN)
{
	//NOT GOOD SOLUTION
	e_path_texture[ENERMY_MOVE_DOWN] = "enermy_down.tga";
	e_path_texture[ENERMY_MOVE_LEFT] = "enermy_left.tga";
	e_path_texture[ENERMY_MOVE_UP] = "enermy_up.tga";
	e_path_texture[ENERMY_MOVE_RIGHT] = "enermy_right.tga";
}

Enermy::~Enermy()
{
}

void Enermy::initEnermy(int location_x, int location_y, int enermy_size_x, int enermy_size_y, int direction)
{
	setEnermyDirection(direction);
	setEnermyLocation(location_x, location_y);
	e_size_x = enermy_size_x;
	e_size_y = enermy_size_y;
}

void Enermy::setEnermyDirection(int direction)
{
	e_direction = direction;
}

void Enermy::setEnermyLocation(int x, int y)
{
	e_location_x = x;
	e_location_y = y;
	e_rec = MRectangle(e_location_x, e_location_y , Globals::item_size, Globals::item_size);
}

void Enermy::setStatus(int status)
{
	e_status = status;
}

MRectangle Enermy::getRect()
{
	return e_rec;
}

int Enermy::getDirection()
{
	return e_direction;
}

int Enermy::getSpeed()
{
	return e_speed;
}

int Enermy::getStatus()
{
	return e_status;
}

std::string Enermy::getPathTexture()
{
	return e_path_texture[e_direction];
}

int Enermy::getLocationX()
{
	return e_location_x;
}

int Enermy::getLocationY()
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

