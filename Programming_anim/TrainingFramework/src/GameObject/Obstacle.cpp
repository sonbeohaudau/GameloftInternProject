#include "Obstacle.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"
#include "Gameplay.h"

#define ADVANCE_PHASE_SCORE 10		// score points required to advance to next phase
#define TINY_SPEED_BOOST 1.2
#define HOP_JUMP_MOMENT 800
#define COBRA_PAUSE_MOMENT 1000
#define COBRA_PAUSE_TIME 1

extern int screenWidth; 
extern int screenHeight; 


Obstacle::Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, ObstacleType type)
	: Sprite2D(model, shader, texture)
{
	SetType(type);
	switch(type) {
	case SPIKE:
		SetY(690);
		SetSize(56, 100);
		SetMove(0);
		break;
	case BAT:
		SetY(-5);
		SetSize(2, 2);
		SetMove(0);
		break;
	default: break;
	}
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(GLfloat deltaTime,int speed) {
	Set2DPosition(Get2DPosition().x - speed*deltaTime, m_obstacleY);

	// TINY special move
	if (m_type == TINY && Get2DPosition().x <= screenWidth && Get2DPosition().x > 10 && m_specialMove == 0) {
			Gameplay::GetInstance()->SetSpeed(speed * TINY_SPEED_BOOST);
			SetMove(1);				
	}
	if (m_specialMove == 1 && Get2DPosition().x <= 10) {
	//	Gameplay::GetInstance()->SetSpeed(speed / TINY_SPEED_BOOST);
		Gameplay::GetInstance()->SetUp();
		SetMove(0);
	}

	// HOP special move
	if (m_type == HOP && Get2DPosition().x <= HOP_JUMP_MOMENT && Get2DPosition().x > 10 && m_specialMove == 0) {
		SetMove(2);
	}

	if (m_specialMove == 2 && Get2DPosition().y >= 500) {
		SetY(m_obstacleY - speed*deltaTime);
	}

	if (m_specialMove == 2 && Get2DPosition().x <= 10) {
		SetY(m_obstacleY - speed*deltaTime);
		SetMove(0);
	}

	// COBRA SPIKE special move
	if (m_type == COBRA_SPIKE && Get2DPosition().x <= COBRA_PAUSE_MOMENT && Get2DPosition().x > 10 && Get2DPosition().x > 10 && m_specialMove == 0) {
		Gameplay::GetInstance()->SetSpeed(0);
		SetMove(3);
		SetTime(COBRA_PAUSE_TIME);
	}
	if (m_specialMove == 3 && m_actionTime > 0) {
		SetTime(m_actionTime - deltaTime);
		if (m_actionTime <= 0) {
			SetTime(0);
			Gameplay::GetInstance()->SetUp();
		}		
	}
	if (m_specialMove == 3 && m_actionTime == 0 && Get2DPosition().x <= 10) {
		SetMove(0);
	}

	
	// Obstacle passed successfully
	if (Get2DPosition().x <= -screenWidth / 4) {		
		Set2DPosition(Get2DPosition().x + 2 * screenWidth, m_obstacleY);
		int score = Gameplay::GetInstance()->GetScore();
		Gameplay::GetInstance()->SetScore(score + 1);
		if (score == ADVANCE_PHASE_SCORE || score == ADVANCE_PHASE_SCORE * 2 || score == ADVANCE_PHASE_SCORE * 3) {
			Gameplay::GetInstance()->AdvanceNextPhase();
		}
		SwitchType();
	}
}

void Obstacle::SwitchType() {
	int newType;
	std::shared_ptr<Texture> newTexture;
	newType = rand() % (Gameplay::GetInstance()->GetNumObs() + 2) + 1; // +1 to set newType value starting from 1, +2 to increase regular spikes and bats spawn rate
//	printf("%d ", newType);
	switch (newType) {
	case 1:		// Spike
	case 2:
		newTexture = ResourceManagers::GetInstance()->GetTexture("spike");
		SetType(SPIKE);
		SetY(690);
		SetSize(56, 100);
		break;
	case 3:		// Bat
	case 4:
		newTexture = ResourceManagers::GetInstance()->GetTexture("spike");
		SetType(BAT);
		SetY(-5);
		SetSize(2, 2);
		break;
	case 5:		// Tiny
		newTexture = ResourceManagers::GetInstance()->GetTexture("spikemonA");
		SetType(TINY);
		SetY(720);
		SetSize(20, 10);
		break;
	case 6:		// Hop
		newTexture = ResourceManagers::GetInstance()->GetTexture("spikemonB");
		SetType(HOP);
		SetY(710);
		SetSize(180, 100);
		break;
	case 7:		// Cobra spike
		newTexture = ResourceManagers::GetInstance()->GetTexture("spike");
		SetType(COBRA_SPIKE);
		SetY(690);
		SetSize(56, 100);
		break;
	default:
		break;
	}
	SetTexture(newTexture);
}





