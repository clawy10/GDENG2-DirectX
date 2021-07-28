#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4()
	{

	}

	void SetIdentity()
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void SetTranslation(const Vector3D& translation)
	{
		this->SetIdentity();
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void SetScale(const Vector3D& scale)
	{
		this->SetIdentity();
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void SetRotationX(float x)
	{
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void SetRotationY(float y)
	{
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void SetRotationZ(float z)
	{
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
		v2 = Vector4D(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
		v3 = Vector4D(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
			this->mat[3][3] * minor.w);
		return det;
	}

	void inverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->mat[j][0]);
					vec[a].y = (this->mat[j][1]);
					vec[a].z = (this->mat[j][2]);
					vec[a].w = (this->mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.mat[0][i] = pow(-1.0f, i) * v.x / det;
			out.mat[1][i] = pow(-1.0f, i) * v.y / det;
			out.mat[2][i] = pow(-1.0f, i) * v.z / det;
			out.mat[3][i] = pow(-1.0f, i) * v.w / det;
		}

		this->SetMatrix(out);
	}

	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];

			}
		}

		::memcpy(mat, out.mat, sizeof(float) * 16);
	}

	void SetMatrix(const Matrix4x4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	Vector3D GetZDirection()
	{
		return Vector3D(this->mat[2][0], this->mat[2][1], this->mat[2][2]);
	}

	Vector3D GetXDirection()
	{
		return Vector3D(this->mat[0][0], this->mat[0][1], this->mat[0][2]);
	}

	Vector3D GetTranslation()
	{
		return Vector3D(this->mat[3][0], this->mat[3][1], this->mat[3][2]);
	}

	void SetPerspectiveFOVLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;

		this->mat[0][0] = xscale;
		this->mat[1][1] = yscale;
		this->mat[2][2] = zfar / (zfar - znear);
		this->mat[2][3] = 1.0f;
		this->mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void SetOrthoLH(float width, float height, float nearPlane, float farPlane)
	{
		SetIdentity();
		this->mat[0][0] = 2.0f / width;
		this->mat[1][1] = 2.0f / height;
		this->mat[2][2] = 1.0f / (farPlane - nearPlane);
		this->mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	~Matrix4x4() {}

private:
	float mat[4][4] = {};
};
