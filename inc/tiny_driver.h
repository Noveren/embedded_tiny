#ifndef __TINY_DRIVER_H_
#define __TINY_DRIVER_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef int (*ty_open_fn_t)(const char *file, int flags, int mode);
typedef int (*ty_close_fn_t)();
typedef int (*ty_write_fn_t)(const void *buf, int len);
typedef int (*ty_read_fn_t)(void *buf, int len);

typedef struct {
  const char *name;
  ty_open_fn_t open_fn;
  ty_close_fn_t close_fn;
  ty_write_fn_t write_fn;
  ty_read_fn_t read_fn;
} ty_device_t;

typedef struct {
  bool is_opened;
} ty_status_t;

typedef struct {
  const ty_device_t **device;
  uint8_t device_num;
  ty_status_t *status;
} ty_driver_t;

extern ty_driver_t *ty_driver_init(const ty_device_t *device[]);
extern int ty_driver_open(ty_driver_t *dri, const char *name, int flags,
                          int mode);
extern int ty_driver_close(ty_driver_t *dri, int fd);
extern int ty_driver_write(ty_driver_t *dri, int fd, const void *buf, int len);
extern int ty_driver_read(ty_driver_t *dri, int fd, void *buf, int len);

#define TY_DRIVER_REGISTER(__name)                                             \
  extern int __name##_open(const char *file, int flags, int mode);             \
  extern int __name##_close();                                                 \
  extern int __name##_read(void *buf, int len);                                \
  extern int __name##_write(const void *buf, int len);                         \
  const ty_device_t __name = {                                                 \
      .name = #__name,                                                         \
      .open_fn = __name##_open,                                                \
      .close_fn = __name##_close,                                              \
      .read_fn = __name##_read,                                                \
      .write_fn = __name##_write,                                              \
  }

#endif