#pragma once
#include "GameConfig.h"
#include "GameManager/Singleton.h"
#include "GameManager/ResourceManagers.h"
#include "Map.h"
#include "MRectangle.h"

class CollisionManager : public CSingleton<CollisionManager> {
public:
	CollisionManager();
	~CollisionManager();

	//player
	int isCollBetweenPlayerAndItemMap(MRectangle pl, int speed, int direction , int &distancePlaAndBarrier , int& smoothPlayer);		//this func was run before change location of player
	int isCollBetweenPlayerAndItemPlayer(MRectangle pl , int &kindItem);

	//enermy
	int isCollBetweenEnermyAndItemMap(MRectangle enermy);
	int isCollBetweenEnermyAndPlayer(MRectangle enermy);
	int isCollBetweenEnermyAndBoom(MRectangle enermy);
	int isCollBetweenEnermyAndWaterBoom(MRectangle enermyRec);
	
	//waterBoom
	int isCollBetweenWaterBoomAndItemMap(MRectangle waterBoom, int &indexMap);
	int isCollBetweenWaterBoomAndItemPlayer(MRectangle waterBoomRec);
	int	isCollBetweenWaterBoomAndBoom(MRectangle wbRec , int timeBoomExplore);

private:
	int smoothMovingPlayer(int orient, MRectangle pl, MRectangle barrier);
};