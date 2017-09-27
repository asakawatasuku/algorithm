#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <vector>
#include "MathGroup.h"

class BreadCrumb
{
private:
	static const float BREAD_CRUMB_MAX_RANGE;	// �p�������̍ő�͈̔�
	static const float BREAD_COLLISION_RANGE;	// �Փ˔͈�

private:
	const int m_bread_num = 20;					// �p�������̈ʒu���X�g�T�C�Y
	VECTOR* m_bread_array;						// �p�������̈ʒu���X�g
	VECTOR m_target_bread;						// �^�[�Q�b�g�̃p������

public:
	// �������֐�
	void Initiarize();
	// �X�V
	void Update(VECTOR& pos,float& direction,float velocity);
	// �p�������𗎂Ƃ�
	void DropBreadCrumb(const VECTOR& pos);
};

