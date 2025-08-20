#pragma once

#include "sound/SoundSource.h"

class Game;
class Player;
class Item :public IGameObject
{
public:
	Item();
	~Item();
	bool Start();
	//更新処理。
	void Update();
	//移動処理。
	void Move();
	//回転処理。
	void Rotation();
	//描画処理。
	void Render(RenderContext& rc);

	ModelRender m_box;
	PhysicsStaticObject physicsStaticObject;
	Quaternion m_rot;

	Vector3 m_pos = Vector3::Zero;//Itemの座標。使う座標。
	Vector3 m_scale = Vector3(1.0f, 1.4f, 1.8f);//Itemの大きさ。
	Vector3 firstPosition;//Itemの最初の座標。

	Player      *     m_player  = nullptr;
	Game        *     game      = nullptr;
	SoundSource *     m_se      = nullptr;
};

