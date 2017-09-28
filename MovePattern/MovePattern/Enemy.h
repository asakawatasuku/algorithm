/// <summary>
/// エネミークラス
/// </summary>

#pragma once

#include "Base.h"

class Enemy :public Base
{
public:
	Enemy();
	~Enemy();

	void Update();
};
