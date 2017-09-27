#pragma once

#include "Base.h"

class Enemy :public Base
{
public:
	Enemy();
	~Enemy();

	void Initialize(std::shared_ptr<Camera> camera);
	void Update();
	void Render();
};

