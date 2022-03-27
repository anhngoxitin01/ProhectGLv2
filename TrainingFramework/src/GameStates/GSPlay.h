#pragma once
#include "GameStateBase.h"
#include "GameConfig.h"

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

	void	prepareForDrawingBackground(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingMap(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingText(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingPlayer(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingEnermy(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
	void	prepareForDrawingAnimation(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader);
    int		m_Test;

private:
	std::shared_ptr<Sprite2D>					m_background;
	std::shared_ptr<Text>						m_score;
	std::list<std::shared_ptr<GameButton>>		m_listButton;
	std::list<std::shared_ptr<SpriteAnimation>>	m_listAnimation;

	//key_board
	bool			m_key[5];	// define key in GameConfig in CustomKey
	

	//map
	std::list<std::shared_ptr<Sprite2D>>		m_list_items_map;
	int											m_map[14*14];			//not good must fix

	//player
	std::shared_ptr<Sprite2D>					m_player;

	//enermy
	std::list<std::shared_ptr<Sprite2D>>		m_list_enermies;

};

