/// <summary>
/// プレイヤークラス
/// </summary>

#pragma once

#include "Base.h"
#include "KeyboardUtil.h"

class Player :public Base
{
private:
	KeyboardUtil* m_keyboard;
public:
	Player();
	~Player();

	void Update();

	void SetKeyboard(KeyboardUtil* keyboard)
	{
		m_keyboard = keyboard;
	}
};

