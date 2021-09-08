#ifndef SPANDEX_VECTOR3_H_
#define SPANDEX_VECTOR3_H_

namespace spandex
{
	struct Vector3
	{
		float x, y, z;

		Vector3() : x(0), y(0), z(0) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

		Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
		Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
		Vector3 operator*(const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
		Vector3 operator/(const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
		Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		Vector3& operator*=(const float& rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
		Vector3& operator/=(const float& rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }
		Vector3& operator=(const Vector3& rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }

		float MagnitudeSqr() const { return powf(x, 2) + powf(y, 2) + powf(z, 2); }
		float Magnitude() const { return sqrtf(MagnitudeSqr()); }
		Vector3 Normalized() const { return Vector3(*this) / Magnitude(); }
		static float DotProduct(const Vector3& a, const Vector3& b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
	};
}

#endif