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
	DirectX::SimpleMath::Vector3 m_movement;

#define NEXT_POS_MAX 100
	DirectX::SimpleMath::Vector3   m_prevTargetPos;            //1フレーム前の目標地点.
	DirectX::SimpleMath::Vector3   m_nextStepPos[NEXT_POS_MAX];//移動経路.
	int     m_stepCount;                //ステップ数.


public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();
	void UpdateBresenham(DirectX::SimpleMath::Vector3& now, DirectX::SimpleMath::Vector3 &target);

};