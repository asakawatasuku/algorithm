/// <summary>
/// �ړ��p�^�[���̊��N���X
/// </summary>

#include "Base.h"
#include <memory>

class MovingPattern
{
protected:
	// �������g
	std::shared_ptr<Base> m_object;
	// �ΏۃI�u�W�F�N�g
	std::shared_ptr<Base> m_target;
public:
	virtual void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target) = 0;
};