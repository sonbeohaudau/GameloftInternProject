#pragma once

enum ninjaState { RUN, JUMP, SLIDE};

class Player {
	public:
		Player() { m_playerState = RUN; }
		virtual ~Player() {};
		
		void SetPlayerState(ninjaState playerState) { m_playerState = playerState; }
		ninjaState GetPlayerState() { return m_playerState; }

	private:
		ninjaState m_playerState;
};

class PlayerRun : public Player {
	PlayerRun() {};
	~PlayerRun() {};
};

class PlayerJump : public Player {
	PlayerJump() {};
	~PlayerJump() {};
};

class PlayerSlide : public Player {
	PlayerSlide() {};
	~PlayerSlide() {};
};

