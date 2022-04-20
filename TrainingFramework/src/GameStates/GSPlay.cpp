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

GSPlay::GSPlay() : m_time_update_boom(0.0f) , m_gameplayBackground(nullptr) , m_gameMenuBackground(nullptr) ,
				m_listButton(std::list<std::shared_ptr<GameButton>>{}) , m_levelText(nullptr) , m_state_game(STATE_PLAYING) , m_completeBackground(nullptr)
{
	ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_LIVE);
	ResourceManagers::GetInstance()->setLevelMap(MAP_LEVEL_1);
}

GSPlay::~GSPlay() 
{
	
}

void GSPlay::Init()
{
	m_Test = 1;
	m_KeyPress = 0;

	//draw background
	prepareForDrawingBackgroundGamepLay();
	prepareForDrawingBackgroundGameMenu();
	//draw Map
	prepareForDrawingMap();
	//draw PLayer
	prepareForDrawingPlayer();
	//draw heartBoss
	if (ResourceManagers::GetInstance()->managerBoss() != nullptr)
		updateDrawHeartBoss();
	//draw Button
	prepareForDrawingButtonNormal();
	//draw Text
	updateTextDrawLevelMap();
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
	if (m_state_game == STATE_PLAYING)
	{
		if (ResourceManagers::GetInstance()->managerPlayer()->getPlayerStatusLive() == STATUS_LIVE)
		{
			m_time_update_boom += deltaTime;

			//process key input
			switch (m_KeyPress)//Handle Key event
			{
			case 1://Key Left
				handlingKeyEventForPlayer(true, PLAYER_MOVE_LEFT, false);
				break;
			case 1 << 1://Key Down
				handlingKeyEventForPlayer(true, PLAYER_MOVE_DOWN, false);
				break;
			case 1 << 2://Key Right
				handlingKeyEventForPlayer(true, PLAYER_MOVE_RIGHT, false);
				break;
			case 1 << 3://Key Up
				handlingKeyEventForPlayer(true, PLAYER_MOVE_UP, false);
				break;
			case 1 << 4://Key Space
				ResourceManagers::GetInstance()->managerPlayer()->initBoom();
				break;
			case (1 | 1 << 4)://Key Left & Space
				handlingKeyEventForPlayer(true, PLAYER_MOVE_LEFT, true);
				break;
			case (1 << 1 | 1 << 4)://Key Down & Space
				handlingKeyEventForPlayer(true, PLAYER_MOVE_DOWN, true);
				break;
			case (1 << 2 | 1 << 4)://Key Right & Space
				handlingKeyEventForPlayer(true, PLAYER_MOVE_RIGHT, true);
				break;
			case (1 << 3 | 1 << 4)://Key Up & Space
				handlingKeyEventForPlayer(true, PLAYER_MOVE_UP, true);
				break;
			}

			//update boom animation
			for (auto it : m_mapAnimationBoom)
			{
				it.second->Update(deltaTime);
			}

			//update enermy animation
			for (auto it : m_mapAniamtionEnermies)
			{
				it.second->Update(deltaTime);
			}

			//update boss animation
			for (auto it : m_mapAniamtionBoss)
			{
				it.second->Update(deltaTime);
			}

			if (ResourceManagers::GetInstance()->managerBoss() != nullptr)
			{
				//make boss moving
				autoMovingBoss(deltaTime);
			}
			
			//make enermy auto moving
			autoMovingEnermy(deltaTime);

			//make boom increase time to explode
			autoIncreaseTimeBoom();
		}
	}
	

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_gameMenuBackground->Draw();
	//level map 
	m_levelText->Draw();

	//background
	m_gameplayBackground->Draw();

	//map
	for (auto it : m_listItemsMap)
	{
		it->Draw();
	}

	//boom
	for (auto it : m_mapAnimationBoom)
	{
		it.second->Draw();
	}

	//water boom
	for (auto it : m_listBoomExplode)
	{
		it->Draw();
	}
	for (auto it : m_listBossBoomExplode)
	{
		it->Draw();
	}

	//itemPLayer
	for (auto it : m_listItemPlayer)
	{
		it->Draw();
	}

	//Enermy
	for (auto it : m_mapAniamtionEnermies)
	{
		it.second->Draw();
	}

	//Boss
	for (auto it : m_mapAniamtionBoss)
	{
		it.second->Draw();
	}
	for (auto it : m_listHeartBoss)
	{
		it->Draw();
	}

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
	m_player->Draw();

	if (m_state_game == STATE_GAME_OVER)
	{
		m_gameoverBackground->Draw();
	}
	
	if (m_state_game == STATE_COMPLETE_LEVEL)
	{
		m_completeBackground->Draw();
	}

	for (auto it : m_listButton)
	{
		if (it->GetName().compare("btn_volumn") == 0)
		{
			if (GameStateMachine::GetInstance()->isMute())
			{
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga"));
			}
			else
				it->SetTexture(ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga"));
		}
		it->Draw();
	}
}

void GSPlay::autoMovingEnermy(float deltaTime)
{
	//create a rect to save new rect of enermy after testing move enermy
	MRectangle tempRect;

	for (auto enermy : *ResourceManagers::GetInstance()->managerEnermy())
	{
		if (enermy->getStatus() == STATUS_LIVE)
		{
			
				switch (enermy->getDirection())
				{
				case ENERMY_MOVE_DOWN:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() + enermy->getSpeed(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + enermy->getSpeed());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad = 
							Globals::item_size - ((int)(enermy->getRect().getRecY() + enermy->getRect().getRecHeight() / 2) % Globals::item_size);
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + distanceToEndRoad);
						else
							enermy->setEnermyDirection(randomDirection());
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						setPlayerDead();
					break;
				case ENERMY_MOVE_UP:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() - enermy->getSpeed(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - enermy->getSpeed());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad = 
							(int)((enermy->getRect().getRecY() - enermy->getRect().getRecHeight() / 2)) % Globals::item_size;
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - distanceToEndRoad);
						else
							enermy->setEnermyDirection(randomDirection());
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						setPlayerDead();
					break;
				case ENERMY_MOVE_RIGHT:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX() + enermy->getSpeed(), enermy->getRect().getRecY(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX() + enermy->getSpeed(), enermy->getLocationY());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						float distanceToEndRoad = 
							Globals::item_size - ((int)(enermy->getRect().getRecX() + enermy->getRect().getRecWidth() / 2) % Globals::item_size);
						
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX() + distanceToEndRoad, enermy->getLocationY());
						else
							enermy->setEnermyDirection(randomDirection());
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						setPlayerDead();
					break;
				case ENERMY_MOVE_LEFT:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getLocationX() - enermy->getSpeed(), enermy->getRect().getRecY(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX() - enermy->getSpeed(), enermy->getLocationY());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad =
							(int)(enermy->getRect().getRecX() - enermy->getRect().getRecWidth() / 2) % enermy->getRect().getRecWidth();
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX() - distanceToEndRoad, enermy->getLocationY());
						else
							enermy->setEnermyDirection(randomDirection());
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						setPlayerDead();
					break;
				default:
					break;
				}

		}
		//draw again that enermy
		updateDrawEnermy(enermy);
	}
}

