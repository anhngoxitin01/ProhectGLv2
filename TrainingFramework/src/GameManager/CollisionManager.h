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
	/*This fun will change the parameter boomIdIsStanding*/
	int	isCollBetweenPlayerAndBoom(MRectangle pl , int &boomIdIsStanding);
	int	isCollBetweenPlayerAndBoom(MRectangle pl , MRectangle boom);

	//enermy
	int isCollBetweenEnermyAndItemMap(MRectangle enermy);
	int isCollBetweenEnermyAndPlayer(MRectangle enermy);
	int isCollBetweenEnermyAndBoom(MRectangle enermy);
	int isCollBetweenEnermyAndWaterBoom(MRectangle enermyRec);
	
	//waterBoom
	int isCollBetweenWaterBoomAndItemMap(MRectangle waterBoom, int &indexMap);
	int isCollBetweenWaterBoomAndItemPlayer(MRectangle waterBoomRec);
	int	isCollBetweenWaterBoomAndBoom(MRectangle wbRec , int timeBoomExplore);
	int isCollBetweenWaterBoomAndPlayer(MRectangle wbRec);

private:
	int smoothMovingPlayer(int orient, MRectangle pl, MRectangle barrier);
};