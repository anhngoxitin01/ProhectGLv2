#pragma once
#include <map>
#include <stdio.h>
#include <string>

//define map
#define PATHFILE_MAP_1			"..\\Data\\Map\\map1.txt"
#define MAP_SIZE_X				14
#define MAP_SIZE_Y				14
#define MAP_TOP_LEFT_CORNER		48					//so 0
#define MAP_TOP_RIGHT_CORNER	49					//so 1
#define MAP_BOTTOM_LEFT_CORNER	50					//so 2
#define MAP_BOTTOM_RIGHT_CORNER	51					//so 3
#define MAP_TOP_BORDER			52					//so 4
#define MAP_LEFT_BORDER			53					//so 5
#define MAP_BOTTOM_BORDER		54					//so 6
#define MAP_RIGHT_BORDER		55					//so 7
#define MAP_ITEM_TREE			56					//so 8
#define MAP_ITEM_BUSH			57					//so 9
#define MAP_PLAYER_SPON			63					//ki tu ?
#define MAP_NOTHING				111					//ki tu o

#define MAP_ITEM_CAN_DESTROY		0				//item which can be destroy
#define MAP_ITEM_CAN_NOT_DESTROY	1				//item which can not be destroy
#define MAP_ROAD					2				//item which is road

#define MAP_LEVEL_1					0
#define MAP_LEVEL_2					1
#define MAP_LEVEL_3					2


class Map
{
public:
	Map();
	~Map();

	std::string getTextureMapItem(int index);
	void getSponPlayerByValue(int &x , int &y);

	void initMap(int level);
	void checkMapInCMD();

private:
	void readMapFromFile(char* namePath, int arr[][2], std::string arrTexture[]);
	void setMapSponPlayer(int x, int y);
	
	int			map_items[MAP_SIZE_Y * MAP_SIZE_Y][2];				// save kind of each item
	std::string map_items_texture[MAP_SIZE_Y * MAP_SIZE_Y];			// save texture for each item in map_items
	int			map_spon_player_x;
	int			map_spon_player_y;
	
};