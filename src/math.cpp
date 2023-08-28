#include "math.h"

static Vec2 operator+(const Vec2& left, const Vec2& right)
{
	Vec2	result;
	
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	return (result);
}

static Vec2 operator-(const Vec2& left, const Vec2& right)
{
	Vec2	result;
	
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	return (result);
}

static Vec2 operator*(f32 left, const Vec2& right)
{
	Vec2	result;
	
	result.x = left * right.x;
	result.y = left * right.y;
	return (result);
}

static Vec2 operator*(const Vec2& left, const f32 right)
{
	Vec2	result;
	
	result.x = left.x * right;
	result.y = left.y * right;
	return (result);
}

static Vec2 operator*(const Vec2& left, const Vec2& right)
{
	Vec2	result;
	
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	return (result);
}

Vec2& Vec2::operator+=(const Vec2& right)
{
	this->x += right.x;
	this->y += right.y;
	return (*this);
}

Vec2& Vec2::operator-=(const Vec2& right)
{
	this->x -= right.x;
	this->y -= right.y;
	return (*this);
}

Vec2& Vec2::operator*=(const Vec2& right)
{
	this->x *= right.x;
	this->y *= right.y;
	return (*this);
}

Vec2& Vec2::operator*=(const f32 right)
{
	this->x *= right;
	this->y *= right;
	return (*this);
}


static Vec3 operator+(const Vec3& left, const Vec3& right)
{
	Vec3	result = {};
#if defined(SSE_ENABLE)
	result.sse = _mm_add_ps(left.sse, right.sse);
#else
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
#endif //SSE_ENABLE
	return (result);
}

static Vec3 operator-(const Vec3& left, const Vec3& right)
{
	Vec3	result = {};
#if defined(SSE_ENABLE)
	result.sse = _mm_sub_ps(left.sse, right.sse);
#else
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
#endif
	return (result);
}

static Vec3 operator*(f32 left, const Vec3& right)
{
	Vec3	result = {};
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(_mm_set_ps1(left), right.sse);
#else
	result.x = left * right.x;
	result.y = left * right.y;
	result.z = left * right.z;
#endif //SSE_ENABLE
	return (result);
}

static Vec3 operator*(const Vec3& left, f32 right)
{
	Vec3	result = {};
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(left.sse, _mm_set_ps1(right));
#else
	result.x = left.x * right;
	result.y = left.y * right;
	result.z = left.z * right;
#endif // SSE_ENABLE
	return (result);
}

// NOTE(yassine): Hadamard product.
static Vec3 operator*(const Vec3& left, const Vec3& right)
{
	Vec3	result = {};
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(left.sse, right.sse);
#else
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
#endif //SSE_ENABLE
	
	return (result);
}

Vec3& Vec3::operator+=(const Vec3& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_add_ps(this->sse, right.sse);
#else
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
#endif //SSE_ENABLE
	return (*this);
}

Vec3& Vec3::operator-=(const Vec3& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_sub_ps(this->sse, right.sse);
#else
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
#endif //SSE_ENABLE
	return (*this);
}

Vec3& Vec3::operator*=(const Vec3& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_mul_ps(this->sse, right.sse);
#else
	this->x *= right.x;
	this->y *= right.y;
	this->z *= right.z;
#endif //SSE_ENABLE
	return (*this);
}

Vec3& Vec3::operator*=(const f32 right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_mul_ps(this->sse, _mm_set_ps1(right));
#else
	this->x *= right;
	this->y *= right;
	this->z *= right;
#endif //SSE_ENABLE
	return (*this);
}

static f32 dot(const Vec3& left, const Vec3& right)
{
	f32	result = 0.0f;
	
#if defined(SSE_ENABLE)
	__m128 res1 = _mm_mul_ps(left.sse, right.sse);
	__m128 res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(0, 1, 2, 3));
	res1 = _mm_add_ps(res1, res2);
	res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(1, 0, 3, 2));
	res1 = _mm_add_ps(res1, res2);
	_mm_store_ss(&result, res1);
	//result = res1.m128_f32[0] + res1.m128_f32[1] + res1.m128_f32[2] + res1.m128_f32[3];
#else
	result = (left.x * right.x) +
	(left.y * right.y) +
	(left.z * right.z);
#endif
	return (result);
}

static f32 length(const Vec3& vec)
{
	f32	result;
#if defined(SSE_ENABLE)
	__m128 res1 = _mm_mul_ps(vec.sse, vec.sse);
	__m128 res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(0, 1, 2, 3));
	res1 = _mm_add_ps(res1, res2);
	res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(1, 0, 3, 2));
	res1 = _mm_add_ps(res1, res2);
	res1 = _mm_sqrt_ps(res1);
	_mm_store_ss(&result, res1);
#else
	result = dot(vec, vec);
	result = sqrtf(result);
#endif//SSE_ENABLE
	return (result);
}

static f32 lengthSquared(const Vec3& vec)
{
	return (dot(vec, vec));
}

static Vec3  normalize(const Vec3& vec)
{
	Vec3	result = {};
	
#if defined(SSE_ENABLE)
	__m128 res1 = _mm_mul_ps(vec.sse, vec.sse);
	__m128 res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(0, 1, 2, 3));
	res1 = _mm_add_ps(res1, res2);
	res2 = _mm_shuffle_ps(res1, res1, _MM_SHUFFLE(1, 0, 3, 2));
	res1 = _mm_add_ps(res1, res2);
	res1 = _mm_sqrt_ps(res1);
	
	result.sse = _mm_div_ps(vec.sse, res1);
