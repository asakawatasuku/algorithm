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
	//m_Sr.Normalize();

	//  �ڋߎ���
	m_Tc = 0;
	double distance = sqrt(m_Sr.x * m_Sr.x + m_Sr.z * m_Sr.z);
	double velcity = sqrt(m_Vr.x * m_Vr.x + m_Vr.z * m_Vr.z);
	// ���[�u(0���Z�ɂȂ�Ȃ����߂̑΍�)
	if (velcity == 0) {
		velcity = 1;
	}

	/*if (!(0.000f <= velcity && velcity <= 0.000f))*/ {
		m_Tc = distance / velcity;
		m_Tc = fabs(m_Tc);

		//�\���|�C���g��ڕW�n�_�ɐݒ�.
		m_point.x = m_Sp.x + (LONG)((double)m_Vp.x * m_Tc);
		m_point.z = m_Sp.z + (LONG)((double)m_Vp.z * m_Tc);
	}

	// �ڕW�n�_�ɓ��B������
	if (m_target->GetPos() != m_point) {

		//LOS�A���S���Y�����g���Ĉړ�.
		UpdateBresenham(m_Se, m_point);

		Vector3 tmp = m_object->GetSpeed() + (m_object->GetSpeed() - m_Se) * 0.005f;

		m_object->SetSpeed(-tmp);
	}
	else {
		m_object->SetSpeed(Vector3::Zero);
	}
}

void Interception::UpdateBresenham(Vector3& now, Vector3 &target)
{
	if ((m_prevTargetPos.x == target.x) && (m_prevTargetPos.z == target.z)) {
		//�ڕW�n�_���ς���Ă��Ȃ��ꍇ�́C�O�����Čv�Z���Ă��������̂��g��.
		if (m_stepCount >= NEXT_POS_MAX) { return; }
		if (m_nextStepPos[m_stepCount].x < 0 && m_nextStepPos[m_stepCount].z < 0) {
			return;
		}
	}
	else {
		//�ڕW�n�_���ς�����̂Ōo�H���Čv�Z����.
		m_stepCount = 0;
		for (int i = 0; i < NEXT_POS_MAX; ++i) {
			m_nextStepPos[i].x = m_nextStepPos[i].z = -1;
		}

		Vector3 pos = now;

		int deltaX = target.x - pos.x;
		int deltaZ = target.z - pos.z;

		const int stepX = (deltaX >= 0) ? 1 : -1;
		const int stepY = (deltaZ >= 0) ? 1 : -1;

		deltaX = abs(deltaX);
		deltaZ = abs(deltaZ);

		if (deltaZ > deltaX) {
			//Z����������.
			int f = (deltaX << 1) - deltaZ;   //�����������l.
			for (int i = 0; i < deltaZ; ++i) {
				if (f >= 0) {
					pos.x += stepX;           //X�����X�V.
					f -= (deltaZ << 1); //X�����̈ړ�������.
				}
				pos.z += stepY;           //Z�����X�V.
				f += (deltaX << 1); //Z�����̈ړ�������.

				m_nextStepPos[i] = pos;
			}
		}
		else {
			//X����������.
			int f = (deltaZ << 1) - deltaX;   //�����������l.
			for (int i = 0; i < deltaX; ++i) {
				if (f >= 0) {
					pos.z += stepY;           //Z�����X�V.
					f -= (deltaX << 1); //Z�����̈ړ�������.
				}
				pos.x += stepX;           //X�����X�V.
				f += (deltaZ << 1); //X�����̈ړ�������.

				m_nextStepPos[i] = pos;
			}
		}

		m_prevTargetPos = target;   //�T�����̖ڕW�n�_�͕ۑ����Ă���.
	}

	now = m_nextStepPos[m_stepCount++];
}

void Interception::Finalize(){
}


