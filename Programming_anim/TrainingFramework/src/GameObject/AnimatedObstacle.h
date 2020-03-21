#pragma once
#include "SpriteAnimation.h"

// obstacle class for the bat (for displaying animation only)

class AObstacle : public SpriteAnimation
{
	private:

		GLfloat			obstacleY;

	public:
		AObstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime);
		virtual ~AObstacle();

		void			Update(GLfloat deltaTime, int screenSpeed, GLfloat x);
		void			SetY(GLfloat oby) { obstacleY = oby; }
		GLfloat			GetY() { return obstacleY; }

};