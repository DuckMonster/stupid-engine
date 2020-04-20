#include "graphics.h"
#include "context.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

inline f32 min_3(f32 a, f32 b, f32 c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
inline f32 max_3(f32 a, f32 b, f32 c)
{
	return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

u8* screen = NULL;
inline u8* screen_ptr(u32 x, u32 y)
{
	return &screen[(x + y * SCREEN_WIDTH) * SCREEN_CHANNELS];
}

void graphics_init()
{
	screen = (u8*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_CHANNELS);
	graphics_clear(0xFF000000);
}

void graphics_clear()
{
	memset(screen, 0, SCREEN_WIDTH * SCREEN_HEIGHT * SCREEN_CHANNELS);
}

void draw_line(Vec3 from, Vec3 to)
{

}

void draw_triangle(Vec3 a, Vec3 b, Vec3 c)
{
	Vec3 a_b = v3_sub(b, a);
	Vec3 b_c = v3_sub(c, b);
	Vec3 c_a = v3_sub(a, c);

	u32 x_min = (u32)min_3(a.x, b.x, c.x);
	u32 x_max = (u32)max_3(a.x, b.x, c.x);
	u32 y_min = (u32)min_3(a.y, b.y, c.y);
	u32 y_max = (u32)max_3(a.y, b.y, c.y);

	for(u32 y=y_max; y>=y_min; --y)
	{
		u32* ptr = (u32*)screen_ptr(x_min, y);
		for(u32 x=x_min; x<=x_max; ++x)
		{
			u32 color = ~0;
			Vec3 pixel = v3((f32)x, (f32)y, 0.f);
			Vec3 a_p = v3_sub(pixel, a);
			Vec3 b_p = v3_sub(pixel, b);
			Vec3 c_p = v3_sub(pixel, c);

			if (v3_cross_2D(&a_b, &a_p) < 0.f)
				color = 0xFFFF0000;
			if (v3_cross_2D(&b_c, &b_p) < 0.f)
				color = 0xFFFF0000;
			if (v3_cross_2D(&c_a, &c_p) < 0.f)
				color = 0xFFFF0000;

			ptr[x - x_min] = color;
		}
	}
}

void draw_line_old(i32 x1, i32 y1, i32 x2, i32 y2)
{
	f32 delta_x = (f32)(x2 - x1);
	f32 delta_y = (f32)(y2 - y1);

	float length = (f32)sqrt(delta_x * delta_x + delta_y * delta_y);
	u32 steps = (u32)length;

	delta_x /= length;
	delta_y /= length;

	// White pixels bejbi
	u32 color = ~0;

	for(u32 i=0; i<=steps; ++i)
	{
		i32 x = (i32)(x1 + delta_x * i);
		i32 y = (i32)(y1 + delta_y * i);

		u32* pixel = (u32*)screen_ptr(x, y);
		*pixel = color;

		context_debug_pause();
	}
}