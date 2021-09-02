#pragma once
#include "Vector3D.h"

class AQuaternion
{
public:
	AQuaternion() : x(0), y(0), z(0), w(1)
	{
		
	}

	AQuaternion(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w; 
	}

	AQuaternion(Vector3D vector, float w)
	{
		this->x = vector.x;
		this->y = vector.y;
		this->z = vector.z;
		this->w = w;
	}

public:
	float x;
	float y;
	float z;
	float w; 
};
