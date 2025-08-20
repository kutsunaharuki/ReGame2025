#include "stdafx.h"
#include "GameClear.h"
#include "Game.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

GameClear::GameClear()
{
	
}

GameClear::~GameClear()
{

}

bool GameClear::Start()
{
	gameclearRender.Init("Assets/Sprite/GameClear000.dds", 1920.0f, 1080.0f);
	gameclearRender.Update();
	return true;
}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "Title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	gameclearRender.Draw(rc);
}
