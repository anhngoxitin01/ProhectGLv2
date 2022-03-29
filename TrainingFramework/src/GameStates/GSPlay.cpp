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




GSPlay::GSPlay() : m_time_enermy_moving(0.0f)
{

}


GSPlay::~GSPlay() 
{
	
}


void GSPlay::Init()
{
	m_Test = 1;
	m_KeyPress = 0;
	// create model , texture and shader
	/*auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");*/

	//draw background
	prepareForDrawingBackground();
	//draw Map
	prepareForDrawingMap();
	//draw Enermy
	prepareForDrawingEnermy();
	//draw PLayer
	prepareForDrawingPlayer();
	//draw Button
	prepareForDrawingButton();
	//draw Text
	prepareForDrawingText();
	//draw Animation
	prepareForDrawingAnimation();
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
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_DOWN:
			m_KeyPress |= 1 << 1;
			break;
		case KEY_RIGHT:
			m_KeyPress |= 1 << 2;
			break;
		case KEY_UP:
			m_KeyPress |= 1 << 3;
			break;
		case KEY_SPACE:
			m_KeyPress |= 1 << 4;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_DOWN:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_UP:
			m_KeyPress ^= 1 << 3;
			break;
		case KEY_SPACE:
			m_KeyPress ^= 1 << 4;
			ResourceManagers::GetInstance()->managerPlayer()->setPrepateNextBoom(true);
			break;
		default:
			break;
		}

		ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(false);
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
	m_time_enermy_moving += deltaTime;

	//process key input
	if(ResourceManagers::GetInstance()->managerPlayer()->getPlayerStatusLive() == STATUS_LIVE)
	{
		switch (m_KeyPress)//Handle Key event
		{
		case 1://Key Left
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_LEFT);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_LEFT);
			break;
		case 1 << 1://Key Down
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_DOWN);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_DOWN);
			break;
		case 1 << 2://Key Right
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_RIGHT);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_RIGHT);
			break;
		case 1 << 3://Key Up
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_UP);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_UP);
			break;
		case 1 << 4://Key Space
			//TODO init boom
			ResourceManagers::GetInstance()->managerPlayer()->initBoom();
			prepareForDrawingBoom();
			break;
		case (1 | 1 << 4)://Key Left & Space
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_LEFT);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_LEFT);
			ResourceManagers::GetInstance()->managerPlayer()->initBoom();
			break;
		case (1 << 1 | 1 << 4)://Key Down & Space
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_DOWN);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_DOWN);
			ResourceManagers::GetInstance()->managerPlayer()->initBoom();
			break;
		case (1 << 2 | 1 << 4)://Key Right & Space
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_RIGHT);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_RIGHT);
			ResourceManagers::GetInstance()->managerPlayer()->initBoom();
			break;
		case (1 << 3 | 1 << 4)://Key Up & Space
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(true);
			ResourceManagers::GetInstance()->managerPlayer()->movePlayer(PLAYER_MOVE_UP);
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(PLAYER_MOVE_UP);
			ResourceManagers::GetInstance()->managerPlayer()->initBoom();
			break;
		}
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}

	//make enermy auto moving
	autoMovingEnermy(deltaTime);

}

void GSPlay::Draw()
{
	//background
	m_background->Draw();
	
	//map
	for (auto it : m_listItemsMap)
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

	//Enermy
	for (auto it : m_listEnermies)
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
	else 
	{
		int playerX = ResourceManagers::GetInstance()->managerPlayer()->getPlayerLocationX();
		int playerY = ResourceManagers::GetInstance()->managerPlayer()->getPlayerLocationY();
		std::string texture;
		switch (ResourceManagers::GetInstance()->managerPlayer()->getPlayerDirection())
		{
		case PLAYER_MOVE_DOWN:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_DOWN);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			m_player->Set2DPosition(playerX, playerY);
			break;
		case PLAYER_MOVE_UP:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_UP);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			m_player->Set2DPosition(playerX, playerY);
			break;
		case PLAYER_MOVE_RIGHT:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_RIGHT);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			m_player->Set2DPosition(playerX, playerY);
			break;
		case PLAYER_MOVE_LEFT:
			texture = ResourceManagers::GetInstance()->managerPlayer()->getPlayerTextureStading(PLAYER_MOVE_LEFT);
			m_player->SetTexture(ResourceManagers::GetInstance()->GetTexture(texture));
			m_player->Set2DPosition(playerX, playerY);
			break;
		default:
			break;
		}
	}

	//boom
	for (auto it : m_listBoom)
	{
		it->Draw();
	}

	m_player->Draw();
}