void GSPlay::autoMovingBoss(float deltaTime)
{
	//create a rect to save new rect of enermy after testing move enermy
	MRectangle tempRect;

	//get enermy from boss
	Enermy* enermy = ResourceManagers::GetInstance()->managerBoss()->getEnermy();

	//add time for check coll boss and wb
	ResourceManagers::GetInstance()->managerBoss()->addTimeCollWithWB(deltaTime);

	if (enermy)
	{
		if (enermy->getStatus() == STATUS_LIVE)
		{
			//add time to boss
			ResourceManagers::GetInstance()->managerBoss()->addTimeUseSkill(deltaTime);

			//check to move or use skill (make the boss stand after 2.0f time)
			if (ResourceManagers::GetInstance()->managerBoss()->getTimeUseSkill() >= 0)
			{
				if (!ResourceManagers::GetInstance()->managerBoss()->checkTimeUseSkill() && ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == -1)
				{
					//clear the list water boom explore
					if (m_listBossBoomExplode.size() != 0)
						m_listBossBoomExplode.clear();

					switch (enermy->getDirection())
					{
					case ENERMY_MOVE_DOWN:
						// create a new rect after move enermy to test
						tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() + enermy->getSpeed(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
						//check collision with ItemMap and Boom
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
							&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + enermy->getSpeed());
						else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
							|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
						{
							int distanceToEndRoad =
								enermy->getRect().getRecHeight() - ((int)(enermy->getRect().getRecY() + enermy->getRect().getRecHeight() / 2) % enermy->getRect().getRecHeight());
							if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
								enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + distanceToEndRoad);
							else
								enermy->setEnermyDirection(randomDirection());
						}
						//check collision with player
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
							setPlayerDead();
						break;
					case ENERMY_MOVE_UP:
						// create a new rect after move enermy to test
						tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() - enermy->getSpeed(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
						//check collision with ItemMap and Boom
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
							&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - enermy->getSpeed());
						else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
							|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
						{
							int distanceToEndRoad =
								(int)((enermy->getRect().getRecY() - enermy->getRect().getRecHeight() / 2)) % enermy->getRect().getRecHeight();
							if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
								enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - distanceToEndRoad);
							else
								enermy->setEnermyDirection(randomDirection());
						}
						//check collision with player
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
							setPlayerDead();
						break;
					case ENERMY_MOVE_RIGHT:
						// create a new rect after move enermy to test
						tempRect = MRectangle(enermy->getRect().getRecX() + enermy->getSpeed(), enermy->getRect().getRecY(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
						//check collision with ItemMap and Boom
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
							&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
							enermy->setEnermyLocation(enermy->getLocationX() + enermy->getSpeed(), enermy->getLocationY());
						else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
							|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
						{
							int distanceToEndRoad =
								enermy->getRect().getRecWidth() - ((int)(enermy->getRect().getRecX() + enermy->getRect().getRecWidth() / 2) % enermy->getRect().getRecWidth());
							if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
								enermy->setEnermyLocation(enermy->getLocationX() + distanceToEndRoad, enermy->getLocationY());
							else
								enermy->setEnermyDirection(randomDirection());
						}
						//check collision with player
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
							setPlayerDead();
						break;
					case ENERMY_MOVE_LEFT:
						// create a new rect after move enermy to test
						tempRect = MRectangle(enermy->getLocationX() - enermy->getSpeed(), enermy->getRect().getRecY(), enermy->getRect().getRecHeight(), enermy->getRect().getRecWidth());
						//check collision with ItemMap and Boom
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
							&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
							enermy->setEnermyLocation(enermy->getLocationX() - enermy->getSpeed(), enermy->getLocationY());
						else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
							|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
						{
							int distanceToEndRoad =
								(int)(enermy->getRect().getRecX() - enermy->getRect().getRecWidth() / 2) % enermy->getRect().getRecWidth();
							if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
								enermy->setEnermyLocation(enermy->getLocationX() - distanceToEndRoad, enermy->getLocationY());
							else
								enermy->setEnermyDirection(randomDirection());
						}
						//check collision with player
						if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
							setPlayerDead();
						break;
					default:
						break;
					}
				}
				else if (ResourceManagers::GetInstance()->managerBoss()->checkTimeUseSkill()){
					//random use skill for boss if it was not using skill
					if (ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == -1)
					{
						int skill = rand() % 2;
						if (skill == 0)
						{
							ResourceManagers::GetInstance()->managerBoss()->useSkill_1();
							checkcollForSkillBoss();
						}
						else if (skill == 1)
						{
							ResourceManagers::GetInstance()->managerBoss()->useSkill_2(1);
							checkcollForSkillBoss();
						}
						//set the skill is using
						ResourceManagers::GetInstance()->managerBoss()->setSkillIsUsingSkill(skill);
					}
					else if (ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == 0)
					{
						if (ResourceManagers::GetInstance()->managerBoss()->getTimeUseSkill() >= TIME_USE_SKILL + 1.2f)
						{
							//resset time
							ResourceManagers::GetInstance()->managerBoss()->setTimeUseSkill(0);
							//change the skill is using to -1
							ResourceManagers::GetInstance()->managerBoss()->setSkillIsUsingSkill(-1.0f);
							//clear explore boom
							m_listBossBoomExplode.clear();
						}
					}
					else if (ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == 1)
					{
						if (ResourceManagers::GetInstance()->managerBoss()->getTimeUseSkill() >= TIME_USE_SKILL + 0.6f)
						{
							//change the skill is using 
							ResourceManagers::GetInstance()->managerBoss()->setSkillIsUsingSkill(1.2f);
							//change the phase 2 to skill 2
							ResourceManagers::GetInstance()->managerBoss()->useSkill_2(2);
							//clear the list boom explore
							m_listBossBoomExplode.clear();

							checkcollForSkillBoss();
						}
					}
					else if (ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == 1.2f)
					{
						if (ResourceManagers::GetInstance()->managerBoss()->getTimeUseSkill() >= TIME_USE_SKILL + 1.2f) {
							//change the skill is using 
							ResourceManagers::GetInstance()->managerBoss()->setSkillIsUsingSkill(1.3f);
							//change the phase 2 to skill 2
							ResourceManagers::GetInstance()->managerBoss()->useSkill_2(3);
							//clear the list boom explore
							m_listBossBoomExplode.clear();

							checkcollForSkillBoss();
						}
					}
					else if (ResourceManagers::GetInstance()->managerBoss()->skillIsUsingSkill() == 1.3f)
					{
						if (ResourceManagers::GetInstance()->managerBoss()->getTimeUseSkill() >= TIME_USE_SKILL + 1.8f) {
							//resset time
							ResourceManagers::GetInstance()->managerBoss()->setTimeUseSkill(0);
							//change the skill is using to -1
							ResourceManagers::GetInstance()->managerBoss()->setSkillIsUsingSkill(-1);
							//clear explore boom
							m_listBossBoomExplode.clear();
						}
					}
				}
			}
		}

		//draw again that boss
		updateDrawBoss(ResourceManagers::GetInstance()->managerBoss());
	}
}

