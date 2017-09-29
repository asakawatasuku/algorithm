#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

#include "MovingPattern.h"

class Pursuit : public MovingPattern
{
private:
	// À•W‚Ì·
	DirectX::SimpleMath::Vector3 m_dif_position;

	// ’ÇÕˆÚ“®—Ê(Pusuit moving distance)
	DirectX::SimpleMath::Vector3 m_pmd;

public:
	void Initialize(Base* object, Base* target) override;
	void Update();
	void Finalize();

};
