/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#include "Enemy.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	m_scale = DirectX::SimpleMath::Vector3(1.0f);
	m_pos = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 0.0f);
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// �X�V����
/// </summary>
void Enemy::Update()
{
	Base::Update();
}
