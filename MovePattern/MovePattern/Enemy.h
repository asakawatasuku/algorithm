/// <summary>
/// �G�l�~�[�N���X
/// </summary>

#pragma once

#include "Base.h"
#include "MovingPattern.h"

class Enemy :public Base
{
private:
	// �ړ��p�^�[��
	std::unique_ptr<MovingPattern> m_moving_pattern;
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
