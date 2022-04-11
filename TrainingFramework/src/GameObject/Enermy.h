#pragma once
#include "GameConfig.h"
#include "MRectangle.h"

class Enermy 
{
public:
	Enermy();
	Enermy(int location_x, int location_y, int enermy_size_x, int enermy_size_y, int direction);
	~Enermy();

	void		setEnermyDirection(int direction);
	void		setEnermyLocation(int x, int y);		// auto create Rect for player
	void		setStatus(int status);
	void		setTimeEnermy(float time);
	


	std::string getPathTexture();		//getTexture of the direction the enermy is having
	int			getLocationX();
	int			getLocationY();
	int			getSizeX();
	int			getSizeY();
	MRectangle	getRect();
	int			getDirection();
	int			getSpeed();
	int			getStatus();
	float		getTimeEnermy();
	void		show();

	void		addTimeToEnermy(float addTime);

private:
	int			e_status;
	int			e_speed;
	int			e_direction;
	float		e_time;
	MRectangle	e_rec;
	std::string	e_path_texture[ENERMY_TEXTURE_EACH_DIRECTION * 4];
	int			e_size_x;
	int			e_size_y;
	int			e_location_x;
	int			e_location_y;
	
};