#include "ItemPlayer.h"

ItemPlayer::ItemPlayer()
{

}

ItemPlayer::ItemPlayer(int kind, MRectangle rec)
{
	ip_kind = kind;
	ip_rec = rec;
	ip_status = STATUS_LIVE;

	switch (kind)
	{
	case ITEMPL_KIND_BOMB:
		ip_pathTextureBoom = "item_bomb.tga";
		break;
	case ITEMPL_KIND_BOMBSIZE:
		ip_pathTextureBoom = "item_bombsize.tga";
		break;
	case ITEMPL_KIND_SHOE:
		ip_pathTextureBoom = "item_shoe.tga";
		break;
	default:
		printf("can not set pathtexture for this item player\n");
		break;
	}
}

ItemPlayer::~ItemPlayer()
{
}

MRectangle ItemPlayer::getRect()
{
	return ip_rec;
}

int ItemPlayer::getKind()
{
	return ip_kind;
}

int ItemPlayer::getStatus()
{
	return ip_status;
}

std::string ItemPlayer::getPathTextureObjectPlayer()
{
	return ip_pathTextureBoom;
}

void ItemPlayer::show()
{
	printf("Item player: rec:%d, %d || kind: %d || status: %d || pathTexture: %s\n"
		, ip_rec.getRecX()
		, ip_rec.getRecY()
		, ip_kind
		, ip_status
		, ip_pathTextureBoom.c_str());
}

void ItemPlayer::setRec(MRectangle rec)
{
	ip_rec = rec;
}

void ItemPlayer::setKind(int kind)
{
	ip_kind = kind;
}

void ItemPlayer::setStatus(int status)
{
	ip_status = status;
}

void ItemPlayer::setPathTextureObjectPlayer(std::string texture)
{
	ip_pathTextureBoom = texture;
}