void GSPlay::autoIncreaseTimeBoom()
{
	//reload boom
	ResourceManagers::GetInstance()->managerPlayer()->reLoadBoom();

	//increase time boom
	if (m_time_update_boom >= TIME_BOOM_UPDATE)
	{
		for (auto *boom : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
		{
			float timeBoom = boom->getTimeExploding();
			//TODO
			//update hinh anh hoac chay animation
			if (timeBoom == 0)
				prepareForDrawingAnimationBoom();
			//set status for boom
			else if (timeBoom >= TIME_BOOM_DESTROY)
			{
				boom->setStatusBoom(STATUS_BOOM_DESTROY);
				//reload texture
				prepareForDrawingBoomExplore();
			}
			else if (boom->canBoomExplode() && boom->getStatusBoom() == STATUS_BOOM_PREPARE_EXPLODE)
			{
				updateAllDrawingWhenBoomExplore(boom);
			}

			//icrease time of each boom
			boom->setTimeBoomExploding(boom->getTimeExploding() + m_time_update_boom);
		}

		//reset check time boom
		m_time_update_boom = 0;
	}

	//check to update level map when all enermies was destroyed
	checkToNextLevel();
}

void GSPlay::generateLocationWaterBoom(Boom *boom)
{
	int power = boom->getPower();
	MRectangle tempRec;

	//index of item map for destroy
	int index = -1;

	for (int i = 0; i < (power * 4 + 1); i++)
	{
		// center water boom
		if (i == 0)
		{
			WaterBoom *wb = new WaterBoom(boom->getRect(), "bombbang_mid.tga");
			boom->getListWaterBoom()->push_back(wb);
		}
		//	up water boom
		else if (i <= power)
		{
			tempRec = MRectangle(boom->getRect().getRecX(), boom->getRect().getRecY() - Globals::item_size * i, Globals::item_size, Globals::item_size);
			//check coll wb with itemMap
			if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemMap(tempRec, index) == COLL_OK)
			{
				// destroy the item map by change the kind of item map to road
				if (ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getKindBlock() == MAP_ITEM_CAN_DESTROY)
				{
					ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].changeToRoadItem();
					generateItemPlayer(ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getRect());
				}
				// go to next direction to generate the water
				if (i != power)
					i = power;
				// go to next value
				continue;
			}

			//update normal if no coll with other item map
			if(i < power)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_up_1.tga"));
			else if (i == power)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_up_2.tga"));
		}
		//	left water boom
		else if (i <= power * 2)
		{
			tempRec = MRectangle(boom->getRect().getRecX() - Globals::item_size * (i - power), boom->getRect().getRecY(), Globals::item_size, Globals::item_size);
			//check coll wb with itemMap
			if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemMap(tempRec, index) == COLL_OK)
			{
				// destroy the item map by change the kind of item map to road
				if (ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getKindBlock() == MAP_ITEM_CAN_DESTROY)
				{
					ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].changeToRoadItem();
					generateItemPlayer(ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getRect());
				}
				// go to next direction to generate the water
				if (i != power * 2)
					i = power * 2;
				// go to next value
				continue;
			}
			//update normal if no coll with other item map
			if (i < power * 2)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_left_1.tga"));
			else if (i == power * 2)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_left_2.tga"));
		}
		//	down water boom
		else if (i <= power * 3)
		{
			tempRec = MRectangle(boom->getRect().getRecX(), boom->getRect().getRecY() + Globals::item_size * (i - power * 2), Globals::item_size, Globals::item_size);
			//check coll wb with itemMap
			if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemMap(tempRec, index) == COLL_OK)
			{
				//// destroy the item map by change the kind of item map to road
				//printf("kind of block%d\n", ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getKindBlock());
				if (ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getKindBlock() == MAP_ITEM_CAN_DESTROY)
				{
					ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].changeToRoadItem();
					generateItemPlayer(ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getRect());
				}
				// go to next direction to generate the water
				if (i != power * 3)
					i = power * 3;
				// go to next value
				continue;
			}
			//update normal if no coll with other item map
			if (i < power * 3)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_down_1.tga"));
			else if (i == power * 3)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_down_2.tga"));
		}
		//	right water boom
		else if (i <= power * 4)
		{
			tempRec = MRectangle(boom->getRect().getRecX() + Globals::item_size * (i - power * 3), boom->getRect().getRecY(), Globals::item_size, Globals::item_size);
			//check coll wb with itemMap
			if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemMap(tempRec, index) == COLL_OK)
			{
				// destroy the item map by change the kind of item map to road
				if (ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getKindBlock() == MAP_ITEM_CAN_DESTROY)
				{
					ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].changeToRoadItem();
					generateItemPlayer(ResourceManagers::GetInstance()->managerMap()->getArrayItemMap()[index].getRect());
				}
				// go to next direction to generate the water
				if (i != power * 4)
					i = power * 4;
				// go to next value
				continue;
			}
			//update normal if no coll with other item map
			if (i < power * 4)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_right_1.tga"));
			else if (i == power * 4)
				boom->getListWaterBoom()->push_back(new WaterBoom(tempRec, "bombbang_right_2.tga"));
		}

		//check coll wb with itemPlayer to delete the ItemPlayer in this func || update UI in fun prepareForDrawingBoom
		CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemPlayer(tempRec);
		//check coll wb with another boom and set the new time to the boom coll with wb to explore
		CollisionManager::GetInstance()->isCollBetweenWaterBoomAndBoom(tempRec , boom->getTimeExploding());
	}
}

