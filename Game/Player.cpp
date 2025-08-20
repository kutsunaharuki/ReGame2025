#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//falseにするとそのまま静止してしまう。
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm",animationClips,enAnimationClip_Num,enModelUpAxisY);
	characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{

}

bool Player::Start()
{
	return true;
}

void Player::Update()
{
	Move();

	Rotation();

	PlayAnimation();

	ManageState();

	m_modelRender.Update();
	
}

void Player::Move()
{
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	right *= stickL.x * 600.0f;
	forward *= stickL.y * 600.0f;

	moveSpeed += right + forward;
	
	if (g_pad[0]->IsPress(enButtonB))
	{
		moveSpeed.x *= 1.6f;
		moveSpeed.z *= 1.6f;
	}

	if (characterController.IsOnGround())
	{
		moveSpeed.y = 0.0f;
		jumpCount = 0;
	}

	else {
		moveSpeed.y -= 9.0f * 2.0;
	}

	if (jumpCount < maxjumpCount)
	{
		jump = true;
	}
	else if (jumpCount >= maxjumpCount)
	{
		jump = false;
	}

	if (jump)
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			moveSpeed.y = 440.0f;
			jumpCount++;
		}
	}

	m_position = characterController.Execute(moveSpeed, 1.0f / 60.0f);
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		rot.SetRotationYFromDirectionXZ(moveSpeed);
		m_modelRender.SetRotation(rot);
	}
}

void Player::ManageState()
{
	if (characterController.IsOnGround() == false)
	{
		playerState = 1;
		return;
	}
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f)
	{
		playerState = 2;
		if (g_pad[0]->IsPress(enButtonB))
		{
			playerState = 3;
		}
	}
	else
	{
		playerState = 0;
	}
}



void Player::PlayAnimation()
{
	switch (playerState) {
	case 0:
		//待機モーション。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		//ジャンプモーション。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		//歩きモーション。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		//走りモーション。
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
	

}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
