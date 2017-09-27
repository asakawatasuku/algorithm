#pragma once
#include <SimpleMath.h>
#include "MovingPattern.h"



class Interception : public MovingPattern
{
public:
	Interception();
	~Interception();
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

public:
	void Initialize(std::shared_ptr<Base> object, std::shared_ptr<Base> target);
	void Update();
};