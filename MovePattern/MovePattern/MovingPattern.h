/// <summary>
/// �ړ��p�^�[���̊��N���X
/// </summary>

#pragma once
<<<<<<< HEAD
=======

>>>>>>> 654ea966a3efe9126b795e385db2ae1acb73bc9d
#include "Base.h"
#include <memory>

class MovingPattern
{
protected:
	// �������g
	Base* m_object;
	// �ΏۃI�u�W�F�N�g
	Base* m_target;
public:
	virtual void Initialize(Base* object, Base* target) = 0;
	virtual void Finalize()
	{
		delete m_object;
		delete m_target;
	}
};