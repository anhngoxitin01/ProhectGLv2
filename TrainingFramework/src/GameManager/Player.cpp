#include"Player.h"

Player::Player(): p_speed(3) , p_status_live(PLAYER_STATUS_LIVE) , p_direction(PLAYER_MOVE_DOWN), p_is_move(false) 
{
	//NOT GOOD SOLUTION
	p_texture[PLAYER_MOVE_DOWN]		= "bomber_down.tga";
	p_texture[PLAYER_MOVE_LEFT]		= "bomber_left.tga";
	p_texture[PLAYER_MOVE_UP]		= "bomber_up.tga";
	p_texture[PLAYER_MOVE_RIGHT]	= "bomber_right.tga";
}

Player::~Player(){}

void Player::setPlayerDirection(int direction)
{
	p_direction = direction;
}

void Player::setPlayerIsMoving(bool isMoving)
{
	p_is_move = isMoving;
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
