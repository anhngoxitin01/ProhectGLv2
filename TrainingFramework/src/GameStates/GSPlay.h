#pragma once
#include "GameStateBase.h"
#include "GameConfig.h"
#include "CollisionManager.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

	void	autoMovingEnermy(float deltaTime);
	void	autoIncreaseTimeBoom();
	/*in this func it also have the checkColl wb
	* with itemMap and destroy it 
	*/
	void	generateLocationWaterBoom(Boom *boom);
	void	checkcollEnermyAndWaterBoom();
	void	checkcollWaterBoomAndPlayer(Boom *boom);
	void	generateItemMap();
	void	generateItemPlayer(MRectangle rec);

	void	prepareForDrawingBackgroundScore();
	void	prepareForDrawingBackgroundGamepLay();
	void	prepareForDrawingMap();
	void	prepareForDrawingButton();
	void	prepareForDrawingPlayer();
	void	updateDrawEnermy(Enermy* enermy);
	void	prepareForDrawingBoomExplore();
	void	updateForDrawingItemPlayer();
	void	prepareForDrawingWaterBoom(Boom *boom);
	void	prepareForDrawingAnimationBoom();
	void	updateDrawMap();
	void	updateDrawScore();

	void    removeDrawingAnimationBoom();
	void	handlingKeyEventForPlayer(bool isMoving , int directionMove , bool isInitingBoom);
	void	increaseScore();

    int		m_Test;

private:
	std::shared_ptr<Sprite2D>					m_gameplayBackground;
	std::shared_ptr<Sprite2D>					m_scoreBackground;
	std::shared_ptr<Text>						m_scoreText;
	std::list<std::shared_ptr<GameButton>>		m_listButton;

	//time
	float	m_time_update_boom;

	//score
	int		m_score;

	//key_board
	int			m_KeyPress;
	
	//map
	std::list<std::shared_ptr<Sprite2D>>		m_listItemsMap;
	int											m_map[14*14];			//not good must fix now it just denpend on MAP_SIZE

	//player
	std::shared_ptr<Sprite2D>					m_player;

	//enermy
	std::map<int, std::shared_ptr<SpriteAnimation>> m_mapAniamtionEnermies;

	//Item Player
	std::list<std::shared_ptr<Sprite2D>>		m_listItemPlayer;

	//boom
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimationBoom;
	std::list<std::shared_ptr<Sprite2D>>		m_listBoomExplode;

};

