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
	//Player�̃I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player>(0, "BattleCharacter");

	//GameCamera�̃I�u�W�F�N�g���쐬����B
	gamecamera = NewGO<GameCamera>(0, "gamecamera");

	//SkyCube�̃I�u�W�F�N�g���쐬����B
	m_skyCube = NewGO<SkyCube>(0, "skyCube");


	//SoundSource�̃I�u�W�F�N�g���쐬����B
	/*g_soundEngine->ResistWaveFileBank(1, "Assets/Sound/gameBGM.wav");
	gameBGM = NewGO<SoundSource>(1);
	gameBGM->Init(1);
	gameBGM->Play(true);*/


	//�l��ς���Ɗ����i������j��ύX�o�����B
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.2f);

	//�J�X�P�[�h�V���h�E�̃G���A���̐ݒ�B
	g_renderingEngine->SetCascadeNearAreaRates(0.01f, 0.1f, 0.5f);

	//���x�����\�z����B
	m_levelRender.Init("Assets/modelData/Stage00.tkl", [&](LevelObjectData& objData) {

		if (objData.EqualObjectName(L"Item") == true) {

			auto item = NewGO<Item>(0, "item");
			//�z�u���W�A�X�P�[���A��]���擾����B
			item->m_pos = objData.position;
			item->m_scale = objData.scale;
			item->m_rot = objData.rotation;
			//��ō폜���邽�߂ɁA�{�b�N�X���v�b�V�����Ă����B
			m_items.push_back(item);

			//true�ɂ���ƁA���x���̕��Ń��f�����ǂݍ��܂�Ȃ��B
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