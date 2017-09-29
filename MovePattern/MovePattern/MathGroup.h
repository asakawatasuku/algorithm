/// <summary>
/// 数学関連
/// </summary>

#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

//角度計算用マクロ
#define L_H_DEG     (180.0000f)
#define L_DEG       (360.0000f)
#define ADJUST_RAD(e) (((e)<(0.0000f))?(e)+(DirectX::XM_PI):((e)>(DirectX::XM_PI))?(e)-(DirectX::XM_PI):(e))
#define ADJUST_DEG(e) (((e)<(0.0000f))?(e)+(L_DEG):((e)>(L_DEG))?(e)-(L_DEG):(e))

//ベクトル構造体
#define VECTOR SVector3D<float>
template <class T>
struct SVector3D
{
	typedef T DataType;
	T x;
	T y;
	T z;
	SVector3D() { Init(); }
	void Init()
	{
		x = T();
		y = T();
		z = T();
	}
	SVector3D   operator +  (const SVector3D& e) const { SVector3D tmp; tmp.x = x + e.x; tmp.y = y + e.y; tmp.z = z + e.z; return tmp; }
	SVector3D&  operator += (const SVector3D& e) { x += e.x; y += e.y; z += e.z; return (*this); }
	SVector3D   operator -  (const SVector3D& e) const { SVector3D tmp; tmp.x = x - e.x; tmp.y = y - e.y; tmp.z = z - e.z; return tmp; }
	SVector3D&  operator -= (const SVector3D& e) { x -= e.x; y -= e.y; z -= e.z; return (*this); }
	T           operator *  (const SVector3D& e) const { return (x * e.x) + (y * e.y) + (z * e.z); }
	SVector3D&  operator *= (const int e) { x *= e; y *= e; z *= e; return (*this); }
	SVector3D&  operator *= (const float e) { x *= e; y *= e; z *= e; return (*this); }
	SVector3D&  operator /= (const int e) { x /= e; y /= e; z /= e; return (*this); }
	SVector3D&  operator /= (const float e) { x /= e; y /= e; z /= e; return (*this); }
};

//数学関連の関数群
namespace LMath
{
	float GetScalar(DirectX::SimpleMath::Vector3 vec);

	DirectX::SimpleMath::Vector3 Normalize(DirectX::SimpleMath::Vector3 vec);

	DirectX::SimpleMath::Vector3 Normalize(DirectX::SimpleMath::Vector3 from, DirectX::SimpleMath::Vector3 to);

	float GetRotateRad(const float from, const float to);

	bool IsCollisionCircle(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2, const float r);
};
