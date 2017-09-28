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
	// 相対速度(ベクトル)
	float m_Vr;
	// 相対距離
	DirectX::SimpleMath::Vector3 m_Sr;	
	// 接近時間
	double m_Tc;			

	// プレイヤーの現在座標
	DirectX::SimpleMath::Vector3 m_Sp;		
	// プレイヤーの移動ベクトル
	float m_Vp;
	// 敵の現在座標
	DirectX::SimpleMath::Vector3 m_Se;			
	// 敵の移動ベクトル
	float m_Ve;

	// 迎撃ポイント
	DirectX::SimpleMath::Vector3 m_point;
	// 迎撃移動量
	DirectX::SimpleMath::Vector3 m_movement;

public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();

};