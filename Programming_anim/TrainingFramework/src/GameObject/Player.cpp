#include "Player.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"

#define ACTION_TIME 0.5		// Time interval in a jump/slide
#define JUMP_POWER 1000

extern int character;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, frameTime)
{
	m_playerState = RUN;
	actionTime = 0;
}

Player::~Player()
{
}

void Player::Update(GLfloat deltaTime) {
	if (actionTime > 0) {
		actionTime -= deltaTime;
		if (m_playerState == JUMP) {
			if (actionTime >= ACTION_TIME / 2) {
				Set2DPosition(240, Get2DPosition().y - deltaTime * JUMP_POWER);
			}
			else {
				Set2DPosition(240, Get2DPosition().y + deltaTime * JUMP_POWER);
			}
		}
		if (actionTime <= 0) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("running");
			if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("run_girl");
			SetTexture(texture);
			ResetAnimation();
			Set2DPosition(240, 650);
			SetPlayerState(RUN); actionTime = 0;
		}
	} 

	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}
	
}

void Player::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed = true) {
		switch (key) {

			//SLIDE	
		case KEY_DOWN: if (m_playerState != JUMP) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("slide");
			if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("slide_girl");
			SetPlayerState(SLIDE); actionTime = ACTION_TIME;
			Set2DPosition(240, 680);
			SetTexture(texture);
			ResetAnimation();
		}
					 break;

					   //JUMP
		case KEY_UP: if (m_playerState != JUMP) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("jump");
			if (character == 2) texture = ResourceManagers::GetInstance()->GetTexture("jump_girl");
			SetPlayerState(JUMP); actionTime = ACTION_TIME;
			SetTexture(texture);
			ResetAnimation();
		}
					 break;

		default:
			break;
		}
	}
	
}



