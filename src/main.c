#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "context.h"
#include "graphics.h"

int main()
{
	graphics_init();

	context_open("Stupid Game", 800, 600);

	u32 tic_num = 0;

	while(context_is_open())
	{
		u32 tics_to_run = context_begin_frame();
		tic_num += tics_to_run;

		//i32 y = 50 + (i32)(sin(tic_num * TIC_FRAC) * 20.f);

		graphics_clear();

		Vec3 a = v3(-10.f, -20.f, 0.f);
		Vec3 b = v3(10.f, -20.f, 0.f);
		Vec3 c = v3(0.f, 20.f, 0.f);

		f32 angle = tic_num * TIC_FRAC * 0.8f;
		f32 sin_a = (f32)sin(angle);
		f32 cos_a = (f32)cos(angle);

		Vec3 mid = v3(50.f, 50.f, 50.f);

		a = v3_add(mid, v3(a.x * cos_a + a.y * sin_a, a.y * cos_a - a.x * sin_a, 0.f));
		b = v3_add(mid, v3(b.x * cos_a + b.y * sin_a, b.y * cos_a - b.x * sin_a, 0.f));
		c = v3_add(mid, v3(c.x * cos_a + c.y * sin_a, c.y * cos_a - c.x * sin_a, 0.f));
		draw_triangle(a, b, c);

		context_end_frame();
	}
	return 0;
}