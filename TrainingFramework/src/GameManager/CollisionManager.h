#pragma once
#include"GameConfig.h"
#include "GameManager/Singleton.h"
#include "GameManager/ResourceManagers.h"
#include"Map.h"

class CollisionManager : public CSingleton<CollisionManager> {
public:
	CollisionManager();
	~CollisionManager();


	int isCollBetweenPlayerAndItemMap(int plX, int plY, int speed, int direction);		//this fun was run before change location of player

private:
	void	caculateCenterPlayerForCollision(int basePlX, int basePlY, int& newPlX, int& newPlY);
	int		getKindBlockPlayer(int kindBlock);
};