#else
	f32	len = 1.0f / length(vec);
	
	result = vec * len;
#endif //SSE_ENABLE
	return (result);
}

static Vec3  cross(const Vec3& left, const Vec3& right)
{
	Vec3	result = {};
	
#if defined(SSE_ENABLE)
	__m128	tmp1 = _mm_shuffle_ps(left.sse, left.sse, _MM_SHUFFLE(3, 0, 2, 1));
	__m128	tmp2 = _mm_shuffle_ps(right.sse, right.sse, _MM_SHUFFLE(3, 1, 0, 2));
	__m128	tmp3 = _mm_shuffle_ps(left.sse, left.sse, _MM_SHUFFLE(3, 1, 0, 2));
	__m128	tmp4 = _mm_shuffle_ps(right.sse, right.sse, _MM_SHUFFLE(3, 0, 2, 1));
	
	tmp1 = _mm_mul_ps(tmp1, tmp2);
	tmp3 = _mm_mul_ps(tmp3, tmp4);
	result.sse = _mm_sub_ps(tmp1, tmp3);
#else
	result.x = (left.y * right.z) - (left.z * right.y);
	result.y = (right.x * left.z) - (left.x * right.z);
	result.z = (left.x * right.y) - (left.y * right.x);
#endif //SSE_ENABLE
	return (result);
}

static inline f32 toRadians(f32 value)
{
	return (value * MY_PI / 180.0f);
}

static inline f32 toDegrees(f32 value)
{
	return (value * 180.0f / MY_PI);
}


static Vec4 operator+(const Vec4& left, const Vec4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_add_ps(left.sse, right.sse);
#else
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;
	result.w = left.w + right.w;
#endif //SSE_ENABLE
	return (result);
}

static Vec4 operator-(const Vec4& left, const Vec4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_sub_ps(left.sse, right.sse);
#else
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;
	result.w = left.w - right.w;
#endif //SSE_ENABLE
	return (result);
}

static Vec4 operator*(const f32 left, const Vec4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(_mm_set_ps1(left), right.sse);
#else
	result.x = left * right.x;
	result.y = left * right.y;
	result.z = left * right.z;
	result.w = left * right.w;
#endif //SSE_ENABLE
	return (result);
}

static Vec4 operator*(const Vec4& left, const f32 right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(left.sse, _mm_set_ps1(right));
#else
	result.x = left.x * right;
	result.y = left.y * right;
	result.z = left.z * right;
	result.w = left.w * right;
#endif //SSE_ENABLE
	return (result);
}

static Vec4 operator*(const Vec4& left, const Vec4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(left.sse, right.sse);
#else
	result.x = left.x * right.x;
	result.y = left.y * right.y;
	result.z = left.z * right.z;
	result.w = left.w * right.w;
#endif //SSE_ENABLE
	return (result);
}

Vec4& Vec4::operator+=(const Vec4& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_add_ps(this->sse, right.sse);
#else
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	this->w += right.w;
#endif //SSE_ENABLE
	return (*this);
}

Vec4& Vec4::operator-=(const Vec4& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_sub_ps(this->sse, right.sse);
#else
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	this->w -= right.w;
#endif //SSE_ENABLE
	return (*this);
}

Vec4& Vec4::operator*=(const Vec4& right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_mul_ps(this->sse, right.sse);
#else
	this->x *= right.x;
	this->y *= right.y;
	this->z *= right.z;
	this->w *= right.w;
#endif //SSE_ENABLE
	return (*this);
}

Vec4& Vec4::operator*=(const f32 right)
{
#if defined(SSE_ENABLE)
	this->sse = _mm_mul_ps(this->sse, _mm_set_ps1(right));
#else
	this->x *= right;
	this->y *= right;
	this->z *= right;
	this->w *= right;
#endif //SSE_ENABLE
	return (*this);
}

static M2x2 operator+(const M2x2& left, const M2x2& right)
{
	M2x2	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_add_ps(left.sse, right.sse);
#else
	result.elems[0][0] = left.elems[0][0] + right.elems[0][0];
	result.elems[0][1] = left.elems[0][1] + right.elems[0][1];
	result.elems[1][0] = left.elems[1][0] + right.elems[1][0];
	result.elems[1][1] = left.elems[1][1] + right.elems[1][1];
#endif
	return (result);
}

static M2x2 operator-(const M2x2& left, const M2x2& right)
{
	M2x2	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_sub_ps(left.sse, right.sse);
#else
	result.elems[0][0] = left.elems[0][0] - right.elems[0][0];
	result.elems[0][1] = left.elems[0][1] - right.elems[0][1];
	result.elems[1][0] = left.elems[1][0] - right.elems[1][0];
	result.elems[1][1] = left.elems[1][1] - right.elems[1][1];
#endif
	return (result);
}

