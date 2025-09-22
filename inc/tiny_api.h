#ifndef __TINY_API_H_
#define __TINY_API_H_

#include <stdbool.h>
#include <stdint.h>

// FIXME 设置相同优先级时 ? 可能发生冲突
#define TY_GCC_CONSTRUCTOR_LEVEL_CLOCK 101
#define TY_GCC_CONSTRUCTOR_LEVEL_PERIPHERAL 201

#define NEED_IMPL extern

NEED_IMPL void ty_delay_us(uint32_t us);
extern void ty_delay_ms(uint32_t ms);

NEED_IMPL int ty_sleep(uint32_t s);

NEED_IMPL int ty_io_enable(bool status);
NEED_IMPL int ty_io_putchar(char ch);
NEED_IMPL int ty_io_getchar(void);
NEED_IMPL bool ty_io_receive_is_empty(void);
extern bool ty_io_receive_timeout(uint32_t ms);
extern int ty_io_receive_flush(void);

NEED_IMPL int ty_spi_enable(bool status);
NEED_IMPL int ty_spi_select(bool status);
NEED_IMPL uint8_t ty_spi_access(uint8_t byte);
NEED_IMPL void ty_spi_write(uint8_t byte);

NEED_IMPL const uint8_t ty_adc_CHANNEL_LENGTH;
NEED_IMPL int ty_adc_enable(bool status);
NEED_IMPL const uint16_t *ty_adc_get(void);

extern void ty_print_malloc_info(void);

#undef NEED_IMPL

#endif