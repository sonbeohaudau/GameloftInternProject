/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSSettings.h"
#include "GSPause.h"
#include "GSCredits.h"
#include "GSGameOver.h"

#include "GameStatebase.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_Settings:
		gs = std::make_shared<GSSettings>();
		break;
	case STATE_Pause:
		gs = std::make_shared<GSPause>();
		break;
	case STATE_Credits:
		gs = std::make_shared<GSCredits>();
		break;
	case STATE_GameOver:
		gs = std::make_shared<GSGameOver>();
	default:
		break;
	}
	return gs;
}