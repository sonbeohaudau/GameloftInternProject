#pragma once
#include "Sprite2D.h"


enum ObstacleType { SPIKE, BAT, TINY, HOP, COBRA_SPIKE };

class Obstacle : public Sprite2D
{
	private:
		ObstacleType	m_type;
		GLfloat			m_obstacleY;
		GLint			m_specialMove;		
			// m_specialMove = 0: normal movement
			// m_specialMove = 1: move a bit faster
			// m_specialMove = 2: jump midway
			// m_specialMove = 3: pause midway a short amount of time

		GLfloat			m_actionTime;		// special time interval for some special moves

	public:
		Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, ObstacleType type);
		Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
		virtual ~Obstacle();

		ObstacleType	GetObstacleType() { return m_type; }

	
		void			Update(GLfloat deltaTime, int speed);
		void			SetType(ObstacleType type) { m_type = type; }
		void			SetY(GLfloat oby) { m_obstacleY = oby; }
		void			SetMove(GLint move) { m_specialMove = move; }
		void			SetTime(GLfloat time) { m_actionTime = time; }
		GLfloat			GetY() { return m_obstacleY; }
		void			SwitchType();	// call "Switch" but actually can remain type :)
		

};

