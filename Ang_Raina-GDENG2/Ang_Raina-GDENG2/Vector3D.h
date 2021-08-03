#pragma once
class Vector3D
{
public:
	Vector3D() : x(0), y(0), z(0)
	{

	}

	Vector3D(float x, float y, float z) : x(x), y(y), z(z)
	{

	}

	Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z)
	{

	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;

		v.x = start.x * (1.0f - delta) + end.x * delta;
		v.y = start.y * (1.0f - delta) + end.y * delta;
		v.z = start.z * (1.0f - delta) + end.z * delta;

		return v;
	}

	static Vector3D normalize(Vector3D vector)
	{
		float w = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		Vector3D result = Vector3D(vector.x / w, vector.y / w, vector.z / w);

		return result;
	}

	Vector3D operator *(float num)
	{
		return Vector3D(this->x * num, this->y * num, this->z * num);
	}

	Vector3D operator +(Vector3D vec)
	{
		return Vector3D(this->x + vec.x, this->y + vec.y, this->z + vec.z);
	}

	Vector3D operator -(Vector3D vec)
	{
		return Vector3D(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	~Vector3D() {}

public:
	float x, y, z;
};