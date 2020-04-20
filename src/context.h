#pragma once
#include "types.h"

#define TIC_RATE (35)
#define TIC_FRAC (1.f / TIC_RATE)

typedef struct
{
	u32 width;
	u32 height;
} Context;

extern Context context;

void context_open(const char* title, u32 width, u32 height);
bool context_is_open();
void context_close();

void context_debug_pause();

// Returns number of tics to run
u32 context_begin_frame();
void context_end_frame();