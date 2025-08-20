#include "stdafx.h"
#include "Item.h"
#include "Game.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

using namespace std;
namespace
{
	float GET_ITEM_LENGTH = 120.0f;
}
Item::Item()
{

}

Item::~Item()
{

}

bool Item::Start()
{
	m_box.Init("Assets/modelData/item00.tkm");
	m_box.SetPosition(m_pos);
	m_box.SetScale(m_scale);
	m_box.SetRotation(m_rot);
	m_box.Update();

	m_player = FindGO<Player>("BattleCharacter");

	g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/GetItemSe01.wav");

	//ボックスの当たり判定。
	/*physicsStaticObject.CreateFromModel(m_box.GetModel(),
		m_box.GetModel().GetWorldMatrix());*/
	return true;
}

void Item::Update()
{
	Rotation();

	Move();

	Vector3 diff = m_player->m_position - m_pos;

	if (diff.Length() <= GET_ITEM_LENGTH)
	{
		m_player->itemCount += 1;
		g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/GetItemSe01.wav");
		m_se = NewGO<SoundSource>(0);
		m_se->Init(0);
		m_se->Play(false);
		m_se->SetVolume(10.0f);
		DeleteGO(this);
	}
}

void Item::Move()
{
	m_box.SetPosition(m_pos);
	m_box.Update();
}

void Item::Rotation()
{
	m_rot.AddRotationDegY(5.0f);
	m_box.SetRotation(m_rot);
	m_box.Update();
}

void Item::Render(RenderContext& rc)
{
	m_box.Draw(rc);
}
