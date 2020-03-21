#include "Obstacle.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"

extern int SCREEN_SPEED;
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
		break;
	case SPIKEMONA:
		SetY(560);
		SetSize(114, 59);
		break;
	default: break;
	}
	
}

Obstacle::~Obstacle()
{
}

void Obstacle::Update(GLfloat deltaTime,int screenSpeed) {

	Set2DPosition(Get2DPosition().x - screenSpeed*deltaTime, obstacleY);
	if (Get2DPosition().x <= -screenWidth / 2) {		
		Set2DPosition(Get2DPosition().x + 2 * screenWidth, obstacleY);
	}
}





