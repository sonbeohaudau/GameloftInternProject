#pragma once
#include "Sprite2D.h"

enum ObstacleType { SPIKE, SPIKEMONA, SPIKEMONB };

class Obstacle : public Sprite2D
{
	private:
		ObstacleType	m_obstacle;
		GLfloat			obstacleY;

	public:
		Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, ObstacleType type);
		virtual ~Obstacle();

		ObstacleType	GetObstacleType() { return m_obstacle; }

	
		void			Update(GLfloat deltaTime, int screenSpeed);
		void			SetType(ObstacleType type) { m_obstacle = type; }
		void			SetY(GLfloat oby) { obstacleY = oby; }
		GLfloat			GetY() { return obstacleY; }
	

};

