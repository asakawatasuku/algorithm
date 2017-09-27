#pragma once
#include <d3d11_1.h>
#include <SimpleMath.h>
#include <vector>
#include "MathGroup.h"

class BreadCrumb
{
private:
	static const float BREAD_CRUMB_MAX_RANGE;	// パンくずの最大の範囲
	static const float BREAD_COLLISION_RANGE;	// 衝突範囲

private:
	const int m_bread_num = 20;					// パンくずの位置リストサイズ
	VECTOR* m_bread_array;						// パンくずの位置リスト
	VECTOR m_target_bread;						// ターゲットのパンくず

public:
	// 初期化関数
	void Initiarize();
	// 更新
	void Update(VECTOR& pos,float& direction,float velocity);
	// パンくずを落とす
	void DropBreadCrumb(const VECTOR& pos);
};