static M2x2 operator*(const M2x2& left, const M2x2& right)
{
	M2x2	result = {};
	
#if defined(SSE_ENABLE)
	// NOTE(yassine): there is probably a faster way to do it
	__m128 res1 = _mm_shuffle_ps(left.sse, left.sse, _MM_SHUFFLE(2, 2, 0, 0));
	__m128 res2 = _mm_shuffle_ps(right.sse, right.sse, _MM_SHUFFLE(1, 0, 1, 0));
	
	res1 = _mm_mul_ps(res1, res2);
	
	__m128 res3 = _mm_shuffle_ps(left.sse, left.sse, _MM_SHUFFLE(3, 3, 1, 1));
	__m128 res4 = _mm_shuffle_ps(right.sse, right.sse, _MM_SHUFFLE(3, 2, 3, 2));
	
	res3 = _mm_mul_ps(res3, res4);
	
	
	result.sse = _mm_add_ps(res1, res3);
	
#else
	result.elems[0][0] = left.elems[0][0] * right.elems[0][0] + left.elems[0][1] * right.elems[1][0];
	result.elems[0][1] = left.elems[0][0] * right.elems[0][1] + left.elems[0][1] * right.elems[1][1];
	result.elems[1][0] = left.elems[1][0] * right.elems[0][0] + left.elems[1][1] * right.elems[1][0];
	result.elems[1][1] = left.elems[1][0] * right.elems[0][1] + left.elems[1][1] * right.elems[1][1];
#endif //SSE_ENABLE
	
	return (result);
}

static Vec2 operator*(const M2x2& left, const Vec2& right)
{
	Vec2	result = {};
	
#if defined(SSE_ENABLE)
	__m128	res = _mm_set_ps(0.0f, 0.0f, right.e[1], right.e[0]);
	res = _mm_shuffle_ps(res, res, _MM_SHUFFLE(1, 0, 1, 0));
	res = _mm_mul_ps(res, left.sse);
	__m128 shuff = _mm_shuffle_ps(res, res, _MM_SHUFFLE(2, 3, 0, 1));
	res = _mm_add_ps(res, shuff);
	result.e[0] = res.m128_f32[0];
	result.e[1] = res.m128_f32[2];
#else
	result.e[0] = left.elems[0][0] * right.e[0] + left.elems[0][1] * right.e[1];
	result.e[1] = left.elems[1][0] * right.e[0] + left.elems[1][1] * right.e[1];
#endif //SSE_ENABLE
	
	return (result);
}

static Vec2 operator*(const Vec2& left, const M2x2& right)
{
	Vec2	result = {};
	
#if defined(SSE_ENABLE)
	__m128	res = _mm_set_ps(0.0f, 0.0f, left.e[0], left.e[1]);
	res = _mm_shuffle_ps(res, res, _MM_SHUFFLE(0, 0, 1, 1));
	res = _mm_mul_ps(res, right.sse);
	__m128 shuff = _mm_shuffle_ps(res, res, _MM_SHUFFLE(1, 0, 3, 2));
	res = _mm_add_ps(res, shuff);
	result.e[0] = res.m128_f32[0];
	result.e[1] = res.m128_f32[1];
	
#else
	result.e[0] = left.e[0] * right.elems[0][0] + left.e[1] * right.elems[1][0];
	result.e[1] = left.e[0] * right.elems[0][1] + left.e[1] * right.elems[1][1];
#endif //SSE_ENABLE
	
	return (result);
}

static M4x4 operator+(const M4x4& left, const M4x4& right)
{
	M4x4	result = {};
	
#if defined(SSE_ENABLE)
	/*
	for (u32 rowIdx = 0; rowIdx < 4; rowIdx++)
		result.rows[rowIdx] = _mm_add_ps(left.rows[rowIdx], right.rows[rowIdx]);
*/
	result.rows[0] = _mm_add_ps(left.rows[0], right.rows[0]);
	result.rows[1] = _mm_add_ps(left.rows[1], right.rows[1]);
	result.rows[2] = _mm_add_ps(left.rows[2], right.rows[2]);
	result.rows[3] = _mm_add_ps(left.rows[3], right.rows[3]);
#else
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			result.elems[row][col] = left.elems[row][col] + right.elems[row][col];
		}
	}
#endif
	
	return (result);
}

static M4x4 operator-(const M4x4& left, const M4x4& right)
{
	M4x4	result = {};
	
#if defined(SSE_ENABLE)
	/*
	for (u32 rowIdx = 0; rowIdx < 4; rowIdx++)
		result.rows[rowIdx] = _mm_sub_ps(left.rows[rowIdx], right.rows[rowIdx]);
*/
	result.rows[0] = _mm_sub_ps(left.rows[0], right.rows[0]);
	result.rows[1] = _mm_sub_ps(left.rows[1], right.rows[1]);
	result.rows[2] = _mm_sub_ps(left.rows[2], right.rows[2]);
	result.rows[3] = _mm_sub_ps(left.rows[3], right.rows[3]);
#else
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			result.elems[row][col] = left.elems[row][col] - right.elems[row][col];
		}
	}
#endif
	
	return (result);
}

