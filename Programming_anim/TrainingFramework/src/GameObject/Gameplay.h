#pragma once
#include <memory>
#include "Player.h"
#include "Obstacle.h"
#include "AnimatedObstacle.h"


class Gameplay {
	private:


	public:
		Gameplay() {}
		virtual ~Gameplay() {}

		
		bool CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<Obstacle> ob);
		bool CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<AObstacle> ob);


};