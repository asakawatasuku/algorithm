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
	m_speed = Vector3::Zero;
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Up))
	{
		m_speed = Vector3::Forward * 0.2f;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Down))
	{
		m_speed = Vector3::Backward * 0.2f;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Right))
	{
		m_speed = Vector3::Right * 0.2f;
	}
	if (m_keyboard->IsPressed(DirectX::Keyboard::Keys::Left))
	{
		m_speed = Vector3::Left * 0.2f;
	}

	m_pos += m_speed;

	Base::Update();
}
