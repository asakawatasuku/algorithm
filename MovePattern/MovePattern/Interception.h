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
	DirectX::SimpleMath::Vector3 m_movement;

#define NEXT_POS_MAX 100
	DirectX::SimpleMath::Vector3   m_prevTargetPos;            //1�t���[���O�̖ڕW�n�_.
	DirectX::SimpleMath::Vector3   m_nextStepPos[NEXT_POS_MAX];//�ړ��o�H.
	int     m_stepCount;                //�X�e�b�v��.


public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();
	void UpdateBresenham(DirectX::SimpleMath::Vector3& now, DirectX::SimpleMath::Vector3 &target);

};