static M4x4 operator*(const M4x4& left, const M4x4& right)
{
	M4x4	result = {};
	
#if defined(SSE_ENABLE)
	/*for (u32 i = 0; i < 4; i++)
	{
		
		result.rows[i] = _mm_mul_ps(_mm_shuffle_ps(left.rows[i], left.rows[i], 0x00), right.rows[0]);
		result.rows[i] = _mm_add_ps(result.rows[i], _mm_mul_ps(_mm_shuffle_ps(left.rows[i], left.rows[i], 0x55), right.rows[1]));
		result.rows[i] = _mm_add_ps(result.rows[i], _mm_mul_ps(_mm_shuffle_ps(left.rows[i], left.rows[i], 0xAA), right.rows[2]));
		result.rows[i] = _mm_add_ps(result.rows[i], _mm_mul_ps(_mm_shuffle_ps(left.rows[i], left.rows[i], 0xFF), right.rows[3]));
	}
	*/
	result.rows[0] = _mm_mul_ps(_mm_shuffle_ps(left.rows[0], left.rows[0], 0x00), right.rows[0]);
	result.rows[0] = _mm_add_ps(result.rows[0], _mm_mul_ps(_mm_shuffle_ps(left.rows[0], left.rows[0], 0x55), right.rows[1]));
	result.rows[0] = _mm_add_ps(result.rows[0], _mm_mul_ps(_mm_shuffle_ps(left.rows[0], left.rows[0], 0xAA), right.rows[2]));
	result.rows[0] = _mm_add_ps(result.rows[0], _mm_mul_ps(_mm_shuffle_ps(left.rows[0], left.rows[0], 0xFF), right.rows[3]));
	
	result.rows[1] = _mm_mul_ps(_mm_shuffle_ps(left.rows[1], left.rows[1], 0x00), right.rows[0]);
	result.rows[1] = _mm_add_ps(result.rows[1], _mm_mul_ps(_mm_shuffle_ps(left.rows[1], left.rows[1], 0x55), right.rows[1]));
	result.rows[1] = _mm_add_ps(result.rows[1], _mm_mul_ps(_mm_shuffle_ps(left.rows[1], left.rows[1], 0xAA), right.rows[2]));
	result.rows[1] = _mm_add_ps(result.rows[1], _mm_mul_ps(_mm_shuffle_ps(left.rows[1], left.rows[1], 0xFF), right.rows[3]));
	
	result.rows[2] = _mm_mul_ps(_mm_shuffle_ps(left.rows[2], left.rows[2], 0x00), right.rows[0]);
	result.rows[2] = _mm_add_ps(result.rows[2], _mm_mul_ps(_mm_shuffle_ps(left.rows[2], left.rows[2], 0x55), right.rows[1]));
	result.rows[2] = _mm_add_ps(result.rows[2], _mm_mul_ps(_mm_shuffle_ps(left.rows[2], left.rows[2], 0xAA), right.rows[2]));
	result.rows[2] = _mm_add_ps(result.rows[2], _mm_mul_ps(_mm_shuffle_ps(left.rows[2], left.rows[2], 0xFF), right.rows[3]));
	
	result.rows[3] = _mm_mul_ps(_mm_shuffle_ps(left.rows[3], left.rows[3], 0x00), right.rows[0]);
	result.rows[3] = _mm_add_ps(result.rows[3], _mm_mul_ps(_mm_shuffle_ps(left.rows[3], left.rows[3], 0x55), right.rows[1]));
	result.rows[3] = _mm_add_ps(result.rows[3], _mm_mul_ps(_mm_shuffle_ps(left.rows[3], left.rows[3], 0xAA), right.rows[2]));
	result.rows[3] = _mm_add_ps(result.rows[3], _mm_mul_ps(_mm_shuffle_ps(left.rows[3], left.rows[3], 0xFF), right.rows[3]));
#else
	
	/*
	f32 sum = 0.0f;
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			for (u32 k = 0; k < 4; k++)
			{
				sum += left.elems[row][k] * right.elems[k][col];
			}
			result.e[row][col] = sum;
			sum = 0.0f;
		}
	}
	*/
	result.elems[0][0] = left.elems[0][0] * right.elems[0][0] + left.elems[0][1] * right.elems[1][0] + left.elems[0][2] * right.elems[2][0] + left.elems[0][3] * right.elems[3][0];
	result.elems[0][1] = left.elems[0][0] * right.elems[0][1] + left.elems[0][1] * right.elems[1][1] + left.elems[0][2] * right.elems[2][1] + left.elems[0][3] * right.elems[3][1];
	result.elems[0][2] = left.elems[0][0] * right.elems[0][2] + left.elems[0][1] * right.elems[1][2] + left.elems[0][2] * right.elems[2][2] + left.elems[0][3] * right.elems[3][2];
	result.elems[0][3] = left.elems[0][0] * right.elems[0][3] + left.elems[0][1] * right.elems[1][3] + left.elems[0][2] * right.elems[2][3] + left.elems[0][3] * right.elems[3][3];
	
	result.elems[1][0] = left.elems[1][0] * right.elems[0][0] + left.elems[1][1] * right.elems[1][0] + left.elems[1][2] * right.elems[2][0] + left.elems[1][3] * right.elems[3][0];
	result.elems[1][1] = left.elems[1][0] * right.elems[0][1] + left.elems[1][1] * right.elems[1][1] + left.elems[1][2] * right.elems[2][1] + left.elems[1][3] * right.elems[3][1];
	result.elems[1][2] = left.elems[1][0] * right.elems[0][2] + left.elems[1][1] * right.elems[1][2] + left.elems[1][2] * right.elems[2][2] + left.elems[1][3] * right.elems[3][2];
	result.elems[1][3] = left.elems[1][0] * right.elems[0][3] + left.elems[1][1] * right.elems[1][3] + left.elems[1][2] * right.elems[2][3] + left.elems[1][3] * right.elems[3][3];
	
	result.elems[2][0] = left.elems[2][0] * right.elems[0][0] + left.elems[2][1] * right.elems[1][0] + left.elems[2][2] * right.elems[2][0] + left.elems[2][3] * right.elems[3][0];
	result.elems[2][1] = left.elems[2][0] * right.elems[0][1] + left.elems[2][1] * right.elems[1][1] + left.elems[2][2] * right.elems[2][1] + left.elems[2][3] * right.elems[3][1];
	result.elems[2][2] = left.elems[2][0] * right.elems[0][2] + left.elems[2][1] * right.elems[1][2] + left.elems[2][2] * right.elems[2][2] + left.elems[2][3] * right.elems[3][2];
	result.elems[2][3] = left.elems[2][0] * right.elems[0][3] + left.elems[2][1] * right.elems[1][3] + left.elems[2][2] * right.elems[2][3] + left.elems[2][3] * right.elems[3][3];
	
	result.elems[3][0] = left.elems[3][0] * right.elems[0][0] + left.elems[3][1] * right.elems[1][0] + left.elems[3][2] * right.elems[2][0] + left.elems[3][3] * right.elems[3][0];
	result.elems[3][1] = left.elems[3][0] * right.elems[0][1] + left.elems[3][1] * right.elems[1][1] + left.elems[3][2] * right.elems[2][1] + left.elems[3][3] * right.elems[3][1];
	result.elems[3][2] = left.elems[3][0] * right.elems[0][2] + left.elems[3][1] * right.elems[1][2] + left.elems[3][2] * right.elems[2][2] + left.elems[3][3] * right.elems[3][2];
	result.elems[3][3] = left.elems[3][0] * right.elems[0][3] + left.elems[3][1] * right.elems[1][3] + left.elems[3][2] * right.elems[2][3] + left.elems[3][3] * right.elems[3][3];
	
	
#endif //SSE_ENABLE
	
	return (result);
}

