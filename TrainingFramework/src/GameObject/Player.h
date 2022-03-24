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
#define PLAYER_SIZE_X					Globals::item_size
#define PLAYER_SIZE_Y					Globals::item_size + 25

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
	void setPlayerLocation(int x, int y);

	int			getPlayerDirection();
	int			getPlayerSpeed();
	int			getPlayerNumBomb();
	int			getPlayerLengthBomb();
	int			getPlayerStatusLive();
	bool		isPlayerMoving();
	int			getPlayerLocationX();
	int			getPlayerLocationY();
	std::string	getPlayerTextureStading(int direction);

	void		movePlayer(int direction);

private:
	int											p_speed;
	int											p_status_live;			// 1: live , 2: is bubbles , 3:is dead
	int											p_direction;			// 1: up , 2: left , 3:down , 4: right
	bool										p_is_move;				// true: isRunning, false:isStanding
	int											p_location_x;
	int											p_location_y;
	std::string									p_texture[PLAYER_TEXTURE_EACH_DIRECTION * 4];
	int											p_size_x;
	int											p_size_y;
};