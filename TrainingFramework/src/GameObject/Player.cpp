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
	p_rec = MRectangle(p_location_x, p_location_y + (PLAYER_SIZE_Y - Globals::item_size) / 2, Globals::item_size, Globals::item_size);
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
	int newLocation = 0;
	int distancePlaAndBarrier;
	int smoothPlayer = 0;

	switch (direction)
	{
	case PLAYER_MOVE_RIGHT:
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_RIGHT, distancePlaAndBarrier , smoothPlayer) == COLL_NOT_OK)
			newLocation = p_location_x + p_speed;
		else {
			if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
				newLocation = p_location_x + distancePlaAndBarrier;
			else
				newLocation = p_location_x;
		}
		//set new player location
		printf("the value smoothPlayer func smoothMovingPlayer = %d\n", smoothPlayer);
		setPlayerLocation(newLocation, p_location_y + smoothPlayer);
		break;
	case PLAYER_MOVE_LEFT:
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
		break;
	case PLAYER_MOVE_UP:
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
		break;
	case PLAYER_MOVE_DOWN:
		if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemMap(getRectPlayer(), p_speed, PLAYER_MOVE_DOWN, distancePlaAndBarrier, smoothPlayer) == COLL_NOT_OK)
			newLocation = p_location_y + p_speed;
		else {
			if (distancePlaAndBarrier <= p_speed && distancePlaAndBarrier > 0)
				newLocation = p_location_y + distancePlaAndBarrier;
			else 
				newLocation = p_location_y;
			/*printf("Location Player in moving func %d , %d\n", getRectPlayer().getRecX(), getRectPlayer().getRecY());
			printf("speed %d , distance = %d\n", p_speed, distancePlaAndBarrier);*/
		}
		//set new player location
		setPlayerLocation(p_location_x + smoothPlayer, newLocation);
		break;
	default:
		printf("Something wrong in movePlayer");
		break;
	}
	
}

