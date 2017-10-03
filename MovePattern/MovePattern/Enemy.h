/// <summary>
/// エネミークラス
/// </summary>

#pragma once

#include "Base.h"
#include "A_star.h"
#include "BreadCrumb.h"
#include "MovingPattern.h"
#include "WaypointNavigation.h"

class Enemy :public Base
{
private:
	// 移動パターン
	std::unique_ptr<MovingPattern> m_moving_pattern;
	std::unique_ptr<A_Star> m_a_star;
	std::unique_ptr<BreadCrumb> m_bread_crumb;
	std::unique_ptr<WaypointNavigation> m_waypoint;
	// 追跡対象
	Base* m_target;
public:
	Enemy();
	~Enemy();

	void Initialize(const std::wstring& file_name);
	void Update();
	void Render();
	void Finalize();

	void SetTarget(Base* target)
	{
		m_target = target;
	}
};
