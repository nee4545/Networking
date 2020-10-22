#pragma once


class IntVec2
{
public:
	int x=0;
	int y=0;

	//construction and destruction
	IntVec2()=default;
	~IntVec2()=default;
	IntVec2(const IntVec2 &copyFrom);
	explicit IntVec2(int initialX, int initialY);

	float GetLength() const;
	int GetLengthSquared() const;
	int GetTaxicabLength() const;
	float GetOrientationRadians() const;
	float GetOrientationDegrees() const;
	const IntVec2 GetRotated90Degrees() const;
	const IntVec2 GetRotatedMinus90Degrees() const;


	void Rotate90Degrees();
	void RotateMinus90Degrees();


	bool operator==(const IntVec2& compare) const;
	bool operator!=(const IntVec2& compare) const;
	const IntVec2 operator+=(const IntVec2& vecToAdd) const;
	const IntVec2 operator-=(const IntVec2& vecToSubtract) const;
	const IntVec2 operator-()const;
	const IntVec2 operator*(int uniformScale) const;
	const IntVec2 operator*(const IntVec2& vecToMultiply) const;
	const IntVec2 operator-( const IntVec2& vecToSubtract ) const;


	void operator+=(const IntVec2& vecToAdd);
	void operator-=(const IntVec2& vecToSubtract);
	void operator*=(const IntVec2& vecToMultiply);
	void operator=(const IntVec2& copyFrom);

	friend const IntVec2 operator*(int uniformScale, const IntVec2& vecToScale);

	void SetFromText(const char* asText);

};