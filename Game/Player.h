#pragma once

class Player :public IGameObject
{
public:
	Player();
	~Player();
	//bool Start();
	void Update();
	bool Start();
	void Move();
	void Rotation();
	void PlayAnimation();
	void ManageState();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;
	Vector3 m_position;
	Vector3 moveSpeed;
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Run,
		enAnimationClip_Num
	};

	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController characterController;
	Quaternion rot;

	int playerState = 0;
	int jumpCount = 0;
	int maxjumpCount = 2;

	bool jump = true;

	int itemCount = 0;
};

