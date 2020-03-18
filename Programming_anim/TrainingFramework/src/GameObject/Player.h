#pragma once
#include "SpriteAnimation.h"


enum ninjaState { RUN, JUMP, SLIDE};

class Player: public SpriteAnimation
{
	public:
		Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
		virtual ~Player();
		
		void SetPlayerState(ninjaState playerState) { m_playerState = playerState; }
		ninjaState GetPlayerState() { return m_playerState; }

		ninjaState m_playerState;
		void Update(GLfloat deltaTime);
		void HandleKeyEvents(int key, bool bIsPressed);

		float actionTime;
		
};

