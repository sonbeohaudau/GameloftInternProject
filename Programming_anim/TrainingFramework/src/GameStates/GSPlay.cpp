#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"


#define SCREEN_SPEED 600

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_autumn");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D> bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth / 2, screenHeight / 2);
	bg->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(bg);

	bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth * 3 / 2, screenHeight / 2);
	bg->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(bg);

	// Obstacles
	texture = ResourceManagers::GetInstance()->GetTexture("spike");
	std::shared_ptr<Obstacle> obs = std::make_shared<Obstacle>(model, shader, texture);
	obs = std::make_shared<Obstacle>(model, shader, texture);
	obs->SetType(SPIKE);
	obs->SetY(670);
	obs->Set2DPosition(screenWidth * 3 / 2, obs->GetY());
	obs->SetSize(70, 125);
	m_listObstacle.push_back(obs);

	texture = ResourceManagers::GetInstance()->GetTexture("spikemonA");
	obs = std::make_shared<Obstacle>(model, shader, texture);
	obs->SetType(SPIKEMONA);
	obs->SetY(560);
	obs->Set2DPosition(screenWidth * 5 / 2, obs->GetY());
	obs->SetSize(114, 59);
	m_listObstacle.push_back(obs);


	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(1050, 100);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
	});
	m_listButton.push_back(button);

	//restart button
/*	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(900, 100);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);
	*/

	//show score
/*	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	*/

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("running");
/*	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.06f);
	obj->Set2DPosition(240, 650);
	obj->SetSize(160, 200);
	m_listSpriteAnimations.push_back(obj); */

	ninja = std::make_shared<Player>(model, shader, texture, 10, 0.06f);
	ninja->Set2DPosition(240, 650);
	ninja->SetSize(160, 200);
}

void GSPlay::Exit()
{

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
	ninja->HandleKeyEvents(key, bIsPressed);
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{	
	
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	for (auto bg : m_listSprite2D)
	{
		bg->Update(deltaTime);
		bg->Set2DPosition(bg->Get2DPosition().x - SCREEN_SPEED*deltaTime, screenHeight / 2);
		if (bg->Get2DPosition().x <= -screenWidth / 2) {
			bg->Set2DPosition(bg->Get2DPosition().x + 2 * screenWidth, screenHeight / 2);
		}
	}

	ninja->Update(deltaTime);
	for (auto ob : m_listObstacle)
	{
		ob->Update(deltaTime, SCREEN_SPEED);
		GameEvent(ob);
	}

}

void GSPlay::Draw()
{
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}

	//m_score->Draw();

/*	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	} */

	

	for (auto it : m_listButton)
	{
		it->Draw();
	}

	ninja->Draw();

	for (auto ob : m_listObstacle)
	{
		ob->Draw();
	}

}

void GSPlay::SetNewPostionForBullet()
{
}

void GSPlay::GameEvent(std::shared_ptr<Obstacle> ob) {
	switch (ob->GetObstacleType()) {
	case SPIKE: 
		if (ob->Get2DPosition().x <= 300 && ob->Get2DPosition().x >= 160) {
			if (ninja->GetPlayerState() != JUMP) GameStateMachine::GetInstance()->PopState();
		}
		break;
	case SPIKEMONA:
		if (ob->Get2DPosition().x <= 340 && ob->Get2DPosition().x >= 120) {
			if (ninja->GetPlayerState() != SLIDE) GameStateMachine::GetInstance()->PopState();
		}
		break;
	default: break;
	}
}