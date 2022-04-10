#pragma once
#include"MRectangle.h"
#include"GameConfig.h"


class ItemPlayer {
public:
	ItemPlayer();
	ItemPlayer(int kind, MRectangle rec);
	~ItemPlayer();

	MRectangle			getRect();
	int					getKind();
	int					getStatus();
	std::string			getPathTextureObjectPlayer();
	void				show();

	void				setRec(MRectangle rec);
	void				setKind(int kind);
	void				setStatus(int status);
	void				setPathTextureObjectPlayer(std::string texture);

private:
	MRectangle	ip_rec;
	int			ip_kind;
	int			ip_status;
	std::string	ip_pathTextureBoom;
};