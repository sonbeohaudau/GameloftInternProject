#include "GSPause.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float bgmLoop;
extern bool bgm_on;
extern bool button_update;

GSPause::GSPause()
{

}


GSPause::~GSPause()
{
}



void GSPause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_relax");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//resume
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(400, 450);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		if (bgm_on == true) ResourceManagers::GetInstance()->PlaySound("bgm_play");
		bgmLoop = 12.8;
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//go back to main menu
	texture = ResourceManagers::GetInstance()->GetTexture("button_main_menu");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(800, 450);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(STATE_Menu);
		if (bgm_on == true) ResourceManagers::GetInstance()->PlaySound("bgm_main_menu");
		bgmLoop = 14.3;
	});
	m_listButton.push_back(button);

	//turn on/off music button
	texture = ResourceManagers::GetInstance()->GetTexture("button_music_on");
	if (bgm_on == false) texture = ResourceManagers::GetInstance()->GetTexture("button_music_off");
	m_bgmButton = std::make_shared<GameButton>(model, shader, texture);
	m_bgmButton->Set2DPosition(1100, 100);
	m_bgmButton->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	m_bgmButton->SetOnClick([]() {
		button_update = true;
	});
	m_listButton.push_back(m_bgmButton);


	//"Paused" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_paused = std::make_shared< Text>(shader, font, "PAUSED", TEXT_COLOR::RED, 1.0);
	m_Text_paused->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));

	ResourceManagers::GetInstance()->PauseSound("bgm_play");
}

void GSPause::Exit()
{
}


void GSPause::Pause()
{

}

void GSPause::Resume()
{

}


void GSPause::HandleEvents()
{

}

void GSPause::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPause::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (button_update) {
		UpdateButtons();
	}
}

void GSPause::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_paused->Draw();
}

void GSPause::UpdateButtons() {

	if (bgm_on == true) {
		auto newTexture = ResourceManagers::GetInstance()->GetTexture("button_music_off");
		m_bgmButton->SetTexture(newTexture);
		bgm_on = false;
	}
	else
	{
		auto newTexture = ResourceManagers::GetInstance()->GetTexture("button_music_on");
		m_bgmButton->SetTexture(newTexture);
		bgm_on = true;
	}


	button_update = false;
}
