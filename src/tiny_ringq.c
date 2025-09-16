
#include "tiny_ringq.h"

void ty_ringq_init(ty_ringq_t *q, volatile uint8_t *memory, uint8_t capacity) {
  q->head = 0;
  q->tail = 0;
  q->flag = 0;
  q->capacity = capacity;
  q->memory = memory;
}

int ty_ringq_push(ty_ringq_t *q, uint8_t byte) {
  if (ty_ringq_is_full(q)) {
    return -1;
  }
  q->memory[q->tail] = byte;
  q->tail = (q->tail + 1) % q->capacity;
  if (q->tail == q->head) {
    q->flag = 1;
  }
  return 0;
}

int ty_ringq_poll(ty_ringq_t *q) {
  if (ty_ringq_is_empty(q)) {
    return -1;
  }
  int ret = (int)(q->memory[q->head]);
  q->head = (q->head + 1) % q->capacity;
  if (q->tail == q->head) {
    q->flag = 0;
  }
  return ret;
}
