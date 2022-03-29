#include"Player.h"
#include "GameManager/CollisionManager.h"

Player::Player() : p_speed(PLAYER_BASE_SPEED), p_status_live(STATUS_LIVE), p_direction(PLAYER_MOVE_DOWN), p_is_move(false) 
					, p_location_x(25) , p_location_y(75) , p_num_boom(5) , p_isPrepareNextBoom(true)
{
	//NOT GOOD SOLUTION
	p_texture[PLAYER_MOVE_DOWN]		= "bomber_down.tga";
	p_texture[PLAYER_MOVE_LEFT]		= "bomber_left.tga";
	p_texture[PLAYER_MOVE_UP]		= "bomber_up.tga";
	p_texture[PLAYER_MOVE_RIGHT]	= "bomber_right.tga";

	p_boom.setPower(1);
}

Player::~Player() {}

void Player::setPlayerDirection(int direction)
{
	p_direction = direction;
}

void Player::setPlayerSpeed(int speed)
{
	p_speed = speed;
}

void Player::setPlayerNumBomb(int numBomb)
{
	p_num_boom = numBomb;
}

void Player::setPlayerLengthBomb(int lengthBomb)
{
	p_boom.setPower(lengthBomb);
}

void Player::setPlayerStatusLive(int statusLive)
{
	p_status_live = statusLive;
}

void Player::setPlayerIsMoving(bool isMoving)
{
	p_is_move = isMoving;
}

void Player::setPlayerLocation(int x, int y)
{
	p_location_x = x;
	p_location_y = y;
	p_rec = MRectangle(p_location_x, p_location_y + (PLAYER_SIZE_Y - Globals::item_size) / 2, Globals::item_size, Globals::item_size);
}

void Player::setPrepateNextBoom(bool status)
{
	p_isPrepareNextBoom = status;
}

int Player::getPlayerDirection()
{
	return p_direction;
}

int Player::getPlayerSpeed()
{
	return p_speed;
}

int Player::getPlayerNumBomb()
{
	return p_num_boom;
}

int Player::getPlayerLengthBomb()
{
	return p_boom.getPower();
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

std::list<Boom>* Player::getPlayerListBoom()
{
	return &p_list_boom;
}

bool Player::isPrepareNextBoom()
{
	return p_isPrepareNextBoom;
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
	int newLocation = 0;
	int distancePlaAndBarrier;
	int smoothPlayer = 0;

	switch (direction)
	{
	case PLAYER_MOVE_RIGHT:
		if(p_is_move)
		{
			if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_RIGHT, distancePlaAndBarrier, smoothPlayer) == COLL_NOT_OK)
				newLocation = p_location_x + p_speed;
			else {
				if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
					newLocation = p_location_x + distancePlaAndBarrier;
				else
					newLocation = p_location_x;
			}
			//set new player location
			setPlayerLocation(newLocation, p_location_y + smoothPlayer);
		}
		break;
	case PLAYER_MOVE_LEFT:
		if (p_is_move)
		{
			if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_LEFT, distancePlaAndBarrier, smoothPlayer) == COLL_NOT_OK)
				newLocation = p_location_x - p_speed;
			else {
				if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
					newLocation = p_location_x - distancePlaAndBarrier;
				else
					newLocation = p_location_x;
			}
			//set new player location
			setPlayerLocation(newLocation, p_location_y + smoothPlayer);
		}
		break;
	case PLAYER_MOVE_UP:
		if (p_is_move)
		{
			if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_UP, distancePlaAndBarrier, smoothPlayer) == COLL_NOT_OK)
				newLocation = p_location_y - p_speed;
			else {
				if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
					newLocation = p_location_y - distancePlaAndBarrier;
				else
					newLocation = p_location_y;
			}
			//set new player location
			setPlayerLocation(p_location_x + smoothPlayer, newLocation);
		}
		break;
	case PLAYER_MOVE_DOWN:
		if (p_is_move)
		{
			if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_DOWN, distancePlaAndBarrier, smoothPlayer) == COLL_NOT_OK)
				newLocation = p_location_y + p_speed;
			else {
				if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
					newLocation = p_location_y + distancePlaAndBarrier;
				else
					newLocation = p_location_y;
			}
			//set new player location
			setPlayerLocation(p_location_x + smoothPlayer, newLocation);
		}
		break;
	default:
		printf("Something wrong in movePlayer");
		break;
	}
	
}

void Player::initBoom()
{
	//calulate boom to init
	p_boom.setRec(p_boom.calculateLocationGenerate(p_rec));

	if (p_list_boom.size() < p_num_boom && p_isPrepareNextBoom)
	{
		p_list_boom.push_back(p_boom);
		p_isPrepareNextBoom = false;
	}
}

