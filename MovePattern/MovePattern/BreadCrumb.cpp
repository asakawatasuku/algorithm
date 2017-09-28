#include "BreadCrumb.h"

using namespace std;

const float BreadCrumb::BREAD_CRUMB_MAX_RANGE = 60.0f;
const float BreadCrumb::BREAD_COLLISION_RANGE = 15.0f;

/// <summary>
/// 初期化関数
/// </summary>
void BreadCrumb::Initiarize(shared_ptr<Base> object, shared_ptr<Base> target)
{
	m_object = object;
	m_target = target;
}

/// <summary>
/// 更新関数
/// </summary>
/// <param name="pos">現在の位置</param>
/// <param name="direction">向き</param>
/// <param name="velocity">速度</param>
void BreadCrumb::Update(VECTOR& pos, float& direction, float velocity)
{
	// 既に到着している場合
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		if (LMath::IsCollisionCircle(m_target_bread, pos, BREAD_COLLISION_RANGE))
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
			VECTOR bread_pos = m_bread_array[i];
			if (!(bread_pos.x >= 0.0f && bread_pos.z >= 0.0f))
			{
				continue;
			}

			// 範囲外のものは判定から外す
			const float r = BREAD_CRUMB_MAX_RANGE + (BREAD_COLLISION_RANGE * 2.0f);
			if (!LMath::IsCollisionCircle(bread_pos, pos, r)) {
				continue;
			}

			// パンくずがある位置を参照
			m_target_bread = bread_pos;
			break;
		}
	}

	// 目標のパンくずに向かう
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		VECTOR dir_vec = LMath::Normalize(pos, m_target_bread);

		direction = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));
	}
	else
	{
		direction = 0;
	}

	// 目標座標に向かって移動
	pos.x += velocity * cosf(direction);
	pos.z += velocity * -sinf(direction);
}

/// <summary>
/// パンくずを落とす
/// </summary>
/// <param name="pos">現在の位置</param>
void BreadCrumb::DropBreadCrumb(const VECTOR& pos)
{
	// パンくずの集合
	if (!(m_bread_array && (m_bread_num > 0)))
	{
		return;
	}

	// 落としたパンくずより一定範囲離れていたら
	if (LMath::IsCollisionCircle(m_bread_array[0], pos, BREAD_CRUMB_MAX_RANGE))
	{
		return;
	}
	// パンくずの鮮度更新
	for (int i = m_bread_num - 1; i >= 1; --i) 
	{
		m_bread_array[i] = m_bread_array[i - 1];
	}

	// 新しいパンくずを登録
	m_bread_array[0] = pos;

}
