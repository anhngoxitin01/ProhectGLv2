#pragma once
#include "GameConfig.h"
#include "MRectangle.h"

class Enermy 
{
public:
	Enermy();
	Enermy(float location_x, float location_y,int width , int height, int enermy_size_x, int enermy_size_y, int direction , int level);
	~Enermy();

	void		setEnermyDirection(int direction);
	void		setEnermyLocation(float x, float y);		// auto create Rect for player
	void		setEnermyLocation(float x, float y, int width , int height);		// custom
	void		setStatus(int status);
	void		setSpeed(int speed);
	

	int			getEnermyId();
	std::string getPathTexture();
	float		getLocationX();
	float		getLocationY();
	int			getSizeX();
	int			getSizeY();
	MRectangle	getRect();
	int			getDirection();
	float		getSpeed();
	int			getStatus();
	void		show();

private:
	int			e_id;
	int			e_status;
	float		e_speed;
	int			e_direction;
	MRectangle	e_rec;
	std::string	e_path_texture;
	int			e_size_x;
	int			e_size_y;
	float		e_location_x;
	float		e_location_y;
	
};