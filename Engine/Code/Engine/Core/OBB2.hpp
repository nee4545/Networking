#pragma once
#include "Engine/Math/Vec2.hpp"
class RandomNumberGenerator;
struct AABB2;

struct OBB2
{
	Vec2 m_center;
	Vec2 m_halfDimensions;
	Vec2 m_iBasis=Vec2(1.f,0.f);

	//Construction and Destruction
	OBB2()=default;
	~OBB2()=default;
	OBB2(const OBB2& copyFrom);
	explicit OBB2(const Vec2& center,const Vec2& fullDimensions,const Vec2& iBasisNormal=Vec2(1.f,0.f));
	explicit OBB2(const Vec2& center, const Vec2&fullDimensions, float orientationDegrees);
	explicit OBB2(const AABB2& asAxisAlignedBox, float orientationDegrees=0.f);

	//Accessors
	bool IsPointInside(const Vec2& point) const; // does not include positions on edges
	const Vec2 GetCenter() const;
	const Vec2 GetDimensions() const;
	const Vec2 GetIBasisNormal() const;
	const Vec2 GetJBasisNormal() const;
	float GetOrientationDegrees() const;
	const Vec2 GetNearestPoint(const Vec2& referencePoint) const;
	const Vec2 GetPointAtUV(const Vec2& uvCoordsZeroToOne) const;
	const Vec2 GetUVForPoint(const Vec2& point) const;
	void GetCornerPositions( Vec2* out_fourPoints ) const;
	float GetOuterRadius() const;
	float GetInnerRadius() const;


    //Mutators
	void Translate(const Vec2& translation);
	void SetCenter(const Vec2& newCenter);
	void SetDimensions(const Vec2& newDimensions);
	void SetOrientationDegrees(float newAbsoluteOrientationDegrees);
	void RotateByDegrees(float relativeOrientationDegrees);
	void StretchToIncludePoint(const Vec2& point);
	void Fix();

	//Operators self mutating

	void operator=(const OBB2&assignFrom );


};