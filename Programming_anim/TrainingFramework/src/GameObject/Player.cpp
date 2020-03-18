#include "Player.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"


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
			if (actionTime >= 0.25) {
				Set2DPosition(240, this->Get2DPosition().y - deltaTime * 1000);
			}
			else {
				Set2DPosition(240, this->Get2DPosition().y + deltaTime * 1000);
			}
		}
		if (actionTime <= 0) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("running");
			SetTexture(texture);
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
			SetPlayerState(SLIDE); actionTime = 0.5;
			Set2DPosition(240, 680);
			SetTexture(texture);
		}
					 break;

					   //JUMP
		case KEY_UP: if (m_playerState != JUMP) {
			auto texture = ResourceManagers::GetInstance()->GetTexture("jump");
			SetPlayerState(JUMP); actionTime = 0.5;
			SetTexture(texture);
		}
					 break;

		default:
			break;
		}
	}
	
}



