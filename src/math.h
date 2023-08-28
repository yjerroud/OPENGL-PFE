#ifndef LIME_MATH_H
#define LIME_MATH_H

#include <math.h>
#include "tools.h"
#if defined (_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <string.h>
#endif


struct Camera;

#ifdef SSE_ENABLE
#include <xmmintrin.h>
#endif

#define MY_PI 3.141592653589793

union	Vec2
{
	struct{
		f32 x;
		f32 y;
	};
	f32 e[2];
	
	Vec2()
	{
		
	}
	
	Vec2(f32 _x, f32 _y)
	{
		this->x = _x;
		this->y = _y;
	}
	
	Vec2& operator+=(const Vec2& right);
	Vec2& operator-=(const Vec2& right);
	Vec2& operator*=(const Vec2& right);
	Vec2& operator*=(const f32 right);
};


union	Vec3
{
	struct{
		f32 x;
		f32 y;
		f32 z;
	};
	struct{
		f32 r;
		f32 g;
		f32 b;
	};
	f32	e[3];
	
#ifdef SSE_ENABLE
	__m128	sse;
#endif
	
	Vec3()
	{
#if defined(SSE_ENABLE)
		this->sse = _mm_setzero_ps();
#else
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
#endif // SSE_ENABLE
	}
	
	Vec3(f32 x, f32 y, f32 z)
	{
#if defined(SSE_ENABLE)
		this->sse = _mm_setr_ps(x, y, z, 0.0f);
#else
		this->x = x;
		this->y = y;
		this->z = z;
#endif // SSE_ENABLE
	}
	
	Vec3& operator+=(const Vec3& right);
	Vec3& operator-=(const Vec3& right);
	Vec3& operator*=(const Vec3& right);
	Vec3& operator*=(const f32 right); 
};

union	Vec4
{
	struct{
		f32 x;
		f32 y;
		f32 z;
		f32 w;
	};
	
	struct{
		f32 r;
		f32 g;
		f32 b;
		f32 a;
	};
	
	f32	e[4];
	
#ifdef SSE_ENABLE
	__m128	sse;
#endif
	
	Vec4()
	{
#if defined(SSE_ENABLE)
		this->sse = _mm_setzero_ps();
#else
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
#endif // SSE_ENABLE
	}
	
	Vec4(f32 x, f32 y, f32 z, f32 w)
	{
#if defined(SSE_ENABLE)
		this->sse = _mm_setr_ps(x, y, z, w);
#else
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
#endif // SSE_ENABLE
	}
	
	
	Vec4(Vec3& vec)
	{
#if defined(SSE_ENABLE)
		this->sse = vec.sse;
#else
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		this->w = 0.0f;
#endif // SSE_ENABLE
	}
	
	
	Vec4& operator+=(const Vec4& right);
	Vec4& operator-=(const Vec4& right);
	Vec4& operator*=(const Vec4& right);
	Vec4& operator*=(const f32 right);
};

union	M2x2
{
	f32 elems[2][2];
#if defined(SSE_ENABLE)
	__m128 sse;
#endif
	
	
	M2x2()
	{
#if defined(_WIN64) || defined(_WIN32)
		ZeroMemory(&(elems[0][0]), 4 * sizeof(f32));
#else
		memset(&(elems[0][0]), 0, 4 * sizeof(f32));
#endif
	}
	
	M2x2(f32 a11, f32 a12, f32 a21, f32 a22)
	{
#if defined(SSE_ENABLE)
		sse = _mm_set_ps(a22, a21, a12, a11);
#else
		elems[0][0] = a11;
		elems[0][1] = a12;
		elems[1][0] = a21;
		elems[1][1] = a22;
#endif
	}
	
};

union	 M4x4
{
	f32 elems[4][4];
#if defined(SSE_ENABLE)
	__m128 rows[4];
#endif
	
	M4x4()
	{
#if defined(_WIN64) || defined(_WIN32)
		ZeroMemory(&(elems[0][0]), sizeof(f32) * 4 * 4);
#else
		memset(&(elems[0][0]), 0, 4 * 4 * sizeof(f32));
#endif
	}
	
	M4x4(f32 d)
	{
#if defined(_WIN64) || defined(_WIN32)
		ZeroMemory(&(elems[0][0]), sizeof(f32) * 4 * 4);
#else
		memset(&(elems[0][0]), 0, 4 * 4 * sizeof(f32));
#endif
		elems[0][0] = d;
		elems[1][1] = d;
		elems[2][2] = d;
		elems[3][3] = d;
	}
	
