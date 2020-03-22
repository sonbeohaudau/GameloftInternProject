#include "GSSettings.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern float bgmLoop;
extern int gameDifficulty;
extern int character;
extern int backGround;
extern bool button_update;
extern bool bgm_on;


GSSettings::GSSettings()
{

}


GSSettings::~GSSettings()
{
}



void GSSettings::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_relax");

	// BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// Background options
	texture = ResourceManagers::GetInstance()->GetTexture("bg_autumn_setting");
	auto sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(250, 300);
	sprite2D->SetSize(300, 200);
	m_listSprite2D.push_back(sprite2D);

	texture = ResourceManagers::GetInstance()->GetTexture("bg_park_setting");
	sprite2D = std::make_shared<Sprite2D>(model, shader, texture);
	sprite2D->Set2DPosition(800, 300);
	sprite2D->SetSize(300, 200);
	m_listSprite2D.push_back(sprite2D);

	// return main menu button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	m_backButton = std::make_shared<GameButton>(model, shader, texture);
	m_backButton->Set2DPosition(100, 100);
	m_backButton->SetSize(GAME_BUTTON_SIZE, GAME_BUTTON_SIZE);
	m_backButton->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(m_backButton);

	// button for background, character and difficulty options

	// background options
	texture = ResourceManagers::GetInstance()->GetTexture("button_selected");
	m_bgButton1 = std::make_shared<GameButton>(model, shader, texture);
	m_bgButton1->Set2DPosition(500, 300);
	m_bgButton1->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_bgButton1->SetOnClick([]() {
		backGround = 1;
		button_update = true;
	});
	m_listButton.push_back(m_bgButton1);

	m_bgButton2 = std::make_shared<GameButton>(model, shader, texture);
	m_bgButton2->Set2DPosition(1050, 300);
	m_bgButton2->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_bgButton2->SetOnClick([]() {
		backGround = 2;
		button_update = true;
	});
	m_listButton.push_back(m_bgButton2);

	// character options

	m_charaButton1 = std::make_shared<GameButton>(model, shader, texture);
	m_charaButton1->Set2DPosition(200, 700);
	m_charaButton1->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_charaButton1->SetOnClick([]() {
		character = 1;
		button_update = true;
	});
	m_listButton.push_back(m_charaButton1);

	m_charaButton2 = std::make_shared<GameButton>(model, shader, texture);
	m_charaButton2->Set2DPosition(400, 700);
	m_charaButton2->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_charaButton2->SetOnClick([]() {
		character = 2;
		button_update = true;
	});
	m_listButton.push_back(m_charaButton2);

	// difficulty options

	m_difButton1 = std::make_shared<GameButton>(model, shader, texture);
	m_difButton1->Set2DPosition(700, 550);
	m_difButton1->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_difButton1->SetOnClick([]() {
		gameDifficulty = 1;
		button_update = true;
	});
	m_listButton.push_back(m_difButton1);

	m_difButton2 = std::make_shared<GameButton>(model, shader, texture);
	m_difButton2->Set2DPosition(900, 550);
	m_difButton2->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_difButton2->SetOnClick([]() {
		gameDifficulty = 2;
		button_update = true;
	});
	m_listButton.push_back(m_difButton2);

	m_difButton3 = std::make_shared<GameButton>(model, shader, texture);
	m_difButton3->Set2DPosition(700, 650);
	m_difButton3->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_difButton3->SetOnClick([]() {
		gameDifficulty = 3;
		button_update = true;
	});
	m_listButton.push_back(m_difButton3);

	m_difButton4 = std::make_shared<GameButton>(model, shader, texture);
	m_difButton4->Set2DPosition(900, 650);
	m_difButton4->SetSize(GAME_BUTTON_SIZE / 2, GAME_BUTTON_SIZE / 2);
	m_difButton4->SetOnClick([]() {
		gameDifficulty = 4;
		button_update = true;
	});
	m_listButton.push_back(m_difButton4);

	//"SETTINGS" text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_settings = std::make_shared< Text>(shader, font, "SETTINGS", TEXT_COLOR::RED, 1.0);
	m_Text_settings->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));

	// Other texts
	auto sometext = std::make_shared< Text>(shader, font, "Select background", TEXT_COLOR::RED, 1.0);
	sometext->Set2DPosition(Vector2(500, 180));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Select character", TEXT_COLOR::RED, 1.0);
	sometext->Set2DPosition(Vector2(200, 480));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Select difficulty", TEXT_COLOR::RED, 1.0);
	sometext->Set2DPosition(Vector2(750, 480));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Very Easy", TEXT_COLOR::WHILE, 1.0);
	sometext->Set2DPosition(Vector2(740, 550));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Easy", TEXT_COLOR::GREEN, 1.0);
	sometext->Set2DPosition(Vector2(940, 550));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Medium", TEXT_COLOR::YELLOW, 1.0);
	sometext->Set2DPosition(Vector2(740, 650));
	m_listText.push_back(sometext);

	sometext = std::make_shared< Text>(shader, font, "Hard", TEXT_COLOR::PURPLE, 1.0);
	sometext->Set2DPosition(Vector2(940, 650));
	m_listText.push_back(sometext);

	// Character animations
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("running");
	auto chara = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.06f);
	chara->Set2DPosition(200, 580);
	chara->SetSize(120, 150);
	m_listSpriteAnimations.push_back(chara);

	texture = ResourceManagers::GetInstance()->GetTexture("run_girl");
	chara = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.06f);
	chara->Set2DPosition(400, 580);
	chara->SetSize(120, 150);
	m_listSpriteAnimations.push_back(chara);

	// Set up button textures
	UpdateButtons();
}

