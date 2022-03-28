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
int CollisionManager::isCollBetweenPlayerAndItemMap(MRectangle pl, int speed, int direction, int& distancePlaAndBarrier , int& smoothPLayer)
{
	smoothPLayer = 0;	// define the value to end func if not anything change

	int index_x;
	int index_y;
	int calcu;	// the value will change when move . May be x or y

	ItemMap forward_left_block;
	ItemMap forward_right_block;
	ItemMap forward_block;

	switch (direction)
	{
	case PLAYER_MOVE_UP:
		// update location
		calcu = pl.getRecY() - speed;
		index_y = (calcu - Globals::item_size / 2) / Globals::item_size; //this index of 3 blocks forward are same value

		//check kind of block
		//if the player move in a col of map just check the forward block
		if ((pl.getRecX() - Globals::item_size / 2) % Globals::item_size == 0)
		{
			//get index forward block
			index_x = pl.getRecX() / Globals::item_size;
			forward_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);			//beacause you read map row y then col x 
			//forward_block.showInfor();
			//check kind block
			if (forward_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				//spacPLaAndBarrier = distance for the top line of rec player overlapping the bottom line of forward block  
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_TOP_REC);
				return COLL_OK;
			}
		}
		else	// else just check the forward_left_block and forware_right_block
		{
			//get index forward left block
			index_x = (pl.getRecX() - Globals::item_size / 2) / Globals::item_size;
			forward_left_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//get index forward right block
			index_x = (pl.getRecX() + Globals::item_size / 2) / Globals::item_size;
			forward_right_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);	//beacause you read map row y then col x 
			//check kind block
			if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD || forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				//cacul to smoothPlayer
				if (forward_left_block.getKindBlock() == MAP_ITEM_ROAD && forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_UP, pl, forward_left_block.getRect());
				else if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD && forward_right_block.getKindBlock() == MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_UP, pl, forward_right_block.getRect());
				//cacul to go to end road
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_TOP_REC);
				return COLL_OK;
			}
		}
		return COLL_NOT_OK;
		break;
	case PLAYER_MOVE_LEFT:
		// update location
		calcu = pl.getRecX() - speed;
		index_x = (calcu - Globals::item_size / 2) / Globals::item_size; //this index of 3 blocks forward are same value

		//check kind of block
		//if the player move in a row of map just check the forward block
		if ((pl.getRecY() - Globals::item_size / 2) % Globals::item_size == 0)
		{
			//get index forward block
			index_y = pl.getRecY() / Globals::item_size;
			forward_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//check kind block
			//forward_block.showInfor();
			if (forward_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_LEFT_REC);
				return COLL_OK;
			}
		}
		else	// else just check the forward_left_block and forware_right_block
		{
			//get index forward left block
			index_y = (pl.getRecY() + Globals::item_size / 2) / Globals::item_size;
			forward_left_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//get index forward right block
			index_y = (pl.getRecY() - Globals::item_size / 2) / Globals::item_size;
			forward_right_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//check kind block
			if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD || forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				//cacul to smoothPlayer
				if (forward_left_block.getKindBlock() == MAP_ITEM_ROAD && forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_LEFT, pl, forward_left_block.getRect());
				else if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD && forward_right_block.getKindBlock() == MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_LEFT, pl, forward_right_block.getRect());
				//cacul to go to end road
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_LEFT_REC);
				return COLL_OK;
			}
		}
		return COLL_NOT_OK;
		break;
	case PLAYER_MOVE_DOWN:
		// update location
		calcu = pl.getRecY() + speed;
		index_y = (calcu + Globals::item_size / 2) / Globals::item_size; //this index of 3 blocks forward are same value

		//check kind of block
		//if the player move in a col of map just check the forward block
		if ((pl.getRecX() - Globals::item_size / 2) % Globals::item_size == 0)
		{
			//get index forward block
			index_x = pl.getRecX() / Globals::item_size;
			forward_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//check kind block
			if (forward_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_BOTTOM_REC);
				return COLL_OK;
			}
		}
		else	// else just check the forward_left_block and forware_right_block
		{
			//get index forward left block
			index_x = (pl.getRecX() + Globals::item_size / 2) / Globals::item_size;
			forward_left_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//get index forward right block
			index_x = (pl.getRecX() - Globals::item_size / 2) / Globals::item_size;
			forward_right_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//check kind block
			if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD || forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				//cacul to smoothPlayer
				if (forward_left_block.getKindBlock() == MAP_ITEM_ROAD && forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_DOWN, pl, forward_left_block.getRect());
				else if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD && forward_right_block.getKindBlock() == MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_DOWN, pl, forward_right_block.getRect());
				//cacul to go to end road
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_BOTTOM_REC);
				return COLL_OK;
			}
		}
		return COLL_NOT_OK;
		break;
	case PLAYER_MOVE_RIGHT:
		// update location
		calcu = pl.getRecX() + speed;
		index_x = (calcu + Globals::item_size / 2) / Globals::item_size; //this index of 3 blocks forward are same value

		//check kind of block
		//if the player move in a row of map just check the forward block
		if ((pl.getRecY() - Globals::item_size / 2) % Globals::item_size == 0)
		{
			//get index forward block
			index_y = pl.getRecY() / Globals::item_size;
			forward_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//check kind block
			if (forward_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_RIGHT_REC);
				return COLL_OK;
			}
		}
		else	// else just check the forward_left_block and forware_right_block
		{
			//get index forward left block
			index_y = (pl.getRecY() - Globals::item_size / 2) / Globals::item_size;
			forward_left_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 
			//get index forward right block
			index_y = (pl.getRecY() + Globals::item_size / 2) / Globals::item_size;
			forward_right_block = ResourceManagers::GetInstance()->managerMap()->getItemMap(index_y * 14 + index_x);		//beacause you read map row y then col x 

			/*printf("Location player: %d , %d\n", pl.getRecX(), pl.getRecY());
			forward_left_block.showInfor();
			forward_right_block.showInfor();*/

			//check kind block
			if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD || forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
			{
				//cacul to smoothPlayer
				if (forward_left_block.getKindBlock() == MAP_ITEM_ROAD && forward_right_block.getKindBlock() != MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_RIGHT, pl, forward_left_block.getRect());
				else if (forward_left_block.getKindBlock() != MAP_ITEM_ROAD && forward_right_block.getKindBlock() == MAP_ITEM_ROAD)
					smoothPLayer = smoothMovingPlayer(PLAYER_MOVE_RIGHT, pl, forward_right_block.getRect());
				/*printf("the value smoothPLayer func isCollBetweenPlayerAndItemMap = %d\n", smoothPLayer);
				printf("rec player : %d , %d\n", pl.getRecX(), pl.getRecY());
				printf("rec left : %d , %d\n", forward_left_block.getRect().getRecX(), forward_left_block.getRect().getRecY());
				printf("rec right : %d , %d\n", forward_right_block.getRect(), forward_right_block.getRect().getRecY());
				printf("==========/n");*/
				//cacul to go to end road
				distancePlaAndBarrier = pl.caculDistanceToAnotherRecWithDirection(forward_block.getRect(), ON_THE_RIGHT_REC);
				return COLL_OK;
			}
		}
		return COLL_NOT_OK;
		break;
	default:
		//return -1 if something wrong
		return -1;
		break;
	}
}

