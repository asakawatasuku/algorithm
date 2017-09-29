#include"Interception.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// �����ݒ�
//---------------------------------------
void Interception::Initialize(Base* object, Base* target) {
	m_object = object;
	m_target = target;
	m_stepCount = 0;
}

//---------------------------------------
// ����
//---------------------------------------
void Interception::Update() {

	// ���΋���
	m_Sp = m_object->GetPos();
	m_Se = m_target->GetPos();

	m_Sr.x = m_Sp.x - m_Se.x;
	m_Sr.z = m_Sp.z - m_Se.z;

	// ���Α��x
	Vector3 vel;
	vel.x = m_object->GetSpeed().x - m_target->GetSpeed().x;
	vel.z = m_object->GetSpeed().z - m_target->GetSpeed().z;


	// ���K��
	m_Sr.Normalize();

	//  �ڋߎ���
	m_Tc = 0;
	double distance = sqrt(m_Sr.x * m_Sr.x + m_Sr.z * m_Sr.z);
	double velcity = sqrt(m_Vr.x * m_Vr.x + m_Vr.z * m_Vr.z);
	if (!(0.000f <= velcity && velcity <= 0.000f)) {
		m_Tc = distance / velcity;
		m_Tc = fabs(m_Tc);

		//�\���|�C���g��ڕW�n�_�ɐݒ�.
		m_point.x = m_Sp.x + (LONG)((double)m_Vp.x * m_Tc);
		m_point.y = m_Sp.y + (LONG)((double)m_Vp.y * m_Tc);
	}

	//LOS�A���S���Y�����g���Ĉړ�.
	UpdateBresenham(m_Sp, m_point);
}

void Interception::UpdateBresenham(Vector3& now, Vector3 &target)
{
	if ((m_prevTargetPos.x == target.x) && (m_prevTargetPos.y == target.y)) {
		//�ڕW�n�_���ς���Ă��Ȃ��ꍇ�́C�O�����Čv�Z���Ă��������̂��g��.
		if (m_stepCount >= NEXT_POS_MAX) { return; }
		if (m_nextStepPos[m_stepCount].x < 0 && m_nextStepPos[m_stepCount].y < 0) {
			return;
		}
	}
	else {
		//�ڕW�n�_���ς�����̂Ōo�H���Čv�Z����.
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
			//Y����������.
			int f = (deltaX << 1) - deltaY;   //�����������l.
			for (int i = 0; i < deltaY; ++i) {
				if (f >= 0) {
					pos.x += stepX;           //X�����X�V.
					f -= (deltaY << 1); //X�����̈ړ�������.
				}
				pos.y += stepY;           //Y�����X�V.
				f += (deltaX << 1); //Y�����̈ړ�������.

				m_nextStepPos[i] = pos;
			}
		}
		else {
			//X����������.
			int f = (deltaY << 1) - deltaX;   //�����������l.
			for (int i = 0; i < deltaX; ++i) {
				if (f >= 0) {
					pos.y += stepY;           //Y�����X�V.
					f -= (deltaX << 1); //Y�����̈ړ�������.
				}
				pos.x += stepX;           //X�����X�V.
				f += (deltaY << 1); //X�����̈ړ�������.

				m_nextStepPos[i] = pos;
			}
		}

		m_prevTargetPos = target;   //�T�����̖ڕW�n�_�͕ۑ����Ă���.
	}

	now = m_nextStepPos[m_stepCount++];
}

void Interception::Finalize(){
}


