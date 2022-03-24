#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"




GSPlay::GSPlay()
{

}


GSPlay::~GSPlay()
{
	
}


void GSPlay::Init()
{
	m_Test = 1;
	// create model , texture and shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//draw background
	prepareForDrawingBackground(model , texture , shader);
	//draw Map
	prepareForDrawingMap(model, texture, shader);
	//draw PLayer
	prepareForDrawingPlayer(model, texture, shader);
	//draw Button
	prepareForDrawingButton(model, texture, shader);
	//draw Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	prepareForDrawingText(model, texture, shader);
	//draw Animation
	prepareForDrawingAnimation(model, texture, shader);
}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if(bIsPressed)
	{
		switch (key)
		{
		case KEY_DOWN:
			printf("press down\n");
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_DOWN);
			break;
		case KEY_UP:
			printf("press up\n");
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_UP);
			break;
		case KEY_RIGHT:
			printf("press right\n");
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_RIGHT);
			break;
		case KEY_LEFT:
			printf("press left\n");
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_LEFT);
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	//background
	m_background->Draw();
	
	//map
	for (auto it : m_list_items_map)
	{
		it->Draw();
	}

	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}

	//text
	m_score->Draw();

	//Player 
	if (!ResourceManagers::GetInstance()->managerPlayer()->isPlayerMoving())
	{
		std::string texture;
		switch (ResourceManagers::GetInstance()->managerPlayer()->getPlayerDirection())
		{
		case PLAYER_MOVE_DOWN:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_DOWN);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			break;
		case PLAYER_MOVE_UP:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_UP);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			break;
		case PLAYER_MOVE_RIGHT:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_RIGHT);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			break;
		case PLAYER_MOVE_LEFT:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_LEFT);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			break;
		default:
			break;
		}
	}

	m_player->Draw();
}

void GSPlay::prepareForDrawingBackground(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(700 / 2, 700 / 2);
	m_background->SetSize(Globals::item_size * 12, Globals::item_size * 12);
}

void GSPlay::prepareForDrawingMap(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{

	//read file
	ResourceManagers::GetInstance()->readMapFromFile(PATHFILE_MAP_1, m_map);
	//check map in cmd
	for (int i = 0; i < Globals::rowMap * Globals::colMap; i++)
	{
		if (i % Globals::colMap == 0)
			printf("\n");
		printf("%d", m_map[i]);
	}
	//create item_map shader
	std::shared_ptr<Sprite2D> item_map = std::make_shared<Sprite2D>(model, shader, texture);
	//run for to add item map
	for (int i = 0; i < Globals::rowMap * Globals::colMap; i++)
	{
		switch (m_map[i])
		{
		case MAP_TOP_LEFT_CORNER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_top_left_corner.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_TOP_RIGHT_CORNER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_top_right_corner.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_BOTTOM_LEFT_CORNER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_bottom_left_corner.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_BOTTOM_RIGHT_CORNER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_bottom_right_corner.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_TOP_BORDER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_top_border.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_BOTTOM_BORDER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_bottom_border.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_LEFT_BORDER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_left_border.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_RIGHT_BORDER:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_right_border.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_ITEM_TREE:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_item_tree.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		case MAP_ITEM_BUSH:
		{
			texture = ResourceManagers::GetInstance()->GetTexture("map_item_bush.tga");
			item_map = std::make_shared<Sprite2D>(model, shader, texture);
			item_map->Set2DPosition(Globals::item_size * (i % Globals::colMap) + Globals::item_size / 2
				, Globals::item_size * (i / Globals::rowMap) + Globals::item_size / 2);
			item_map->SetSize(Globals::item_size, Globals::item_size);
			m_list_items_map.push_back(item_map);
			break;
		}
		default:
			break;
		}
	}
}

void GSPlay::prepareForDrawingButton(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{
	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition((float)Globals::screenWidth - 25, 25);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSPlay::prepareForDrawingText(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{
	//score
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(Globals::screenWidth - Globals::menuGPWidth + 50, 25));
}

void GSPlay::prepareForDrawingPlayer(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{
	texture = ResourceManagers::GetInstance()->GetTexture("bomber_down.tga");
	m_player = std::make_shared<GameButton>(model, shader, texture);
	m_player->Set2DPosition(50, 50);
	// must change it
	m_player->SetSize(Globals::item_size, Globals::item_size + 25);
}

void GSPlay::prepareForDrawingAnimation(std::shared_ptr<Model> model, std::shared_ptr<Texture> texture, std::shared_ptr<Shader> shader)
{
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Actor1_2.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 6, 5, 0.1f);

	obj->Set2DPosition(240, 400);
	obj->SetSize(334, 223);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	m_listAnimation.push_back(obj);
}