/*
* check the coll between enermy and item map
*/
int CollisionManager::isCollBetweenEnermyAndItemMap(MRectangle enermy)
{
	// get arr Item Map
	ItemMap* arrItemMap = ResourceManagers::GetInstance()->managerMap()->getArrayItemMap();
	// the range of arrItemMap is MAP_SIZE_X * MAP_SIZE_Y please fix this code if you have any idea to get the range throught the func or math, do not use like this for loop
	for (int i = 0; i < MAP_SIZE_X * MAP_SIZE_Y ; i++)
	{
		if (enermy.isInteract(arrItemMap[i].getRect()) == REC_ABOVE)
		{
			return COLL_OK;
		}
	}
	return COLL_NOT_OK;
}

/*
* return the distance from player to the road
*/
int CollisionManager::smoothMovingPlayer(int orient, MRectangle pl , MRectangle barrier)
{
	int cacul = 0;

	switch (orient)
	{
	case PLAYER_MOVE_LEFT: case PLAYER_MOVE_RIGHT:
		cacul = abs(pl.getRecY() - barrier.getRecY());
		if (cacul <= PLAYER_SMOOTH_MOVING) 
			return barrier.getRecY() - pl.getRecY() ;		// must use bari - pl because if you use pl - bari then + pl it will make you far over
		cacul = 0;	// reset cacul to return 
		break;
	case PLAYER_MOVE_UP: case PLAYER_MOVE_DOWN:
		cacul = abs(pl.getRecX() - barrier.getRecX());
		if (cacul <= PLAYER_SMOOTH_MOVING)
			return barrier.getRecX() - pl.getRecX();		// must use bari - pl because if you use pl - bari then + pl it will make you far over
		cacul = 0;	// reset cacul to return 
		break;
	default:
		break;
	}
	return cacul;
}