void GSSettings::Exit()
{
}


void GSSettings::Pause()
{

}

void GSSettings::Resume()
{

}


void GSSettings::HandleEvents()
{

}

void GSSettings::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == 1) {
		switch (key) {
		case KEY_BACK: GameStateMachine::GetInstance()->PopState();
			break;
		default:
			break;
		}

	}
}

void GSSettings::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSettings::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	bgmLoop -= deltaTime;
	if (bgmLoop <= 0) {
		if (bgm_on == true) ResourceManagers::GetInstance()->PlaySound("bgm_main_menu");
		bgmLoop = 14.3;
	}

	for (auto it : m_listSpriteAnimations)
	{
		it->Update(deltaTime);
	}

	if (button_update) {
		UpdateButtons();
	}
}

void GSSettings::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_settings->Draw();
	for (auto bg : m_listSprite2D)
	{
		bg->Draw();
	}
	for (auto it : m_listText)
	{
		it->Draw();
	}
	for (auto it : m_listSpriteAnimations)
	{
		it->Draw();
	}
}

void GSSettings::UpdateButtons() {
	auto newTexture = ResourceManagers::GetInstance()->GetTexture("button_unselected");
	for (auto it : m_listButton)
	{
		it->SetTexture(newTexture);
	}
	newTexture = ResourceManagers::GetInstance()->GetTexture("button_back");
	m_backButton->SetTexture(newTexture);
	newTexture = ResourceManagers::GetInstance()->GetTexture("button_selected");
	switch (backGround) {
	case 1: m_bgButton1->SetTexture(newTexture); break;
	case 2: m_bgButton2->SetTexture(newTexture); break;
	default: break;
	}	
	switch (character) {
	case 1: m_charaButton1->SetTexture(newTexture); break;
	case 2: m_charaButton2->SetTexture(newTexture); break;
	default: break;
	}
	switch (gameDifficulty) {
	case 1: m_difButton1->SetTexture(newTexture); break;
	case 2: m_difButton2->SetTexture(newTexture); break;
	case 3: m_difButton3->SetTexture(newTexture); break;
	case 4: m_difButton4->SetTexture(newTexture); break;
	default: break;
	}
	
	button_update = false;
}
