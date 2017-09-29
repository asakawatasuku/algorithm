/// <summary>
/// ���w�֘A
/// </summary>

#include "MathGroup.h"

using namespace DirectX::SimpleMath;


float LMath::GetScalar(Vector3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}



Vector3 LMath::Normalize(Vector3 vec)
{
	const float vecLen = GetScalar(vec);
	vec.x /= vecLen;
	vec.y /= vecLen;
	vec.z /= vecLen;
	return vec;
}



Vector3 LMath::Normalize(Vector3 from, Vector3 to)
{
	Vector3 tmp = to - from;
	return Normalize(tmp);
}



float LMath::GetRotateRad(const float from, const float to)
{
	//�p�x���1
	const float dir1st = (to - from);
	const float dir1stVal = fabsf(dir1st);

	//�p�x���2
	const float dir2ndVal = (DirectX::XM_PI - dir1stVal);
	const float dir2nd = ((dir1st >= 0.0f) ? -1.0f : 1.0f) * dir2ndVal;

	//��Βl�������������̗p
	return (dir1stVal > dir2ndVal) ? dir2nd : dir1st;
}



bool LMath::IsCollisionCircle(const Vector3& pos1, const Vector3& pos2, const float r)
{
	Vector3 tmp = pos1 - pos2;
	return (GetScalar(tmp) < r);
}
