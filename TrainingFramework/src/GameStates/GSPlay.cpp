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

GSPlay::GSPlay() : m_time_update_boom(0.0f)
{

}

GSPlay::~GSPlay() 
{
	
}

void GSPlay::Init()
{
	m_Test = 1;
	m_KeyPress = 0;

	//draw background
	prepareForDrawingBackground();
	//draw Map
	prepareForDrawingMap();
	//draw PLayer
	prepareForDrawingPlayer();
	//draw Button
	prepareForDrawingButton();
	//draw Text
	prepareForDrawingText();
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
	m_time_update_boom += deltaTime;

	//process key input
	if(ResourceManagers::GetInstance()->managerPlayer()->getPlayerStatusLive() == STATUS_LIVE)
	{
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
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	//update boom animation
	for (auto it : m_listAnimationBoom)
	{
		it->Update(deltaTime);
	}

	//update enermy animation
	for (auto it : m_mapAniamtionEnermies)
	{
		it.second->Update(deltaTime);
	}

	//make enermy auto moving
	autoMovingEnermy(deltaTime);

	//make boom increase time to explode
	autoIncreaseTimeBoom();


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

	//boom
	for (auto it : m_listAnimationBoom)
	{
		it->Draw();
	}

	//water boom
	for (auto it : m_listBoomExplode)
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
	m_player->Draw();
}

void GSPlay::autoMovingEnermy(float deltaTime)
{
	//create a rect to save new rect of enermy after testing move enermy
	MRectangle tempRect;
	
	for (auto enermy : *ResourceManagers::GetInstance()->managerEnermy())
	{
		if (enermy->getStatus() == STATUS_LIVE)
		{
			//Get time of enermy
			if (enermy->getTimeEnermy() >= TIME_ENERMY_MOVING)
			{
				switch (enermy->getDirection())
				{
				case ENERMY_MOVE_DOWN:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() + enermy->getSpeed(), Globals::item_size, Globals::item_size);
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + enermy->getSpeed());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad = 
							(Globals::item_size - (enermy->getRect().getRecY() + enermy->getRect().getRecWidth() / 2) % Globals::item_size);
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() + distanceToEndRoad);
						else
							enermy->setEnermyDirection(ENERMY_MOVE_LEFT);
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
					break;
				case ENERMY_MOVE_UP:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX(), enermy->getRect().getRecY() - enermy->getSpeed(), Globals::item_size, Globals::item_size);
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - enermy->getSpeed());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad = 
							(enermy->getRect().getRecY() - enermy->getRect().getRecWidth() / 2) % Globals::item_size;
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX(), enermy->getLocationY() - distanceToEndRoad);
						else
							enermy->setEnermyDirection(ENERMY_MOVE_RIGHT);
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
					break;
				case ENERMY_MOVE_RIGHT:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getRect().getRecX() + enermy->getSpeed(), enermy->getRect().getRecY(), Globals::item_size, Globals::item_size);
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX() + enermy->getSpeed(), enermy->getLocationY());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad = 
							(Globals::item_size - (enermy->getRect().getRecX() + enermy->getRect().getRecWidth() / 2) % Globals::item_size);
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX() + distanceToEndRoad, enermy->getLocationY());
						else
							enermy->setEnermyDirection(ENERMY_MOVE_DOWN);
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
					break;
				case ENERMY_MOVE_LEFT:
					// create a new rect after move enermy to test
					tempRect = MRectangle(enermy->getLocationX() - enermy->getSpeed(), enermy->getRect().getRecY(), Globals::item_size, Globals::item_size);
					//check collision with ItemMap and Boom
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_NOT_OK
						&& CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_NOT_OK)		// if not coll update location enermy
						enermy->setEnermyLocation(enermy->getLocationX() - enermy->getSpeed(), enermy->getLocationY());
					else if (CollisionManager::GetInstance()->isCollBetweenEnermyAndItemMap(tempRect) == COLL_OK
						|| CollisionManager::GetInstance()->isCollBetweenEnermyAndBoom(tempRect) == COLL_OK)		// if coll change direction enermy
					{
						int distanceToEndRoad =
							(enermy->getRect().getRecX() - enermy->getRect().getRecWidth() / 2) % Globals::item_size;
						if (distanceToEndRoad < enermy->getSpeed() && distanceToEndRoad != 0)
							enermy->setEnermyLocation(enermy->getLocationX() - distanceToEndRoad, enermy->getLocationY());
						else
							enermy->setEnermyDirection(ENERMY_MOVE_UP);
					}
					//check collision with player
					if (CollisionManager::GetInstance()->isCollBetweenEnermyAndPlayer(tempRect) == COLL_OK)
						ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
					break;
				default:
					break;
				}

				//reset time of enermy to continue increase
				enermy->setTimeEnermy(0.0f);
			}
			else {
				//update time to trigger the next movement 
				enermy->addTimeToEnermy(deltaTime);
			}

		}
		//draw again that enermy
		updateDrawEnermy(enermy);
	}
}

