#pragma once
extern double sqrt(double v);

// Vector 3
typedef struct
{
	f32 x;
	f32 y;
	f32 z;
} Vec3;

inline Vec3 v3(f32 x, f32 y, f32 z)
{
	Vec3 v;
	v.x = x;
	v.y = y;
	v.z = z;

	return v;
}

inline Vec3 v3_add(Vec3 a, Vec3 b) { return v3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec3 v3_sub(Vec3 a, Vec3 b) { return v3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 v3_inv(Vec3 vec) { return v3(-vec.x, -vec.y, -vec.z); }

inline f32 v3_length(Vec3 vec)
{
	return (f32)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

inline Vec3 v3_normalize(Vec3 vec)
{
	float len = v3_length(vec);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;

	return vec;
}

inline f32 v3_dot(const Vec3* a, const Vec3* b) { return (a->x * b->x + a->y * b->y + a->z * b->z); }
inline Vec3 v3_cross(const Vec3* a, const Vec3* b)
{
	return v3(
		a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x
	);
}

inline float v3_cross_2D(const Vec3* a, const Vec3* b)
{
	return a->x * b->y - a->y * b->x;
}

// Matrixes baby
typedef struct 
{
	float x0, x1, x2, x3;
	float y0, y1, y2, y3;
	float z0, z1, z2, z3;
	float w0, w1, w2, w3;
} Mat4;

inline Mat4 mat4(
	float x0, float x1, float x2, float x3,
	float y0, float y1, float y2, float y3,
	float z0, float z1, float z2, float z3,
	float w0, float w1, float w2, float w3
)
{
	Mat4 result;
	result.x0 = x0; result.x1 = x1; result.x2 = x2; result.x3 = x3;
	result.y0 = y0; result.y1 = y1; result.y2 = y2; result.y3 = y3;
	result.z0 = z0; result.z1 = z1; result.z2 = z2; result.z3 = z3;
	result.w0 = w0; result.w1 = w1; result.w2 = w2; result.w3 = w3;

	return result;
}

inline Mat4 mat_look_forward(Vec3 eye, Vec3 forward, Vec3 up)
{
	/*
	Vec3 axis_z = v3_normalize(v3_inv(forward));
	Vec3 axis_y = v3_normalize(v3_cross(&forward, &up));
	Vec3 axis_x = v3_cross(&axis_y, &axis_x);
	*/

	Mat4 result;
	result.x0 = 0;
	return result;
}