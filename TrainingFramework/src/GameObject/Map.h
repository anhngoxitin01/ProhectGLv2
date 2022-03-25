#pragma once
#include <map>
#include <stdio.h>
#include <string>
#include"GameConfig.h"



class Map
{
public:
	Map();
	~Map();

	std::string getTextureMapItem(int index);
	void getSponPlayerByValue(int &x , int &y);
	int getKindOfBlock(int index_x, int index_y);

	void initMap(int level);
	void checkMapInCMD();

private:
	void readMapFromFile(char* namePath, int arr[][2], std::string arrTexture[]);
	void setMapSponPlayer(int x, int y);
	
	int			map_items[MAP_SIZE_Y * MAP_SIZE_Y][2];				// save kind of each item  [kind item][acsii]
	std::string map_items_texture[MAP_SIZE_Y * MAP_SIZE_Y];			// save texture for each item in map_items
	int			map_spon_player_x;
	int			map_spon_player_y;
	
};