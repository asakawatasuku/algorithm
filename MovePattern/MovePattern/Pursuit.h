#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

#include "MovingPattern.h"

class Pursuit : public MovingPattern
{
private:
	// ���W�̍�
	DirectX::SimpleMath::Vector3 m_dif_position;

	// �ǐՈړ���(Pusuit moving distance)
	DirectX::SimpleMath::Vector3 m_pmd;

public:
	void Initialize(Base* object, Base* target) override;
	void Update();
	void Finalize();

};
