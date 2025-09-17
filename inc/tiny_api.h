#ifndef __TINY_API_H_
#define __TINY_API_H_

#include <stdbool.h>
#include <stdint.h>

#define TY_GCC_CONSTRUCTOR_LEVEL_CLOCK 101
#define TY_GCC_CONSTRUCTOR_LEVEL_PERIPHERAL 201

#define NEED_IMPL extern

NEED_IMPL void ty_delay_us(uint32_t us);
extern void ty_delay_ms(uint32_t ms);

NEED_IMPL int ty_sleep(uint32_t s);

NEED_IMPL void ty_led_set(bool status);
NEED_IMPL int ty_io_putchar(char ch);
NEED_IMPL int ty_io_getchar(void);
NEED_IMPL int ty_io_enable(bool status);

extern void ty_print_malloc_info(void);

#undef NEED_IMPL

#endif