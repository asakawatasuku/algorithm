#include "BreadCrumb.h"

using namespace std;
using namespace DirectX::SimpleMath;

const float BreadCrumb::BREAD_CRUMB_MAX_RANGE = 60.0f;
const float BreadCrumb::BREAD_COLLISION_RANGE = 15.0f;

/// <summary>
/// �������֐�
/// </summary>
void BreadCrumb::Initialize(Base* object, Base* target)
{
	m_object = object;
	m_target = target;

	m_object->SetSpeed(Vector3::Forward * 0.1f);

	m_bread_array = new Vector3();
}

/// <summary>
/// �X�V�֐�
/// </summary>
void BreadCrumb::Update()
{
	// ���ɓ������Ă���ꍇ
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		if (LMath::IsCollisionCircle(m_target_bread, m_object->GetPos(), BREAD_COLLISION_RANGE))
		{
			m_target_bread.x = -1.0f;
			m_target_bread.z = -1.0f;
		}
	}

	// �p���������Ȃ��ꍇ�T��
	if (!(m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f))
	{
		for (int i = 0; i < m_bread_num; i++)
		{
			Vector3 bread_pos = m_bread_array[i];
			if (!(bread_pos.x >= 0.0f && bread_pos.z >= 0.0f))
			{
				continue;
			}

			// �͈͊O�̂��͔̂��肩��O��
			const float r = BREAD_CRUMB_MAX_RANGE + (BREAD_COLLISION_RANGE * 2.0f);
			if (!LMath::IsCollisionCircle(bread_pos, m_object->GetPos(), r)) {
				continue;
			}

			// �p������������ʒu���Q��
			m_target_bread = bread_pos;
			break;
		}
	}

	Vector3 direction = m_object->GetRot();
	// �ڕW�̃p�������Ɍ�����
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		Vector3 dir_vec = LMath::Normalize(m_object->GetPos(), m_target_bread);

		direction.y = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));
	}
	// �ڕW�̃p���������Ȃ��Ȃ烉���_���ňړ�
	else
	{
		float displace = DirectX::XMConvertToRadians(m_angle);
		if (rand() % 2)
		{
			displace *= -1.0f;
		}

		direction.y = ADJUST_RAD(direction.y + displace);
	}

	// �ڕW���W�Ɍ������Ĉړ�
	Vector3 pos;
	pos.x += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * cosf(direction.y);
	pos.z += Vector3::Distance(Vector3::Zero, m_object->GetSpeed()) * -sinf(direction.y);
	m_object->SetPos(pos);
	m_object->SetRot(direction);
}

/// <summary>
/// �p�������𗎂Ƃ�
/// </summary>
void BreadCrumb::DropBreadCrumb()
{
	// �p�������̏W��
	if (!(m_bread_array && (m_bread_num > 0)))
	{
		return;
	}

	// ���Ƃ����p�����������͈͗���Ă�����
	if (LMath::IsCollisionCircle(m_bread_array[0], m_target->GetPos(), BREAD_CRUMB_MAX_RANGE))
	{
		return;
	}
	// �p�������̑N�x�X�V
	for (int i = m_bread_num - 1; i >= 1; --i) 
	{
		m_bread_array[i] = m_bread_array[i - 1];
	}

	// �V�����p��������o�^
	m_bread_array[0] = m_target->GetPos();

}

/// <summary>
/// �I������
/// </summary>
void BreadCrumb::Finalize()
{
	delete[] m_bread_array;
}
