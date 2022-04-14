#pragma once
#include <map>
#include <stdio.h>
#include <string>
#include "GameConfig.h"
#include "ItemMap.h"
#include "Enermy.h"


class Map
{
public:
	Map();
	~Map();

	std::string getTextureMapItem(int index);
	void		getSponPlayerByValue(int &x , int &y);
	int			getKindOfBlock(int index_x, int index_y);
	MRectangle	getRectItem(int index);
	ItemMap		getItemMap(int index);
	std::list<Enermy*>*		getSponEnermy();
	ItemMap*	getArrayItemMap();

	void clearData();

	void initMap(int map_level);
	void checkMapInCMD();
	void checkEnermies();

private:
	void readMapFromFile(char* namePath, ItemMap map_items[]);
	void setMapSponPlayer(int x, int y);
	
	ItemMap		map_items[MAP_SIZE_Y * MAP_SIZE_Y];
	int			map_spon_player_x;
	int			map_spon_player_y;

	std::list<Enermy*>  map_enermies;
	
};