#pragma once

#include<list>
#include<string>

//Player
#define PLAYER_STATUS_LIVE				0
#define PLAYER_STATUS_BUBBLE			1
#define PLAYER_STATUS_DEAD				2
#define PLAYER_MOVE_DOWN				0
#define PLAYER_MOVE_LEFT				1
#define PLAYER_MOVE_UP					2
#define PLAYER_MOVE_RIGHT				3
#define PLAYER_TEXTURE_EACH_DIRECTION	1
#define PLAYER_BASE_SPEED				2

class Sprite2D;


class Player
{
public:
	Player();
	~Player();

	void setPlayerDirection(int direction);
	void setPlayerSpeed(int speed);
	void setPlayerNumBomb(int numBomb);
	void setPlayerLengthBomb(int lengthBomb);
	void setPlayerStatusLive(int statusLive);
	void setPlayerIsMoving(bool isMoving);
	void setPlayerLocation(double x, double y);

	int			getPlayerDirection();
	int			getPlayerSpeed();
	int			getPlayerNumBomb();
	int			getPlayerLengthBomb();
	int			getPlayerStatusLive();
	bool		isPlayerMoving();
	std::string	getPlayerTextureStading(int direction);
	double		getPlayerLocationX();
	double		getPlayerLocationY();

	void		movePlayer(int direction);

private:
	int											p_speed;
	int											p_status_live;			// 1: live , 2: is bubbles , 3:is dead
	int											p_direction;			// 1: up , 2: left , 3:down , 4: right
	bool										p_is_move;				// true: isRunning, false:isStanding
	double										p_location_x;
	double										p_location_y;
	std::string									p_texture[PLAYER_TEXTURE_EACH_DIRECTION * 4];
};