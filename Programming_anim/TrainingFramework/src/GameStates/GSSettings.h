#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "GameObject\AnimatedObstacle.h"

class GSSettings :
	public GameStateBase
{
public:
	GSSettings();
	~GSSettings();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void UpdateButtons();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>	m_listText;
	std::shared_ptr<GameButton> m_backButton;

	// button for background, character and difficulty options
	std::shared_ptr<GameButton> m_bgButton1;
	std::shared_ptr<GameButton> m_bgButton2;
	std::shared_ptr<GameButton> m_charaButton1;
	std::shared_ptr<GameButton> m_charaButton2;
	std::shared_ptr<GameButton> m_difButton1;
	std::shared_ptr<GameButton> m_difButton2;
	std::shared_ptr<GameButton> m_difButton3;
	std::shared_ptr<GameButton> m_difButton4;

	std::shared_ptr<Text>  m_Text_settings;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;

};

