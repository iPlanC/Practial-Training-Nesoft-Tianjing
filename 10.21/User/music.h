#ifndef __MUSIC_H__
#define __MUSIC_H__

#include <stm32f10x.h>

extern unsigned int tone[];
extern unsigned int music_little_star[][2];

void sound(unsigned int k);

#endif
