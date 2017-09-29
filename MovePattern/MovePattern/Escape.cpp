#include "Escape.h"

using namespace DirectX::SimpleMath;

void Escape::Initialize(Base * object, Base * target)
{
	m_object = object;
	m_target = target;
	m_object->SetSpeed(Vector3::Forward * 0.05f);

}

void Escape::Update()
{
	// プレイヤー座標から敵座標の差を求める
	m_dif_position = m_object->GetPos() - m_target->GetPos();
	// 求めた差を正規化する
	m_dif_position.Normalize();

	// 追跡移動量を求める
	m_escape = m_dif_position * m_object->GetSpeed().Distance(Vector3::Zero, m_object->GetSpeed());

	m_object->SetSpeed(m_escape);

}

void Escape::Finalize()
{
}
