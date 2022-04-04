#pragma once
#include <string>
#include "GameConfig.h"
#include "MRectangle.h"
#include "GameObject/Texture.h"

class ItemMap {
public:
	ItemMap();
	~ItemMap();

	void		setRect(MRectangle MR);
	void		setKindBlock(int kind);
	void		setPathTexture(std::string pathTexture);
	void		setAllValue(int x, int y, std::string pathTexture, int kind);		// rectangle will auto create in this func

	MRectangle					getRect();
	std::string					getPathTexture();
	int							getKindBlock();

	void						showInfor();
	void						changeToRoadItem();
private:
	std::string					im_path_texture;
	MRectangle					im_rect;
	int							im_kind_block;
};