#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <Windows.h>
#include "MovingPattern.h"



class Interception : public MovingPattern
{
private:
	// 相対速度(ベクトル)
	DirectX::SimpleMath::Vector3 m_Vr;
	// 相対距離
	DirectX::SimpleMath::Vector3 m_Sr;	
	// 接近時間
	double m_Tc;

	// プレイヤーの現在座標
	DirectX::SimpleMath::Vector3 m_Sp;		
	// プレイヤーの移動ベクトル
	DirectX::SimpleMath::Vector3 m_Vp;
	// 敵の現在座標
	DirectX::SimpleMath::Vector3 m_Se;			
	// 敵の移動ベクトル
	DirectX::SimpleMath::Vector3 m_Ve;

	// 迎撃ポイント
	DirectX::SimpleMath::Vector3 m_point;
	// 迎撃移動量
	//DirectX::SimpleMath::Vector3 m_movement;

#define NEXT_POS_MAX 10000
	//1フレーム前の目標地点
	DirectX::SimpleMath::Vector3   m_prevTargetPos;
	//移動経路
	DirectX::SimpleMath::Vector3   m_nextStepPos[NEXT_POS_MAX];
	//ステップ数
	int     m_stepCount;


public:
	void Initialize(Base* object, Base* target);
	void Finalize();
	void Update();

private:
	void UpdateBresenham(DirectX::SimpleMath::Vector3& now, DirectX::SimpleMath::Vector3 &target);
};