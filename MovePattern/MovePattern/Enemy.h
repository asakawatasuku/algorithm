/// <summary>
/// エネミークラス
/// </summary>

#pragma once

#include "Base.h"
#include "MovingPattern.h"

class Enemy :public Base
{
private:
	// 移動パターン
	std::unique_ptr<MovingPattern> m_moving_pattern;
	// 追跡対象
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
