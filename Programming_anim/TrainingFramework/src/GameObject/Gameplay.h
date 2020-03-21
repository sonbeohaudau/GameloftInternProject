#pragma once
#include <memory>
#include "Player.h"
#include "Obstacle.h"
#include "AnimatedObstacle.h"
#include "GameManager/Singleton.h"


class Gameplay: public CSingleton<Gameplay>
{
	private:
		int m_score;
		int m_gamePhase;
		int m_screenSpeed;	
		int m_numOfObs;		// number of obstacle types available in a phase

	public:
		Gameplay() {}
		virtual ~Gameplay() {}

		int GetScore() { return m_score; }
		void SetScore(int score) { m_score = score; }
		int GetPhase() { return m_gamePhase; }
		void SetPhase(int phase) { m_gamePhase = phase; }
		int GetSpeed() { return m_screenSpeed; }
		void SetSpeed(int speed) { m_screenSpeed = speed; }
		int GetNumObs() { return m_numOfObs; }
		void SetNumObs(int numObs) { m_numOfObs = numObs; }

		void SetUp();
		bool CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<Obstacle> ob);
		bool CheckCollision(std::shared_ptr<Player> ninja, std::shared_ptr<AObstacle> ob);


};