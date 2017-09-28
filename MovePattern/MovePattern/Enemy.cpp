/// <summary>
/// エネミークラス
/// </summary>

#include "Enemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_scale = DirectX::SimpleMath::Vector3(1.0f);
	m_pos = DirectX::SimpleMath::Vector3(5.0f, 0.0f, 0.0f);

	m_moving_pattern = std::make_unique<MovingPattern>();
}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// 初期化処理
/// </summary>
void Enemy::Initialize(const std::wstring& file_name)
{
	Base::Initialize(file_name);

	m_moving_pattern->Initialize(this, m_target);
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	Base::Update();
}



/// <summary>
/// 解放処理
/// </summary>
void Enemy::Finalize()
{
	m_moving_pattern->Finalize();
	delete m_target;
}
