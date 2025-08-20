#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "Item.h"
#include "Title.h"
#include "GameOver.h"
#include "GameClear.h"
#include "sound/SoundEngine.h"

Game::Game()
{
	
}

Game::~Game()
{
	DeleteGO(m_player);
	DeleteGO(gamecamera);
	for (Item* item : m_items)
	{
		DeleteGO(item);
	}
	m_items.clear();
	//DeleteGO(titleBGM);
	//DeleteGO(gameBGM);
}

bool Game::Start()
{
	//Playerのオブジェクトを作成する。
	m_player = NewGO<Player>(0, "BattleCharacter");

	//GameCameraのオブジェクトを作成する。
	gamecamera = NewGO<GameCamera>(0, "gamecamera");

	//SkyCubeのオブジェクトを作成する。
	m_skyCube = NewGO<SkyCube>(0, "skyCube");


	//SoundSourceのオブジェクトを作成する。
	/*g_soundEngine->ResistWaveFileBank(1, "Assets/Sound/gameBGM.wav");
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);*/


	//値を変えると環境光（明かり）を変更出来るやつ。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.2f);

	//カスケードシャドウのエリア率の設定。
	g_renderingEngine->SetCascadeNearAreaRates(0.01f, 0.1f, 0.5f);

	//レベルを構築する。
	m_levelRender.Init("Assets/modelData/Stage00.tkl", [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"Item") == true) {

			auto item = NewGO<Item>(0, "item");
			//配置座標、スケール、回転を取得する。
			item->m_pos = objData.position;
			item->m_scale = objData.scale;
			item->m_rot = objData.rotation;
			//後で削除するために、ボックスをプッシュしておく。
			m_items.push_back(item);

			//trueにすると、レベルの方でモデルが読み込まれない。
			return true;
		}
		return false;
		});

	return true;
}

void Game::Update()
{
	if (m_player->itemCount == 5)
	{
		auto gameclear = NewGO<GameClear>(0, "GameClear");
		DeleteGO(this);
	}

	if (m_player->m_position.y <= -1000.0f)
	{
		auto gameover = NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}
	// g_renderingEngine->DisableRaytracing();
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
	m_levelRender.Draw(rc);
}