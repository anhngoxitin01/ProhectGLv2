#include"Player.h"

Player::Player() : p_speed(3), p_status_live(PLAYER_STATUS_LIVE), p_direction(PLAYER_MOVE_DOWN), p_is_move(false) 
					, p_location_x(25) , p_location_y(75)
{
	//NOT GOOD SOLUTION
	p_texture[PLAYER_MOVE_DOWN]		= "bomber_down.tga";
	p_texture[PLAYER_MOVE_LEFT]		= "bomber_left.tga";
	p_texture[PLAYER_MOVE_UP]		= "bomber_up.tga";
	p_texture[PLAYER_MOVE_RIGHT]	= "bomber_right.tga";
}

Player::~Player() {}

void Player::setPlayerDirection(int direction)
{
	p_direction = direction;
}

void Player::setPlayerIsMoving(bool isMoving)
{
	p_is_move = isMoving;
}

void Player::setPlayerLocation(double x, double y)
{
	p_location_x = x;
	p_location_y = y;
}

int Player::getPlayerDirection()
{
	return p_direction;
}

int Player::getPlayerStatusLive()
{
	return p_status_live;
}

bool Player::isPlayerMoving()
{
	return p_is_move;
}

std::string Player::getPlayerTextureStading(int direction)
{
	return p_texture[direction];
}

double Player::getPlayerLocationX()
{
	return p_location_x;
}

double Player::getPlayerLocationY()
{
	return p_location_y;
}

void Player::movePlayer(int direction)
{
	switch (direction)
	{
	case PLAYER_MOVE_RIGHT:
		p_location_x += p_speed;
		break;
	case PLAYER_MOVE_LEFT:
		p_location_x -= p_speed;
		break;
	case PLAYER_MOVE_UP:
		p_location_y -= p_speed;
		break;
	case PLAYER_MOVE_DOWN:
		p_location_y += p_speed;
		break;
	default:
		printf("Something wrong in movePlayer");
		break;
	}
}
