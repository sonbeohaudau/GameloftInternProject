#include "GSGameOver.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float bgmLoop;

GSGameOver::GSGameOver()
{

}


GSGameOver::~GSGameOver()
{
}



void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_relax");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//restart
	texture = ResourceManagers::GetInstance()->GetTexture("button_restart");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(400, 450);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(STATE_Play);
		ResourceManagers::GetInstance()->PlaySound("bgm_play");
		bgmLoop = 12.8;
		
	});
	m_listButton.push_back(button);

	//go back to main menu
	texture = ResourceManagers::GetInstance()->GetTexture("button_main_menu");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(800, 450);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		ResourceManagers::GetInstance()->PlaySound("bgm_main_menu");
		bgmLoop = 14.3;
	});
	m_listButton.push_back(button);


	// "GAME OVER" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_GameOver = std::make_shared< Text>(shader, font, "GAME OVER", TEXT_COLOR::RED, 3.0);
	m_Text_GameOver->Set2DPosition(Vector2(screenWidth / 2 - 200, 120));

	// Show score
	std::string finalscore = std::to_string(Gameplay::GetInstance()->GetScore());

	m_Text_Score = std::make_shared< Text>(shader, font, "YOUR SCORE: " + finalscore, TEXT_COLOR::GREEN, 2.0);
	m_Text_Score->Set2DPosition(Vector2(screenWidth / 2 - 200, 320));
}

void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void GSGameOver::Resume()
{

}


void GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_GameOver->Draw();
	m_Text_Score->Draw();
}