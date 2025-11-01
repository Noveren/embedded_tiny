
#include "tiny_utils.h"

// TODO Reference https://www.cnblogs.com/h5l0/p/12219247.html
uint32_t ty_sqrt(uint32_t n) {
  uint32_t a = 0, b = 0;
  for (int i = 15; i >= 0; i--) {
    b = ((a << 1) + (1 << i)) << i;
    if (b <= n) {
      a += (1 << i);
      n -= b;
    }
  }
  return a;
}