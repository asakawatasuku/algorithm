#pragma once
#include <SimpleMath.h>

class Base
{
private:
	float m_speed;			
	DirectX::SimpleMath::Vector3 m_velocity;	// ‘¬“x

protected:
	virtual void Update() = 0;	// XVŠÖ”
};

