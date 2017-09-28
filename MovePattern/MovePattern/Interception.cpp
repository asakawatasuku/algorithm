#include"Interception.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// �R���X�g���N�^
//---------------------------------------
Interception::Interception() {

}

//---------------------------------------
// �f�X�g���N�^
//---------------------------------------
Interception::~Interception() {

}

//---------------------------------------
// �����ݒ�
//---------------------------------------
void Interception::Initialize(shared_ptr<Base> object, shared_ptr<Base> target) {
	m_object = object;
	m_target = target;
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
	m_Vp = sqrt(m_Sp.x * m_Sp.x + m_Sp.y * m_Sp.y + m_Sp.z * m_Sp.z);
	m_Ve = sqrt(m_Se.x * m_Se.x + m_Se.y * m_Se.y + m_Se.z * m_Se.z);

	m_Vr = m_Vp - m_Ve;

	// ���K��
	m_Sr.Normalize();
	//m_Vr.Normalize();

	//  �ڋߎ���
	m_Tc = 0;
	double distance = sqrt(m_Sr.x * m_Sr.x + m_Sr.z * m_Sr.z);
	double velcity = sqrt(m_Vr);
	if (!(0.000f <= velcity && velcity <= 0.000f)) {
		m_Tc = distance / velcity;
		m_Tc = fabs(m_Tc);
	}

	// �}���|�C���g�����߂�
	m_point = m_Sp + Vector3(m_Vp) * m_Tc;

	// �}���ړ���
	m_movement = m_point - m_Se * 1.0;

}


