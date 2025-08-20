#include "stdafx.h"
#include "GameOver.h"
#include "Game.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

GameOver::GameOver()
{

}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
	gameoverRender.Init("Assets/Sprite/GameOver001.dds", 1920.0f, 1080.0f);
	gameoverRender.Update();
	return true;
}

void GameOver::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void GameOver::Render(RenderContext& rc)
{
	gameoverRender.Draw(rc);
}
