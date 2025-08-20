#pragma once
#include "sound/SoundSource.h"
class GameClear:public IGameObject
{
public:
	GameClear();
	~GameClear();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender gameclearRender;

	SoundSource* gameclearSe = nullptr;
};