	M4x4(Vec4 r1, Vec4 r2, Vec4 r3, Vec4 r4)
	{
		elems[0][0] = r1.e[0];
		elems[0][1] = r1.e[1];
		elems[0][2] = r1.e[2];
		elems[0][3] = r1.e[3];
		
		elems[1][0] = r2.e[0];
		elems[1][1] = r2.e[1];
		elems[1][2] = r2.e[2];
		elems[1][3] = r2.e[3];
		
		elems[2][0] = r3.e[0];
		elems[2][1] = r3.e[1];
		elems[2][2] = r3.e[2];
		elems[2][3] = r3.e[3];
		
		elems[3][0] = r4.e[0];
		elems[3][1] = r4.e[1];
		elems[3][2] = r4.e[2];
		elems[3][3] = r4.e[3];
	}
	
	M4x4(f32 a11, f32 a12, f32 a13, f32 a14,
		 f32 a21, f32 a22, f32 a23, f32 a24,
		 f32 a31, f32 a32, f32 a33, f32 a34,
		 f32 a41, f32 a42, f32 a43, f32 a44)
	{
		elems[0][0] = a11;
		elems[0][1] = a12;
		elems[0][2] = a13;
		elems[0][3] = a14;
		
		elems[1][0] = a21;
		elems[1][1] = a22;
		elems[1][2] = a23;
		elems[1][3] = a24;
		
		elems[2][0] = a31;
		elems[2][1] = a32;
		elems[2][2] = a33;
		elems[2][3] = a34;
		
		elems[3][0] = a41;
		elems[3][1] = a42;
		elems[3][2] = a43;
		elems[3][3] = a44;
	}
};

static  Vec2 operator+(const Vec2& left, const Vec2& right);
static  Vec2 operator-(const Vec2& left, const Vec2& right);
static  Vec2 operator*(f32 left, const Vec2& right);
static  Vec2 operator*(const Vec2& left, const f32 right);
static  Vec2 operator*(const Vec2& left, const Vec2& right);

static Vec3 operator+(const Vec3& left, const Vec3& right);
static Vec3 operator-(const Vec3& left, const Vec3& right);
static Vec3 operator*(f32 left, const Vec3& right);
static Vec3 operator*(const Vec3& left, const f32 right);
static Vec3 operator*(const Vec3& left, const Vec3& right);

static Vec4 operator+(const Vec4& left, const Vec4& right);
static Vec4 operator-(const Vec4& left, const Vec4& right);
static Vec4 operator*(const f32 left, const Vec4& right);
static Vec4 operator*(const Vec4& left, const f32 right);
static Vec4 operator*(const Vec4& left, const Vec4& right);

static M2x2 operator+(const M2x2& left, const M2x2& right);
static M2x2 operator-(const M2x2& left, const M2x2& right);
static M2x2 operator*(const M2x2& left, const M2x2& right);
static Vec2 operator*(const M2x2& left, const Vec2& right);
static Vec2 operator*(const Vec2& left, const M2x2& right);

static M4x4 operator+(const M4x4& left, const M4x4& right);
static M4x4 operator-(const M4x4& left, const M4x4& right);
static M4x4 operator*(const M4x4& left, const M4x4& right);
static Vec4 operator*(const Vec4& left, const M4x4& right);
static M4x4 operator*(f32 left, const M4x4& right);

static f32 dot(const Vec3& left, const Vec3& right);
static f32 length(const Vec3& vec);
static f32 lengthSquared(const Vec3& vec);
static Vec3  normalize(const Vec3& vec);
static Vec3  cross(const Vec3& left, const Vec3& right);

static M4x4  inverse(const M4x4& mat, float* det);
static M4x4  translate(f32 tX, f32 tY, f32 tZ);
static M4x4  transpose(M4x4& mat);
static M4x4  scale(f32 sX, f32 sY, f32 sZ);
static M4x4  rotateX(f32 angle);
static M4x4  rotateY(f32 angle);
static M4x4  rotateZ(f32 angle);
static M4x4  rotateAxis(f32 angle, Vec3 Axis);
static M4x4  orthographicRH(f32 left, f32 right,
							f32 bottom, f32 top,
							f32 nearP, f32 farP);
static M4x4 perspectiveLH(float fov, float aspectRatio, float Near, float Far);
static M4x4 perspectiveRH(float fov, float aspectRatio, float Near, float Far);
static M4x4 lookAtLH(Vec3 pos, Vec3 at, Vec3 worldUp);
static M4x4 lookAtRH(Vec3 pos, Vec3 at, Vec3 worldUp);
static M4x4 lookAtRH(Camera& camera);

static inline f32 toRadians(f32 value);
static inline f32 toDegrees(f32 value);


#endif //MATH_H