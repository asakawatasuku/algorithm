#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <Windows.h>
#include "MovingPattern.h"



class Interception : public MovingPattern
{
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
	// �}���ړ���
	//DirectX::SimpleMath::Vector3 m_movement;

#define NEXT_POS_MAX 10000
	//1�t���[���O�̖ڕW�n�_
	DirectX::SimpleMath::Vector3   m_prevTargetPos;
	//�ړ��o�H
	DirectX::SimpleMath::Vector3   m_nextStepPos[NEXT_POS_MAX];
	//�X�e�b�v��
	int     m_stepCount;


public:
	void Initialize(Base* object, Base* target);
	void Finalize();
	void Update();

private:
	void UpdateBresenham(DirectX::SimpleMath::Vector3& now, DirectX::SimpleMath::Vector3 &target);
};