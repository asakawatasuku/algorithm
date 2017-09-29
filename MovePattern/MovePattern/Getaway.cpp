#include "Getaway.h"

using namespace DirectX::SimpleMath;

void Getaway::Initialize(Base * object, Base * target)
{
	m_object = object;
	m_target = target;
	m_object->SetSpeed(Vector3::Forward * 0.05f);

}

void Getaway::Update()
{
	// �v���C���[���W����G���W�̍������߂�
	m_dif_position = m_object->GetPos() - m_target->GetPos();
	// ���߂����𐳋K������
	m_dif_position.Normalize();

	// �ǐՈړ��ʂ����߂�
	m_escape = m_dif_position * m_object->GetSpeed().Distance(Vector3::Zero, m_object->GetSpeed());

	m_object->SetSpeed(m_escape);

}

void Getaway::Finalize()
{
}
