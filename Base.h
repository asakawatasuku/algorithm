#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>

class Base
{
private:
	static const float SPEED;
private:
	float m_speed;	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;

protected:
	void Initiarize();
	virtual void Move();		// 移動関数
};

