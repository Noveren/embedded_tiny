
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

// FIXME: Unsafe for letter_shell
signed short ty_io_read(char *data, unsigned short len) {
  int ch = 0;
  for (int i = 0; i < len; i++) {
    ch = ty_io_getchar();
    if (ch < 0) {
      return -1;
    }
    data[i] = (char)ch;
  }
  return len;
}

// FIXME: Unsafe for letter_shell
signed short ty_io_write(char *data, unsigned short len) {
  signed short i = 0;
  while ((i < len) && (ty_io_putchar(data[i]) == 0)) {
    i += 1;
  }
  return i;
}

bool ty_io_receive_timeout(uint32_t ms) {
  bool ret = true;
  for (uint32_t _ms = 0; ms > 0; ms -= _ms) {
    if (!ty_io_receive_is_empty()) {
      ret = false;
      break;
    }
    _ms = (ms > 50) ? 50 : ms;
    ty_delay_ms(_ms);
  }
  return ret;
}

int ty_io_receive_flush(void) {
  while (!ty_io_receive_is_empty()) {
    ty_io_getchar();
  }
  return 0;
}

void ty_print_malloc_info(void) {
  struct mallinfo mi = mallinfo();
  printf("Arena %d bytes; ordblks (%d, %d) bytes\n", mi.arena, mi.uordblks,
         mi.fordblks);
}