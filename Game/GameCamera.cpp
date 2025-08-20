#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
	
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//注視点からの視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 120.0f, -200.0f);
	m_player = FindGO<Player>("BattleCharacter");
	g_camera3D->SetNear(10.0f);
	g_camera3D->SetFar(100000.0f);
	return true;
}

void GameCamera::Update()
{
	Vector3 target = m_player->m_position;
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	Vector3 m_toCameraPosOld = m_toCameraPos;

	//Y軸周りの回転。
	qrot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qrot.Apply(m_toCameraPos);

	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qrot.SetRotationDeg(axisX, 1.3f * y);
	qrot.Apply(m_toCameraPos);
	
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 pos = target + m_toCameraPos;
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	g_camera3D->Update();
}