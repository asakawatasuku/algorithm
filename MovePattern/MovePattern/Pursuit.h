#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

#include "MovingPattern.h"

class Pursuit : public MovingPattern
{
private:
	// ���W�̍�
	DirectX::SimpleMath::Vector3 m_Dif_position;

	// �ǐՈړ���(Tracking travel distance)
	DirectX::SimpleMath::Vector3 m_ttd;

public:
	void Initialize(Base* object, Base* target)override;
	void Update();
	void Finalize();

};

