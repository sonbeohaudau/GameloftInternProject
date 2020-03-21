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
#include "ResourceManagers.h"


#define SCREEN_SPEED 600
#define DEAD_ANIMATION_TIME 1

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float bgmLoop;
extern int gameDifficulty;
extern int character;
extern int backGround;


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	// Set starting difficulty and set up game
	Gameplay::GetInstance()->SetPhase(gameDifficulty);
	
	
	//BackGround
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_autumn");
	if (backGround == 2) texture = ResourceManagers::GetInstance()->GetTexture("bg_park");
 
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
/*	std::shared_ptr<Obstacle> obs = std::make_shared<Obstacle>(model, shader, texture, SPIKE);
	obs->Set2DPosition(screenWidth * 3 / 2, obs->GetY());
	m_listObstacle.push_back(obs);

	obs = std::make_shared<Obstacle>(model, shader, texture, BAT);
	obs->Set2DPosition(screenWidth * 5 / 2, obs->GetY());
	m_listObstacle.push_back(obs);	
*/
	m_obstacle1 = std::make_shared<Obstacle>(model, shader, texture, SPIKE);
	m_obstacle1->Set2DPosition(screenWidth * 3 / 2, m_obstacle1->GetY());

	m_obstacle2 = std::make_shared<Obstacle>(model, shader, texture, BAT);
	m_obstacle2->Set2DPosition(screenWidth * 5 / 2, m_obstacle2->GetY());
	

	//pause button
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(1050, 100);
	button->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("bgm_play");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
	});
	m_listButton.push_back(button);


	//show score
	Gameplay::GetInstance()->SetScore(0);
	tmpscore = std::to_string(Gameplay::GetInstance()->GetScore());

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared<Text>(shader, font, "SCORE: "+ tmpscore , TEXT_COLOR::RED, 2.0);
	m_score->Set2DPosition(Vector2(5, 50));
	

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("running");
	if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("run_girl");

	m_ninja = std::make_shared<Player>(model, shader, texture, 10, 0.06f);
	m_ninja->Set2DPosition(240, 650);
	m_ninja->SetSize(160, 200);

	texture = ResourceManagers::GetInstance()->GetTexture("bat");
//	m_bat = std::make_shared<AObstacle>(model, shader, texture, 5, 0.06f);
//	m_bat->Set2DPosition(screenWidth * 5 / 2, obs->GetY());
	m_bat1 = std::make_shared<AObstacle>(model, shader, texture, 5, 0.06f);
	m_bat1->Set2DPosition(-screenWidth / 2, m_bat1->GetY());
	m_bat2 = std::make_shared<AObstacle>(model, shader, texture, 5, 0.06f);
	m_bat2->Set2DPosition(-screenWidth / 2, m_bat2->GetY());

	// BGM
	ResourceManagers::GetInstance()->PlaySound("bgm_play");


	// Some gameplay parameters
	m_update = true;	// Allow the update in gameplay
	m_dead = false;		// true when game over
	GameOverTime = DEAD_ANIMATION_TIME;	
	bgmLoop = 12.8;		// time each loop
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
	if (m_update == true) m_ninja->HandleKeyEvents(key, bIsPressed);
	
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (m_update == true) {
		for (auto it : m_listButton)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
	}
}

void GSPlay::Update(float deltaTime)
{	
	if (m_update == true) {
		for (auto obj : m_listSpriteAnimations)
		{
			obj->Update(deltaTime);
		}

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}

		// Scrolling background
		for (auto bg : m_listSprite2D)
		{
			bg->Update(deltaTime);
			bg->Set2DPosition(bg->Get2DPosition().x - SCREEN_SPEED*deltaTime, screenHeight / 2);
			if (bg->Get2DPosition().x <= -screenWidth / 2) {
				bg->Set2DPosition(bg->Get2DPosition().x + 2 * screenWidth, screenHeight / 2);
			}
		}

		// Player and obstacle's animation + check collision
		m_ninja->Update(deltaTime);
/*		for (auto ob : m_listObstacle)
		{
			ob->Update(deltaTime, SCREEN_SPEED);
			if (Gameplay::GetInstance()->CheckCollision(m_ninja, ob) == true) GameOver();
			m_bat->Update(deltaTime, SCREEN_SPEED);
			if (Gameplay::GetInstance()->CheckCollision(m_ninja, m_bat)) GameOver();
			
		}
*/
		m_obstacle1->Update(deltaTime, SCREEN_SPEED);
		if (Gameplay::GetInstance()->CheckCollision(m_ninja, m_obstacle1) == true) GameOver();
		m_obstacle2->Update(deltaTime, SCREEN_SPEED);
		if (Gameplay::GetInstance()->CheckCollision(m_ninja, m_obstacle2) == true) GameOver();
		if(m_obstacle1->GetObstacleType() == BAT){
			m_bat1->Update(deltaTime, SCREEN_SPEED, m_obstacle1->Get2DPosition().x);
			if (Gameplay::GetInstance()->CheckCollision(m_ninja, m_bat1) == true) GameOver();
		}
		if(m_obstacle2->GetObstacleType() == BAT) {
			m_bat2->Update(deltaTime, SCREEN_SPEED, m_obstacle2->Get2DPosition().x);
			if (Gameplay::GetInstance()->CheckCollision(m_ninja, m_bat2) == true) GameOver();
		}
		// Loop bgm
		bgmLoop -= deltaTime;
		if (bgmLoop <= 0) {
			ResourceManagers::GetInstance()->PlaySound("bgm_play");
			bgmLoop = 12.8;
		}

		// Update score
		tmpscore = std::to_string(Gameplay::GetInstance()->GetScore());
		m_score->setText("SCORE: " + tmpscore);
	}

	if (m_dead == true) {
		// dead animation when game over
		m_ninja->Update(deltaTime);
		GameOverTime -= deltaTime;
		if (GameOverTime <= 0) {
			GameStateMachine::GetInstance()->PopState();
			ResourceManagers::GetInstance()->PlaySound("bgm_main_menu");
			bgmLoop = 14.3;
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


	for (auto it : m_listButton)
	{
		it->Draw();
	}

	m_ninja->Draw();
	m_obstacle1->Draw();
	m_obstacle2->Draw();
	m_bat1->Draw();
	m_bat2->Draw();

/*	for (auto ob : m_listObstacle)
	{
		ob->Draw();
	}
*/
}

void GSPlay::GameOver() {
	// stop update
	m_update = false;

	// dead animation when game over
	auto texture = ResourceManagers::GetInstance()->GetTexture("dead");
	if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("dead_girl");
	m_ninja->actionTime = 0;
	m_ninja->SetTexture(texture);
	m_ninja->ResetAnimation();
	m_ninja->SetFrameTime(0.12f);
	m_ninja->SetSize(200, 200);
	m_dead = true;
	ResourceManagers::GetInstance()->PauseSound("bgm_play");
	
}

