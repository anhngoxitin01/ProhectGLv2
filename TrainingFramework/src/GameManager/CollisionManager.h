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


	int isCollBetweenPlayerAndItemMap(MRectangle pl, int speed, int direction);		//this fun was run before change location of player

private:
};