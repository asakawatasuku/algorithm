#include"Interception.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// コンストラクタ
//---------------------------------------
Interception::Interception() {

}

//---------------------------------------
// デストラクタ
//---------------------------------------
Interception::~Interception() {

}

//---------------------------------------
// 初期設定
//---------------------------------------
void Interception::Initialize(shared_ptr<Base> object, shared_ptr<Base> target) {
	m_object = object;
	m_target = target;
}

//---------------------------------------
// 処理
//---------------------------------------
void Interception::Update() {

	// 相対距離
	m_Sp = m_object->GetPos();
	m_Se = m_target->GetPos();

	m_Sr.x = m_Sp.x - m_Se.x;
	m_Sr.z = m_Sp.z - m_Se.z;

	// 相対速度
	m_Vp = Vector3(m_Sp.x + m_Se.x, m_Sp.y + m_Se.y, m_Sp.z + m_Se.z);
	//m_Ve = Vetor3();

	m_Vr = m_Vp - m_Ve;

	// 正規化
	m_Sr.Normalize();
	m_Vr.Normalize();

	//  接近時間
	m_Tc = 0;
	double distance = sqrt(m_Sr.x * m_Sr.x + m_Sr.z * m_Sr.z);
	double velcity = sqrt(m_Vr.x * m_Vr.x + m_Vr.z * m_Vr.z);
	if (!(0.000f <= velcity && velcity <= 0.000f)) {
		m_Tc = distance / velcity;
		m_Tc = fabs(m_Tc);
	}

	// 迎撃ポイントを求める
	m_point = m_Sp + m_Vp * m_Tc;

}