#pragma once
#include "SpriteAnimation.h"

// obstalce class for the bat

class AObstacle : public SpriteAnimation
{
	private:

		GLfloat			obstacleY;

	public:
		AObstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
		virtual ~AObstacle();

		void			Update(GLfloat deltaTime, int screenSpeed);
		void			SetY(GLfloat oby) { obstacleY = oby; }
		GLfloat			GetY() { return obstacleY; }

};