void GSPlay::checkcollEnermyAndWaterBoom()
{
	for (auto* enermy : *ResourceManagers::GetInstance()->managerEnermy())
	{
		if (CollisionManager::GetInstance()->isCollBetweenEnermyAndWaterBoom(enermy->getRect()) == COLL_OK)
		{
			enermy->setStatus(STATUS_DEAD);
			updateDrawEnermy(enermy);
		}
	}

	// remove all enermies have status die
	ResourceManagers::GetInstance()->managerEnermy()
		->remove_if([](Enermy* it)
			{
				if (it->getStatus() == STATUS_DEAD)
				{
					printf("This enermy was destroy\n");
					return true;
				}
				return false;
			});
}

void GSPlay::checkcollWaterBoomAndBoss(Boom* boom)
{
	if (ResourceManagers::GetInstance()->managerBoss() != nullptr 
		&& ResourceManagers::GetInstance()->managerBoss()->getTimeCollWithWB() >= TIME_BOSS_COLL_WB)
	{
		//printf("hp boss : %d \n", ResourceManagers::GetInstance()->managerBoss()->getHpBoss());
		for (auto wb : *boom->getListWaterBoom())
		{
			if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndBoss(wb->getRect()) == COLL_OK)
			{
				//decrease the hp boss
				ResourceManagers::GetInstance()->managerBoss()->decreaseHpBoss();
				//reset time to the next check
				ResourceManagers::GetInstance()->managerBoss()->setTimeCollWithWB(0);
				break;
			}
		}
		//check if boss has zero hp throw win game 
		if (ResourceManagers::GetInstance()->managerBoss()->getHpBoss() <= 0)
		{
			//throw screen win game
		}
		else // update screen draw hp boss 
		{
			updateDrawHeartBoss();
		}
	}
}

