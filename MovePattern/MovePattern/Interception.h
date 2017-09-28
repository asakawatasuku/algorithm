#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <Windows.h>
#include "MovingPattern.h"



class Interception : public MovingPattern
{
public:
	Interception();
	~Interception();
private:
	// ���Α��x(�x�N�g��)
	float m_Vr;
	// ���΋���
	DirectX::SimpleMath::Vector3 m_Sr;	
	// �ڋߎ���
	double m_Tc;			

	// �v���C���[�̌��ݍ��W
	DirectX::SimpleMath::Vector3 m_Sp;		
	// �v���C���[�̈ړ��x�N�g��
	float m_Vp;
	// �G�̌��ݍ��W
	DirectX::SimpleMath::Vector3 m_Se;			
	// �G�̈ړ��x�N�g��
	float m_Ve;

	// �}���|�C���g
	DirectX::SimpleMath::Vector3 m_point;
	// �}���ړ���
	DirectX::SimpleMath::Vector3 m_movement;

public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();

};