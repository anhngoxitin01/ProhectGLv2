#include"Player.h"
#include "GameManager/CollisionManager.h"

Player::Player() : p_speed(PLAYER_BASE_SPEED), p_status_live(STATUS_LIVE), p_direction(PLAYER_MOVE_DOWN), p_is_move(false) 
					, p_location_x(25) , p_location_y(75) , p_num_boom(PLAYER_BOMB_NUM) , p_isPrepareNextBoom(true) , p_power(PLAYER_BOMB_STRENGTH)
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
	p_power = lengthBomb;
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
	return p_power;
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

std::list<Boom*>* Player::getPlayerListBoom()
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
			//check to movement
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
	if (p_list_boom.size() < p_num_boom && p_isPrepareNextBoom)
	{
		//create boom to init
		Boom *boom = new Boom();
		boom->setRec(boom->calculateLocationGenerate(p_rec));	//set location for boom
		boom->setPower(p_power);								//set power for boom

		//player can not init more than one him/her boom in a place
		bool check_can_init_boom_in_this_place = true;
		for (auto *it : p_list_boom)
		{
			if (it->getRect().getRecX() == boom->getRect().getRecX() && it->getRect().getRecY() == boom->getRect().getRecY())
			{
				check_can_init_boom_in_this_place = false;
			}
		}

		//push boom to list
		if (check_can_init_boom_in_this_place)
		{
			p_list_boom.push_back(boom);
			printf("size of boom %d", p_list_boom.size());
			p_isPrepareNextBoom = false;
		}
	}
}

void Player::reLoadBoom()
{
	p_list_boom.remove_if([](auto it)
		{
			if (it->getStatusBoom() == STATUS_BOOM_DESTROY)
			{
				printf("This boom was destroy\n");
				return true;
			}
			return false;
		});
}

int Player::isCollWithItemPlayer()
{
	//check with Item Player
	int kindItem = 0;
	if (CollisionManager::GetInstance()->isCollBetweenPlayerAndItemPlayer(getRectPlayer(), kindItem) == COLL_OK)
	{
		updatePlayerWithItemPlayer(kindItem);
		return true;
	}
	return false;
}

void Player::updatePlayerWithItemPlayer(int kindItem)
{
	switch (kindItem)
	{
	case ITEMPL_KIND_BOMB:
		p_num_boom++;
		break;
	case ITEMPL_KIND_BOMBSIZE:
		p_power++;
		break;
	case ITEMPL_KIND_SHOE:
		p_speed++;
		break;
	default:
		printf("there is some error when update streng player through item player\n");
		break;
	}
}