void GSPlay::checkcollWaterBoomAndPlayer(std::list<WaterBoom*> *listWaterBoom)
{
	for (auto wb : *listWaterBoom)
	{
		if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndPlayer(wb->getRect()) == COLL_OK)
		{
			if(ResourceManagers::GetInstance()->managerPlayer()->getPlayerStatusLive() == STATUS_LIVE)
				// change status player to dead
				setPlayerDead();
		}
	}
	
}

void GSPlay::checkcollWaterBoomAndItemPlayer(std::list<WaterBoom*>* listWaterBoom)
{
	for (auto wb : *listWaterBoom)
	{
		//auto remove item player out of list in this fun
		CollisionManager::GetInstance()->isCollBetweenWaterBoomAndItemPlayer(wb->getRect());
	}
	//update ui for itemplayer
	updateForDrawingItemPlayer();
}

void GSPlay::checkcollForSkillBoss()
{
	//draw waterboom
	prepareForDrawingWaterBoom(ResourceManagers::GetInstance()->managerBoss()->getListWaterBoom(), 2);

	//check coll with pLayer
	checkcollWaterBoomAndPlayer(ResourceManagers::GetInstance()->managerBoss()->getListWaterBoom());
	//check coll with Item Player
	checkcollWaterBoomAndItemPlayer(ResourceManagers::GetInstance()->managerBoss()->getListWaterBoom());

	//check coll wb boss with boom player
	for (auto wbb : *ResourceManagers::GetInstance()->managerBoss()->getListWaterBoom())
	{
		for (auto b : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
		{
			int checkColl = wbb->getRect().isInteract(b->getRect());
			if(b->getStatusBoom() == STATUS_BOOM_PREPARE_EXPLODE 
				&& (checkColl == REC_OVER_LAP || checkColl == REC_ABOVE))
			{
				//set time boom to explore
				b->setTimeBoomExploding(TIME_BOOM_EXPLORE);
				updateAllDrawingWhenBoomExplore(b);
			}
		}
	}
}

void GSPlay::generateItemMap()
{
	//read map from file
	int level = ResourceManagers::GetInstance()->getLevelMap();
	ResourceManagers::GetInstance()->managerMap()->initMap(level);
}

void GSPlay::generateItemPlayer(MRectangle rec)
{
	//generate item player
	ResourceManagers::GetInstance()->addRandomItemPlayer(rec);

	//show list item player
	/*ResourceManagers::GetInstance()->checkListItemPLayer();*/
}

void GSPlay::updateAllDrawingWhenBoomExplore(Boom* boom)
{
	//set boom to explore
	boom->setStatusBoom(STATUS_BOOM_EXPLODE);

	generateLocationWaterBoom(boom);
	//update draw for itemPlayer if itemMap was destroy
	updateForDrawingItemPlayer();

	//reload texture
	prepareForDrawingBoomExplore();

	//remove the last Animation it have
	removeDrawingAnimationBoom(boom);
}

void GSPlay::prepareForDrawingBackgroundGameMenu()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("score_background.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_gameMenuBackground = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameMenuBackground->Set2DPosition(700 + 300/ 2, 700 / 2);
	m_gameMenuBackground->SetSize(300,700);

}

void GSPlay::prepareForDrawingBackgroundGamepLay()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_gameplayBackground = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameplayBackground->Set2DPosition(700 / 2, 700 / 2);
	m_gameplayBackground->SetSize(Globals::item_size * 12, Globals::item_size * 12);
}

