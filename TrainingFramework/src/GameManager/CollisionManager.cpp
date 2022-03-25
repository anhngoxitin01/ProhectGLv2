#include"CollisionManager.h"


CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

/*
* return -1 if not check successful
* return other value if successful
*/
int CollisionManager::isCollBetweenPlayerAndItemMap(int plX, int plY, int speed, int direction)
{
	int newPlX;
	int newPlY;
	int calcu;	// the value will change when move . May be x or y

	int top_left_corner;
	int top_right_corner;
	int bottom_left_corner;
	int bottom_right_corner;

	caculateCenterPlayerForCollision(plX, plY, newPlX, newPlY);

	switch (direction)
	{
	case PLAYER_MOVE_UP:
		calcu = newPlY - speed;
		//get kind of block through the index
		if ((newPlX - Globals::item_size / 2) % Globals::item_size != 0)
		{
			top_left_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((newPlX - Globals::item_size / 2) / Globals::item_size, (calcu - Globals::item_size / 2) / Globals::item_size));
			top_right_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((newPlX + Globals::item_size / 2) / Globals::item_size, (calcu - Globals::item_size / 2) / Globals::item_size));
			if (top_left_corner == COLL_NOT_OK && top_right_corner == COLL_NOT_OK)
				return COLL_NOT_OK;
		}
		else 
			return getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock(newPlX / Globals::item_size, (calcu - Globals::item_size / 2) / Globals::item_size));
		break;
	case PLAYER_MOVE_LEFT:
		calcu = newPlX - speed;
		//get kind of block through the index
		if ((newPlY - Globals::item_size / 2) % Globals::item_size != 0)
		{
			top_left_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu - Globals::item_size / 2) / Globals::item_size, (newPlY - Globals::item_size / 2) / Globals::item_size));
			bottom_left_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu - Globals::item_size / 2) / Globals::item_size, (newPlY + Globals::item_size / 2) / Globals::item_size));
			if (top_left_corner == COLL_NOT_OK && bottom_left_corner == COLL_NOT_OK)
				return COLL_NOT_OK;
		}
		else 
			return getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu - Globals::item_size / 2) / Globals::item_size, newPlY / Globals::item_size));
		break;
	case PLAYER_MOVE_DOWN:
		calcu = newPlY + speed;
		if ((newPlX - Globals::item_size / 2) % Globals::item_size != 0)
		{
			bottom_left_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((newPlX - Globals::item_size / 2) / Globals::item_size, (calcu + Globals::item_size / 2) / Globals::item_size));
			bottom_right_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((newPlX + Globals::item_size / 2) / Globals::item_size, (calcu + Globals::item_size / 2) / Globals::item_size));
			if (bottom_left_corner == COLL_NOT_OK && bottom_right_corner == COLL_NOT_OK)
				return COLL_NOT_OK;
		}
		else 
			return bottom_left_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock(newPlX / Globals::item_size, (calcu + Globals::item_size / 2) / Globals::item_size));
		break;
	case PLAYER_MOVE_RIGHT:
		calcu = newPlX + speed;
		//get kind of block through the index
		if ((newPlY - Globals::item_size / 2) % Globals::item_size != 0)
		{
			top_right_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu + Globals::item_size / 2) / Globals::item_size, (newPlY - Globals::item_size / 2) / Globals::item_size));
			bottom_right_corner = getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu + Globals::item_size / 2) / Globals::item_size, (newPlY + Globals::item_size / 2) / Globals::item_size));
			if (top_right_corner == COLL_NOT_OK && bottom_right_corner == COLL_NOT_OK)
				return COLL_NOT_OK;
		}
		else 
			return getKindBlockPlayer(ResourceManagers::GetInstance()->managerMap()->getKindOfBlock((calcu + Globals::item_size / 2) / Globals::item_size, newPlY / Globals::item_size));
		break;
	default:
		//return -1 if something wrong
		return -1;
		break;
	}
}

void CollisionManager::caculateCenterPlayerForCollision(int basePlX, int basePlY, int& newPlX, int& newPlY)
{
	//because the player width = item width
	newPlX = basePlX;
	//becasue the player height > item height
	newPlY = basePlY + (PLAYER_SIZE_Y / 2 - Globals::item_size / 2);
}

int CollisionManager::getKindBlockPlayer(int kindBlock)
{
	switch (kindBlock) {
	case MAP_ITEM_CAN_DESTROY: case MAP_ITEM_CAN_NOT_DESTROY:
		return COLL_OK;
		break;
	case MAP_ITEM_ROAD:
		return COLL_NOT_OK;
		break;
	default:
		return -1;
		break;
	}
}
