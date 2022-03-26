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
int CollisionManager::isCollBetweenPlayerAndItemMap(MRectangle pl, int speed, int direction, int& distancePlaAndBarrier)
{
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