void GSPlay::autoIncreaseTimeBoom()
{
	//reload boom
	ResourceManagers::GetInstance()->managerPlayer()->reLoadBoom();

	//increase time boom
	if (m_time_update_boom >= TIME_BOOM_UPDATE)
	{
		for (auto *it : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
		{
			float timeBoom = it->getTimeExploding();
			//TODO
			//update hinh anh hoac chay animation
			if (timeBoom == 0)
				prepareForDrawingAnimationBoom();
			//set status for boom
			else if (timeBoom >= TIME_BOOM_DESTROY)
			{
				it->setStatusBoom(STATUS_BOOM_DESTROY);
				//reload texture
				prepareForDrawingBoomExplore();
			}
			else if (it->canBoomExplode() && it->getStatusBoom() == STATUS_BOOM_PREPARE_EXPLODE)
			{
				it->setStatusBoom(STATUS_BOOM_EXPLODE);
				generateLocationWaterBoom(it);
				//update draw for itemPlayer if itemMap was destroy
				updateForDrawingItemPlayer();

				//remove the last Animation it have
				removeDrawingAnimationBoom();

				//reload texture
				prepareForDrawingBoomExplore();
			}

			//icrease time of each boom
			it->setTimeBoomExploding(it->getTimeExploding() + m_time_update_boom);
		}

		//reset check time boom
		m_time_update_boom = 0;
	}
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
			tempRec = MRectangle(boom->getRect().getRecX(), boom->getRect().getRecY() + Globals::item_size * i, Globals::item_size, Globals::item_size);
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
			tempRec = MRectangle(boom->getRect().getRecX(), boom->getRect().getRecY() - Globals::item_size * (i - power * 2), Globals::item_size, Globals::item_size);
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

void GSPlay::checkcollWaterBoomAndPlayer(Boom *boom)
{
	for (auto wb : *boom->getListWaterBoom())
	{
		if (CollisionManager::GetInstance()->isCollBetweenWaterBoomAndPlayer(wb->getRect()) == COLL_OK)
		{
			// change status player to dead
			ResourceManagers::GetInstance()->managerPlayer()->setPlayerStatusLive(STATUS_DEAD);
		}
	}
	
}

void GSPlay::generateItemMap()
{
	//read map from file
	ResourceManagers::GetInstance()->managerMap()->setMapLevel(MAP_LEVEL_1);
	ResourceManagers::GetInstance()->managerMap()->initMap();
}

void GSPlay::generateItemPlayer(MRectangle rec)
{
	//generate item player
	ResourceManagers::GetInstance()->addRandomItemPlayer(rec);

	//show list item player
	/*ResourceManagers::GetInstance()->checkListItemPLayer();*/
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

		printf("drawing enermy animation\n");
		texture = ResourceManagers::GetInstance()->GetTexture(enermy->getPathTexture());
		std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 2, 4, enermy->getDirection(), TIME_ENERMY_MOVING / 2);

		//update the enermy animation
		obj->Set2DPosition(enermy->getRect().getRecX(), enermy->getRect().getRecY());
		obj->SetSize(Globals::item_size * 2.5, Globals::item_size * 2.5);

		m_mapAniamtionEnermies.insert({ enermy->getEnermyId(), obj });
	}
	
}

void GSPlay::prepareForDrawingBoomExplore()
{	
	//clear mListBoom and mListBoomExplode
	m_listBoomExplode.clear();

	//add sprinte2D to list to draw
	for (auto *it : *ResourceManagers::GetInstance()->managerPlayer()->getPlayerListBoom())
	{
		if(it->getStatusBoom() == STATUS_BOOM_EXPLODE)
		{
			//draw water boom
			prepareForDrawingWaterBoom(it);

			//draw again itemPLayer if it was destroyed
			updateForDrawingItemPlayer();

			//draw again map if it was destroyed
			updateDrawMap();

			//check water boom coll with enermy
			checkcollEnermyAndWaterBoom();

			//check water boom coll with player
			checkcollWaterBoomAndPlayer(it);

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

void GSPlay::prepareForDrawingWaterBoom(Boom *boom)
{
	//creat model , texture , shader
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_gameplay.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//create water boom sprite2D
	std::shared_ptr<Sprite2D> sprite2D = std::make_shared<Sprite2D>(model, shader, texture);

	//draw water boom
	for (WaterBoom *wb : *boom->getListWaterBoom())
	{
		texture = ResourceManagers::GetInstance()->GetTexture(wb->getTexture());
		sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
		sprite2D->Set2DPosition(wb->getRect().getRecX(), wb->getRect().getRecY());
		sprite2D->SetSize(wb->getRect().getRecWidth(), wb->getRect().getRecHeight());
		m_listBoomExplode.push_back(sprite2D);
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
	m_listAnimationBoom.push_back(obj);
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

void GSPlay::removeDrawingAnimationBoom()
{
	m_listAnimationBoom.pop_front();
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


