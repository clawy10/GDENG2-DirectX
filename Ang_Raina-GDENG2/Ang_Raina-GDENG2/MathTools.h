#pragma once
#include "AQuaternion.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

class MathTools
{
public:
	static float ConvertDegreesToRadians(float degree)
	{
		float pi = 3.14159265359;
		return (degree * (pi / 180));
	}

	static float ConvertRadiansToDegrees(float radian)
	{
		float pi = 3.14159265359;
		return(radian * (180 / pi));
	}

	static Matrix4x4 QuaternionToMatrix(float qx, float qy, float qz, float qw)
	{
		float wx, wy, wz, xx, yy, yz, xy, xz, zz;

		xx = qx * qx;
		xy = qx * qy;
		xz = qx * qz;
		yy = qy * qy;
		zz = qz * qz;
		yz = qy * qz;

		wx = qw * qx;
		wy = qw * qy;
		wz = qw * qz;

		float matrix[16];
		matrix[0] = 1.0f - 2.0f * (yy + zz);
		matrix[4] = 2.0f * (xy - wz);
		matrix[8] = 2.0f * (xz + wy);
		matrix[12] = 0.0;

		matrix[1] = 2.0f * (xy + wz);
		matrix[5] = 1.0f - 2.0f * (xx + zz);
		matrix[9] = 2.0f * (yz - wx);
		matrix[13] = 0.0;

		matrix[2] = 2.0f * (xz - wy);
		matrix[6] = 2.0f * (yz + wx);
		matrix[10] = 1.0f - 2.0f * (xx + yy);
		matrix[14] = 0.0;

		matrix[3] = 0;
		matrix[7] = 0;
		matrix[11] = 0;
		matrix[15] = 1;

		return Matrix4x4(matrix);
	}

	// from radians
	static AQuaternion EulerToQuaternion(Vector3D euler)
	{
		float c1 = cos(euler.z * 0.5);
		float c2 = cos(euler.y * 0.5);
		float c3 = cos(euler.x * 0.5);
		float s1 = sin(euler.z * 0.5);
		float s2 = sin(euler.y * 0.5);
		float s3 = sin(euler.x * 0.5);

		float x = c1 * c2 * s3 - s1 * s2 * c3;
		float y = c1 * s2 * c3 + s1 * c2 * s3;
		float z = s1 * c2 * c3 - c1 * s2 * s3;
		float w = c1 * c2 * c3 + s1 * s2 * s3;

		return AQuaternion(x, y, z, w);
	}

	static Vector3D QuaternionToEuler(AQuaternion quaternion)
	{
		float pi = 3.14159265359;
		const static double PI_OVER_2 = pi * 0.5;
		const static double EPSILON = 1e-10;
		float x, y, z;
		float sqw, sqx, sqy, sqz;

		// quick conversion to Euler angles to give tilt to user
		sqw = quaternion.w * quaternion.w;
		sqx = quaternion.x * quaternion.x;
		sqy = quaternion.y * quaternion.y;
		sqz = quaternion.z * quaternion.z;

		y = asin(2.0 * (quaternion.w * quaternion.y - quaternion.x * quaternion.z));
		if (PI_OVER_2 - fabs(y) > EPSILON) {
			z = atan2(2.0 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z),
				sqx - sqy - sqz + sqw);
			x = atan2(2.0 * (quaternion.w * quaternion.x + quaternion.y * quaternion.z),
				sqw - sqx - sqy + sqz);
		}
		else {
			// compute heading from local 'down' vector
			z = atan2(2 * quaternion.y * quaternion.z - 2 * quaternion.x * quaternion.w,
				2 * quaternion.x * quaternion.z + 2 * quaternion.y * quaternion.w);
			x = 0.0;

			// If facing down, reverse yaw
			if (y < 0)
				z = pi - z;
		}		
		
		return Vector3D(x, y, z);
	}

	static float RandomNumber(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = max - min;
		float r = random * diff;
		return min + r;
	}

};