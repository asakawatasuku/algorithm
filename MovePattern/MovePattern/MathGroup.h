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
	VECTOR::DataType GetScalar(VECTOR vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	VECTOR Normalize(VECTOR vec)
	{
		const VECTOR::DataType vecLen = GetScalar(vec);
		vec.x /= vecLen;
		vec.y /= vecLen;
		vec.z /= vecLen;
		return vec;
	}

	VECTOR Normalize(VECTOR from, VECTOR to)
	{
		VECTOR tmp = to - from;
		return Normalize(tmp);
	}

	float GetRotateRad(const float from, const float to)
	{
		//角度候補1
		const float dir1st = (to - from);
		const float dir1stVal = fabsf(dir1st);

		//角度候補2
		const float dir2ndVal = (DirectX::XM_PI - dir1stVal);
		const float dir2nd = ((dir1st >= 0.0f) ? -1.0f : 1.0f) * dir2ndVal;

		//絶対値が小さい方を採用
		return (dir1stVal > dir2ndVal) ? dir2nd : dir1st;
	}

	bool IsCollisionCircle(const VECTOR& pos1, const VECTOR& pos2, const float r)
	{
		VECTOR tmp = pos1 - pos2;
		return (GetScalar(tmp) < r);
	}
};