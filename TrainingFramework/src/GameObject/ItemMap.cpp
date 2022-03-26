#include "ItemMap.h"


ItemMap::ItemMap()
{
}

ItemMap::~ItemMap()
{
}

void ItemMap::setRect(MRectangle MR)
{
	im_rect = MR;
}

void ItemMap::setKindBlock(int kind)
{
	im_kind_block = kind;
}

void ItemMap::setPathTexture(std::string pathTexture)
{
	im_path_texture = pathTexture;
}

void ItemMap::setAllValue(int x, int y, std::string pathTexture, int kind)
{
	im_path_texture = pathTexture;
	im_kind_block = kind;
	im_rect = MRectangle(x, y, Globals::item_size, Globals::item_size);
}

MRectangle ItemMap::getRect()
{
	return im_rect;
}

std::string ItemMap::getPathTexture()
{
	return im_path_texture;
}

int ItemMap::getKindBlock()
{
	return im_kind_block;
}

void ItemMap::showInfor()
{
	printf("location: %d,%d || texture = %s || kind = ", im_rect.getRecX(), im_rect.getRecY(), im_path_texture.c_str());
	switch (im_kind_block)
	{
	case MAP_ITEM_CAN_DESTROY:
		printf("MAP_ITEM_CAN_DESTROY");
		break;
	case MAP_ITEM_CAN_NOT_DESTROY:
		printf("MAP_ITEM_CAN_NOT_DESTROY");
		break;
	case MAP_ITEM_ROAD:
		printf("MAP_ITEM_ROAD");
		break;
	default:
		break;
	}
	printf("\n");
}
