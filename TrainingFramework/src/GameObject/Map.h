#pragma once
#include <map>
#include <stdio.h>
#include <string>
#include"GameConfig.h"
#include "ItemMap.h"


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

	void initMap(int level);
	void checkMapInCMD();

private:
	void readMapFromFile(char* namePath, ItemMap map_items[]);
	void setMapSponPlayer(int x, int y);
	
	ItemMap		map_items[MAP_SIZE_Y * MAP_SIZE_Y];
	int			map_spon_player_x;
	int			map_spon_player_y;

	
	
};