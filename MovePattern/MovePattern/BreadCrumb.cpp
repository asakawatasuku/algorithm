#include "BreadCrumb.h"

using namespace std;

const float BreadCrumb::BREAD_CRUMB_MAX_RANGE = 60.0f;
const float BreadCrumb::BREAD_COLLISION_RANGE = 15.0f;

/// <summary>
/// �������֐�
/// </summary>
void BreadCrumb::Initiarize(shared_ptr<Base> object, shared_ptr<Base> target)
{
	m_object = object;
	m_target = target;
}

/// <summary>
/// �X�V�֐�
/// </summary>
/// <param name="pos">���݂̈ʒu</param>
/// <param name="direction">����</param>
/// <param name="velocity">���x</param>
void BreadCrumb::Update(VECTOR& pos, float& direction, float velocity)
{
	// ���ɓ������Ă���ꍇ
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		if (LMath::IsCollisionCircle(m_target_bread, pos, BREAD_COLLISION_RANGE))
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
			VECTOR bread_pos = m_bread_array[i];
			if (!(bread_pos.x >= 0.0f && bread_pos.z >= 0.0f))
			{
				continue;
			}

			// �͈͊O�̂��͔̂��肩��O��
			const float r = BREAD_CRUMB_MAX_RANGE + (BREAD_COLLISION_RANGE * 2.0f);
			if (!LMath::IsCollisionCircle(bread_pos, pos, r)) {
				continue;
			}

			// �p������������ʒu���Q��
			m_target_bread = bread_pos;
			break;
		}
	}

	// �ڕW�̃p�������Ɍ�����
	if (m_target_bread.x >= 0.0f && m_target_bread.z >= 0.0f)
	{
		VECTOR dir_vec = LMath::Normalize(pos, m_target_bread);

		direction = ADJUST_RAD(atan2f(-dir_vec.z, dir_vec.x));
	}
	else
	{
		direction = 0;
	}

	// �ڕW���W�Ɍ������Ĉړ�
	pos.x += velocity * cosf(direction);
	pos.z += velocity * -sinf(direction);
}

/// <summary>
/// �p�������𗎂Ƃ�
/// </summary>
/// <param name="pos">���݂̈ʒu</param>
void BreadCrumb::DropBreadCrumb(const VECTOR& pos)
{
	// �p�������̏W��
	if (!(m_bread_array && (m_bread_num > 0)))
	{
		return;
	}

	// ���Ƃ����p�����������͈͗���Ă�����
	if (LMath::IsCollisionCircle(m_bread_array[0], pos, BREAD_CRUMB_MAX_RANGE))
	{
		return;
	}
	// �p�������̑N�x�X�V
	for (int i = m_bread_num - 1; i >= 1; --i) 
	{
		m_bread_array[i] = m_bread_array[i - 1];
	}

	// �V�����p��������o�^
	m_bread_array[0] = pos;

}
