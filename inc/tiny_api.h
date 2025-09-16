#ifndef __TINY_API_H_
#define __TINY_API_H_

#include <stdbool.h>
#include <stdint.h>

#define NEED_IMPL extern

NEED_IMPL void ty_delay_us(uint32_t us);
extern void ty_delay_ms(uint32_t ms);

NEED_IMPL int ty_sleep(uint32_t s);

extern void ty_print_malloc_info(void);

#undef NEED_IMPL

#endif