static Vec4 operator*(const Vec4& left, const M4x4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	result.sse = _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0x00), right.rows[0]);
	result.sse = _mm_add_ps(result.sse, _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0x55), right.rows[1]));
	result.sse = _mm_add_ps(result.sse, _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0xAA), right.rows[2]));
	result.sse = _mm_add_ps(result.sse, _mm_mul_ps(_mm_shuffle_ps(left.sse, left.sse, 0xFF), right.rows[3]));
#else
	result.e[0] = left.e[0] * right.elems[0][0] + left.e[1] * right.elems[1][0] + left.e[2] * right.elems[2][0] + left.e[3] * right.elems[3][0];
	result.e[1] = left.e[0] * right.elems[0][1] + left.e[1] * right.elems[1][1] + left.e[2] * right.elems[2][1] + left.e[3] * right.elems[3][1];
	result.e[2] = left.e[0] * right.elems[0][2] + left.e[1] * right.elems[1][2] + left.e[2] * right.elems[2][2] + left.e[3] * right.elems[3][2];
	result.e[3] = left.e[0] * right.elems[0][3] + left.e[1] * right.elems[1][3] + left.e[2] * right.elems[2][3] + left.e[3] * right.elems[3][3];
#endif //SSE_ENABLE
	
	return (result);
}

static M4x4 operator*(f32 left, const M4x4& right)
{
	M4x4 result = {};
#if defined(SSE_ENABLE)
	__m128 num = _mm_set_ps1(left);
	result.rows[0] = _mm_mul_ps(num, right.rows[0]);
	result.rows[1] = _mm_mul_ps(num, right.rows[1]);
	result.rows[2] = _mm_mul_ps(num, right.rows[2]);
	result.rows[3] = _mm_mul_ps(num, right.rows[3]);
#else
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			result.elems[row][col] = right.elems[row][col] * left;
		}
	}
#endif // SSE_ENABLE
	return (result);
}

/*
static Vec4 operator*(const M4x4& left, const Vec4& right)
{
	Vec4	result = {};
	
#if defined(SSE_ENABLE)
	
#else
	result.e[0] = left.elems[0][0] * right.e[0] + left.elems[0][1] * right.e[1] + left.elems[0][2] * right.e[2] + left.elems[0][3] * right.e[3];
	result.e[1] = left.elems[1][0] * right.e[0] + left.elems[1][1] * right.e[1] + left.elems[1][2] * right.e[2] + left.elems[1][3] * right.e[3];
	result.e[2] = left.elems[2][0] * right.e[0] + left.elems[2][1] * right.e[1] + left.elems[2][2] * right.e[2] + left.elems[2][3] * right.e[3];
	result.e[3] = left.elems[3][0] * right.e[0] + left.elems[3][1] * right.e[1] + left.elems[3][2] * right.e[2] + left.elems[3][3] * right.e[3];
#endif
	
	return (result);
}
*/

static M4x4  translate(f32 tX, f32 tY, f32 tZ)
{
	M4x4	result = M4x4(1.0f);
	
#if defined(SSE_ENABLE)
	result.rows[3] = _mm_set_ps(1.0f, tZ, tY, tX);
#else
	result.elems[3][0] = tX;
	result.elems[3][1] = tY;
	result.elems[3][2] = tZ;
#endif//SSE_ENABLE
	return (result);
}

static M4x4  scale(f32 sX, f32 sY, f32 sZ)
{
	M4x4	result = {};
	
	result.elems[0][0] = sX;
	result.elems[1][1] = sY;
	result.elems[2][2] = sZ;
	result.elems[3][3] = 1.0f;
	return (result);
}

static M4x4  rotateX(f32 angle)
{
	M4x4	result = M4x4(1.0f);
	
	f32 c = cosf(angle);
	f32 s = sinf(angle);
	
	result.elems[1][1] = c;
	result.elems[1][2] = -s;
	result.elems[2][1] = s;
	result.elems[2][2] = c;
	
	return (result);
}

