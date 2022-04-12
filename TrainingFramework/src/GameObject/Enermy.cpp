#include "Enermy.h"

Enermy::Enermy(): e_status(STATUS_LIVE), e_speed(ENERMY_BASE_SPEED), e_direction(ENERMY_MOVE_DOWN) , e_time(0.0f)
{
	//NOT GOOD SOLUTION
	e_path_texture = "enermy_animation.tga";
	//increase the id enermy system
	e_id = Globals::enermy_Id++;
}

Enermy::Enermy(int location_x, int location_y, int enermy_size_x, int enermy_size_y, int direction) : e_status(STATUS_LIVE), e_speed(ENERMY_BASE_SPEED), e_time(0.0f)
{
	setEnermyDirection(direction);
	setEnermyLocation(location_x, location_y);
	e_size_x = enermy_size_x;
	e_size_y = enermy_size_y;

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

void Enermy::setTimeEnermy(float time)
{
	e_time = time;
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

float Enermy::getTimeEnermy()
{
	return e_time;
}

void Enermy::show()
{
	printf("Enermy: rec:%d, %d || location:%d, %d || direction: %d || status: %d || speed: %d || time: %f\n"
		, e_rec.getRecX()
		, e_rec.getRecY()
		, e_location_x
		, e_location_y
		, e_direction
		, e_status
		, e_time);
}

void Enermy::addTimeToEnermy(float addTime)
{
	e_time += addTime;
}

int Enermy::getEnermyId()
{
	return e_id;
}

std::string Enermy::getPathTexture()
{
	return e_path_texture;
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

