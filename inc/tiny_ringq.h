#ifndef __TINY_RINGQ_H_
#define __TINY_RINGQ_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t head;
  uint8_t tail;
  uint8_t flag;
  uint8_t capacity;
  volatile uint8_t *memory;
} ty_ringq_t;

extern void ty_ringq_init(ty_ringq_t *q, volatile uint8_t *memory,
                          uint8_t capacity);
extern int ty_ringq_push(ty_ringq_t *q, uint8_t byte);
extern int ty_ringq_poll(ty_ringq_t *q);
#define ty_ringq_is_empty(ty_ringq_ptr)                                        \
  (((ty_ringq_ptr)->head == (ty_ringq_ptr)->tail) && (ty_ringq_ptr)->flag == 0)
#define ty_ringq_is_full(ty_ringq_ptr)                                         \
  (((ty_ringq_ptr)->head == (ty_ringq_ptr)->tail) && (ty_ringq_ptr)->flag != 0)

#endif