static M4x4  rotateY(f32 angle)
{
	M4x4	result = M4x4(1.0f);
	
	f32 c = cosf(angle);
	f32 s = sinf(angle);
	
	result.elems[0][0] = c;
	result.elems[0][2] = s;
	result.elems[2][0] = -s;
	result.elems[2][2] = c;
	
	return (result);
}

static M4x4  rotateZ(f32 angle)
{
	M4x4	result = M4x4(1.0f);
	
	f32 c = cosf(angle);
	f32 s = sinf(angle);
	
	result.elems[0][0] = c;
	result.elems[0][1] = -s;
	result.elems[1][0] = s;
	result.elems[1][1] = c;
	
	return (result);
}

static M4x4  rotateAxis(f32 angle, Vec3 Axis)
{
	M4x4	result = M4x4(1.0f);
	
	f32 c = cosf(angle);
	f32 s = sinf(angle);
	f32 cv = 1 - c;
	
	f32 x = Axis.x;
	f32 y = Axis.y;
	f32 z = Axis.z;
	
	result.elems[0][0] = c + cv * x * x;
	result.elems[0][1] = cv * x *y + s * z;
	result.elems[0][2] = cv * x * z - s * y;
	result.elems[1][0] = cv * x * y - s * z;
	result.elems[1][1] = c + cv * y * y;
	result.elems[1][2] = cv * y * z + s * x;
	result.elems[2][0] = cv * x * z + s * y;
	result.elems[2][1] = cv * y * z - s * x;
	result.elems[2][2] = c + cv * z * z;
	
	return (result);
}


static M4x4  orthographicRH(f32 left, f32 right,
							f32 bottom, f32 top,
							f32 nearP, f32 farP)
{
	M4x4	result = {};
	
	result.elems[0][0] = 2.0f / (right - left);
	result.elems[1][1] = 2.0f / (top - bottom);
	result.elems[2][2] = 2.0f / (nearP- farP);
	result.elems[3][3] = 1.0f;
	
	result.elems[3][0] = (left + right) / (left - right);
	result.elems[3][1] = (bottom + top) / (bottom - top);
	result.elems[3][2] = (farP + nearP) / (nearP - farP);
	return (result);
}


static M4x4 perspectiveLH(float fov, float aspectRatio, float Near, float Far)
{
	M4x4 result = {};
	
	float cot = 1.0f / tanf(fov * 0.5f);
	
	result.elems[0][0] = cot / aspectRatio;
	result.elems[1][1] = cot;
	result.elems[2][3] = 1.0f;
	result.elems[2][2] = -Far / (Near - Far);
	result.elems[3][2] = (Near * Far) / (Near - Far);
	
	return (result);
}

static M4x4 perspectiveRH(float fov, float aspectRatio, float Near, float Far)
{
	M4x4	result = {};
	
	float cot = 1.0f / tanf(fov * 0.5f);
	
	result.elems[0][0] = cot / aspectRatio;
	result.elems[1][1] = cot;
	result.elems[2][3] = -1.0f;
	result.elems[2][2] = (Near + Far) / (Near - Far);
	result.elems[3][2] = (2.0f * Near * Far) / (Near - Far);
	
	return (result);
}

static M4x4 transpose(M4x4& mat)
{
	M4x4 result = {};
	
	for (u32 row = 0; row < 4; row++)
	{
		for (u32 col = 0; col < 4; col++)
		{
			result.elems[row][col] = mat.elems[col][row];
		}
	}
	return (result);
}


static M4x4 lookAtLH(Vec3 pos, Vec3 at, Vec3 worldUp)
{
	M4x4 result = {};
	
	Vec3 zAxis = normalize(at - pos);
	Vec3 xAxis = normalize(cross(worldUp, zAxis));
	Vec3 yAxis = normalize(cross(zAxis, xAxis));
	
	result.elems[0][0] = xAxis.x;
	result.elems[1][0] = xAxis.y;
	result.elems[2][0] = xAxis.z;
	
	result.elems[0][1] = yAxis.x;
	result.elems[1][1] = yAxis.y;
	result.elems[2][1] = yAxis.z;
	
	result.elems[0][2] = zAxis.x;
	result.elems[1][2] = zAxis.y;
	result.elems[2][2] = zAxis.z;
	
	
	result.elems[3][0] = -dot(xAxis, pos);
	result.elems[3][1] = -dot(yAxis, pos);
	result.elems[3][2] = -dot(zAxis, pos);
	result.elems[3][3] = 1.0f;
	
	
	return (result);
}


static M4x4 lookAtRH(Vec3 pos, Vec3 at, Vec3 worldUp)
{
	M4x4	result = {};
	
	Vec3	zAxis = normalize(at - pos);
	Vec3	xAxis = normalize(cross(zAxis, worldUp));
	Vec3	yAxis = cross(xAxis, zAxis);
	
	result.elems[0][0] = xAxis.x;
	result.elems[1][0] = xAxis.y;
	result.elems[2][0] = xAxis.z;
	
	result.elems[0][1] = yAxis.x;
	result.elems[1][1] = yAxis.y;
	result.elems[2][1] = yAxis.z;
	
	result.elems[0][2] = -zAxis.x;
	result.elems[1][2] = -zAxis.y;
	result.elems[2][2] = -zAxis.z;
	
	
	result.elems[3][0] = -dot(xAxis, pos);
	result.elems[3][1] = -dot(yAxis, pos);
	result.elems[3][2] = dot(zAxis, pos);
	result.elems[3][3] = 1.0f;
	
	return (result);
}


