#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

class Base
{
private:
	float m_speed;
	DirectX::SimpleMath::Vector3 m_pos;	// À•W

public:
	float GetSpeed()
	{
		return m_speed;
	}
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

protected:
	virtual void Update() = 0;	// XVŠÖ”
};

