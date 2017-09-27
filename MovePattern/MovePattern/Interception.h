#pragma once
#include <SimpleMath.h>
#include "MovingPattern.h"



class Interception : public MovingPattern
{
public:
	Interception();
	~Interception();
private:
	// ���Α��x(�x�N�g��)
	DirectX::SimpleMath::Vector3 m_Vr;
	// ���΋���
	DirectX::SimpleMath::Vector3 m_Sr;	
	// �ڋߎ���
	double m_Tc;			

	// �v���C���[�̌��ݍ��W
	DirectX::SimpleMath::Vector3 m_Sp;		
	// �v���C���[�̈ړ��x�N�g��
	DirectX::SimpleMath::Vector3 m_Vp;
	// �G�̌��ݍ��W
	DirectX::SimpleMath::Vector3 m_Se;			
	// �G�̈ړ��x�N�g��
	DirectX::SimpleMath::Vector3 m_Ve;

	// �}���|�C���g
	DirectX::SimpleMath::Vector3 m_point;		

public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();
};