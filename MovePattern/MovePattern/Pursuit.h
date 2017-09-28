#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

#include "MovingPattern.h"

class Pursuit : public MovingPattern
{
public:
	Pursuit();
	~Pursuit();

private:
	// ���W�̍�
	DirectX::SimpleMath::Vector3 m_Dif_position;

	// �ǐՈړ���(Tracking travel distance)
	DirectX::SimpleMath::Vector3 m_ttd;

public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target)override;
	void Update();


};

