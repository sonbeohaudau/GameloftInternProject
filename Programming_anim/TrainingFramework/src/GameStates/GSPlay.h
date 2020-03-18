#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "GameObject\Player.h"
#include "GameObject\Obstacle.h"

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

	void GameEvent(std::shared_ptr<Obstacle> ob);
	void SetNewPostionForBullet();

private:

	//std::shared_ptr<Sprite2D> m_BackGround;
	//std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Player> ninja;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<Obstacle>> m_listObstacle;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

