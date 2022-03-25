#include"Player.h"
#include "GameManager/CollisionManager.h"

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

void Player::setPlayerLocation(int x, int y)
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

int Player::getPlayerLocationX()
{
	return p_location_x;
}

int Player::getPlayerLocationY()
{
	return p_location_y;
}

void Player::movePlayer(int direction)
{
	int newLocation;

	switch (direction)
	{
	case PLAYER_MOVE_RIGHT:
		newLocation = p_location_x + p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(p_location_x, p_location_y, p_speed, PLAYER_MOVE_RIGHT) == COLL_NOT_OK)
			p_location_x = newLocation;
		// not move out map
		/*if (newLocation < Globals::item_size * (Globals::colMap - 1) - Globals::item_size / 2)
			p_location_x = newLocation;*/
		break;
	case PLAYER_MOVE_LEFT:
		newLocation = p_location_x - p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(p_location_x, p_location_y, p_speed, PLAYER_MOVE_LEFT) == COLL_NOT_OK)
			p_location_x = newLocation;
		// not move out map
		/*if (newLocation > Globals::item_size + Globals::item_size / 2)
			p_location_x = newLocation;*/
		break;
	case PLAYER_MOVE_UP:
		newLocation = p_location_y - p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(p_location_x, p_location_y, p_speed, PLAYER_MOVE_UP) == COLL_NOT_OK)
			p_location_y = newLocation;
		// not move out map
		/*if (newLocation > Globals::item_size)
			p_location_y = newLocation;*/
		break;
	case PLAYER_MOVE_DOWN:
		newLocation = p_location_y + p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(p_location_x, p_location_y, p_speed, PLAYER_MOVE_DOWN) == COLL_NOT_OK)
			p_location_y = newLocation;
		// not move out map
		/*if (newLocation < Globals::item_size * (Globals::rowMap - 1) - PLAYER_SIZE_Y/2)
			p_location_y = newLocation;*/
		break;
	default:
		printf("Something wrong in movePlayer");
		break;
	}
}
