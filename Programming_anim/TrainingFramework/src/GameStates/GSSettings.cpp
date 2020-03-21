#include "GSSettings.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float bgmLoop;
extern int gameDifficulty;
extern int character;
extern int backGround;


GSSettings::GSSettings()
{

}


GSSettings::~GSSettings()
{
}



void GSSettings::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_relax");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//return main menu button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 600);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//"SETTINGS" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_settings = std::make_shared< Text>(shader, font, "SETTINGS", TEXT_COLOR::RED, 1.0);
	m_Text_settings->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));
}

void GSSettings::Exit()
{
}


void GSSettings::Pause()
{

}

void GSSettings::Resume()
{

}


void GSSettings::HandleEvents()
{

}

void GSSettings::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == 1) {
		switch (key) {
		case KEY_BACK: GameStateMachine::GetInstance()->PopState();
			break;
		default:
			break;
		}

	}
}

void GSSettings::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSettings::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	bgmLoop -= deltaTime;
	if (bgmLoop <= 0) {
		ResourceManagers::GetInstance()->PlaySound("bgm_main_menu");
		bgmLoop = 14.3;
	}
}

void GSSettings::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_settings->Draw();
}
