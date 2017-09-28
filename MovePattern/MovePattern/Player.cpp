/// <summary>
/// �v���C���[�N���X
/// </summary>

#include "Player.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}



/// <summary>
/// �X�V����
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
