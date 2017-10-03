#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>
#include "MathGroup.h"
#include "Base.h"

class BreadCrumb
{
private:
	static const float BREAD_CRUMB_MAX_RANGE;	// �p�������̍ő�͈̔�
	static const float BREAD_COLLISION_RANGE;	// �Փ˔͈�

private:
	const int m_bread_num = 10;					// �p�������̈ʒu���X�g�T�C�Y
	const float m_angle = 30.0f;
	DirectX::SimpleMath::Vector3* m_bread_array;	// �p�������̈ʒu���X�g
	DirectX::SimpleMath::Vector3 m_target_bread;	// �^�[�Q�b�g�̃p������
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 direction;

	Base* m_object;		// ���g
	Base* m_target;		// �Ǐ]�Ώ�

public:
	// �������֐�
	void Initialize(Base* object, Base* target);
	// �X�V
	void Update();
	// �p�������𗎂Ƃ�
	void DropBreadCrumb();
	// �I������
	void Finalize();
};

