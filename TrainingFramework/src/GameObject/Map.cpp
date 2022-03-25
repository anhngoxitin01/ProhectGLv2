#include "Map.h"
#include "GameConfig.h"

Map::Map()
{
}

Map::~Map()
{
}

std::string Map::getTextureMapItem(int index)
{
	if (index < 0 || index >= MAP_SIZE_Y * MAP_SIZE_X)
		return "";
	return map_items_texture[index];
}

void Map::getSponPlayerByValue(int& x, int& y)
{
	x = map_spon_player_x;
	y = map_spon_player_y;
}

/*
* return -1 for not found or another value if found it
*/
int Map::getKindOfBlock(int index_x, int index_y)
{
	if (index_x < 0 || index_x >= MAP_SIZE_X || index_y < 0 || index_y >= MAP_SIZE_Y)
	{
		//return -1 for all case not found
		return -1;
	}
	else {
		return map_items[index_y * 14 + index_x][0];
	}
}



void Map::initMap(int level)
{
	switch (level)
	{
	case MAP_LEVEL_1: case MAP_LEVEL_2: case MAP_LEVEL_3:
		readMapFromFile(PATHFILE_MAP_1 , map_items , map_items_texture);
		break;
	default:
		printf("Out range level to read map");
		break;
	}
}

void Map::checkMapInCMD()
{
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			printf("arr[%d][%d] = %d \t arr[%d][%d] = %d"
				, i * 14 + j
				, 0
				, map_items[i * 14 + j][0]
				, i * 14 + j
				, 1
				, map_items[i * 14 + j][1]);
		}
	}
}

void Map::readMapFromFile(char* namePath, int arr[][2] , std::string arrTexture[])
{
	char c[10];
	FILE* fptr;

	if ((fptr = fopen(namePath, "r")) == NULL)
	{
		printf("Error! opening file");
	}
	else
	{
		for (int i = 0 ; i < MAP_SIZE_Y ; i++)
		{
			for (int j = 0; j < MAP_SIZE_X; j++)
			{
				fscanf(fptr, "%c", c);
				switch (toascii(c[0]))
				{
				case MAP_ITEM_BUSH:
					arr[i * 14 + j][0] = MAP_ITEM_CAN_DESTROY;
					arrTexture[i * 14 + j] = "map_item_bush.tga";
					break;
				case MAP_ITEM_TREE: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_item_tree.tga";
					break;
				case MAP_TOP_BORDER: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_top_border.tga";
					break;
				case MAP_LEFT_BORDER:
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_left_border.tga";
					break;
				case MAP_RIGHT_BORDER: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_right_border.tga";
					break;
				case MAP_BOTTOM_BORDER:
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_bottom_border.tga";
					break;
				case MAP_TOP_LEFT_CORNER: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_top_left_corner.tga";
					break;
				case MAP_TOP_RIGHT_CORNER: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_top_right_corner.tga";
					break;
				case MAP_BOTTOM_LEFT_CORNER: 
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_bottom_left_corner.tga";
					break;
				case MAP_BOTTOM_RIGHT_CORNER:
					arr[i * 14 + j][0] = MAP_ITEM_CAN_NOT_DESTROY;
					arrTexture[i * 14 + j] = "map_bottom_right_corner.tga";
					break;
				case MAP_PLAYER_SPON:
					setMapSponPlayer(j * Globals::item_size + Globals::item_size/2, (i +1)  * Globals::item_size - PLAYER_SIZE_Y/2 );
					printf("spon location plyer: x= %d, y=%d\n", j * Globals::item_size + Globals::item_size / 2, (i + 1) * Globals::item_size - PLAYER_SIZE_Y / 2);
					arr[i * 14 + j][0] = MAP_ITEM_ROAD;
					break;
				case MAP_NOTHING:
					arr[i * 14 + j][0] = MAP_ITEM_ROAD;
					break;
				default:
					printf("Can not read map");
					break;
				}
				arr[i * 14 + j][1] = toascii(c[0]);
			}
			fscanf(fptr, "\n");
		}
	}

	fclose(fptr);
}

void Map::setMapSponPlayer(int x, int y)
{
	map_spon_player_x = x;
	map_spon_player_y = y;
}
