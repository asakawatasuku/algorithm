#pragma once
#include <SimpleMath.h>

class Base
{
private:
	float m_speed;			
	DirectX::SimpleMath::Vector3 m_velocity;	// 速度

protected:
	virtual void Update() = 0;	// 更新関数
};

