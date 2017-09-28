/// <summary>
/// �ړ��p�^�[���̊��N���X
/// </summary>

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
	virtual void Finalize() = 0;
};