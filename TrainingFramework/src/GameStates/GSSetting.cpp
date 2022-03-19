#include "GSSetting.h"

GSSetting::GSSetting() : GameStateBase(StateType::STATE_SETTING),
m_background(nullptr), m_listButton(std::list<std::shared_ptr<GameButton>>{}), m_textGameName(nullptr)
{
}


GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// turn back button
	texture = ResourceManagers::GetInstance()->GetTexture("btn_prev.tga");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("btn_turnBack");
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
	});
	m_listButton.push_back(button);

	// volumn turn on button
	button = std::make_shared<GameButton>(model, shader, texture);
	button->SetName("btn_volumn");
	button->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	button->SetSize(200, 200);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->changeMute();
		if (GameStateMachine::GetInstance()->isMute()) {
			ResourceManagers::GetInstance()->StopSound("soundMenu.wav");
		}
		});
	m_listButton.push_back(button);

	// game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_textGameName = std::make_shared< Text>(shader, font, "Setting", Vector4(1.0f, 0.5f, 0.0f, 1.0f), 3.0f);
	m_textGameName->Set2DPosition(Vector2(60, 200));

	//sound
}


void GSSetting::Exit()
{
	ResourceManagers::FreeInstance();
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw()
{
	m_background->Draw();
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
	m_textGameName->Draw();
}
