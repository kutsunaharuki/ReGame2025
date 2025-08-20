#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
	titleRender.Init("Assets/Sprite/Title000.dds", 1920.0f, 1080.0f);
	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	titleRender.Draw(rc);
}