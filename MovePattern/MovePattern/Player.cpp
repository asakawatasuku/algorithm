/// <summary>
/// プレイヤークラス
/// </summary>

#include "Player.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
}



/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}



/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	m_speed = 0.0f;
	Vector3 dir;
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Up))
	{
		m_speed = 0.2f;
		dir = Vector3::Forward * m_speed;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Down))
	{
		m_speed = 0.2f;
		dir = Vector3::Backward * m_speed;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Right))
	{
		m_speed = 0.2f;
		dir = Vector3::Right * m_speed;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Left))
	{
		m_speed = 0.2f;
		dir = Vector3::Left * m_speed;
	}

	m_pos += dir;

	Base::Update();
}



/// <summary>
/// 解放処理
/// </summary>
void Player::Finalize()
{
	delete m_keyboard;
}
