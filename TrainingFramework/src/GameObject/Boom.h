#pragma once
#include"MRectangle.h"
#include "WaterBoom.h"
//#include "CollisionManager.h"
#include<GameConfig.h>
#include<string>
#include<list>

class Boom {
public:
	Boom();
	~Boom();

	std::string			getPathTextureBoom(int index);
	MRectangle			getRect();
	int					getPower();
	int					getIndexBoomExploding();
	float				getTimeExploding();
	int					getStatusBoom();
	std::list<WaterBoom> getListWaterBoom();

	void				setPower(int power);
	void				setRec(MRectangle rec);
	void				setTimeBoomExploding(float timeExploding);
	void				setIndexBoomExploding(int indexExploding);
	void				setStatusBoom(int statusBoom);

	void				increaseTimeBoom(float deltaTime);
	bool				canBoomExplode();
	MRectangle			calculateLocationGenerate(MRectangle playerRec);
	void				autoGenerateLocationWaterBoom();
	void				removeWaterBoom(WaterBoom wb);

private:
	MRectangle					b_rec;
	float						b_time_boom_exploding;
	std::string					b_pathTextureBoom[NUM_PATH_TEXTURE_BOOM];
	int							b_index_boom_exploding;
	int							b_power;
	int							b_status_boom;
	std::list<WaterBoom>		b_list_water_boom;
};