void GSPlay::autoMovingEnermy(float deltaTime)
{
	//create a rect to save new rect of enermy after testing move enermy
	MRectangle tempRect;

	if (m_time_enermy_moving >= TIME_ENERMY_MOVING)
	{
		//create index to update enermy through func changeStatusEnermy()
		int index = 0;
		//create temp list enermy
		std::list<Enermy> tempListEnermy;

		for each (auto it in *ResourceManagers::GetInstance()->managerEnermy())
		{
			switch (it.getDirection())
			{
			case ENERMY_MOVE_DOWN:
				tempRect = MRectangle(it.getRect().getRecX(), it.getRect().getRecY() + it.getSpeed(), Globals::item_size, Globals::item_size);
				//check collision with item map
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK 
					&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
					it.setEnermyLocation(it.getLocationX(), it.getLocationY() + it.getSpeed());
				else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
					|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					it.setEnermyDirection(ENERMY_MOVE_LEFT);
				//check collision with player
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
					ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
				break;
			case ENERMY_MOVE_UP:
				// create a new rect after move enermy to test
				tempRect = MRectangle(it.getRect().getRecX(), it.getRect().getRecY() - it.getSpeed(), Globals::item_size, Globals::item_size);
				//check collision
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
					&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
					it.setEnermyLocation(it.getLocationX(), it.getLocationY() - it.getSpeed());
				else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
					|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					it.setEnermyDirection(ENERMY_MOVE_RIGHT);
				//check collision with player
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
					ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
				break;
			case ENERMY_MOVE_RIGHT:
				// create a new rect after move enermy to test
				tempRect = MRectangle(it.getRect().getRecX() + it.getSpeed(), it.getRect().getRecY(), Globals::item_size, Globals::item_size);
				//check collision
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
					&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
					it.setEnermyLocation(it.getLocationX() + it.getSpeed(), it.getLocationY());
				else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
					|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					it.setEnermyDirection(ENERMY_MOVE_DOWN);
				//check collision with player
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
					ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
				break;
			case ENERMY_MOVE_LEFT:
				// create a new rect after move enermy to test
				tempRect = MRectangle(it.getLocationX() - it.getSpeed(), it.getRect().getRecY() , Globals::item_size, Globals::item_size);
				//check collision
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
					&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
					it.setEnermyLocation(it.getLocationX() - it.getSpeed(), it.getLocationY() );
				else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
					|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					it.setEnermyDirection(ENERMY_MOVE_UP);
				//check collision with player
				if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
					ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
				break;
			default:
				break;
			}

			//add enermy to templist
			tempListEnermy.push_back(it);
		}
		//update value in list ResourceManager
		ResourceManagers::GetInstance()->managerEnermy()->swap(tempListEnermy);
		//update value texture for draw in map 
		prepareForDrawingEnermy();

		//reset timing for enermy
		m_time_enermy_moving = 0;
	}
}

void GSPlay::prepareForDrawingBackground()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(700 / 2, 700 / 2);
	m_background->SetSize(Globals::item_size * 12, Globals::item_size * 12);
}

