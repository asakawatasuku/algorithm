/// <summary>
/// 移動パターンの基底クラス
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
	// 自分自身
	Base* m_object;
	// 対象オブジェクト
	Base* m_target;
public:
	virtual void Initialize(Base* object, Base* target) = 0;
	virtual void Finalize()
	{
		delete m_object;
		delete m_target;
	}
};