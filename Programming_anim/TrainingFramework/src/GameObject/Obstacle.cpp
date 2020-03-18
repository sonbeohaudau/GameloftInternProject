#include "Obstacle.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"

extern int SCREEN_SPEED;
extern int screenWidth; 
extern int screenHeight; 


Obstacle::Obstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(GLfloat deltaTime,int screenSpeed) {
/*	switch (m_obstacle) {
	case SPIKE: obstacleY = 670; break;
	case SPIKEMONA: obstacleY = 600; break;
	default: obstacleY = 670; break;
	}	*/
	Set2DPosition(Get2DPosition().x - screenSpeed*deltaTime, obstacleY);
	if (Get2DPosition().x <= -screenWidth / 2) {		
		Set2DPosition(Get2DPosition().x + 2 * screenWidth, obstacleY);
	}
}





