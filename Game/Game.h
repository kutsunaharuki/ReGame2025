#pragma once
#include "sound/SoundSource.h"
#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Item;
class Title;
class GameClear;
class GameOver;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	LevelRender m_levelRender;
	std::vector<Item*> m_items;//itemÅB

	Player        *       m_player     = nullptr;
	GameCamera    *       gamecamera   = nullptr;
	Item          *       item         = nullptr;
	Title         *       title        = nullptr;
	//SoundSource   *       gameBGM      = nullptr;
	GameClear     *       gameclear    = nullptr;
	GameOver      *       gameover     = nullptr;
	SkyCube       *       m_skyCube    = nullptr;
};

