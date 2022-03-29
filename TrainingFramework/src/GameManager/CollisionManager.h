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


	int isCollBetweenPlayerAndItemMap(MRectangle pl, int speed, int direction , int &distancePlaAndBarrier , int& smoothPlayer);		//this func was run before change location of player

	int isCollBetweenEnermyAndItemMap(MRectangle enermy);
	int isCollBetweenEnermyAndPlayer(MRectangle enermy);

private:
	int smoothMovingPlayer(int orient, MRectangle pl, MRectangle barrier);
};