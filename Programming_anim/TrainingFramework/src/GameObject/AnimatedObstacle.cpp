#include "AnimatedObstacle.h"

#include "Texture.h"
#include "GameManager/ResourceManagers.h"
#include "Gameplay.h"

extern int SCREEN_SPEED;
extern int screenWidth;
extern int screenHeight;


AObstacle::AObstacle(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime)
	: SpriteAnimation(model, shader, texture, numFrames, frameTime)
{
	SetY(545);
	SetSize(60, 60);
}

AObstacle::~AObstacle()
{
}

void AObstacle::Update(GLfloat deltaTime, int screenSpeed, GLfloat x) {
	
/*	Set2DPosition(Get2DPosition().x - screenSpeed*deltaTime, obstacleY);
	if (Get2DPosition().x <= -screenWidth / 4) {
		Set2DPosition(Get2DPosition().x + 2 * screenWidth, obstacleY);
		Gameplay::GetInstance()->SetScore(Gameplay::GetInstance()->GetScore() + 1);
	}
*/
	Set2DPosition(x, obstacleY);

	m_currentTime += deltaTime;
	if (m_currentTime >= m_frameTime)
	{
		m_currentFrame++;
		if (m_currentFrame >= m_numFrames)
			m_currentFrame = 0;
		m_currentTime -= m_frameTime;
	}
}