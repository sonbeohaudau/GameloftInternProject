#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "GameObject\Player.h"
#include "GameObject\Obstacle.h"
#include "GameObject\Gameplay.h"
#include "GameObject\AnimatedObstacle.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void GameOver();



private:

	
	bool m_update;		// =0 -> Stop update
	bool m_dead;		// =1 -> Player die (Game over)
	float GameOverTime;	// Time of character dead animation
	std::shared_ptr<Text>  m_score;
	std::string tmpscore;
	std::shared_ptr<Player> m_ninja;
//	std::shared_ptr<Gameplay> m_gameplay;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
//	std::vector < std::shared_ptr<Obstacle>> m_listObstacle;
	std::shared_ptr<Obstacle> m_obstacle1;
	std::shared_ptr<Obstacle> m_obstacle2;
	std::shared_ptr<AObstacle> m_bat1;
	std::shared_ptr<AObstacle> m_bat2;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

