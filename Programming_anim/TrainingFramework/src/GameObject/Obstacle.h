#pragma once
#include "Sprite2D.h"

enum obstacleType { SPIKE, SPIKEMONA, SPIKEMONB, BAT };

class Obstacle : public Sprite2D
{
	private:
		obstacleType m_obstacle;
		GLfloat obstacleY;

	public:
		Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
		virtual ~Obstacle();

		obstacleType GetObstacleType() { return m_obstacle; }

	
		void Update(GLfloat deltaTime, int screenSpeed);
		void SetType(obstacleType type) { m_obstacle = type; }
		void SetY(GLfloat oby) { obstacleY = oby; }
		GLfloat GetY() { return obstacleY; }
		float actionTime;

};

