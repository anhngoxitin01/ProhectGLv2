#include"Player.h"
#include "GameManager/CollisionManager.h"

Player::Player() : p_speed(PLAYER_BASE_SPEED), p_status_live(PLAYER_STATUS_LIVE), p_direction(PLAYER_MOVE_DOWN), p_is_move(false) 
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
	p_rec = MRectangle(p_location_x, p_location_y + (PLAYER_SIZE_Y - Globals::item_size) / 2, PLAYER_SIZE_X, PLAYER_SIZE_Y);
	/*printf("in func setPlayerLocation infor player: \nLocation_draw = %d , %d \n Location_rec = %d, %d\n"
		, p_location_x
		, p_location_y
		, p_rec.getRecX()
		, p_rec.getRecY());*/
}

void Player::upgradeRect()
{
	p_rec.setRecXY(p_location_x, p_location_y + (PLAYER_SIZE_Y - Globals::item_size) / 2);
}

int Player::getPlayerDirection()
{
	return p_direction;
}

int Player::getPlayerSpeed()
{
	return p_speed;
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

MRectangle Player::getRectPlayer()
{
	return p_rec;
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
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_RIGHT) == COLL_NOT_OK)
			setPlayerLocation(newLocation, p_location_y);
		break;
	case PLAYER_MOVE_LEFT:
		newLocation = p_location_x - p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_LEFT) == COLL_NOT_OK)
			setPlayerLocation(newLocation, p_location_y);
		break;
	case PLAYER_MOVE_UP:
		newLocation = p_location_y - p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_UP) == COLL_NOT_OK)
			setPlayerLocation(p_location_x, newLocation);
		break;
	case PLAYER_MOVE_DOWN:
		newLocation = p_location_y + p_speed;
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_DOWN) == COLL_NOT_OK)
			setPlayerLocation(p_location_x, newLocation);
		break;
	default:
		printf("Something wrong in movePlayer");
		break;
	}
}
