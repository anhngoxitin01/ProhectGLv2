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
	void	generateLocationWaterBoom(Boom &boom);
	void	checkcollWaterBoomAndEnermy();
	void	generateItemMap();
	void	generateItemPlayer(MRectangle rec);

	void	prepareForDrawingBackground();
	void	prepareForDrawingMap();
	void	prepareForDrawingButton();
	void	prepareForDrawingText();
	void	prepareForDrawingPlayer();
	void	prepareForDrawingEnermy();
	void	prepareForDrawingBoom();
	void	prepareForDrawingItemPlayer();
	void	prepareForDrawingWaterBoom(Boom *boom);
	void	prepareForDrawingAnimation();
	void	updateDrawMap();

    int		m_Test;

private:
	std::shared_ptr<Sprite2D>					m_background;
	std::shared_ptr<Text>						m_score;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

	//time
	float	m_time_enermy_moving;
	float	m_time_update_boom;

	//key_board
	int			m_KeyPress;
	
	//map
	std::list<std::shared_ptr<Sprite2D>>		m_listItemsMap;
	int											m_map[14*14];			//not good must fix now it just denpend on MAP_SIZE

	//player
	std::shared_ptr<Sprite2D>					m_player;

	//enermy
	std::list<std::shared_ptr<Sprite2D>>		m_listEnermies;

	//Item Player
	std::list<std::shared_ptr<Sprite2D>>		m_listItemPlayer;

	//boom
	std::list<std::shared_ptr<Sprite2D>>		m_listBoom;
	std::list<std::shared_ptr<Sprite2D>>		m_listBoomExplode;

};