void GSPlay::prepareForDrawingMap()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//read map from file
	ResourceManagers::GetInstance()->managerMap()->setMapLevel(MAP_LEVEL_1);
	ResourceManagers::GetInstance()->managerMap()->initMap();
	//create item_map sprite2D
	std::shared_ptr<Sprite2D> item_map = std::make_shared<Sprite2D>(model, shader, texture);
	//create valuable for draw map
	std::string pathTexture;
	int item_x;
	int item_y;
	//use for to add texture to m_list_item_map
	for (int i = 0; i < MAP_SIZE_Y * MAP_SIZE_Y; i++)
	{
			pathTexture = ResourceManagers::GetInstance()->managerMap()->getTextureMapItem(i);
			item_x = ResourceManagers::GetInstance()->managerMap()->getRectItem(i).getRecX();
			item_y = ResourceManagers::GetInstance()->managerMap()->getRectItem(i).getRecY();
			if (pathTexture.compare("") != 0)
			{
				texture = ResourceManagers::GetInstance()->GetTexture(pathTexture);
				item_map = std::make_shared<Sprite2D>(model, shader, texture);
				item_map->Set2DPosition(item_x, item_y);
				item_map->SetSize(Globals::item_size, Globals::item_size);
				m_listItemsMap.push_back(item_map);
			}
	}
	//set spon for player through var (get from read text) to player
	ResourceManagers::GetInstance()->autoSetSponToPlayerFromMap();
	//set spon for enermy through var (get from read text) to player
	ResourceManagers::GetInstance()->autoSetSponToEnermyFromMap();
}

void GSPlay::prepareForDrawingButton()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");

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

void GSPlay::prepareForDrawingText()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//score
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(Globals::screenWidth - Globals::menuGPWidth + 50, 25));
}

void GSPlay::prepareForDrawingPlayer()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	int playerX = ResourceManagers::GetInstance()->managerPlayer()->getPlayerLocationX();
	int playerY = ResourceManagers::GetInstance()->managerPlayer()->getPlayerLocationY();

	texture = ResourceManagers::GetInstance()->GetTexture("bomber_down.tga");
	m_player = std::make_shared<GameButton>(model, shader, texture);
	m_player->Set2DPosition(playerX, playerY);
	// must change it
	m_player->SetSize(PLAYER_SIZE_X, PLAYER_SIZE_Y);
}

void GSPlay::prepareForDrawingEnermy()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create enermy sprite2D
	std::shared_ptr<Sprite2D> enermySprite2D = std::make_shared<Sprite2D>(model, shader, texture);

	//reset the m_list_enermies
	m_listEnermies.clear();

	//get element in list enermy from ResourceManagers
	for (Enermy it : *ResourceManagers::GetInstance()->managerEnermy())
	{
		texture = ResourceManagers::GetInstance()->GetTexture(it.getPathTexture());
		enermySprite2D = std::make_shared<Sprite2D>(model, shader, texture);
		enermySprite2D->Set2DPosition(it.getLocationX(), it.getLocationY());
		enermySprite2D->SetSize(it.getSizeX(), it.getSizeY());
		m_listEnermies.push_back(enermySprite2D);
	}
}

void GSPlay::prepareForDrawingBoom()
{
	//creat model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create boom sprite2D
	std::shared_ptr<Sprite2D> boomSprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	
	//clear mListBoom
	m_listBoom.clear();

	//add sprinte2D to list to draw
	for (Boom it : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
	{
		texture = ResourceManagers::GetInstance()->GetTexture(it.getPathTexture(0));
		boomSprite2D = std::make_shared<Sprite2D>(model, shader, texture);
		boomSprite2D->Set2DPosition(it.getRect().getRecX(), it.getRect().getRecY());
		boomSprite2D->SetSize(it.getRect().getRecWidth(), it.getRect().getRecLength());
		m_listBoom.push_back(boomSprite2D);
	}
	
}

void GSPlay::prepareForDrawingAnimation()
{
	//creat model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");

	texture = ResourceManagers::GetInstance()->GetTexture("Actor1_2.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 9, 6, 5, 0.1f);

	obj->Set2DPosition(240, 400);
	obj->SetSize(334, 223);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	m_listAnimation.push_back(obj);
}

