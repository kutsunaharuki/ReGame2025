#pragma once
class Player;
class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	void Move();
	Player* m_player = nullptr;

	Quaternion qrot;
	Vector3 m_toCameraPos;
	Vector3 CameraPos;
	Vector3 targetPos;
};

