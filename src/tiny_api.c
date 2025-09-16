
#include <malloc.h>
#include <stdio.h>

#include "tiny_api.h"

void ty_delay_ms(uint32_t ms) {
  while (ms > 0) {
    if (UINT32_MAX / 1000U < ms) {
      ty_delay_us(UINT32_MAX);
      ms -= UINT32_MAX / 1000U;
    } else {
      ty_delay_us(ms * 1000U);
      ms = 0;
    }
  }
}

void ty_print_malloc_info(void) {
  struct mallinfo mi = mallinfo();
  printf("Arena %d bytes; ordblks (%d, %d) bytes\n", mi.arena, mi.uordblks,
         mi.fordblks);
}