static M4x4	lookAtRH(Camera& camera)
{
	M4x4	result = {};
	
	result.elems[0][0] = camera.x.x;
	result.elems[1][0] = camera.x.y;
	result.elems[2][0] = camera.x.z;
	
	result.elems[0][1] = camera.y.x;
	result.elems[1][1] = camera.y.y;
	result.elems[2][1] = camera.y.z;
	
	result.elems[0][2] = -camera.z.x;
	result.elems[1][2] = -camera.z.y;
	result.elems[2][2] = -camera.z.z;
	
	
	result.elems[3][0] = -dot(camera.x, camera.position);
	result.elems[3][1] = -dot(camera.y, camera.position);
	result.elems[3][2] = dot(camera.z, camera.position);
	result.elems[3][3] = 1.0f;
	
	return (result);
}

static M4x4 inverse(const M4x4& mat, float* det)
{
	M4x4 result = {};
	
	M4x4 coMat = {};
	
	coMat.elems[0][0] = mat.elems[1][1] * mat.elems[2][2] * mat.elems[3][3] -
		mat.elems[1][1] * mat.elems[3][2] * mat.elems[2][3] -
		mat.elems[2][1] * mat.elems[1][2] * mat.elems[3][3] +
		mat.elems[2][1] * mat.elems[3][2] * mat.elems[1][3] +
		mat.elems[3][1] * mat.elems[1][2] * mat.elems[2][3] -
		mat.elems[3][1] * mat.elems[2][2] * mat.elems[1][3];
	
	coMat.elems[0][1] = -mat.elems[1][0] * mat.elems[2][2] * mat.elems[3][3] +
		mat.elems[1][0] * mat.elems[3][2] * mat.elems[2][3] +
		mat.elems[2][0] * mat.elems[1][2] * mat.elems[3][3] -
		mat.elems[2][0] * mat.elems[3][2] * mat.elems[1][3] -
		mat.elems[3][0] * mat.elems[1][2] * mat.elems[2][3] +
		mat.elems[3][0] * mat.elems[2][2] * mat.elems[1][3];
	
	coMat.elems[0][2] = mat.elems[1][0] * mat.elems[2][1] * mat.elems[3][3] -
		mat.elems[1][0] * mat.elems[3][1] * mat.elems[2][3] -
		mat.elems[2][0] * mat.elems[1][1] * mat.elems[3][3] +
		mat.elems[2][0] * mat.elems[3][1] * mat.elems[1][3] +
		mat.elems[3][0] * mat.elems[1][1] * mat.elems[2][3] -
		mat.elems[3][0] * mat.elems[2][1] * mat.elems[1][3];
	
	coMat.elems[0][3] = -mat.elems[1][0] * mat.elems[2][1] * mat.elems[3][2] +
		mat.elems[1][0] * mat.elems[3][1] * mat.elems[2][2] +
		mat.elems[2][0] * mat.elems[1][1] * mat.elems[3][2] -
		mat.elems[2][0] * mat.elems[3][1] * mat.elems[1][2] -
		mat.elems[3][0] * mat.elems[1][1] * mat.elems[2][2] +
		mat.elems[3][0] * mat.elems[2][1] * mat.elems[1][2];
	
	coMat.elems[1][0] = -mat.elems[0][1] * mat.elems[2][2] * mat.elems[3][3] +
		mat.elems[0][1] * mat.elems[3][2] * mat.elems[2][3] +
		mat.elems[2][1] * mat.elems[0][2] * mat.elems[3][3] -
		mat.elems[2][1] * mat.elems[3][2] * mat.elems[0][3] -
		mat.elems[3][1] * mat.elems[0][2] * mat.elems[2][3] +
		mat.elems[3][1] * mat.elems[2][2] * mat.elems[0][3];
	
	coMat.elems[1][1] = mat.elems[0][0] * mat.elems[2][2] * mat.elems[3][3] -
		mat.elems[0][0] * mat.elems[3][2] * mat.elems[2][3] -
		mat.elems[2][0] * mat.elems[0][2] * mat.elems[3][3] +
		mat.elems[2][0] * mat.elems[3][2] * mat.elems[0][3] +
		mat.elems[3][0] * mat.elems[0][2] * mat.elems[1][3] -
		mat.elems[3][0] * mat.elems[1][2] * mat.elems[0][3];
	
	coMat.elems[1][2] = -mat.elems[0][0] * mat.elems[2][1] * mat.elems[3][3] +
		mat.elems[0][0] * mat.elems[3][1] * mat.elems[2][3] +
		mat.elems[2][0] * mat.elems[0][1] * mat.elems[3][3] -
		mat.elems[2][0] * mat.elems[3][1] * mat.elems[0][3] -
		mat.elems[3][0] * mat.elems[0][1] * mat.elems[2][3] +
		mat.elems[3][0] * mat.elems[2][1] * mat.elems[0][3];
	
	coMat.elems[1][3] = mat.elems[0][0] * mat.elems[2][1] * mat.elems[3][2] -
		mat.elems[0][0] * mat.elems[3][1] * mat.elems[2][2] -
		mat.elems[2][0] * mat.elems[1][1] * mat.elems[3][2] +
		mat.elems[2][0] * mat.elems[3][1] * mat.elems[1][2] +
		mat.elems[3][0] * mat.elems[1][1] * mat.elems[2][2] -
		mat.elems[3][0] * mat.elems[2][1] * mat.elems[1][2];
	
	coMat.elems[2][0] = mat.elems[0][1] * mat.elems[1][2] * mat.elems[3][3] -
		mat.elems[0][1] * mat.elems[3][2] * mat.elems[1][3] -
		mat.elems[1][1] * mat.elems[0][2] * mat.elems[3][3] +
		mat.elems[1][1] * mat.elems[3][2] * mat.elems[0][3] +
		mat.elems[3][1] * mat.elems[0][2] * mat.elems[1][3] -
		mat.elems[3][1] * mat.elems[1][2] * mat.elems[0][3];
	
	coMat.elems[2][1] = -mat.elems[0][0] * mat.elems[1][2] * mat.elems[3][3] +
		mat.elems[0][0] * mat.elems[3][2] * mat.elems[1][3] +
		mat.elems[1][0] * mat.elems[0][2] * mat.elems[3][3] -
		mat.elems[1][0] * mat.elems[3][2] * mat.elems[0][3] -
		mat.elems[3][0] * mat.elems[0][2] * mat.elems[1][3] +
		mat.elems[3][0] * mat.elems[1][2] * mat.elems[0][3];
	
	coMat.elems[2][2] = mat.elems[0][0] * mat.elems[1][1] * mat.elems[3][3] -
		mat.elems[0][0] * mat.elems[3][1] * mat.elems[1][3] -
		mat.elems[1][0] * mat.elems[0][1] * mat.elems[3][3] +
		mat.elems[1][0] * mat.elems[3][1] * mat.elems[0][3] +
		mat.elems[3][0] * mat.elems[0][1] * mat.elems[1][3] -
		mat.elems[3][0] * mat.elems[1][1] * mat.elems[0][3];
	
	coMat.elems[2][3] = -mat.elems[0][0] * mat.elems[1][1] * mat.elems[3][2] +
		mat.elems[0][0] * mat.elems[3][1] * mat.elems[1][2] +
		mat.elems[1][0] * mat.elems[0][1] * mat.elems[3][2] -
		mat.elems[1][0] * mat.elems[3][1] * mat.elems[0][2] -
		mat.elems[3][0] * mat.elems[0][1] * mat.elems[1][2] +
		mat.elems[3][0] * mat.elems[1][1] * mat.elems[0][2];
	
	coMat.elems[3][0] = -mat.elems[0][1] * mat.elems[1][2] * mat.elems[2][3] +
		mat.elems[0][1] * mat.elems[2][2] * mat.elems[1][3] +
		mat.elems[1][1] * mat.elems[0][2] * mat.elems[2][3] -
		mat.elems[1][1] * mat.elems[2][2] * mat.elems[0][3] -
		mat.elems[2][1] * mat.elems[0][2] * mat.elems[1][3] +
		mat.elems[2][1] * mat.elems[1][2] * mat.elems[0][3];
	
	coMat.elems[3][1] = mat.elems[0][0] * mat.elems[1][2] * mat.elems[2][3] -
		mat.elems[0][0] * mat.elems[2][2] * mat.elems[1][3] -
		mat.elems[1][0] * mat.elems[0][2] * mat.elems[2][3] +
		mat.elems[1][0] * mat.elems[2][2] * mat.elems[0][3] +
		mat.elems[2][0] * mat.elems[0][2] * mat.elems[1][3] -
		mat.elems[2][0] * mat.elems[1][2] * mat.elems[0][3];
	
	coMat.elems[3][2] = -mat.elems[0][0] * mat.elems[1][1] * mat.elems[2][3] +
		mat.elems[0][0] * mat.elems[2][1] * mat.elems[1][3] +
		mat.elems[1][0] * mat.elems[0][1] * mat.elems[2][3] -
		mat.elems[1][0] * mat.elems[2][1] * mat.elems[0][3] -
		mat.elems[2][0] * mat.elems[0][1] * mat.elems[1][3] +
		mat.elems[2][0] * mat.elems[2][1] * mat.elems[0][3];
	
	coMat.elems[3][3] = mat.elems[0][0] * mat.elems[1][1] * mat.elems[2][2] -
		mat.elems[0][0] * mat.elems[2][1] * mat.elems[1][2] -
		mat.elems[1][0] * mat.elems[0][1] * mat.elems[2][2] +
		mat.elems[1][0] * mat.elems[2][1] * mat.elems[0][2] +
		mat.elems[2][0] * mat.elems[0][1] * mat.elems[1][2] -
		mat.elems[2][0] * mat.elems[1][1] * mat.elems[0][2];
	
	float determinant = mat.elems[0][0] * coMat.elems[0][0] +
		mat.elems[1][0] * coMat.elems[1][0] +
		mat.elems[2][0] * coMat.elems[2][0] +
		mat.elems[3][0] * coMat.elems[3][0];
	
	if (determinant == 0)
		return (result);
	
	*det = 1.0f / determinant;
	
	//for (u32 row = 0; row < 4; row++)
	//	for (u32 col = 0; col < 4; col++)
	//		result.elems[row][col] = coMat.elems[col][row] * (*det);
	
	result = transpose((*det) * coMat);
	
	return (result);
}

static inline f32 toRadians(f32 value);