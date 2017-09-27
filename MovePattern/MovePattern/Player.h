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

	void Initialize(std::shared_ptr<Camera> camera);
	void Update();
	void Render();

	void SetKeyboard(KeyboardUtil* keyboard)
	{
		m_keyboard = keyboard;
	}
};

