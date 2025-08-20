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
	//�X�V�����B
	void Update();
	//�ړ������B
	void Move();
	//��]�����B
	void Rotation();
	//�`�揈���B
	void Render(RenderContext& rc);

	ModelRender m_box;
	PhysicsStaticObject physicsStaticObject;
	Quaternion m_rot;

	Vector3 m_pos = Vector3::Zero;//Item�̍��W�B�g�����W�B
	Vector3 m_scale = Vector3(1.0f, 1.4f, 1.8f);//Item�̑傫���B
	Vector3 firstPosition;//Item�̍ŏ��̍��W�B

	Player      *     m_player  = nullptr;
	Game        *     game      = nullptr;
	SoundSource *     m_se      = nullptr;
};

