#include "Pursuit.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// 初期設定
//---------------------------------------
void Pursuit::Initialize(shared_ptr<Base> object, shared_ptr<Base> target) {
	m_object = object;
	m_target = target;
	m_object->SetSpeed(Vector3());
}

//---------------------------------------
// 処理
//---------------------------------------
void Pursuit::Update() {

	// プレイヤー座標から敵座標の差を求める
	m_Dif_position = m_object->GetPos() - m_target->GetPos();
	// 求めた差を正規化する
	m_Dif_position.Normalize();

	// 追跡移動量を求める
	m_ttd = m_Dif_position * m_object->GetSpeed().Distance(Vector3::Zero, m_object->GetSpeed());
}
	