#include "BreadCrumb.h"

using namespace std;
using namespace DirectX::SimpleMath;

const float BreadCrumb::BREAD_CRUMB_MAX_RANGE = 60.0f;
const float BreadCrumb::BREAD_COLLISION_RANGE = 15.0f;

/// <summary>
/// 初期化関数
/// </summary>
void BreadCrumb::Initialize(Base* object, Base* target)
{
	m_object = object;
	m_target = target;

	m_object->SetSpeed(Vector3::Forward * 0.1f);

	m_bread_array = new Vector3();
}

/// <summary>
/// 更新関数
/// </summary>
void BreadCrumb::Update()
{
	// 既に到着している場合
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		if (LMath::IsCollisionCircle(m_target_bread, m_object->GetPos(), BREAD_COLLISION_RANGE))
		{
			m_target_bread.x = -1.0f;
			m_target_bread.z = -1.0f;
		}
	}

	// パンくずがない場合探す
	if (!(m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f))
	{
		for (int i = 0; i < m_bread_num; i++)
		{
			Vector3 bread_pos = m_bread_array[i];
			if (!(bread_pos.x >= 0.0f && bread_pos.z >= 0.0f))
			{
				continue;
			}

			// 範囲外のものは判定から外す
			const float r = BREAD_CRUMB_MAX_RANGE + (BREAD_COLLISION_RANGE * 2.0f);
			if (!LMath::IsCollisionCircle(bread_pos, m_object->GetPos(), r)) {
				continue;
			}

			// パンくずがある位置を参照
			m_target_bread = bread_pos;
			break;
		}
	}

	Vector3 direction = m_object->GetRot();
	// 目標のパンくずに向かう
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		Vector3 dir_vec = LMath::Normalize(m_object->GetPos(), m_target_bread);

		direction.y = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));
	}
	// 目標のパンくずがないならランダムで移動
	else
	{
		float displace = DirectX::XMConvertToRadians(m_angle);
		if (rand() % 2)
		{
			displace *= -1.0f;
		}

		direction.y = ADJUST_RAD(direction.y + displace);
	}

	// 目標座標に向かって移動
	Vector3 pos;
	pos.x += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * cosf(direction.y);
	pos.z += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * -sinf(direction.y);
	m_object->SetPos(pos);
	m_object->SetRot(direction);
}

/// <summary>
/// パンくずを落とす
/// </summary>
void BreadCrumb::DropBreadCrumb()
{
	// パンくずの集合
	if (!(m_bread_array && (m_bread_num > 0)))
	{
		return;
	}

	// 落としたパンくずより一定範囲離れていたら
	if (LMath::IsCollisionCircle(m_bread_array[0], m_target->GetPos(), BREAD_CRUMB_MAX_RANGE))
	{
		return;
	}
	// パンくずの鮮度更新
	for (int i = m_bread_num - 1; i >= 1; --i) 
	{
		m_bread_array[i] = m_bread_array[i - 1];
	}

	// 新しいパンくずを登録
	m_bread_array[0] = m_target->GetPos();

}

/// <summary>
/// 終了処理
/// </summary>
void BreadCrumb::Finalize()
{
	delete[] m_bread_array;
}
