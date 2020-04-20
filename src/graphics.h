#pragma once
#include "types.h"
#include "vec.h"

extern u8* screen;
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 100
#define SCREEN_CHANNELS 4

void graphics_init();
void graphics_clear();

void draw_line(Vec3 from, Vec3 to);
void draw_triangle(Vec3 a, Vec3 b, Vec3 c);