void GSPlay::prepareForDrawingGameOverBackground()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("gameover.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_gameoverBackground = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameoverBackground->Set2DPosition(700 / 2, 700 / 2);
	m_gameoverBackground->SetSize(Globals::item_size * 6, Globals::item_size * 6);
}

void GSPlay::prepareForDrawingCompleteGameBackground(std::string pathTexture)
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture(pathTexture);
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	if (pathTexture.compare("win_game.tga") == 0)
	{
		m_completeBackground = std::make_shared<Sprite2D>(model, shader, texture);
		m_completeBackground->Set2DPosition(700 / 2, 700 / 2);
		m_completeBackground->SetSize(Globals::item_size * 8, Globals::item_size * 6);
	}
	else {
		m_completeBackground = std::make_shared<Sprite2D>(model, shader, texture);
		m_completeBackground->Set2DPosition(700 / 2, 700 / 2);
		m_completeBackground->SetSize(Globals::item_size * 6, Globals::item_size * 6);
	}
	
}

void GSPlay::prepareForDrawingMap()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//creat map
	generateItemMap();

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
	//set spon for enermy through var (get from read text) to enermy
	ResourceManagers::GetInstance()->autoSetSponToEnermyFromMap();
	////set spon for boss through var (get from read text) to boss
	ResourceManagers::GetInstance()->autoSetSponBossFromMap();
}

void GSPlay::prepareForDrawingButtonNormal()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 200, Globals::screenHeight / 2);
	button->SetSize(100, 100);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// volumn turn on button
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("btn_volumn");
	button->Set2DPosition(Globals::screenWidth - 100, Globals::screenHeight / 2);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->changeMute();
		if (GameStateMachine::GetInstance()->isMute())
		{
			ResourceManagers::GetInstance()->StopSound("soundMenu.wav");
			ResourceManagers::GetInstance()->changeIsPLayingSoundMenu(false);
		}
		else
		{
			ResourceManagers::GetInstance()->PlaySound("soundMenu.wav", true);
			ResourceManagers::GetInstance()->changeIsPLayingSoundMenu(true);
		}

		});
	m_listButton.push_back(button);
}

void GSPlay::prepareForDrawingButtonWhenPlayerDead()
{
	//two button
	// first go GSmenu
	// second play again
	
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// button play again
	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700 / 2 + 40, 700 / 2 + Globals::item_size * 3 + 35);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		restartGame(false);
		});
	m_listButton.push_back(button);

	//button go GSMenu
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700 / 2 - 40, 700 / 2 + Globals::item_size * 3 + 35);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

}

void GSPlay::prepareForDrawingButtonWhenCompleteGame()
{
	//two button
	// first play next
	// second go GSmenu

	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// button play again
	texture = ResourceManagers::GetInstance()->GetTexture("btn_next.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700 / 2 + 40, 700 / 2 + Globals::item_size * 3 + 35);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		increaseLevel();
		restartGame(true);
		m_state_game = STATE_PLAYING;
		});
	m_listButton.push_back(button);

	//button go GSMenu
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700 / 2 - 40, 700 / 2 + Globals::item_size * 3 + 35);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSPlay::prepareForDrawingButtonWhenWinGame()
{
	//one button
	//go home
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//button go GSMenu
	texture = ResourceManagers::GetInstance()->GetTexture("btn_home.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(700 / 2, 700 / 2 + Globals::item_size * 3 + 35);
	button->SetSize(70, 70);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
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

void GSPlay::updateDrawEnermy(Enermy *enermy)
{
	//find the animation have the id enermy then erease/update/create it 
	//find animation enermy has in map
	auto tempEnermyAnimation = m_mapAniamtionEnermies.find(enermy->getEnermyId());

	if (tempEnermyAnimation != m_mapAniamtionEnermies.end())
	{
		if (enermy->getStatus() == STATUS_LIVE)
		{
			tempEnermyAnimation->second->Set2DPosition(enermy->getRect().getRecX(), enermy->getRect().getRecY());
			tempEnermyAnimation->second->SetCurrentAction(enermy->getDirection());
		}
		else if(enermy->getStatus() == STATUS_DEAD)
			m_mapAniamtionEnermies.erase(tempEnermyAnimation);
	}
	else
	{
		//creat model , texture , shader
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("Animation");

		//printf("drawing enermy animation\n");
		texture = ResourceManagers::GetInstance()->GetTexture(enermy->getPathTexture());
		std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 4, enermy->getDirection(), Globals::timeEnermyMoving / 2);

		//update the enermy animation
		obj->Set2DPosition(enermy->getRect().getRecX(), enermy->getRect().getRecY());
		obj->SetSize(enermy->getSizeX(), enermy->getSizeY());

		m_mapAniamtionEnermies.insert({ enermy->getEnermyId(), obj });
	}
	
}

void GSPlay::updateDrawBoss(Boss* boss)
{
	if (boss)
	{
		Enermy* enermy = boss->getEnermy();
		//find the animation have the id enermy then erease/update/create it 
		//find animation enermy has in map
		auto tempEnermyAnimation = m_mapAniamtionBoss.find(enermy->getEnermyId());

		if (tempEnermyAnimation != m_mapAniamtionBoss.end())
		{
			if (enermy->getStatus() == STATUS_LIVE)
			{
				tempEnermyAnimation->second->Set2DPosition(enermy->getRect().getRecX(), enermy->getRect().getRecY());
				tempEnermyAnimation->second->SetCurrentAction(enermy->getDirection());
			}
			else if (enermy->getStatus() == STATUS_DEAD)
				m_mapAniamtionBoss.erase(tempEnermyAnimation);
		}
		else
		{
			printf("speed of enermy: %f\n", enermy->getSpeed());

			//creat model , texture , shader
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
			auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
			auto shader = ResourceManagers::GetInstance()->GetShader("Animation");

			//printf("drawing enermy animation\n");
			texture = ResourceManagers::GetInstance()->GetTexture("boss_animation.tga");
			std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 4, 0, Globals::timeEnermyMoving / 2);

			//update the enermy animation
			obj->Set2DPosition(enermy->getLocationX(), enermy->getLocationY());
			obj->SetSize(enermy->getSizeX(), enermy->getSizeY());

			m_mapAniamtionBoss.insert({ enermy->getEnermyId(), obj });
		}
	}
}

