#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

class Base
{
private:
	float m_speed;
	DirectX::SimpleMath::Vector3 m_pos;	// ���W

public:
	float GetSpeed()
	{
		return m_speed;
	}
	DirectX::SimpleMath::Vector3 GetPos()
	{
		return m_pos;
	}

	void SetPos(DirectX::SimpleMath::Vector3 pos)
	{
		m_pos = pos;
	}

protected:
	virtual void Update() = 0;	// �X�V�֐�
};

