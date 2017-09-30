/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#include "Enemy.h"
#include "BreadCrumb.h"
#include "Pursuit.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	m_scale = DirectX::SimpleMath::Vector3(1.0f);
	m_pos = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 0.0f);

	m_moving_pattern = std::make_unique<BreadCrumb>();
}



/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// ����������
/// </summary>
void Enemy::Initialize(const std::wstring& file_name)
{
	Base::Initialize(file_name);

	m_moving_pattern->Initialize(this, m_target);
}



/// <summary>
/// �X�V����
/// </summary>
void Enemy::Update()
{
	m_moving_pattern->DropBreadCrumb();
	m_moving_pattern->Update();

	Base::Update();
}



/// <summary>
/// �������
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
}
