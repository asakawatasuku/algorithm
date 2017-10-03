/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#pragma once

#include "Base.h"
#include "Pursuit.h"
#include "Interception.h"
#include "BreadCrumb.h"

class Enemy :public Base
{
private:
	// �ړ��p�^�[��
	std::unique_ptr<BreadCrumb> m_moving_pattern;
	// �ǐՑΏ�
	Base* m_target;
public:
	Enemy();
	~Enemy();

	void Initialize(const std::wstring& file_name);
	void Update();
	void Finalize();

	void SetTarget(Base* target)
	{
		m_target = target;
	}
};
