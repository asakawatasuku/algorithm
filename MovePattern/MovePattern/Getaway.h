#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

#include "MovingPattern.h"
class Getaway : public MovingPattern{
private:
	// ���W�̍�
	DirectX::SimpleMath::Vector3 m_dif_position;

	// �����ړ���
	DirectX::SimpleMath::Vector3 m_escape;

public:
	void Initialize(Base* object, Base* target) override;
	void Update();
	void Finalize();

};

