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
	int			getLevelMap();
	std::list<Enermy>		getSponEnermy();

	void initMap();
	void checkMapInCMD();

	void		setMapLevel(int level);

private:
	void readMapFromFile(char* namePath, ItemMap map_items[]);
	void setMapSponPlayer(int x, int y);
	
	ItemMap		map_items[MAP_SIZE_Y * MAP_SIZE_Y];
	int			map_spon_player_x;
	int			map_spon_player_y;

	int			map_level;

	std::list<Enermy>  map_enermies;
	
};