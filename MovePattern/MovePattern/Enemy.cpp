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
}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update()
{
	Base::Update();
}