void GSPlay::prepareForDrawingBoomExplore()
{	
	//clear mListBoomExplode
	m_listBoomExplode.clear();

	//add sprinte2D to list to draw
	for (auto *it : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
	{
		if(it->getStatusBoom() == STATUS_BOOM_EXPLODE)
		{
			//draw water boom
			prepareForDrawingWaterBoom(it->getListWaterBoom() , 1);

			//draw again itemPLayer if it was destroyed
			updateForDrawingItemPlayer();

			//draw again map if it was destroyed
			updateDrawMap();

			//check water boom coll with enermy
			checkcollEnermyAndWaterBoom();

			//check water boom coll with player
			checkcollWaterBoomAndPlayer(it->getListWaterBoom());

			//check water boom coll with boss
			checkcollWaterBoomAndBoss(it);
		}
	}
}

void GSPlay::updateForDrawingItemPlayer()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create item_player sprite2D
	std::shared_ptr<Sprite2D> sprite2D = std::make_shared<Sprite2D>(model, shader, texture);

	//reset m_listItemPlayer
	m_listItemPlayer.clear();

	//add texture to draw itemPlayer
	for (auto *ip : *ResourceManagers::GetInstance()->managerItemPLayer())
	{
		texture = ResourceManagers::GetInstance()->GetTexture(ip->getPathTextureObjectPlayer());
		sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
		sprite2D->Set2DPosition(ip->getRect().getRecX(), ip->getRect().getRecY());
		sprite2D->SetSize(ip->getRect().getRecWidth(), ip->getRect().getRecHeight());
		m_listItemPlayer.push_back(sprite2D);
	}
}

void GSPlay::prepareForDrawingWaterBoom(std::list<WaterBoom*>* listWaterBoom , int kind)
{
	//creat model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create water boom sprite2D
	std::shared_ptr<Sprite2D> sprite2D = std::make_shared<Sprite2D>(model, shader, texture);

	if (kind == 1) // waterboom for player
	{
		//draw water boom
		for (WaterBoom* wb : *listWaterBoom)
		{
			texture = ResourceManagers::GetInstance()->GetTexture(wb->getTexture());
			sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
			sprite2D->Set2DPosition(wb->getRect().getRecX(), wb->getRect().getRecY());
			sprite2D->SetSize(wb->getRect().getRecWidth(), wb->getRect().getRecHeight());
			m_listBoomExplode.push_back(sprite2D);
		}
	}
	else if (kind == 2) // waterboom for boss
	{
		//draw water boom
		for (WaterBoom* wb : *listWaterBoom)
		{
			texture = ResourceManagers::GetInstance()->GetTexture(wb->getTexture());
			sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
			sprite2D->Set2DPosition(wb->getRect().getRecX(), wb->getRect().getRecY());
			sprite2D->SetSize(wb->getRect().getRecWidth(), wb->getRect().getRecHeight());
			m_listBossBoomExplode.push_back(sprite2D);
		}
	}
}

void GSPlay::prepareForDrawingAnimationBoom()
{
	//creat model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");

	Boom* tempBoom = ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom()->back();

	/*printf("drawing boom animation\n");*/
	texture = ResourceManagers::GetInstance()->GetTexture(tempBoom->getPathTextureBoom());
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 8, 1, 0, 0.2f);

	obj->Set2DPosition(tempBoom->getRect().getRecX(), tempBoom->getRect().getRecY() - 13);
	obj->SetSize(56 * 2, 77 * 2);
	m_mapAnimationBoom.insert({ tempBoom->getIdBoom(), obj });
}

