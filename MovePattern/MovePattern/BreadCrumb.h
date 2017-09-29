#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include <vector>
#include "MathGroup.h"
#include "MovingPattern.h"

class BreadCrumb:public MovingPattern
{
private:
	static const float BREAD_CRUMB_MAX_RANGE;	// パンくずの最大の範囲
	static const float BREAD_COLLISION_RANGE;	// 衝突範囲

private:
	const int m_bread_num = 20;					// パンくずの位置リストサイズ
	const float m_angle = 30.0f;
	DirectX::SimpleMath::Vector3* m_bread_array;	// パンくずの位置リスト
	DirectX::SimpleMath::Vector3 m_target_bread;	// ターゲットのパンくず

public:
	// 初期化関数
	void Initialize(Base* object, Base* target);
	// 更新
	void Update();
	// パンくずを落とす
	void DropBreadCrumb();
	// 終了処理
	void Finalize();
};

