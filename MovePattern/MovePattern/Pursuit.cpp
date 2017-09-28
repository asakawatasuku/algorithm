#include "Pursuit.h"

using namespace std;
using namespace DirectX::SimpleMath;

//---------------------------------------
// �����ݒ�
//---------------------------------------
void Pursuit::Initialize(shared_ptr<Base> object, shared_ptr<Base> target) {
	m_object = object;
	m_target = target;
	m_object->SetSpeed(Vector3());
}

//---------------------------------------
// ����
//---------------------------------------
void Pursuit::Update() {

	// �v���C���[���W����G���W�̍������߂�
	m_Dif_position = m_object->GetPos() - m_target->GetPos();
	// ���߂����𐳋K������
	m_Dif_position.Normalize();

	// �ǐՈړ��ʂ����߂�
	m_ttd = m_Dif_position * m_object->GetSpeed().Distance(Vector3::Zero, m_object->GetSpeed());
}
	