#include"Interception.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// 初期設定
//---------------------------------------
void Interception::Initialize(Base* object, Base* target) {
	m_object = object;
	m_target = target;
	m_stepCount = 0;
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
	Vector3 vel;
	vel.x = m_object->GetSpeed().x - m_target->GetSpeed().x;
	vel.z = m_object->GetSpeed().z - m_target->GetSpeed().z;


	// 正規化
	m_Sr.Normalize();

	//  接近時間
	m_Tc = 0;
	double distance = sqrt(m_Sr.x * m_Sr.x + m_Sr.z * m_Sr.z);
	double velcity = sqrt(m_Vr.x * m_Vr.x + m_Vr.z * m_Vr.z);
	if (!(0.000f <= velcity && velcity <= 0.000f)) {
		m_Tc = distance / velcity;
		m_Tc = fabs(m_Tc);

		//予測ポイントを目標地点に設定.
		m_point.x = m_Sp.x + (LONG)((double)m_Vp.x * m_Tc);
		m_point.y = m_Sp.y + (LONG)((double)m_Vp.y * m_Tc);
	}

	//LOSアルゴリズムを使って移動.
	UpdateBresenham(m_Sp, m_point);
}

void Interception::UpdateBresenham(Vector3& now, Vector3 &target)
{
	if ((m_prevTargetPos.x == target.x) && (m_prevTargetPos.y == target.y)) {
		//目標地点が変わっていない場合は，前もって計算しておいたものを使う.
		if (m_stepCount >= NEXT_POS_MAX) { return; }
		if (m_nextStepPos[m_stepCount].x < 0 && m_nextStepPos[m_stepCount].y < 0) {
			return;
		}
	}
	else {
		//目標地点が変わったので経路を再計算する.
		m_stepCount = 0;
		for (int i = 0; i < NEXT_POS_MAX; ++i) {
			m_nextStepPos[i].x = m_nextStepPos[i].y = -1;
		}

		Vector3 pos = now;

		int deltaX = target.x - pos.x;
		int deltaY = target.y - pos.y;

		const int stepX = (deltaX >= 0) ? 1 : -1;
		const int stepY = (deltaY >= 0) ? 1 : -1;

		deltaX = abs(deltaX);
		deltaY = abs(deltaY);

		if (deltaY > deltaX) {
			//Y方向が長い.
			int f = (deltaX << 1) - deltaY;   //条件式初期値.
			for (int i = 0; i < deltaY; ++i) {
				if (f >= 0) {
					pos.x += stepX;           //X方向更新.
					f -= (deltaY << 1); //X方向の移動を加味.
				}
				pos.y += stepY;           //Y方向更新.
				f += (deltaX << 1); //Y方向の移動を加味.

				m_nextStepPos[i] = pos;
			}
		}
		else {
			//X方向が長い.
			int f = (deltaY << 1) - deltaX;   //条件式初期値.
			for (int i = 0; i < deltaX; ++i) {
				if (f >= 0) {
					pos.y += stepY;           //Y方向更新.
					f -= (deltaX << 1); //Y方向の移動を加味.
				}
				pos.x += stepX;           //X方向更新.
				f += (deltaY << 1); //X方向の移動を加味.

				m_nextStepPos[i] = pos;
			}
		}

		m_prevTargetPos = target;   //探索時の目標地点は保存しておく.
	}

	now = m_nextStepPos[m_stepCount++];
}

void Interception::Finalize(){
}


