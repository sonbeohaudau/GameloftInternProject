#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSPause :
	public GameStateBase
{
public:
	GSPause();
	~GSPause();

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
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  m_Text_paused;
	std::shared_ptr<GameButton> m_bgmButton;
};

