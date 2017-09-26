#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>

class Base
{
private:
	static const float SPEED;
private:
	float m_speed;	// ‘¬“x
	DirectX::SimpleMath::Vector3 m_velocity;

protected:
	void Initiarize();
	virtual void Move();		// ˆÚ“®ŠÖ”
};

