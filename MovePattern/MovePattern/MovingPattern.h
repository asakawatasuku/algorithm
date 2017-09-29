/// <summary>
/// 移動パターンの基底クラス
/// </summary>

#pragma once

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
	//virtual void Update() = 0;
	virtual void Finalize() = 0;
};