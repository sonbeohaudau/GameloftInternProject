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


#define SCREEN_SPEED 400

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

float actionTime;

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	ninja = std::make_shared<Player>();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_park");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Sprite2D> bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth / 2, screenHeight / 2);
	bg->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(bg);

	bg = std::make_shared<Sprite2D>(model, shader, texture);
	bg->Set2DPosition(screenWidth * 3 / 2, screenHeight / 2);
	bg->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(bg);


	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(900, 100);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
	});
	m_listButton.push_back(button);

	//restart button
	texture = ResourceManagers::GetInstance()->GetTexture("button_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(1050, 100);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(button);


	//show score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));


	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("running");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.06f);
	obj->Set2DPosition(240, 650);
	obj->SetSize(160, 200);
	m_listSpriteAnimations.push_back(obj);

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
	if (bIsPressed = true) {
		switch (key) {
		
		//SLIDE	
		case KEY_DOWN: if (ninja->GetPlayerState() != JUMP) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("slide");
			ninja->SetPlayerState(SLIDE); actionTime = 0.5;
			m_listSpriteAnimations.front()->Set2DPosition(240, 680);
			m_listSpriteAnimations.front()->SetTexture(texture); 
		}
			break;

		//JUMP
		case KEY_UP: if (ninja->GetPlayerState() != JUMP) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("jump");
			ninja->SetPlayerState(JUMP); actionTime = 0.5;
			m_listSpriteAnimations.front()->SetTexture(texture); 
		}
			break;

		//Pause
		case KEY_BACK: GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
			break;
		default:  
			break;
		}		
	}
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
	if (actionTime > 0) {
		actionTime -= deltaTime;
		if (ninja->GetPlayerState() == JUMP) {
			if (actionTime >= 0.25) {
				m_listSpriteAnimations.front()->Set2DPosition(240, m_listSpriteAnimations.front()->Get2DPosition().y - deltaTime * 1000);
			}
			else {
				m_listSpriteAnimations.front()->Set2DPosition(240, m_listSpriteAnimations.front()->Get2DPosition().y + deltaTime * 1000);
			}
		}
		if (actionTime <= 0) { 
			auto texture = ResourceManagers::GetInstance()->GetTexture("running");
			m_listSpriteAnimations.front()->SetTexture(texture);
			m_listSpriteAnimations.front()->Set2DPosition(240, 650);
			ninja->SetPlayerState(RUN); actionTime = 0; }
	}
	
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

}

void GSPlay::Draw()
{
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}

	m_score->Draw();

	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	}

	m_score->Draw();

	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}