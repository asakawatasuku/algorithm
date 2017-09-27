/// <summary>
/// 移動パターンの基底クラス
/// </summary>

#include "Base.h"
#include <memory>

class MovingPattern
{
protected:
	// 自分自身
	std::shared_ptr<Base> m_object;
	// 対象オブジェクト
	std::shared_ptr<Base> m_target;
public:
	virtual void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target) = 0;
};