void GSPlay::updateDrawMap()
{
	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create item_map sprite2D
	std::shared_ptr<Sprite2D> item_map = std::make_shared<Sprite2D>(model, shader, texture);

	//clear m_list_item
	m_listItemsMap.clear();
	
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
}

void GSPlay::updateTextDrawLevelMap()
{
	//create shader
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_levelText = std::make_shared< Text>(shader, font, "Level " + std::to_string(ResourceManagers::GetInstance()->getLevelMap() + 1), Vector4(1.0f, 0.5f, 0.0f, 1.0f), 1.5f);
	m_levelText->Set2DPosition(Vector2(Globals::screenWidth - 250, 70));
}

void GSPlay::updateDrawHeartBoss()
{
	m_listHeartBoss.clear();

	//create model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("heart.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create item_map sprite2D
	std::shared_ptr<Sprite2D> heart = std::make_shared<Sprite2D>(model, shader, texture);

	//draw heart
	for (int i = 0; i < ResourceManagers::GetInstance()->managerBoss()->getHpBoss(); i++)
	{
		heart = std::make_shared<Sprite2D>(model, shader, texture);
		heart->Set2DPosition(Vector2(Globals::screenWidth - 200 + (i%5) * 35, Globals::screenHeight / 4 + (i/5) * 35));
		heart->SetSize(30, 30);
		m_listHeartBoss.push_back(heart);
	}

	//draw a icon boss 
	texture = ResourceManagers::GetInstance()->GetTexture("boss_down.tga");
	heart = std::make_shared<Sprite2D>(model, shader, texture);
	heart->Set2DPosition(Vector2(Globals::screenWidth - 250 , Globals::screenHeight / 4 + 20));
	heart->SetSize(50, 70);
	m_listHeartBoss.push_back(heart);
}

void GSPlay::removeDrawingAnimationBoom(Boom *boom)
{
	auto tempBoomAnimation = m_mapAnimationBoom.find(boom->getIdBoom());
	m_mapAnimationBoom.erase(tempBoomAnimation);
}

void GSPlay::handlingKeyEventForPlayer(bool isMoving, int directionMove , bool isInittingBoom)
{
	ResourceManagers::GetInstance()->managerPlayer()->setPlayerIsMoving(isMoving);
	ResourceManagers::GetInstance()->managerPlayer()->setPlayerDirection(directionMove);
	ResourceManagers::GetInstance()->managerPlayer()->movePlayer(directionMove);
	//check the coll player and itemPlayer then update if it coll
	if (ResourceManagers::GetInstance()->managerPlayer()->isCollWithItemPlayer())
		updateForDrawingItemPlayer();

	//init boom
	if(isInittingBoom)
		ResourceManagers::GetInstance()->managerPlayer()->initBoom();
}

void GSPlay::setPlayerDead()
{
	ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
	checkToNextLevel();
}

void GSPlay::checkToNextLevel()
{
	if (ResourceManagers::GetInstance()->managerPlayer()->getPlayerStatusLive() == STATUS_DEAD)
	{
		prepareForDrawingGameOverBackground();
		prepareForDrawingButtonWhenPlayerDead();
		m_state_game = STATE_GAME_OVER;
	}
	else if (ResourceManagers::GetInstance()->managerBoss() != nullptr
		&& ResourceManagers::GetInstance()->managerBoss()->getHpBoss() <= 0
		&& ResourceManagers::GetInstance()->managerEnermy()->size() == 0)
	{
		prepareForDrawingCompleteGameBackground("win_game.tga");
		prepareForDrawingButtonWhenWinGame();
		m_state_game = STATE_COMPLETE_LEVEL;
	}
	else if (ResourceManagers::GetInstance()->managerEnermy()->size() == 0 && ResourceManagers::GetInstance()->managerBoss() == nullptr)
	{
		prepareForDrawingCompleteGameBackground("MissionComplete.tga");
		prepareForDrawingButtonWhenCompleteGame();
		m_state_game = STATE_COMPLETE_LEVEL;
	}
}

void GSPlay::increaseLevel()
{
	int level = ResourceManagers::GetInstance()->getLevelMap();
	level++;
	ResourceManagers::GetInstance()->setLevelMap(level);
}

int GSPlay::randomDirection()
{
	//srand(time(0));
	//random direction
	return (rand() % 4);
}

void GSPlay::restartGame(bool isIncreaseLevel)
{
	if (!isIncreaseLevel)
	{
		//reset level
		ResourceManagers::GetInstance()->setLevelMap(MAP_LEVEL_1);
	} 
	//do somethng here
	//reset all value game
	ResourceManagers::GetInstance()->resetData();
	m_mapAnimationBoom.clear();
	m_listBoomExplode.clear();
	m_listItemPlayer.clear();
	m_listItemsMap.clear();
	m_mapAniamtionEnermies.clear();
	m_mapAniamtionBoss.clear();
	m_player.reset();
	m_time_update_boom = 0.0f;
	m_listButton.clear();
	Init();
	updateTextDrawLevelMap();
	m_state_game = STATE_PLAYING;
}


