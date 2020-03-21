#include "Gameplay.h"
#include "Texture.h"
#include "GameManager\ResourceManagers.h"
#include "GameStates\GameStateMachine.h"
#define LEFT_PLAYER_HITBOX_FIX 20
#define RIGHT_PLAYER_HITBOX_FIX 40
#define TOP_PLAYER_HITBOX_FIX 8
#define BOTTOM_PLAYER_HITBOX_FIX 30

bool Gameplay::CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<Obstacle> ob) {

	
	// Set player hit box
	GLint x1p = ninja->Get2DPosition().x - ninja->GetWidth() / 2 + LEFT_PLAYER_HITBOX_FIX;
	GLint x2p = ninja->Get2DPosition().x + ninja->GetWidth() / 2 - RIGHT_PLAYER_HITBOX_FIX;
	GLint y1p = ninja->Get2DPosition().y - ninja->GetHeight() / 2 + TOP_PLAYER_HITBOX_FIX;
	GLint y2p = ninja->Get2DPosition().y + ninja->GetHeight() / 2 - BOTTOM_PLAYER_HITBOX_FIX;

	// Set obstacle hit box
	GLint x1o = ob->Get2DPosition().x - ob->GetWidth() / 2;
	GLint x2o = ob->Get2DPosition().x + ob->GetWidth() / 2;
	GLint y1o = ob->Get2DPosition().y - ob->GetHeight() / 2;
	GLint y2o = ob->Get2DPosition().y + ob->GetHeight() / 2;

	// Check collision between player and obstacle
	if (((x1p > x1o && x1p < x2o) || (x2p > x1o && x2p < x2o) || (x1o > x1p && x1o < x2p)) && ((y1p > y1o && y1p < y2o) || (y2p > y1o && y2p < y2o) || (y1o > y1p && y1o < y2p))) {
		return 1;
		//printf("%d %d %d %d %d %d %d %d \n", x1p, x2p, y1p, y2p, x1o, x2o, y1o, y2o);
	}
	return 0;
}

bool Gameplay::CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<AObstacle> ob) {


	// Set player hit box
	GLint x1p = ninja->Get2DPosition().x - ninja->GetWidth() / 2 + LEFT_PLAYER_HITBOX_FIX;
	GLint x2p = ninja->Get2DPosition().x + ninja->GetWidth() / 2 - RIGHT_PLAYER_HITBOX_FIX;
	GLint y1p = ninja->Get2DPosition().y - ninja->GetHeight() / 2 + TOP_PLAYER_HITBOX_FIX;
	GLint y2p = ninja->Get2DPosition().y + ninja->GetHeight() / 2 - BOTTOM_PLAYER_HITBOX_FIX;

	// Set obstacle hit box
	GLint x1o = ob->Get2DPosition().x - ob->GetWidth() / 2;
	GLint x2o = ob->Get2DPosition().x + ob->GetWidth() / 2;
	GLint y1o = ob->Get2DPosition().y - ob->GetHeight() / 2;
	GLint y2o = ob->Get2DPosition().y + ob->GetHeight() / 2;

	// Check collision between player and obstacle
	if (((x1p > x1o && x1p < x2o) || (x2p > x1o && x2p < x2o) || (x1o > x1p && x1o < x2p)) && ((y1p > y1o && y1p < y2o) || (y2p > y1o && y2p < y2o) || (y1o > y1p && y1o < y2p))) {
		return 1;
		//printf("%d %d %d %d %d %d %d %d \n", x1p, x2p, y1p, y2p, x1o, x2o, y1o, y2o);
	}
	return 0;
}

void Gameplay::SetUp() {
	switch (m_gamePhase) {
	case 1:
		SetSpeed(600);
		SetNumObs(2);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
}

