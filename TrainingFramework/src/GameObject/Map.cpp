#include "Map.h"

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
	return map_items[index].getPathTexture();
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
		return map_items[index_y * 14 + index_x].getKindBlock();
	}
}

MRectangle Map::getRectItem(int index)
{
	return map_items[index].getRect();
}

ItemMap Map::getItemMap(int index)
{
	return map_items[index];
}

int Map::getLevelMap()
{
	return map_level;
}

std::list<Enermy> Map::getSponEnermy()
{
	return map_enermies;
}

ItemMap* Map::getArrayItemMap()
{
	return map_items;
}



void Map::initMap()
{
	switch (map_level)
	{
	case MAP_LEVEL_1: case MAP_LEVEL_2: case MAP_LEVEL_3:
		readMapFromFile(PATHFILE_MAP_1 , map_items);
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
			printf("Item[%d] = " , i*14 + j);
			map_items[i * 14 + j].showInfor();
			printf("\n");
		}
	}
}

void Map::setMapLevel(int level)
{
	map_level = level;
}

void Map::readMapFromFile(char* namePath, ItemMap map_items[])
{
	//init temp enermy
	Enermy termEnermy;

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
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_item_bush.tga"
						, MAP_ITEM_CAN_DESTROY);
					break;
				case MAP_ITEM_TREE:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_item_tree.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_TOP_BORDER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_top_border.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_LEFT_BORDER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_left_border.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_RIGHT_BORDER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_right_border.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_BOTTOM_BORDER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_bottom_border.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_TOP_LEFT_CORNER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_top_left_corner.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_TOP_RIGHT_CORNER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_top_right_corner.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_BOTTOM_LEFT_CORNER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_bottom_left_corner.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_BOTTOM_RIGHT_CORNER:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, "map_bottom_right_corner.tga"
						, MAP_ITEM_CAN_NOT_DESTROY);
					break;
				case MAP_PLAYER_SPON:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, ""
						, MAP_ITEM_ROAD);
					setMapSponPlayer(j * Globals::item_size + Globals::item_size / 2, (i + 1) * Globals::item_size - PLAYER_SIZE_Y / 2);
					printf("spon location plyer: x= %d, y=%d\n", j * Globals::item_size + Globals::item_size / 2, (i + 1) * Globals::item_size - PLAYER_SIZE_Y / 2);
					break;
				case MAP_NOTHING:
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, ""
						, MAP_ITEM_ROAD);
					break;
				case MAP_ENERMY_SPON:
					termEnermy.initEnermy(
						j * Globals::item_size + Globals::item_size / 2
						, (i + 1) * Globals::item_size - ENERMY_SIZE_Y / 2
						, ENERMY_SIZE_X
						, ENERMY_SIZE_Y
						, ENERMY_MOVE_DOWN
					);
					map_items[i * 14 + j].setAllValue(
						j * Globals::item_size + Globals::item_size / 2
						, i * Globals::item_size + Globals::item_size / 2
						, ""
						, MAP_ITEM_ROAD);
					map_enermies.push_back(termEnermy);
					break;
				default:
					printf("Can not read map");
					break;
				}
			}
			fscanf(fptr, "\n");
		}
	}
	fclose(fptr);

	checkMapInCMD();
}

void Map::setMapSponPlayer(int x, int y)
{
	map_spon_player_x = x;
	map_spon_player_y = y;
}
